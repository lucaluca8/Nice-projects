import { Component, OnInit } from '@angular/core';
import { MatSnackBar } from '@angular/material/snack-bar';
import { AnimeServService } from '../anime-serv.service';
import { Anime } from '../animeClass';

@Component({
  selector: 'app-manage-anime',
  templateUrl: './manage-anime.component.html',
  styleUrls: ['./manage-anime.component.scss']
})
export class ManageAnimeComponent implements OnInit {

  anime:Anime = new Anime()
  public animes=<any>[]
  id:number=null

  constructor(private animeserv:AnimeServService,private snackBar:MatSnackBar) { }

  ngOnInit(): void {
    this.animeserv.getAnimes().subscribe(data=>{
      this.animes=data;
    });
  }


  addAnime(){
    if( this.anime.name != "" && this.anime.image != "" && this.anime.description != "" && this.anime.rating !="" && this.anime.genre !=""&&this.anime.studio!="")
      {
        this.animeserv.addAnime(this.anime).subscribe(data=>{
          console.log(data);
        });
        this.snackBar.open("Anime added :D","",{duration: 1000});
      }
      else
      {
        this.snackBar.open("You left at least one field empty","",{duration: 1000});
      }
    
  }

  getAnimeId():void {
    this.animes.forEach(data=>{
      if(data.name === this.anime.name) {
        this.anime=data;
        this.id=data.id;     
    }
    });
  }

  getAnimeInfo(){
    if(this.anime.name !="")
    {
      this.getAnimeId();
    }
  }

  changeAnimeInfo():void{
    
    if(this.anime.name !="")
    {
      if(this.anime.image != "" && this.anime.description != "" && this.anime.rating !="" && this.anime.genre !=""&&this.anime.studio!="")
      {
          this.animeserv.updateAnime(this.id,this.anime).subscribe(data=>{
        });
        this.snackBar.open("Updated anime info :)","",{duration: 1000});
      }
      else
      {
        this.snackBar.open("You need to get the anime info first","",{duration: 1000});
      }

    }
    else{
      this.snackBar.open("You need to introduce an anime name first","",{duration: 1000});
    }
  }

  deleteAnime():void{
    if(this.anime.name !="")
    {
      if(this.anime.image != "" && this.anime.description != "" && this.anime.rating !="" && this.anime.genre !=""&&this.anime.studio!="")
      {
         this.animeserv.deleteAnime(this.id);
         this.snackBar.open("Anime deleted :(","",{duration: 1000});
      }
      else
      {
        this.snackBar.open("You need to get the anime info first","",{duration: 1000});
      }

    }
    else{
      this.snackBar.open("You need to introduce an anime name first","",{duration: 1000});
    }
  }


}

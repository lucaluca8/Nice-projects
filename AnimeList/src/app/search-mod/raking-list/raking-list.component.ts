import { Component, OnInit } from '@angular/core';
import { MatTableDataSource } from '@angular/material/table';
import { TableService } from '../table.service';
import { searchValidator } from './validator';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';


@Component({
  selector: 'app-raking-list',
  templateUrl: './raking-list.component.html',
  styleUrls: ['./raking-list.component.scss']
})
export class RakingListComponent implements OnInit {
displayedColumns: string[] = ['id', 'name', 'rating', 'nr_episodes', 'studio', 'genre'];
public  animeList=<any>[]

inputSb:string = "";  
searchResult! : any;
searchedId:any;
check:boolean = false;


validatorForm:FormGroup;
  dataSource: MatTableDataSource<unknown>;

constructor(private tableService: TableService, public fb:FormBuilder,private route:Router) {}

ngOnInit(): void {
  this.validatorForm=this.fb.group(
    {
    search: ['',[searchValidator]]
    }
  );
  this.animeList = this.tableService.getAnimes();
  
  this.tableService.getAnimes().subscribe(data=>{
    this.animeList = data;
    this.dataSource = new MatTableDataSource(this.animeList);
  });
  
  
}

sortByName()
{
  this.animeList = this.animeList.sort((a, b) => (a.name > b.name ? 1 : -1));
  this.dataSource = new MatTableDataSource(this.animeList);
}
sortByRating()
{
  this.animeList = this.animeList.sort((a, b) => (a.rating < b.rating ? 1 : -1));
  this.dataSource = new MatTableDataSource(this.animeList);
}
sortByPopularity()
{
  this.animeList = this.animeList.sort((a, b) => (a.id > b.id ? 1 : -1));
  this.dataSource = new MatTableDataSource(this.animeList);
}
sortByStudio()
{
  this.animeList = this.animeList.sort((a, b) => (a.studio > b.studio ? 1 : -1));
  this.dataSource = new MatTableDataSource(this.animeList);
}



get search(){
  return this.validatorForm.get('search');
}

searchFunction(){
  console.log("binded");
  if(this.inputSb !="")
  {
    
    this.animeList.forEach(data=>{
      if(data.name==this.inputSb) {
      this.searchResult=data;
      if(this.check === false)
      this.check = true;
      this.searchedId=this.searchResult.id;
      this.route.navigate([`/search/${this.searchedId}`]);
      
    }})
      
    if(this.check === false)
    {
      alert("Anime not found");
    }
  }
  else{
    alert("Search box cannot be empty");
  }
}




}

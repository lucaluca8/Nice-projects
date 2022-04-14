import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { TableService } from '../table.service';

@Component({
  selector: 'app-anime',
  templateUrl: './anime.component.html',
  styleUrls: ['./anime.component.scss']
})
export class AnimeComponent implements OnInit {

  anime:any;
  name:any;
  constructor(private tableService: TableService,
    private route : ActivatedRoute) { }

  ngOnInit(): void {
    this.route.params.subscribe(params=>{
      this.name = params['name'];
      this.tableService.getAnimeByName(this.name).subscribe(data =>this.anime = data);   
    });    
   }
}

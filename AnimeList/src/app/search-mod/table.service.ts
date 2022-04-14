import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Anime } from '../manage/animeClass';

@Injectable({
  providedIn: 'root'
})
export class TableService {

  path:string = 'http://localhost:3000/anime'

  constructor(private http:HttpClient) {}
 
  getAnimes(){
    return this.http.get(this.path);
  }
  getAnimeByName(name:string){
    return this.http.get(`http://localhost:3000/anime/${name}`);
      
  }
}

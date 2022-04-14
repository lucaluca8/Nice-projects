import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Anime } from './animeClass';


@Injectable({
  providedIn: 'root'
})
export class AnimeServService {

  path:string = 'http://localhost:3000/anime'
  constructor(private http:HttpClient) { }

  getAnimes(){
    return this.http.get(this.path);
  }

  addAnime(anime:Anime):Observable<any>
  {
    const headers = { 'content-type': 'application/json'}  
    const body=JSON.stringify(anime);
    console.log("This is the body:",body)
    return this.http.post(this.path , body,{'headers':headers})
  }

  updateAnime(id:number,anime:Anime)
  {
    var endPoint = `/${id}`;
    console.log(this.path+endPoint)
    return this.http.put(this.path + endPoint, anime);
  }

  deleteAnime(id:number) {
    var endPoint = `/${id}`;
    this.http.delete(this.path + endPoint).subscribe(data => {
      console.log(data);
    });
  }
}

import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { User } from './registerClass';

@Injectable({
  providedIn: 'root'
})
export class HomeServiceService {

  path:string = 'http://localhost:3000/accounts'

  constructor(private http:HttpClient) {}
 
  getAccounts(){
    return this.http.get(this.path);
  }
  addAccount(user:User):Observable<any>
  {
    const headers = { 'content-type': 'application/json'}  
    const body=JSON.stringify(user);
    console.log("This is the body:",body)
    return this.http.post(this.path , body,{'headers':headers})
  }

}

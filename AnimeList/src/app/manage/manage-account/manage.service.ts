import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { User } from '../../home-mod/registerClass';

@Injectable({
  providedIn: 'root'
})
export class ManageService {


  path:string = `http://localhost:3000/accounts`;
  constructor(private http:HttpClient) { }

  getAccounts(){
    return this.http.get(this.path);
  }
  updateAccount(id:number,user:User)
  {
    var endPoint = `/${id}`;
    console.log(this.path+endPoint)
    return this.http.put(this.path + endPoint, user);
  }
   deleteAccount(id:number) {
    var endPoint = `/${id}`;
    this.http.delete(this.path + endPoint).subscribe(data => {
      console.log(data);
    });
  }
}

import { Component, OnInit } from '@angular/core';
import { SimpleSnackBar } from '@angular/material/snack-bar';
import { Router } from '@angular/router';
import { HomeServiceService } from '../home-service.service';
import { MatSnackBar } from "@angular/material/snack-bar";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent implements OnInit {

  username: string = "";
  password: string = "";
  public  accounts=<any>[]
  constructor(private homeService:HomeServiceService,private route:Router,private snackBar:MatSnackBar) { }

  ngOnInit(): void {
      this.homeService.getAccounts().subscribe(data=>{
        this.accounts=data;
      });
  }
  logInPressed(){
    var check = false
    console.log(this.username);
    console.log(this.password);
    if(this.username !="" && this.password !="")
    {
      
      this.accounts.forEach(data=>{
        if(data.username === this.username && data.password === this.password) {
          check = true;
        this.route.navigate([`/search`]);
        this.snackBar.open("Log In successfully","",{duration: 1000});
      }
      console.log(data.username)
    })
        
      if(check === false)
      {
        this.snackBar.open("Account not found","",{duration: 1000});
      }
    }
    else{
      this.snackBar.open("Cannot leave empty fields","",{duration: 1000});
    }
  }


}

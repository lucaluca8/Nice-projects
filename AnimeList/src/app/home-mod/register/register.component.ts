import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { MatSnackBar } from '@angular/material/snack-bar';
import { Router } from '@angular/router';
import { HomeServiceService } from '../home-service.service';
import { User } from '../registerClass';
import { nameValidator,specialCharactersValidator,emailValidator, 
  passwordContentsValidator} from '../validators/name.validator';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.scss']
})
export class RegisterComponent implements OnInit {

  user:User = new User();

  constructor(public fb:FormBuilder,private homeService:HomeServiceService,private route:Router,private snackBar:MatSnackBar) { }

  validatorForm:FormGroup;
  public  accounts=<any>[]

  ngOnInit(): void {
    this.validatorForm=this.fb.group(
      {
      name: ['',[Validators.required,nameValidator,specialCharactersValidator]],
      username:['',[Validators.required,nameValidator,specialCharactersValidator]],
      email:['',[Validators.required,emailValidator]],
      password:['',[Validators.required,passwordContentsValidator]],
      security: ['', [Validators.required,nameValidator,specialCharactersValidator]],  
      }
  );
  this.accounts = this.homeService.getAccounts();
}

  get name() {
    return this.validatorForm.get('name');
  }
  get username() {
    return this.validatorForm.get('username');
  }
  get email(){
    return this.validatorForm.get('email');
  }
  get password(){
    return this.validatorForm.get('password');
  }
  get security() {
    return this.validatorForm.get('security');
  }

  registerButton(){
    const message =`Registration succsefully`;
    if(this.validatorForm.get('name').value==="" || this.validatorForm.get('username').value==="" || 
      this.validatorForm.get('email').value==="" ||  this.validatorForm.get('password').value==="")
      //alert("You cannot leave empty fields");
      this.snackBar.open("You cannot leave empty fields","",{duration: 1000});
    else if(!this.validatorForm.get('password').valid || !this.validatorForm.get('username').valid
    ||!this.validatorForm.get('name').valid || !this.validatorForm.get('email').valid)
        //alert("Something went wrong. Check the fields for errors")
        this.snackBar.open("Something went wrong. Check the fields for errors","",{duration: 1000});
    else
      {
        this.homeService.addAccount(this.user).subscribe(data=>{
          console.log(data);
        })
        this.homeService.getAccounts().subscribe(data=>{
          console.log(data);
        })
        this.route.navigate([`/login/`]);
      }
    console.log(this.user.name);
    console.log(this.user.username);
    console.log(this.user.email);
    console.log(this.user.password);
  }
  
  }



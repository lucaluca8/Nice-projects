import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ManageAccountComponent } from './manage/manage-account/manage-account.component';
import { SupportComponent } from './support/support.component';

const routes: Routes = [
  {
    path:'search',
    loadChildren:()=>import('./search-mod/search-mod.module').then((module)=>(module).SearchModModule)
  },
  {
    path:'support',
    component:SupportComponent
  },
  { 
    path:'',
    loadChildren:()=>import('./home-mod/home-mod.module').then((module)=>(module).HomeModModule)
  }

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }

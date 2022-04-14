import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ManageAccountComponent } from './manage-account/manage-account.component';
import { ManageAnimeComponent } from './manage-anime/manage-anime.component';

const routes: Routes = [
  {
    path:'account',
    component:ManageAccountComponent

  },
  {
    path:'anime',
    component:ManageAnimeComponent
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class ManageRoutingModule { }

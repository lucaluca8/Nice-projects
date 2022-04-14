import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ManageAccountComponent } from '../manage/manage-account/manage-account.component';
import { ManageAnimeComponent } from '../manage/manage-anime/manage-anime.component';
import { AnimeComponent } from './anime/anime.component';
import { RakingListComponent } from './raking-list/raking-list.component';

const routes: Routes = [
  {
    path:':name',
    component:AnimeComponent
  },
  {
    path:':manage',
    loadChildren:()=>import('../manage/manage.module').then((module)=>(module).ManageModule)
  },
  {
    path:'',
    component:RakingListComponent
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class SearchModRoutingModule { }

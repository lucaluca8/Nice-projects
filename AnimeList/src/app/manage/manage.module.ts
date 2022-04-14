import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ManageRoutingModule } from './manage-routing.module';
import { ManageAnimeComponent } from './manage-anime/manage-anime.component';
import { FormsModule } from '@angular/forms';


@NgModule({
  declarations: [
    ManageAnimeComponent
  ],
  imports: [
    CommonModule,
    ManageRoutingModule,
    FormsModule
  ]
})
export class ManageModule { }

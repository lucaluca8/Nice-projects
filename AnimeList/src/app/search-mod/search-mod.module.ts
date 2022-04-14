import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MatTableModule } from '@angular/material/table';
import { SearchModRoutingModule } from './search-mod-routing.module';
import { RakingListComponent } from './raking-list/raking-list.component';
import { ReactiveFormsModule } from '@angular/forms';
import { AnimeComponent } from './anime/anime.component';

@NgModule({
  declarations: [
    RakingListComponent,
    AnimeComponent
  ],
  imports: [
    CommonModule,
    SearchModRoutingModule,
    MatTableModule,
    ReactiveFormsModule
  ]
})
export class SearchModModule { }

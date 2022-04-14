import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RakingListComponent } from './raking-list.component';

describe('RakingListComponent', () => {
  let component: RakingListComponent;
  let fixture: ComponentFixture<RakingListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ RakingListComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(RakingListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

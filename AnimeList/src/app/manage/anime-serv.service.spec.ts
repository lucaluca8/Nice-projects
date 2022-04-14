import { TestBed } from '@angular/core/testing';

import { AnimeServService } from './anime-serv.service';

describe('AnimeServService', () => {
  let service: AnimeServService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(AnimeServService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});

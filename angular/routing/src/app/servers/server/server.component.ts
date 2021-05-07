import {Component, OnDestroy, OnInit} from '@angular/core';

import { ServersService } from '../servers.service';
import {ActivatedRoute, Data, Params, Router} from '@angular/router';
import {Subscription} from 'rxjs';

@Component({
  selector: 'app-server',
  templateUrl: './server.component.html',
  styleUrls: ['./server.component.css']
})
export class ServerComponent implements OnInit, OnDestroy {
  server: {id: number, name: string, status: string};
  paramsSubscription: Subscription;

  constructor(private serversService: ServersService,
              private route: ActivatedRoute, private router: Router) { }

  ngOnInit(): void {
    // this.server = this.serversService.getServer(+this.route.snapshot.params.id); // + at the beginning converts param to int
    //
    // this.paramsSubscription = this.route.params.subscribe(
    //     (params: Params) => {
    //       this.server = this.serversService.getServer(+params.id);
    //     }
    // );
    this.route.data.subscribe(
        (data: Data) => {
          this.server = data.server;
        }
    );
  }

  ngOnDestroy(): void {
    if (this.paramsSubscription !== undefined) {
      this.paramsSubscription.unsubscribe();
    }
  }

  onEdit(): void {
    this.router.navigate(['edit'], {relativeTo: this.route, queryParamsHandling: 'preserve'});
  }
}

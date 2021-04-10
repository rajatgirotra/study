import { Component, OnInit } from '@angular/core';

@Component({
  // selector: 'app-servers',
  // selector: '[app-servers]', // selector is not an element now, it is an html tag attribute
  selector: '.app-servers', // selector is not an element now, it is a class
  templateUrl: './servers.component.html',
  // template: `
  //   <app-server></app-server>
  //   <app-server></app-server>
  //   <app-server></app-server>
  // `,
  // styleUrls: ['./servers.component.css'],
  styles: [`
    `]
})
export class ServersComponent implements OnInit {
  allowNewServer = false;
  serverCreateStatus = 'No new server created!';
  serverName = 'testserver';
  serverCreated = false;
  servers = ['Testserver', 'Testserver 2'];
  constructor() {
    setTimeout(() => {
      this.allowNewServer = true;
    }, 2000);
  }

  ngOnInit(): void {
  }

  // tslint:disable-next-line:typedef
  onCreateNewServer() {
    this.serverCreated = true;
    this.servers.push(this.serverName);
    this.serverCreateStatus = 'New Server created! Server name is ' + this.serverName ;
  }

  // tslint:disable-next-line:typedef
  onGetServerName(event: any) {
    this.serverName = (event.target as HTMLInputElement).value;
  }
}

/**
 * instead of templateUrl, we can also use the template property in the decorator. in then we can add inline HTML.
 * we can do this when our HTML is very simple and straight forward. Note that we use back ticks for putting multi-line html
 *
 * Infact we can do that with styleUrls also. instead of styleUrls just use styles.
 */

/**
 * () => {} is just like a javascript function() {} except that it can access the this object i guess. will find out more diff later.
 */

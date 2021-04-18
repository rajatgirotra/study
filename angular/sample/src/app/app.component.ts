import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  serverElements = [{type: 'server', name: 'testserver', content: 'This is just a test'}];

  // tslint:disable-next-line:typedef
  onServerAdded(serverData: {serverName: string, serverContent: string}) {
    this.serverElements.push({
      type: 'server',
      name: serverData.serverName,
      content: serverData.serverContent
    });
  }

  // tslint:disable-next-line:typedef
  onBlueprintAdded(blueprintData: {serverName: string, serverContent: string}) {
    this.serverElements.push({
      type: 'blueprint',
      name: blueprintData.serverName,
      content: blueprintData.serverContent
    });
  }

  // tslint:disable-next-line:typedef
  onNameChanged() {
      this.serverElements[0].name = 'Changed!';
  }

  onDestroyComponent() {
    this.serverElements.splice(0, 1);
  }
}

/**
 * How to communicate between components. Remember property and event binding??
 * Property and Event binding can be used to communicate between your TS and your HTML defined properties and events.
 * similarly property and event binding can be used to communicate between TS and angular directives. Remember [ngStyle] and [ngClass]
 * Similarly property and event binding can also be used to communicate between angular components using custom properties and events.
 *
 * We will see that here.
 *
 * What we will go is that we will create a property (member variable) in the ServerElement class. We can call it anything.
 * this will decorated with @Input() decorator. then we will bind this property inside the app.component.html
 * Lets assume we name this property xyz. We will bind it like [xyz]="TSExpression".
 * So whatever will be the TSExpression will be the value of xyz property.
 */

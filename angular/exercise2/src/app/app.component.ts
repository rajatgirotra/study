import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'exercise2';
  // evenEvents: number[] = [];
  // oddEvents: number[] = [];
  events: number[] = [];

  onGameEvent(gameEvent: {eventNumber: number}) {
    console.log('app component: ', gameEvent.eventNumber);
    // if (gameEvent.eventNumber % 2 === 0) {
    //   this.evenEvents.push(gameEvent.eventNumber);
    // }
    // else {
    //   this.oddEvents.push(gameEvent.eventNumber);
    // }
    this.events.push(gameEvent.eventNumber);
  }
}

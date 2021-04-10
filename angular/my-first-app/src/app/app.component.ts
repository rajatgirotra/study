import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  // styleUrls: ['./app.component.css'], // its an array so you can add multiple style sheets
  styles: [`
    h1 {
      color: dodgerblue;
    }
    `]
})
export class AppComponent {
  title = 'my-first-app';
}

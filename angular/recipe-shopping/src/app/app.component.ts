import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'recipe-shopping';
  showRecipes = true;
  onHeaderSelect(event: boolean) {
    this.showRecipes = event;
  }
}

import {Component, ViewChild} from '@angular/core';
import {NgForm} from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  /**
   * can also use @ViewChild instead of passing NgForm argument to onSubmit.
   */
  @ViewChild('f') form: NgForm;

  defaultQuestion = 'pet';
  defaultEmail = 'rajat.girotraGgmail.com';

  suggestUserName() {
    const suggestedName = 'Superuser';
  }

  // onSubmit(f: HTMLFormElement): void {
  // onSubmit(f: NgForm): void {
  //   console.log(f);
  // }

  onSubmit(): void {
    console.log(this.form);
  }

}

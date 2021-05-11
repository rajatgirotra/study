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
  defaultEmail = 'rajat.girotra@gmail.com';
  answer = '';

  suggestUserName() {
    const suggestedName = 'Superuser';
    // this.form.setValue({
    //   // must set all fields of the form here
    //   userData: {
    //     username: suggestedName,
    //     email: ''
    //   },
    //   questionAnswer: '',
    //   secret: ''
    // });

    // the other way is patchValue
    this.form.form.patchValue({
      userData: {
        username: suggestedName
      }
    });
  }

  // onSubmit(f: HTMLFormElement): void {
  // onSubmit(f: NgForm): void {
  //   console.log(f);
  // }

  onSubmit(): void {
    console.log(this.form);
  }

}

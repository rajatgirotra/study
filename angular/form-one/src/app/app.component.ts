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
  genders = ['male', 'female'];

  user = { username: '', email: '', secretQuestion: '', gender: '', answer: ''};
  submitted = false;

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
    this.submitted = true;
    this.user.username = this.form.value.userData.username;
    this.user.email = this.form.value.userData.email;
    this.user.secretQuestion = this.form.value.secret;
    this.user.answer = this.form.value.questionAnswer;
    this.user.gender = this.form.value.gender;

    this.form.reset();
  }
}

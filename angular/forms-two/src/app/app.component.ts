import {Component, OnInit} from '@angular/core';
import {FormControl, FormGroup} from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  genders = ['male', 'female'];

  /**
   * this is the javascript object which will contain the form control values
   */
  signupForm: FormGroup;

  ngOnInit(): void {
    this.signupForm = new FormGroup({
      'username': new FormControl(null), // creating a new FormControl with default as null
      'email': new FormControl(null),
      'gender': new FormControl('male')
    });
  }
}

/**
 * the other way as opposed to template driven approach is reactive approach. in this approach we create the form object ourselves in TypeScript
 * instead of angular providing us. We also need to import ReactiveFormsModule instead of just FormsModule.
 */

import {Component, OnInit} from '@angular/core';
import {AbstractControl, FormArray, FormControl, FormGroup, Validators} from '@angular/forms';
import {Observable} from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  genders = ['male', 'female'];
  illegalUserNames = ['Chris', 'Anna'];

  /**
   * this is the javascript object which will contain the form control values
   */
  signupForm: FormGroup;

  ngOnInit(): void {
    this.signupForm = new FormGroup({
      'userData': new FormGroup({
        'username': new FormControl(null, [Validators.required, this.forbiddenUserNames.bind(this)]), // creating a new FormControl with default as null
        'email': new FormControl(null, [Validators.required, Validators.email], this.forbiddenEmails),
      }),
      'gender': new FormControl('male'),
      'hobbies': new FormArray([])
    });
    /**
     * although you have created a formGroup yourself here, we also have a <form> element in the the corresponding html. Also when angular sees the <form> element in template file
     * it automatically creates a form for us. So we need to do two things now.
     * 1) tell angular to not create a form for us. This is done by using a [formGroup] property binding.
     * 2) Tell angular which form controls in the form should match to which attributes in your signupForm. this is done using formControlName property binding.
     *
     * Also note that since username and email are inside a formGroup of their own, we need the template to be also symmetrical and have formGroupName="userData"
     */

    /**
     * There are two nice Observables that you can subscribe to. Both on the complete form or on the individual form control. These are called
     * valueChanges and statusChanges.
     */
    // this.signupForm.valueChanges.subscribe(
    //     (value) => {
    //       console.log(value); // will log the complete form object.
    //     }
    // );

    // this.signupForm.get('userData.email').statusChanges.subscribe(
    //     (status) => {
    //       console.log(status); // will log the complete form object.
    //     }
    // );
  }

  onSubmit(): void {
    /**
     * no need to get the form anymore from the template as we created on our own.
     */
    console.log(this.signupForm);

  }

  getHobbyControls(): AbstractControl[] {
    return (this.signupForm.get('hobbies') as FormArray).controls;
  }

  onAddHobby(): void {
    const control = new FormControl(null, [Validators.required]);
    (this.signupForm.get('hobbies') as FormArray).push(control);
  }

  forbiddenUserNames(control: FormControl): {[s: string]: boolean} {
    if (this.illegalUserNames.indexOf(control.value) !== -1) {
      return {nameIsForbidden: true};
    }
    return null;
  }

  forbiddenEmails(control: FormControl): Promise<any> | Observable<any> {
    const promise = new Promise((resolve, reject) => {
      setTimeout(() => {
        if (control.value === 'test@test.com') {
          resolve({invalidEmail: true});
        } else {
          resolve(null);
        }
      }, 1500);
    });
    return promise;
  }
}

/**
 * the other way as opposed to template driven approach is reactive approach. in this approach we create the form object ourselves in TypeScript
 * instead of angular providing us. We also need to import ReactiveFormsModule instead of just FormsModule.
 *
 * Just like for form you add formGroup, for nested controls you use formGroupName, for form arrays we have to use formArrayName
 */

/**
 * FormArray is an array of FormControls. you can add dynamically add more form controls at run-time. Here we add a FormArray to let user specify
 * one or more hobbies.
 */

/**
 * adding your own form control validator is trivial. All you need to do is create a function which take a form control parameter.
 * if validation is successful, must return null. If unsuccessful, must return a javascript object of type {[s: string]: boolean}
 *
 * the reason why we need this.forbiddenUserNames.bind(this) is because the validator wont be called on the this object. It's called by angular
 * and it doesnt have the this reference. so we need to bind it explicitly. similar to bind in c++
 *
 * The validation failure and reported in the error property of the control. You can see that in the developer tools window in the form object.
 * also we can tailor the error/warning message in the span element based on the error code we get.
 *
 * Similarly we can have async validators which is passed as third argument to FormControl() ctor. These validator return a promise or observable
 *
 * also patchValue() and setValue() and reset() are also available. They are trivial just like in the template driver approach.
 */

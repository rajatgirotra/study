import {Component, OnDestroy, OnInit} from '@angular/core';
import {NgForm} from '@angular/forms';
import {AuthResponseData, AuthService} from './auth.service';
import {Observable} from 'rxjs';


/**
 * Authentication in Angular --> In a normal HTTP application, a user is authenticated by some mechanism like UserName/Password, DirectLink to login
 * through email (without a password), or through SSO, or through OpenID (like through Google, Facebook, AWS account) etc. In those cases, if authentication
 * is successfull, the server returns a SessionID and all communication then takes place on that session.
 *
 * In Angular however, authentication is handled differently. This is because the back end is mostly stateless, like a JSON REST API. So in this case,
 * Angular back-end should returns something called as a AuthToken. This AuthToken is created by back-end based on some complex algo and has an expiry.
 * It is encoded (not encrypted), so client/browser/user can still modify it, but then the server wont be able to identify a tampered token so the
 * request will be rejected.
 */


@Component({
    selector: 'app-auth',
    templateUrl: './auth.component.html'
})
export class AuthComponent implements  OnInit, OnDestroy {
    isLoginMode = false;
    isLoading = false;
    error: string = null;

    constructor(private authService: AuthService) {
    }
    ngOnDestroy(): void {
    }

    ngOnInit(): void {
    }

    onSubmit(authForm: NgForm) {
        if (!authForm.valid) {
            return;
        }

        /**
         * the reason we copy email and password in separate variables is because we call authForm.reset() which will reset the values.
         * so we cant call signUp(authForm.value.email, authForm.value.password) as those values will be lost.
         */
        let authObs: Observable<AuthResponseData>;

        const email = authForm.value.email;
        const password = authForm.value.password;
        this.isLoading = true;
        if (this.isLoginMode) {
            authObs = this.authService.login(email, password);
        }
        else {
            authObs = this.authService.signUp(email, password);
        }

        authObs.subscribe(
            responseData => {
                console.log(responseData);
                this.error = null;
                this.isLoading = false;
            },
            errorMessage => {
                console.log(errorMessage);
                this.error = errorMessage;
                this.isLoading = false;
            }
        );
        authForm.reset();
    }

    onSwitchMode(): void {
        this.isLoginMode = !this.isLoginMode;
    }
}

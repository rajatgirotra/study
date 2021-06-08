import {Component, ComponentFactoryResolver, OnDestroy, OnInit, ViewChild} from '@angular/core';
import {NgForm} from '@angular/forms';
import {AuthResponseData, AuthService} from './auth.service';
import {Observable, Subscription} from 'rxjs';
import {User} from './user.model';
import {Router} from '@angular/router';
import {AlertComponent} from '../shared/alert/alert.component';
import {AlertDirective} from '../shared/alert/alert.directive';
import {Store} from '@ngrx/store';
import * as fromApp from '../store/app.reducer';
import {LoginStart, SignupStart} from './store/auth.actions';

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
    // userObs = new Observable<User>();
    user: User = null;
    private closeSub: Subscription;

    // ViewChild will fetch the first occurrence of AlertDirective in the html.
    @ViewChild(AlertDirective, {static: false}) alertHost: AlertDirective;

    constructor(private authService: AuthService, private router: Router,
                private componentFactoryResolver: ComponentFactoryResolver,
                private store: Store<fromApp.AppState>) {
    }

    ngOnDestroy(): void {
        if (this.closeSub) {
            this.closeSub.unsubscribe();
        }
    }

    doCloseAlert(): void {
        this.error = null;
    }

    ngOnInit(): void {
        // this.userObs.subscribe(
        //   user => {
        //       this.user = user;
        //   }
        // );
        this.store.select('auth').subscribe(authState => {
            this.isLoading = authState.isLoading;
            this.error = authState.authError;
            if (this.error) {
               this.showErrorAlert(this.error);
            }
        });
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
        // this.isLoading = true;
        if (this.isLoginMode) {
            // authObs = this.authService.login(email, password);
            this.store.dispatch(new LoginStart({email, password}) );
        }
        else {
            // authObs = this.authService.signUp(email, password);
            this.store.dispatch(new SignupStart({email, password}));
        }

        // authObs.subscribe(
        //     responseData => {
        //         console.log(responseData);
        //         this.error = null;
        //         this.isLoading = false;
        //         this.router.navigate(['/recipes']);
        //     },
        //     errorMessage => {
        //         console.log(errorMessage);
        //         this.error = errorMessage;
        //         this.showErrorAlert(errorMessage);
        //         this.isLoading = false;
        //     }
        // );
        authForm.reset();
    }

    showErrorAlert(errorMessage: string) {
        /**
         * though creating a component like below is valid TS code, its not valid Angular code. You cannot add new component just by instantiating
         * it. its because angular does a lot of wiring when creating a new Component for you. like registering for DOM change detection etc.
         * So what we need to do really is create a ComponentFactory for this component, and then create a component object from that component factory.
         */
        // const alertComp = new AlertComponent();
        const componentFactory = this.componentFactoryResolver.resolveComponentFactory(AlertComponent);

        /**
         * now to inject the component, we need a place in the DOM where to add it. right now we dont have that.
         * For that we need a ViewContainerRef.
         * A ViewContainerRef represents a container where one or more views can be attached to a component.
         */
        const hostViewContainerRef = this.alertHost.viewContainerRef;
        hostViewContainerRef.clear(); // clear all angular components that have been rendered.
        const alertCompRef = hostViewContainerRef.createComponent(componentFactory);

        // how to now pass message and listen to events from my component
        alertCompRef.instance.message = errorMessage;
        this.closeSub = alertCompRef.instance.closeError.subscribe(
            () => {
                this.closeSub.unsubscribe();
                hostViewContainerRef.clear();
            }
        );
    }

    onSwitchMode(): void {
        this.isLoginMode = !this.isLoginMode;
    }
}

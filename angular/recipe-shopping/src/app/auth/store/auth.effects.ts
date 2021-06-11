/**
 * what are side-effects in ngrx? side-effects are part of the code-base around the place you dispatch actions. this code is equally important
 * but it does not read or modify our AppState. that's why we call it side-effects. Also since this code does not interact with AppState, we
 * can not make it part of our reducer functions. Example like when you login a user in the authService, you send an HTTP request and when you
 * get a reply you create a state for the user in the AppState. now sending the HTTP request is something we cannot do in the reducer.
 * similarly setting userData in the localStorage (browser localStorage) in auth Service is also a side-effect.
 *
 * @ngrx/effects provides a way to handle these side-effects. first "npm install --save @ngrx/effects" and restart "ng serve"
 * then in this file import Actions from @ngrx/effects.
 * Actions class is a big observable that is called whenever some action is dispatched to your store.
 * So when an action is dispatched you can do anything but change the AppState
 */

import {Actions, Effect, ofType} from '@ngrx/effects';
import * as AuthActions from './auth.actions';
import {catchError, map, switchAll, switchMap, tap} from 'rxjs/operators';
import {environment} from '../../../environments/environment';
import {HttpClient} from '@angular/common/http';
import {of} from 'rxjs';
import {Injectable} from '@angular/core';
import {Router} from '@angular/router';
import {User} from '../user.model';
import {AuthenticateSuccess} from './auth.actions';
import {AuthService} from '../auth.service';


export interface AuthResponseData {
    idToken: string; // A Firebase Auth ID token for the newly created user.
    email: string; // The email for the newly created user.
    refreshToken: string; // A Firebase Auth refresh token for the newly created user.
    expiresIn: string; // The number of seconds in which the ID token expires.
    localId: string; // The uid of the newly created user.
    registered ?: boolean; // Whether the email is for an existing account. Optional as it is only for Login Response and not for SignUp response.
}

const handleAuthentication = (email: string, userId: string, token: string, expiresIn: number) => {
    const expiryDate = new Date(new Date().getTime() + (+expiresIn * 1000));
    const user = new User(email, userId, token, expiryDate);
    localStorage.setItem('userData', JSON.stringify(user));
    return new AuthActions.AuthenticateSuccess({email, userId, token, expirationDate: expiryDate});
};

const handleError = (errorResponse) => {
    let errorMessage = 'An unknown error occurred!';
    if (errorResponse.error && errorResponse.error.error) {
        switch (errorResponse.error.error.message) {
            case 'ADMIN_ONLY_OPERATION':
                errorMessage = 'This is Admin only operation!';
                break;
            case 'EMAIL_EXISTS':
                errorMessage = 'This email exists already!';
                break;
            case 'EMAIL_NOT_FOUND':
                errorMessage = 'This email does not exist!';
                break;
            case 'INVALID_PASSWORD':
                errorMessage = 'This password was incorrect!';
                break;
        }
    }
    return new AuthActions.AuthenticateFailure({error: errorMessage});
};
@Injectable()
export class AuthEffects {

    /**
     * things to note:
     * we dont need to subscribe() to actions$ observable explicitly. ngrx/effects will do for us.
     * also the actions$ observable must be long lived. it must not die for the duration of the application.
     * When does an observable die?? an observable dies when it catches an error. So to prevent actions$ from dying
     * we handle error on the inner observable.
     */
    // .pipe() below returns an object of the Action class
    // we use the switchMap() operator to convert that class to another observable.
        // we use @Effect() decorator to tell angular that this is a effect. Also this effect must return an Obeservable
        // which can be dispatched by ngrx store. that's why we return an action class wrapped in an observable.
        // of() operator just wraps anything in an observable.
    @Effect()
    authLogin = this.actions$.pipe(
        ofType(AuthActions.LOGIN_START),
        switchMap((authData: AuthActions.LoginStart) => {
            return this.http.post<AuthResponseData>(
                'https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=' + environment.firebaseAPIKey,
                {email: authData.payload.email, password: authData.payload.password, returnSecureToken: true})
                .pipe(tap(resData => {
                        this.authService.setLogoutExpirationTimer(+resData.expiresIn * 1000);
                    }),
                    map(resData => {
                        return handleAuthentication(resData.email, resData.localId, resData.idToken, +resData.expiresIn);
                    }),
                    catchError(errorResponse => {
                        // must return a non-error observable
                        return of(handleError(errorResponse));
                    }));
        })
    );

    // dispatch: false means my effect will not dispatch an action at the end.
    @Effect({
        dispatch: false
    })
    authRedirect = this.actions$.pipe(
        ofType(AuthActions.AUTHENTICATE_SUCCESS),
        tap(
        () => {
            this.router.navigate(['/']);
        }
    ));

    @Effect()
    authSignup = this.actions$.pipe(
        ofType(AuthActions.SIGNUP_START),
        switchMap((signupStart: AuthActions.SignupStart) => {
            return this.http.post<AuthResponseData>(
                'https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=' + environment.firebaseAPIKey,
                {email: signupStart.payload.email, password: signupStart.payload.password, returnSecureToken: true})
                .pipe(tap((resData) => {
                        this.authService.setLogoutExpirationTimer(+resData.expiresIn * 1000);
                    }),
                    map(resData => {
                        this.authService.setLogoutExpirationTimer(+resData.expiresIn);
                        return handleAuthentication(resData.email, resData.localId, resData.idToken, +resData.expiresIn);
                    }),
                    catchError(errorResponse => {
                        // must return a non-error observable
                        return of(handleError(errorResponse));
                    }));
        }
    ));

    @Effect({dispatch: false})
    authLogout = this.actions$.pipe(ofType(AuthActions.LOGOUT),
        tap(() => {
            this.authService.clearLogoutExpirationTimer();
            localStorage.removeItem('userData');
            this.router.navigate(['/auth']);
        }));

    @Effect()
    autoLogin = this.actions$.pipe(ofType(AuthActions.AUTO_LOGIN),
        map(() => {
            const loadedUserData = localStorage.getItem('userData');
            if (!loadedUserData) {
                return {type: 'DUMMY'}; // return a dummy action
            }
            const userData: {email: string, userId: string, _token: string, _tokenExpiryDate: string } = JSON.parse(loadedUserData);
            const loadedUser = new User(userData.email, userData.userId, userData._token, new Date(userData._tokenExpiryDate));
            if (loadedUser.token) {
                const duration = new Date(userData._tokenExpiryDate).getTime() - new Date().getTime();
                this.authService.clearLogoutExpirationTimer();
                this.authService.setLogoutExpirationTimer(duration);
                return new AuthenticateSuccess(
                    {email: loadedUser.email, userId: loadedUser.userId,
                        token: loadedUser.token, expirationDate: new Date(userData._tokenExpiryDate)});
            }
            return {type: 'DUMMY'}; // return a dummy action
        }));
    /**
     * Actions is one big observable that gets called for every dispatched action.
     * So in this class we can create multiple subscriptions now and use a special ofType() rxjs operator.
     * in this operator we tell what all actions we are interested in. for all those actions, our side-effect will be called.
     */
    constructor(private actions$: Actions, private http: HttpClient, private router: Router,
                private authService: AuthService) {}
}

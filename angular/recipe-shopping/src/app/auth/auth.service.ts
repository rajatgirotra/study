import {Injectable} from '@angular/core';
import {HttpClient, HttpErrorResponse} from '@angular/common/http';
import {BehaviorSubject, Subject, throwError} from 'rxjs';
import {catchError, tap} from 'rxjs/operators';
import {User} from './user.model';
import {Router} from '@angular/router';
import {environment} from '../../environments/environment';

export interface AuthResponseData {
    idToken: string; // A Firebase Auth ID token for the newly created user.
    email: string; // The email for the newly created user.
    refreshToken: string; // A Firebase Auth refresh token for the newly created user.
    expiresIn: string; // The number of seconds in which the ID token expires.
    localId: string; // The uid of the newly created user.
    registered ?: boolean; // Whether the email is for an existing account. Optional as it is only for Login Response and not for SignUp response.
}

@Injectable({
    providedIn: 'root'
})
export class AuthService {

    user = new BehaviorSubject<User>(null); // see data-storage.service.ts for more information on BehaviorSubject.
    constructor(private http: HttpClient, private router: Router) {
    }

    private logoutExpirationTimer: any;

    private handleError(errorResponse: HttpErrorResponse) {
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
        return throwError(errorMessage);
    }

    private handleAuthentication(email: string, userId: string, token: string, expiresInSeconds: number): void {
        const expiryDate = new Date(new Date().getTime() + (expiresInSeconds * 1000));
        const user = new User(email, userId, token, expiryDate);
        console.log(user);
        this.user.next(user);
        this.autoLogout(expiresInSeconds * 1000);
        // persist user information
        localStorage.setItem('userData', JSON.stringify(user));
    }

    signUp(email: string, password: string) {
        return this.http.post<AuthResponseData>('https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=' + environment.firebaseAPIKey,
            {email, password, returnSecureToken: true})
            .pipe(catchError(this.handleError),
                tap(responseData => {
                    this.handleAuthentication(responseData.email, responseData.localId, responseData.idToken, +responseData.expiresIn);
                    }
                ));
    }

    login(email: string, password: string) {
        return this.http.post<AuthResponseData>('https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=' + environment.firebaseAPIKey,
            {email, password, returnSecureToken: true})
            .pipe(catchError(this.handleError),
                tap(responseData => {
                        this.handleAuthentication(responseData.email, responseData.localId, responseData.idToken, +responseData.expiresIn);
                    }
                ));
    }

    logout(): void {
        this.user.next(null);
        this.router.navigate(['/auth']);
        localStorage.removeItem('userData');
        if (this.logoutExpirationTimer) {
            clearTimeout(this.logoutExpirationTimer);
            this.logoutExpirationTimer = null;
        }
    }

    /**
     * the purpose of autoLogin() is to retrieve user credentials stored on disk (i.e persistence storage) so that we can autologin users
     * if we saved their credentials on disk when they were authenticated. this way we dont need to re-authenticate them everytime they press the
     * browser reload button. If we dont persist user information, we loose all user information as it is only held in memory.
     *
     * For all this we use localStorage service provided by angular. this storage is handled by the browser
     * and we can also see in browser itself under Applications in developer tools the data persisted. data is persisted in simple key value
     * pairs. we can use localStorage.setItem() and localStorage.getItem().
     */
    autoLogin(): void {
        const loadedUserData = localStorage.getItem('userData');
        if (!loadedUserData) {
            return;
        }
        const userData: {email: string, userId: string, _token: string, _tokenExpiryDate: string } = JSON.parse(loadedUserData);
        // if (!this.user) {
        //     return;
        // }

        const loadedUser = new User(userData.email, userData.userId, userData._token, new Date(userData._tokenExpiryDate));
        // console.log('loaded user token', loadedUser.token);
        if (loadedUser.token) {
            this.user.next(loadedUser);
        }

        // clear any old timeout if set and start new timeout to logout after token expires.
        if (this.logoutExpirationTimer) {
            clearTimeout(this.logoutExpirationTimer);
            this.logoutExpirationTimer = null;
            const duration = new Date(userData._tokenExpiryDate).getTime() - new Date().getTime();
            this.autoLogout(duration);
        }
    }

    // expirationDuration is in millisecond
    autoLogout(expirationDuration: number): void {
        /**
         * remember that this timeout should be cancelled if user manually logs out, otherwise
         * we logout again when timeout expires.
         */
        this.logoutExpirationTimer = setTimeout(() => {
            this.logout();
        }, expirationDuration);
    }
    /**
     * where should we call autoLogout. Basically whenever a user logs in, we should start our timer to autoLogout after expirationDuration.
     * that would be in autoLogin() and also in handleAuthentication() methods.
     */
}

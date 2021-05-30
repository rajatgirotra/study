import {Injectable} from '@angular/core';
import {HttpClient, HttpErrorResponse} from '@angular/common/http';
import {BehaviorSubject, Subject, throwError} from 'rxjs';
import {catchError, tap} from 'rxjs/operators';
import {User} from './user.model';
import {Router} from '@angular/router';

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
    }

    signUp(email: string, password: string) {
        return this.http.post<AuthResponseData>('https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=AIzaSyBoNmDrmJI0_-yQWBaPIJOqXeq7T4repkY',
            {email, password, returnSecureToken: true})
            .pipe(catchError(this.handleError),
                tap(responseData => {
                    this.handleAuthentication(responseData.email, responseData.localId, responseData.idToken, +responseData.expiresIn);
                    }
                ));
    }

    login(email: string, password: string) {
        return this.http.post<AuthResponseData>('https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=AIzaSyBoNmDrmJI0_-yQWBaPIJOqXeq7T4repkY',
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
    }
}

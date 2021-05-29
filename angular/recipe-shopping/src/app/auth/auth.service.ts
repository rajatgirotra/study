import {Injectable} from '@angular/core';
import {HttpClient, HttpErrorResponse} from '@angular/common/http';
import {throwError} from 'rxjs';
import {catchError} from 'rxjs/operators';

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

    constructor(private http: HttpClient) {
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

    signUp(email: string, password: string) {
        return this.http.post<AuthResponseData>('https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=AIzaSyBoNmDrmJI0_-yQWBaPIJOqXeq7T4repkY',
            {email, password, returnSecureToken: true})
            .pipe(catchError(this.handleError));
    }

    login(email: string, password: string) {
        return this.http.post<AuthResponseData>('https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=AIzaSyBoNmDrmJI0_-yQWBaPIJOqXeq7T4repkY',
            {email, password, returnSecureToken: true})
            .pipe(catchError(this.handleError));
    }
}

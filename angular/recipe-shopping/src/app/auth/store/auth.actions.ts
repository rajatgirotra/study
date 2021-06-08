import {Action} from '@ngrx/store';

export const LOGIN = 'LOGIN';
export const LOGOUT = 'LOGOUT';

export class LoginAction implements Action {
    readonly type: string = LOGIN;
    constructor(public payload: {email: string, userId: string, token: string, expirationDate: Date}) {}
}

export class LogoutAction implements Action {
    readonly type: string = LOGOUT;
    payload = null;
}

export type AuthActions = LoginAction | LogoutAction;

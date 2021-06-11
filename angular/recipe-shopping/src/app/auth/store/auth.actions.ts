import {Action} from '@ngrx/store';

export const LOGIN_START = '[Auth] LOGIN_START';
export const AUTHENTICATE_FAILURE = '[Auth] LOGIN_FAIL';
export const AUTHENTICATE_SUCCESS = '[Auth] LOGIN';
export const LOGOUT = '[Auth] LOGOUT';
export const SIGNUP_START = '[Auth] SIGNUP_START';
export const CLEAR_ERROR = '[Auth] CLEAR_ERROR';
export const AUTO_LOGIN = '[Auth] AUTO_LOGIN';

export class AuthenticateSuccess implements Action {
    readonly type = AUTHENTICATE_SUCCESS;
    constructor(public payload: {email: string, userId: string, token: string, expirationDate: Date}) {}
}

export class Logout implements Action {
    readonly type = LOGOUT;
    payload = null;
}

export class ClearError implements Action {
    readonly type = CLEAR_ERROR;
    payload = null;
}

export class LoginStart implements Action {
    readonly type = LOGIN_START;
    constructor(public payload: {email: string, password: string}) {
    }
}

export class AuthenticateFailure implements Action {
    readonly type = AUTHENTICATE_FAILURE;
    constructor(public payload: {error: string}) {
    }
}

export class SignupStart implements Action {
    readonly type = SIGNUP_START;
    constructor(public payload: {email: string, password: string}) {
    }
}

export class AutoLogin implements Action {
    readonly type = AUTO_LOGIN;
    public payload: null;
}


export type AuthActions = AuthenticateSuccess | Logout | LoginStart | AuthenticateFailure | SignupStart | ClearError | AutoLogin;

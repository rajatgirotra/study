import {User} from '../user.model';
import * as AuthActions from './auth.actions';

export interface State {
    user: User;
    isLoading: boolean;
    authError: string;
}

export const initialState: State = {
    user: null,
    isLoading: false,
    authError: null
};

export function authReducer(state = initialState, action: AuthActions.AuthActions) {
    switch (action.type) {
        case AuthActions.LOGIN_START:
        case AuthActions.SIGNUP_START:
            return {
                ...state,
                user: null,
                isLoading: true,
                authError: null
            };
        case AuthActions.AUTHENTICATE_FAILURE:
            return {
                ...state,
                user: null,
                authError: action.payload.error,
                isLoading: false
            };
        case AuthActions.AUTHENTICATE_SUCCESS:
            return {
                ...state,
                user: new User(action.payload.email, action.payload.userId, action.payload.token, action.payload.expirationDate),
                isLoading: false,
                authError: null
            };
        case AuthActions.LOGOUT:
            return {
                ...state,
                user: null,
                authError: null,
                isLoading: false
            };
        case AuthActions.CLEAR_ERROR:
            return {
                ...state,
                authError: null
            };
        default:
            return state;
    }
}

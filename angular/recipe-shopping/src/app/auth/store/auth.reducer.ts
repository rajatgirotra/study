import {User} from '../user.model';
import * as AuthActions from './auth.actions';

export interface State {
    user: User;
}

export const initialState: State = {
    user: null
};

export function authReducer(state = initialState, action: AuthActions.AuthActions) {
    switch (action.type) {
        case AuthActions.LOGIN:
            return {
                ...state,
                user: new User(action.payload.email, action.payload.userId, action.payload.token, action.payload.expirationDate)
            };
        case AuthActions.LOGOUT:
            return {
                ...state, user: null
            };
        default:
            return state;
    }
}

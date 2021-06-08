import * as fromShoppingList from '../shopping-list/store/shopping-list.reducer';
import * as fromAuth from '../auth/store/auth.reducer';
import {ActionReducerMap} from '@ngrx/store';
import {shoppingListReducer} from '../shopping-list/store/shopping-list.reducer';
import {authReducer} from '../auth/store/auth.reducer';

export interface AppState {
    shoppingList: fromShoppingList.State;
    auth: fromAuth.State;
}

export const AppReducers: ActionReducerMap<AppState> = {
    shoppingList: shoppingListReducer,
    auth: authReducer
};

/**
 * Note on dispatchers
 * When you call this.store.disptach(someAction), the dispatcher is going to call all your reducers, not reducers only for ShoppingList
 * or Auth or Recipes. that's because it simply can't tell which reducers will change the state. This has two implications.
 *
 * Your action type should be unique across all reducers. otherwise the disptacher will end up changing state in mutiple reducers; not the one
 * in which you intended. Also since all reducer function are called it's important that in all your reducers you specify a "default" in the
 * switch case where you handle the action types. This is for two reason.
 * 1) Example: A LOGIN action meant for AuthReducer will also be called for ShoppingListReducer. So in shopping list reducer function, the
 * default case will trigger which should return the state unchanged.
 *
 * 2) The ngrx store will also call all the reducers initially with a INITIALIZE action type. since we dont handle it yet anywhere in our
 * reducer function, we use a default case to return the initialState.
 */

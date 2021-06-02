/**
 * as you read in 15_README.txt, reducer is a function which takes a state and an Action.
 * the state is the application state (basically a Javascript object). For ShoppingList Component, the state is the ingredients list
 * defined in shopping list service.
 */
import {Ingredient} from '../../shared/ingredient.model';
// import {ShoppingListActions, ADD_INGREDIENT} from './shopping-list.actions';
import * as ShoppingListActions from './shopping-list.actions';

const initialState = {
    ingredients: [
        new Ingredient('Apples', 5),
        new Ingredient('Tomatoes', 10)
    ]
};

export function shoppingListReducer (state = initialState, action: ShoppingListActions.ShoppingListActions) {
    // initialState is the initial value of the application store when the reducer will be first called by @ngrx/store.
    /**
     * remember that Action must have a type and a payload. So lets create a shopping-list.actions.ts
     * thereafter the reducer should return a copy of the new state, based on the action type.
     */
    switch (action.type) {
        /**
         * the problem with string 'ADD_INGREDIENT' is that we can easily have typos. So lets create a string constant and we can use
         * that constant here then.
         */
        // case 'ADD_INGREDIENT':
        case ShoppingListActions.ADD_INGREDIENT:
            /**
             * ...state is a special javascript syntax to extract all the properties of the state object
             * then we can override whichever property we want. Basically we should always do ...state because we must return a complete
             * copy of t
             * the new state including properties we dont modify.
             *
             * similarly ...state.ingredients expands the complete ingredients array
             */
            return {
                ...state, ingredients: [
                    ...(state.ingredients), action.payload
                ]
            };
        case ShoppingListActions.ADD_INGREDIENTS:
            return {
                ...state, ingredients: [
                    ...(state.ingredients), ...(action.payload)
                ]
            };
        case ShoppingListActions.UPDATE_INGREDIENT:
            const ingredient = state.ingredients[action.payload.index];
            const updatedIngredient = {...ingredient, ...action.payload.ingredient};
            const updatedIngredients = [...state.ingredients];
            updatedIngredients[action.payload.index] = updatedIngredient;
            return {
                ...state, ingredients: updatedIngredients
            };
        case ShoppingListActions.DELETE_INGREDIENT:
            return {
                ...state, ingredients: state.ingredients.filter((ig, index) => {
                    return index !== action.payload;
                })
            };
        default:
            // return the state unchanged.
            return state; // must do this when reducer is called with any action we dont handle. like initialization of the initial state
            // when reducer is first registered.
    }
}

/**
 * next we need to go to app-module.ts and add StoreModule from @ngrx/store
 * registering our reducer with StoreModule.forRoot() will allow ngrx to dispatch any actions we raise to the reducers.
 * basically its a way to register our reducers with ngrx,
 *
 * next just inject Store into ShoppingListComponent.
 */

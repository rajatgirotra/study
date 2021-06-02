import {Action} from '@ngrx/store';
import {Ingredient} from '../../shared/ingredient.model';

// the general norm is to create action will all upper case.
export const ADD_INGREDIENT  = 'ADD_INGREDIENT';
export const ADD_INGREDIENTS  = 'ADD_INGREDIENTS';
export const UPDATE_INGREDIENT  = 'UPDATE_INGREDIENT';
export const DELETE_INGREDIENT  = 'DELETE_INGREDIENT';

export class AddIngredient implements Action {
    readonly type = ADD_INGREDIENT;
    constructor(public payload: Ingredient) {
    }
}

export class AddIngredients implements Action {
    readonly type = ADD_INGREDIENTS;
    constructor(public payload: Ingredient[]) {
    }
}

export class UpdateIngredient implements Action {
    readonly type = UPDATE_INGREDIENT;
    constructor(public payload: {index: number, ingredient: Ingredient}) {
    }
}

export class DeleteIngredient implements Action {
    readonly type = DELETE_INGREDIENT;
    constructor(public payload: number) {
    }
}



/**
 * TS feature that says type of ShoppingListActions can ve AddIngredient or AddIngredients
 */
export type ShoppingListActions = AddIngredient | AddIngredients | UpdateIngredient | DeleteIngredient;

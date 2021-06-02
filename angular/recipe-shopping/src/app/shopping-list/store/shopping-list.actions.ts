import {Action} from '@ngrx/store';
import {Ingredient} from '../../shared/ingredient.model';

// the general norm is to create action will all upper case.
export const ADD_INGREDIENT  = 'ADD_INGREDIENT';

export class AddIngredient implements Action {
    readonly type = ADD_INGREDIENT;
    constructor(public payload: Ingredient) {
    }
}

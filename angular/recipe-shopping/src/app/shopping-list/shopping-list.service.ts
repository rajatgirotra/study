import {Ingredient} from '../shared/ingerdient.model';
import {EventEmitter} from '@angular/core';

export class ShoppingListService {
    ingredientsChanged = new EventEmitter<Ingredient[]>();
    private ingredients: Ingredient[] = [
        new Ingredient('Apples', 5),
        new Ingredient('Tomatoes', 10)
    ];

    getIngredients(): Ingredient[] {
        return this.ingredients.slice();
    }

    addIngredient(i: Ingredient): void {
        this.ingredients.push(i);
        this.ingredientsChanged.emit(this.ingredients);
    }

    addIngredients(ingredients: Ingredient[]): void {
        this.ingredients.push(...ingredients); // ES6 way to flatten out array to individual items, so [1, 2, 3] is passed as 1, 2, 3
        this.ingredientsChanged.emit(this.ingredients);
    }

}

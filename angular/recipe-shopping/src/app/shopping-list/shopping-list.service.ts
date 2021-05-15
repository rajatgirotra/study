import {Ingredient} from '../shared/ingerdient.model';
// import {EventEmitter} from '@angular/core';
import {Subject} from 'rxjs';

export class ShoppingListService {
    ingredientsChanged = new Subject<Ingredient[]>();
    startEditingMode = new Subject<number>();

    private ingredients: Ingredient[] = [
        new Ingredient('Apples', 5),
        new Ingredient('Tomatoes', 10)
    ];

    getIngredients(): Ingredient[] {
        return this.ingredients.slice();
    }

    getIngredient(index: number): Ingredient {
        return this.ingredients[index];
    }

    updateIngredient(index: number, ingredient: Ingredient): void {
        this.ingredients[index] = ingredient;
        this.ingredientsChanged.next(this.ingredients);
    }

    addIngredient(i: Ingredient): void {
        this.ingredients.push(i);
        // this.ingredientsChanged.emit(this.ingredients);
        this.ingredientsChanged.next(this.ingredients);
    }

    addIngredients(ingredients: Ingredient[]): void {
        this.ingredients.push(...ingredients); // ES6 way to flatten out array to individual items, so [1, 2, 3] is passed as 1, 2, 3
        // this.ingredientsChanged.emit(this.ingredients);
        this.ingredientsChanged.next(this.ingredients);
    }

    deleteIngredient(index: number): void {
        this.ingredients.splice(index, 1);
        this.ingredientsChanged.next(this.ingredients);
    }
}

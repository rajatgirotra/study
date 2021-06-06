import {EventEmitter, Injectable} from '@angular/core';
import {Recipe} from './recipe.model';
import {Ingredient} from '../shared/ingredient.model';
import {ShoppingListService} from '../shopping-list/shopping-list.service';
import {Subject} from 'rxjs';
import {Store} from '@ngrx/store';
import * as ShoppingListActions from '../shopping-list/store/shopping-list.actions';
import * as fromShoppingList from '../shopping-list/store/shopping-list.reducer';

@Injectable({
    providedIn: 'root'
})
export class RecipeService {
    recipeSelected = new EventEmitter<Recipe>();
    recipesChanged = new Subject<Recipe[]>();

    // recipes: Recipe[] = [
    //     new Recipe('Tandoori Chap',
    //         'Mouth watering soy grilled in clay oven',
    //         'https://img-global.cpcdn.com/recipes/d128d41b0978b2da/1200x630cq70/photo.jpg',
    //         [new Ingredient('Soya',15), new Ingredient('Milk', 500)]),
    //     new Recipe('Chilli Paneer', 'Cubes of paneer cooked with green pepper, green chilli, onion and garlic',
    //         'https://myheartbeets.com/wp-content/uploads/2019/08/indo-chinese-chilli-paneer.jpg',
    //         [new Ingredient('Paneer',500), new Ingredient('Chilli', 50)])
    // ];

    private recipes: Recipe[] = [];

    getRecipes(): Recipe[] {
        return this.recipes.slice();
    }
    constructor(private shoppingListService: ShoppingListService,
                private store: Store<fromShoppingList.AppState>) {
    }

    getRecipe(idx: number): Recipe {
        return this.recipes[idx];
    }

    addRecipe(recipe: Recipe): void {
        this.recipes.push(recipe);
        this.recipesChanged.next(this.recipes.slice());
    }

    updateRecipe(index: number, recipe: Recipe): void {
        this.recipes[index] = recipe;
        this.recipesChanged.next(this.recipes.slice());
    }

    addIngredientsToShoppingCart(ingredients: Ingredient[]): void{
        // this.shoppingListService.addIngredients(ingredients);
        this.store.dispatch(new ShoppingListActions.AddIngredients(ingredients));
    }

    deleteRecipe(index: number) {
        this.recipes.splice(index, 1);
        this.recipesChanged.next(this.recipes.slice());
    }

    saveRecipes(recipes: Recipe[]) {
        this.recipes = recipes;
        this.recipesChanged.next(this.recipes.slice());
    }
}

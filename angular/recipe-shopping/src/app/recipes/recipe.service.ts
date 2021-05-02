import {EventEmitter, Injectable} from '@angular/core';
import {Recipe} from './recipe.model';
import {Ingredient} from '../shared/ingerdient.model';
import {ShoppingListService} from '../shopping-list/shopping-list.service';

@Injectable()
export class RecipeService {
    recipeSelected = new EventEmitter<Recipe>();
    recipes: Recipe[] = [
        new Recipe('Tandoori Chap',
            'Mouth watering soy grilled in clay oven',
            'https://img-global.cpcdn.com/recipes/d128d41b0978b2da/1200x630cq70/photo.jpg',
            [new Ingredient('Soya',15), new Ingredient('Milk', 500)]),
        new Recipe('Chilli Paneer', 'Cubes of paneer cooked with green pepper, green chilli, onion and garlic',
            'https://myheartbeets.com/wp-content/uploads/2019/08/indo-chinese-chilli-paneer.jpg',
            [new Ingredient('Paneer',500), new Ingredient('Chilli', 50)])
    ];

    getRecipes(): Recipe[] {
        return this.recipes.slice();
    }
    constructor(private shoppingListService: ShoppingListService) {
    }

    addIngredientsToShoppingCart(ingredients: Ingredient[]): void{
        this.shoppingListService.addIngredients(ingredients);
    }

}

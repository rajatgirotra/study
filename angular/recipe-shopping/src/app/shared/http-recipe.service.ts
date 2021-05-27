import {Injectable} from '@angular/core';

import {HttpClient} from '@angular/common/http';
import {Recipe} from '../recipes/recipe.model';
import {RecipeService} from '../recipes/recipe.service';
import {map, tap} from 'rxjs/operators';

@Injectable({
    providedIn: 'root'
})
export class HttpRecipeService {
    constructor(private recipeService: RecipeService,
                private http: HttpClient) {
    }

    saveRecipes(): void {
        this.http.put('https://ng-course-recipe-shop-cacba-default-rtdb.asia-southeast1.firebasedatabase.app/recipes.json',
            this.recipeService.getRecipes()).subscribe(
                responseData => {
                    console.log(responseData);
                });
    }

    fetchRecipes() {
        /**
         * if we have any new recipe saved previously which has no ingredient, then in firebase also it will not be present.
         * So when we fetch it now, ingredients will be undefined. But we should not leave it undefined. So we will create
         * an empty array of ingredients here if that is the case.
         */
        return this.http.get<Recipe[]>('https://ng-course-recipe-shop-cacba-default-rtdb.asia-southeast1.firebasedatabase.app/recipes.json')

            .pipe(map(
                (recipes: Recipe[]) => {
                    // javascript array map operator
                    return recipes.map(recipe => {
                        return {...recipe, ingredients: recipe.ingredients ? recipe.ingredients : []};
                    });
                }
            ), tap(recipes => {
                this.recipeService.saveRecipes(recipes);
            }))
         ;
    }
}

import {Injectable} from '@angular/core';
import {ActivatedRouteSnapshot, Resolve, RouterStateSnapshot} from '@angular/router';
import {Observable} from 'rxjs';
import {RecipeService} from './recipe.service';
import {Recipe} from './recipe.model';
import {DataStorageService} from '../shared/data-storage.service';

@Injectable({
    providedIn: 'root'
})
export class RecipesResolverService implements Resolve<Recipe[]> {

    constructor(private recipeService: RecipeService, private httpRecipeService: DataStorageService) {
    }

    resolve(route: ActivatedRouteSnapshot, state: RouterStateSnapshot): Observable<Recipe[]> | Promise<Recipe[]> | Recipe[] {
        const recipes = this.recipeService.getRecipes();
        if (recipes.length === 0) {
            return this.httpRecipeService.fetchRecipes();
        }
        return recipes;
    }
}

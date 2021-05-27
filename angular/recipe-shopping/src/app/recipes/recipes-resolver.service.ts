import {Injectable} from '@angular/core';
import {ActivatedRouteSnapshot, Resolve, RouterStateSnapshot} from '@angular/router';
import {Observable} from 'rxjs';
import {RecipeService} from './recipe.service';
import {Recipe} from './recipe.model';
import {HttpRecipeService} from '../shared/http-recipe.service';

@Injectable({
    providedIn: 'root'
})
export class RecipesResolverService implements Resolve<Recipe[]> {

    constructor(private recipeService: RecipeService, private httpRecipeService: HttpRecipeService) {
    }

    resolve(route: ActivatedRouteSnapshot, state: RouterStateSnapshot): Observable<Recipe[]> | Promise<Recipe[]> | Recipe[] {
        return this.httpRecipeService.fetchRecipes();
    }
}

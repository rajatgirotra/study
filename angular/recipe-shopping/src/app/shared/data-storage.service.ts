import {Injectable} from '@angular/core';

import {HttpClient, HttpParams} from '@angular/common/http';
import {Recipe} from '../recipes/recipe.model';
import {RecipeService} from '../recipes/recipe.service';
import {exhaustMap, map, take, tap} from 'rxjs/operators';
import {AuthService} from '../auth/auth.service';

@Injectable({
    providedIn: 'root'
})
export class DataStorageService {
    constructor(private recipeService: RecipeService,
                private http: HttpClient, private authService: AuthService) {
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

        /**
         * Adding an authenticationToken is a little complex. In the end all we want to do is add a User.token as a query parameter to the
         * outgoing request. But to do that first we need to fetch the user. One way is to use the AuthService and subscribe to the user
         * observable, but we dont want a continuous subscription. So we go to AuthService and change the Subject to BehaviorSubject.
         * BehaviorSubject is exactly like Subject (you can call subscribe() and next() on it), but it also allows you to fetch the most recent
         * value emitted by the Subject even though you are not yet subscribed to it. Since it allows to fetch the most recent value even before
         * any value is emitted, it must be initialized with some starting value. We initialize it by null in AuthService.
         *
         * Then to consume the last emitted value we use the rxjs "take(1)" operator, which tells rxjs to consume one single item and then
         * automatically unsubscribe. the subscribe call on authService will return an observable. this means we need to set auth token inside
         * the authService.user observable and then return the http observable later (only when user changes and we get notified.
         * To get around this issue we use an exhaustMap observable. this observable will switch to the next observable once the current one
         * expires. so from exhaustMap operator we must return the next observable.
         *
         * This means that the map operator after exhaustMap will only apply to the last active observable.
         * Later we will comment this code as we will use an interceptor
         */

        // return this.authService.user.pipe(take(1),
        //     exhaustMap(
        //         user => {
        //             return this.http.get<Recipe[]>('https://ng-course-recipe-shop-cacba-default-rtdb.asia-southeast1.firebasedatabase.app/recipes.json',
        //                 {params: new HttpParams().set('auth', user.token)});
        //         }
        //     ),
        //     map(
        //         (recipes: Recipe[]) => {
        //             // javascript array map operator
        //             return recipes.map(recipe => {
        //                 return {...recipe, ingredients: recipe.ingredients ? recipe.ingredients : []};
        //             });
        //         }
        //     ), tap(recipes => {
        //         this.recipeService.saveRecipes(recipes);
        //     }));

         return this.http.get<Recipe[]>(
             'https://ng-course-recipe-shop-cacba-default-rtdb.asia-southeast1.firebasedatabase.app/recipes.json')
             .pipe(
                 map((recipes: Recipe[]) => {
                     // javascript array map operator
                     return recipes.map(recipe => {
                         return {...recipe, ingredients: recipe.ingredients ? recipe.ingredients : []};
                     });
                 }
                 ),
                 tap(recipes => {
                     this.recipeService.saveRecipes(recipes);
                 }
                 )
             );
    }
}

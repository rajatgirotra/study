import { Component, OnInit, DoCheck } from '@angular/core';
import { Ingredient } from '../shared/ingredient.model';
import {ShoppingListService} from './shopping-list.service';
import {Store} from '@ngrx/store';
import {shoppingListReducer} from './store/shopping-list.reducer';
import {Observable} from 'rxjs';
@Component({
  selector: 'app-shopping-list',
  templateUrl: './shopping-list.component.html',
  styleUrls: ['./shopping-list.component.css']
})
export class ShoppingListComponent implements OnInit, DoCheck {
  // ingredients: Ingredient[] = [];
  ingredients: Observable<{ingredients: Ingredient[]}>;
  // so with ngrx, ingredients is now an Observable, so the template will break
  // but angular provides us with an async pipe which can come to our rescue. the async pipe will subscribe to this observable in side
  // the template and also manage the subscription and we can access the ingredients objects to get the ingredients array.

  /**
   * the Store object is a generic object. So we must give it a type. the type should be a javascript object
   * where the key is the key you registered your reducer with in app-module and the value is the value which your reducer function yields.
   * ie. nothing but the initialState type in shopping-list.reducer.ts
   */
  constructor(private shoppingListService: ShoppingListService,
              private store: Store<{shoppingList: {ingredients: Ingredient[]}}>) {
    console.log('ShoppingListComponent ctor called!');
  }

  ngOnInit(): void {
    // console.log('ngOnInit called!');
    // this.ingredients = this.shoppingListService.getIngredients();
    // this.shoppingListService.ingredientsChanged.subscribe(
    //     (ingredients: Ingredient[]) => {
    //       this.ingredients = this.shoppingListService.getIngredients();
    //     }
    // );

    // store.select returns a slice of the application store as an Observable<> where type is the data format of your store.
    this.ingredients = this.store.select('shoppingList')
  }

  ngDoCheck() {
    console.log('i', this.ingredients);
  }

  onEditItem(index: number): void {
    this.shoppingListService.startEditingMode.next(index);
  }

  // tslint:disable-next-line:typedef
  // onNewIngredient(ingredient: Ingredient) {
  //   this.ingredients.push(ingredient);
  // }
}

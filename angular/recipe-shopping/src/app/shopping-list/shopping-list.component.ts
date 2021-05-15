import { Component, OnInit, DoCheck } from '@angular/core';
import { Ingredient } from '../shared/ingerdient.model';
import {ShoppingListService} from './shopping-list.service';
@Component({
  selector: 'app-shopping-list',
  templateUrl: './shopping-list.component.html',
  styleUrls: ['./shopping-list.component.css']
})
export class ShoppingListComponent implements OnInit, DoCheck {
  ingredients: Ingredient[] = [];
  constructor(private shoppingListService: ShoppingListService) {
    console.log('ShoppingListComponent ctor called!');
  }

  ngOnInit(): void {
    // console.log('ngOnInit called!');
    this.ingredients = this.shoppingListService.getIngredients();
    this.shoppingListService.ingredientsChanged.subscribe(
        (ingredients: Ingredient[]) => {
          this.ingredients = this.shoppingListService.getIngredients();
        }
    );
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

import {Component, ElementRef, OnInit, Output, ViewChild, EventEmitter, OnDestroy} from '@angular/core';
import {Ingredient} from '../../shared/ingredient.model';
import {ShoppingListService} from '../shopping-list.service';
import { NgForm } from '@angular/forms';
import {Subscription} from 'rxjs';
import {Store} from '@ngrx/store';
import * as ShoppingListActions from '../store/shopping-list.actions';
import * as fromShoppingList from '../store/shopping-list.reducer';

@Component({
  selector: 'app-shopping-edit',
  templateUrl: './shopping-edit.component.html',
  styleUrls: ['./shopping-edit.component.css']
})
export class ShoppingEditComponent implements OnInit, OnDestroy {
  // @ViewChild('nameInput') nameInputRef: ElementRef;
  // @ViewChild('amountInput') amountInputRef: ElementRef;
  // @Output() ingredientSelected = new EventEmitter<Ingredient>();

  @ViewChild('f', {static: false}) form: NgForm;
  // ingredient: Ingredient;

  editMode = false;
  // editIndex: number;
  editIngredient: Ingredient;
  editSubscription: Subscription;

  constructor(private shoppingListService: ShoppingListService,
              private store: Store<fromShoppingList.AppState>) { }

  ngOnInit(): void {
    // this.editSubscription = this.shoppingListService.startEditingMode.subscribe(
    //     (index: number) => {
    //       this.editMode = true;
    //       this.editIndex = index;
    //       this.editIngredient = this.shoppingListService.getIngredient(index);
    //
    //       this.form.setValue({
    //         name: this.editIngredient.name,
    //         amount: this.editIngredient.amount
    //       });
    //     }
    // );
    this.editSubscription = this.store.select('shoppingList').subscribe(stateData => {
      if (stateData.editedIngredientIndex > -1) {
        this.editMode = true;
        this.editIngredient = stateData.editedIngredient;
        this.form.setValue({
          name: this.editIngredient.name,
          amount: this.editIngredient.amount
        });
      } else {
        this.editMode = false;
      }
    });
  }

  ngOnDestroy(): void {
    this.store.dispatch(new ShoppingListActions.StopEdit());
    if (this.editSubscription) {
      this.editSubscription.unsubscribe();
    }
  }

  onSubmit(): void {
    // const ingName = this.nameInputRef.nativeElement.value;
    // const ingAmount = this.amountInputRef.nativeElement.value;
    // this.ingredient = new Ingredient(ingName, ingAmount);
    const value = this.form.value;
    // this.ingredient = new Ingredient(value.name, value.amount);
    const ingredient = new Ingredient(value.name, value.amount);
    if (this.editMode) {
      // this.shoppingListService.updateIngredient(this.editIndex, ingredient);
      this.store.dispatch(new ShoppingListActions.UpdateIngredient(ingredient));
      this.editMode = false;
    } else {
      // this.shoppingListService.addIngredient(ingredient);
      this.store.dispatch(new ShoppingListActions.AddIngredient(ingredient));
    }
    this.form.reset();

    // console.log('SE ', this.shoppingListService.getIngredients());
  }

  onClear(): void {
    this.form.reset();
    this.editMode = false;
    this.store.dispatch(new ShoppingListActions.StopEdit());
  }

  onDeleteIngredient(): void {
    // this.shoppingListService.deleteIngredient(this.editIndex);
    this.store.dispatch(new ShoppingListActions.DeleteIngredient());
    this.onClear();
  }
}

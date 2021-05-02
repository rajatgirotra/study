import {Component, ElementRef, OnInit, Output, ViewChild, EventEmitter} from '@angular/core';
import {Ingredient} from '../../shared/ingerdient.model';
import {ShoppingListService} from '../shopping-list.service';

@Component({
  selector: 'app-shopping-edit',
  templateUrl: './shopping-edit.component.html',
  styleUrls: ['./shopping-edit.component.css']
})
export class ShoppingEditComponent implements OnInit {
  @ViewChild('nameInput') nameInputRef: ElementRef;
  @ViewChild('amountInput') amountInputRef: ElementRef;
  // @Output() ingredientSelected = new EventEmitter<Ingredient>();
  ingredient: Ingredient;
  constructor(private shoppingListService: ShoppingListService) { }

  ngOnInit(): void {
  }

  onNewIngredient() {
    const ingName = this.nameInputRef.nativeElement.value;
    const ingAmount = this.amountInputRef.nativeElement.value;
    this.ingredient = new Ingredient(ingName, ingAmount);
    this.shoppingListService.addIngredient(this.ingredient);
    // console.log('SE ', this.shoppingListService.getIngredients());
  }
}

import { Component, OnInit } from '@angular/core';
import {Recipe} from './recipe.model';
import {RecipeService} from './recipe.service';

@Component({
  selector: 'app-recipes',
  templateUrl: './recipes.component.html',
  styleUrls: ['./recipes.component.css'],
  // providers: [RecipeService]
})
export class RecipesComponent implements OnInit {
  // currentRecipeSelected: Recipe;

  constructor(private recipeService: RecipeService) { }

  ngOnInit(): void {
    //   this.recipeService.recipeSelected.subscribe(
    //       (recipe: Recipe) => {
    //         this.currentRecipeSelected = recipe;
    //         // console.log(recipe);
    //       }
    //   );
   }
}

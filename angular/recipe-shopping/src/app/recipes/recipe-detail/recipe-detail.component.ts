import {Component, Input, OnDestroy, OnInit} from '@angular/core';
import {Recipe} from '../recipe.model';
import {RecipeService} from '../recipe.service';
import {ActivatedRoute, Params, Router} from '@angular/router';

@Component({
  selector: 'app-recipe-detail',
  templateUrl: './recipe-detail.component.html',
  styleUrls: ['./recipe-detail.component.css']
})
export class RecipeDetailComponent implements OnInit, OnDestroy {
  recipe: Recipe;
  id: number;
  recipeSubscription;
  constructor(private recipeService: RecipeService,
              private route: ActivatedRoute, private router: Router) { }

  ngOnInit(): void {
    // this.recipe = this.recipeService.getRecipe(+this.route.snapshot.params.id);
    this.recipeSubscription = this.route.params.subscribe(
        (params: Params) => {
          this.id = +params.id;
          this.recipe = this.recipeService.getRecipe(this.id);
    });
  }

  ngOnDestroy(): void {
    if (this.recipeSubscription) {
      this.recipeSubscription.unsubscribe();
    }
  }

  onAddIngredientToShoppingCart(): void {
      this.recipeService.addIngredientsToShoppingCart(this.recipe.ingredients);
  }

  onRecipeEdit(): void {
    this.router.navigate(['edit'], {relativeTo: this.route});
  }
}

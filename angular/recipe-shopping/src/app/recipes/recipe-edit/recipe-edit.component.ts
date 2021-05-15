import {Component, OnDestroy, OnInit} from '@angular/core';
import {ActivatedRoute, Params, Router} from '@angular/router';
import {AbstractControl, Form, FormArray, FormControl, FormGroup, Validators} from '@angular/forms';
import {RecipeService} from '../recipe.service';
import {Recipe} from '../recipe.model';

@Component({
  selector: 'app-recipe-edit',
  templateUrl: './recipe-edit.component.html',
  styleUrls: ['./recipe-edit.component.css']
})
export class RecipeEditComponent implements OnInit, OnDestroy {
  id: number;
  editMode = false;
  paramsSubscription;

  recipeForm: FormGroup;

  constructor(private route: ActivatedRoute, private recipeService: RecipeService,
              private router: Router) { }

  ngOnInit(): void {
    this.paramsSubscription = this.route.params.subscribe(
        (params: Params) => {
          this.id = params.id;
          this.editMode = params.id !== undefined;
          // console.log(this.editMode);
          this.initForm();
        }
    );
  }

  initForm(): void {
      let recipeName = '';
      let recipeImagePath = '';
      let recipeDescription = '';
      const recipeIngredients = new FormArray([]);

      if (this.editMode) {
          const recipe = this.recipeService.getRecipe(this.id);
          recipeName = recipe.name;
          recipeImagePath = recipe.imagePath;
          recipeDescription = recipe.description;
          for (const ingredient of recipe.ingredients) {
              recipeIngredients.push(new FormGroup({
                  'name': new FormControl(ingredient.name, Validators.required),
                  'amount': new FormControl(ingredient.amount,
                      [Validators.required, Validators.pattern(/^[1-9]+[0-9]*$/)])
              }));
          }
      }

      this.recipeForm = new FormGroup({
          'name': new FormControl(recipeName, Validators.required),
          'imagePath': new FormControl(recipeImagePath, Validators.required),
          'description': new FormControl(recipeDescription, Validators.required),
          'ingredients': recipeIngredients
      });
  }

  getIngredientControls(): AbstractControl[] {
      return (this.recipeForm.get('ingredients') as FormArray).controls;
  }

  ngOnDestroy(): void {
    if (this.paramsSubscription) {
      this.paramsSubscription.unsubscribe();
    }
  }

  onSubmit(): void {
      // console.log(this.recipeForm);
      const recipe = new Recipe(this.recipeForm.value.name, this.recipeForm.value.description,
          this.recipeForm.value.imagePath, this.recipeForm.value.ingredients);
      if (this.editMode) {
          this.recipeService.updateRecipe(this.id, recipe);
      } else {
          this.recipeService.addRecipe(recipe);
      }
      this.router.navigate(['../'], {relativeTo: this.route});
  }

  addIngredient(): void {
      (this.recipeForm.get('ingredients') as FormArray).push(new FormGroup({
          'name': new FormControl(null, Validators.required),
          'amount': new FormControl(null, [Validators.required, Validators.pattern(/^[1-9]+[0-9]*$/)])
      }));
  }

  onDeleteIngredient(index: number): void {
      (this.recipeForm.get('ingredients') as FormArray).removeAt(index);
  }

  onCancel(): void {
      // this.recipeForm.reset();
      this.router.navigate(['../'], {relativeTo: this.route});
  }
}

import {Ingredient} from '../shared/ingredient.model';

export class Recipe {
    public name = '';
    public description = '';
    public imagePath = '';
    public ingredients: Ingredient[] = [];

   constructor(name: string, desc: string, imagePath: string, ingredients: Ingredient[]) {
       this.name = name;
       this.description = desc;
       this.imagePath = imagePath;
       this.ingredients = ingredients;
   }
}

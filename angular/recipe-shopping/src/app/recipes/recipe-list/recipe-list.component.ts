import { Component, OnInit } from '@angular/core';
import { Recipe } from '../recipe.model';

@Component({
  selector: 'app-recipe-list',
  templateUrl: './recipe-list.component.html',
  styleUrls: ['./recipe-list.component.css']
})
export class RecipeListComponent implements OnInit {
  recipes: Recipe[] = [
      new Recipe('Tandoori Chap',
          'Mouth watering soy grilled in clay oven',
          'https://img-global.cpcdn.com/recipes/d128d41b0978b2da/1200x630cq70/photo.jpg'),
      new Recipe('Chilli Paneer', 'Cubes of paneer cooked with green pepper, green chilli, onion and garlic',
          'https://myheartbeets.com/wp-content/uploads/2019/08/indo-chinese-chilli-paneer.jpg')
  ];
  constructor() { }

  ngOnInit(): void {
  }

}

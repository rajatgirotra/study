import {Component, OnInit, EventEmitter, Output} from '@angular/core';
import {HttpRecipeService} from '../shared/http-recipe.service';

@Component({
    selector: 'app-header',
    templateUrl: './header.component.html',
    styleUrls: ['./header.component.css']
})
export class HeaderComponent implements OnInit {
     constructor(private httpRecipeService: HttpRecipeService) {
    }

    ngOnInit(): void {
    }

    onSaveData(): void {
         this.httpRecipeService.saveRecipes();
    }

    onFetchData(): void {
         this.httpRecipeService.fetchRecipes().subscribe();
     }
}

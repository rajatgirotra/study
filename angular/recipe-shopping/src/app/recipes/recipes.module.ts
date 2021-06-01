import {NgModule} from '@angular/core';
import {RecipesComponent} from './recipes.component';
import {RecipeListComponent} from './recipe-list/recipe-list.component';
import {RecipeDetailComponent} from './recipe-detail/recipe-detail.component';
import {RecipeItemComponent} from './recipe-list/recipe-item/recipe-item.component';
import {RecipeStartComponent} from './recipe-start/recipe-start.component';
import {RecipeEditComponent} from './recipe-edit/recipe-edit.component';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import {RouterModule, Routes} from '@angular/router';
import {CommonModule} from '@angular/common';
import {DropdownDirective} from '../shared/dropdown.directive';
import {AuthGuard} from '../auth/auth.guard';
import {RecipesResolverService} from './recipes-resolver.service';
import {RecipesRoutingModule} from './recipes-routing.module';


@NgModule({
    declarations: [
        RecipesComponent,
        RecipeListComponent,
        RecipeDetailComponent,
        RecipeItemComponent,
        RecipeStartComponent,
        RecipeEditComponent,
        DropdownDirective,
    ],
    imports: [
        FormsModule,
        ReactiveFormsModule,
        RouterModule,
        CommonModule,
        RecipesRoutingModule
    ],
    exports: [
        // RecipesComponent,
        // RecipeListComponent,
        // RecipeDetailComponent,
        // RecipeItemComponent,
        // RecipeStartComponent,
        // RecipeEditComponent,
        // DropdownDirective,
    ],
})
export class RecipesModule {

}

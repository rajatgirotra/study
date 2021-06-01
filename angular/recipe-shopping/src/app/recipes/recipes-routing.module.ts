import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {RecipesComponent} from './recipes.component';
import {AuthGuard} from '../auth/auth.guard';
import {RecipeStartComponent} from './recipe-start/recipe-start.component';
import {RecipeEditComponent} from './recipe-edit/recipe-edit.component';
import {RecipeDetailComponent} from './recipe-detail/recipe-detail.component';
import {RecipesResolverService} from './recipes-resolver.service';

const appRoutes: Routes = [
    {path: 'recipes', component: RecipesComponent,
        canActivate: [AuthGuard],
        children: [
            {path: '', component: RecipeStartComponent},
            {path: 'new', component: RecipeEditComponent},
            {path: ':id', component: RecipeDetailComponent, resolve: [RecipesResolverService]},
            {path: ':id/edit', component: RecipeEditComponent, resolve: [RecipesResolverService]},
        ]}
]

@NgModule({
    declarations: [],
    imports: [RouterModule.forChild(appRoutes)],
    exports: [RouterModule]
})
export class RecipesRoutingModule {

}

import {NgModule} from '@angular/core';
import {ShoppingListComponent} from './shopping-list.component';
import {ShoppingEditComponent} from './shopping-edit/shopping-edit.component';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import {Router, RouterModule, Routes} from '@angular/router';
import {CommonModule} from '@angular/common';

const appRoutes: Routes = [
    {path: 'shopping-list', component: ShoppingListComponent}
]

@NgModule({
    declarations: [
        ShoppingListComponent,
        ShoppingEditComponent
    ],
    imports: [
        CommonModule,
        FormsModule,
        ReactiveFormsModule,
        RouterModule.forChild(appRoutes)
    ],
    exports: [
        ShoppingListComponent,
        ShoppingEditComponent,
        // RouterModule
    ]
})
export class ShoppingListModule {}

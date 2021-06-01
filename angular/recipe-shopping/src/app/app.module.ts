import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import {HeaderComponent} from './header/header.component';
import {AppRoutingModule} from './app-routing.module';
import {HttpClientModule} from '@angular/common/http';
import {RecipesModule} from './recipes/recipes.module';
import {ShoppingListModule} from './shopping-list/shopping-list.module';
import {SharedModule} from './shared/shared.module';
import {CoreModule} from './core.module';
import {AuthModule} from './auth/auth.module';

@NgModule({
  declarations: [
      AppComponent,
      HeaderComponent,
  ],
    imports: [
        BrowserModule,
        AppRoutingModule,
        HttpClientModule,
        RecipesModule,
        ShoppingListModule,
        SharedModule,
        CoreModule,
        AuthModule
    ],
  providers: [
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }

/**
 * Service classes can have @Injectable({[providedIn: 'root']}. That way you dont need to register them in providers array here.
 * But for some reason if you dont use @Injectable like above, there is a practice to make your app-module.ts leaner by listing all your
 * services in a separate module called CoreModule. see core-module.ts
 */

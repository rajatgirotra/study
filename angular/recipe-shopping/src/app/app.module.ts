import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import {HeaderComponent} from './header/header.component';
import {AppRoutingModule} from './app-routing.module';
import {HttpClientModule} from '@angular/common/http';
import {SharedModule} from './shared/shared.module';
import {CoreModule} from './core.module';

@NgModule({
  declarations: [
      AppComponent,
      HeaderComponent,
  ],
    imports: [
        BrowserModule,
        AppRoutingModule,
        HttpClientModule,
        SharedModule,
        CoreModule
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

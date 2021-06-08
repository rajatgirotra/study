import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import {HeaderComponent} from './header/header.component';
import {AppRoutingModule} from './app-routing.module';
import {HttpClientModule} from '@angular/common/http';
import {SharedModule} from './shared/shared.module';
import {CoreModule} from './core.module';
import {StoreModule} from '@ngrx/store';
import * as fromApp from './store/app.reducer';

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
        // storeModule.forRoot takes a ActionReducerMap which is a js object.
        // key can be any identifier and the value is the reducer
        /**
         * what is the significance of the key. Think of the complete application store as a massive js object and these keys as a key for a
         * particular slice of the store that you want to access/modify within that store. Also the reducer registered with the key will
         * get only that particular slice from the massive application store object.
         */
        StoreModule.forRoot(fromApp.AppReducers),
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

import {NgModule} from '@angular/core';
import {AuthComponent} from './auth.component';
import {SharedModule} from '../shared/shared.module';
import {RouterModule} from '@angular/router';

@NgModule({
    declarations: [
        AuthComponent,
    ],
    imports: [
        SharedModule,
        RouterModule.forChild([
            {path: '', component: AuthComponent}
        ])
    ],
    exports: [
        AuthComponent
    ]
})
export class AuthModule {}

import {NgModule} from '@angular/core';
import {AlertComponent} from './alert/alert.component';
import {AlertDirective} from './alert/alert.directive';
import {SpinningWheelComponent} from './loaders/spinning-wheel.component';
import {DropdownDirective} from './dropdown.directive';
import {CommonModule} from '@angular/common';
import {FormsModule} from '@angular/forms';

@NgModule({
    declarations: [
        AlertComponent,
        AlertDirective,
        SpinningWheelComponent,
        DropdownDirective
    ],
    imports: [
        CommonModule
    ],

    exports: [
        AlertComponent,
        AlertDirective,
        SpinningWheelComponent,
        DropdownDirective,
        CommonModule,
        FormsModule
    ]
})
export class SharedModule {

}

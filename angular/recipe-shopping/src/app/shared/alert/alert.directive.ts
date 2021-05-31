import {Directive, ViewContainerRef} from '@angular/core';

@Directive({
    selector: '[appAlert]'
})
export class AlertDirective {
    constructor(public viewContainerRef: ViewContainerRef) {
    }
}

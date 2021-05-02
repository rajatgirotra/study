import {Directive, Input, TemplateRef, ViewContainerRef} from '@angular/core';

@Directive({
  selector: '[appUnless]'
})


export class UnlessDirective {
  /**
   * this directive must have an @Input() property with value equal to boolean and we should be able to inject the ng-template in and out
   * view based on the boolean condition. For that the @Input() should be a property which is also a function. something like python property.
   * this is achieved using "set"
   *
   * Note that property name must match the selector name; otherwise you'll see an error in developer tools.
   */
  @Input() set appUnless(condition: boolean) {
    /**
     * appUnless is a property and also a function.
     */
    if (!condition) {
      // render template ref in view container ref
      this.vcRef.createEmbeddedView(this.templateRef);
    } else {
      this.vcRef.clear();
    }
  }

  /**
   * the ctor would need two args. 1st the TemplateRef which is a reference to the ng-template element, just like ElementRef is a reference
   * to any HTML element in the template file.
   *
   * 2nd the view container ref inside which the template ref has to be rendered.
   */
  constructor(private templateRef: TemplateRef<any>, private vcRef: ViewContainerRef) { }

}


/**
 * <ng-template [ngIf]="currentRecipeSelected">
 *     //blah blah blah
 *     </ng-template>
 */

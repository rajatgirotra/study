import {Directive, ElementRef, OnInit, Renderer2, HostListener, HostBinding, Input } from '@angular/core';

@Directive({
    selector: '[appBasicHighlight]'
})
export class BasicHighlightDirective  implements OnInit {
    constructor(private elementRef: ElementRef, private renderer: Renderer2) {}
    @Input() defaultBgColor = 'cyan';
    @Input() highlightBgColor = 'blue';
    @Input() defaultFgColor = 'red';
    @Input() highlightFgColor = 'white';

    @HostBinding ('style.backgroundColor') backgroundColor = this.defaultBgColor;
    @HostBinding ('style.color') color = this.defaultFgColor;

    ngOnInit(): void {
        // this.elementRef.nativeElement.style.backgroundColor = 'green';

        // this.renderer.setStyle(this.elementRef.nativeElement, 'background-color', 'blue');
        // this.renderer.setStyle(this.elementRef.nativeElement, 'color', 'white');
    }

    @HostListener('mouseenter') onMouseEnter(eventData: Event): void {
        // Use @HostBinding instead of using Renderer here.
        // this.renderer.setStyle(this.elementRef.nativeElement, 'background-color', 'blue');
        // this.renderer.setStyle(this.elementRef.nativeElement, 'color', 'white');

        this.backgroundColor = this.highlightBgColor;
        this.color = this.highlightFgColor;
    }

    @HostListener('mouseleave') onMouseLeave(eventData: Event): void {
        // Use @HostBinding instead of using Renderer here.
        // this.renderer.setStyle(this.elementRef.nativeElement, 'background-color', 'transparent');
        // this.renderer.setStyle(this.elementRef.nativeElement, 'color', 'black');

        this.backgroundColor = this.defaultBgColor;
        this.color = this.defaultFgColor;
    }
}

/**
 * using this.elementRef.nativeElement.style.backgroundColor = 'green'; and directly accessing the DOM is not a recommended way though.
 * Angular advised that you should use a Renderer2 object. Rendered2 angular object provides access to DOM and also works where there is no
 * DOM (angular can also run in environments where there is no DOM).
 *
 * HostListener decorator allows you to listen to DOM events on the HTML element in your directive. and you can then take actions when certain
 * events occur. So your app becomes reactive. Lets use @HostListener to change background and foreground color when mouse enters or leaves the
 * html element.
 *
 * An even cleaner way of modifying host properties (host means the HTML element this directive is sitting on), is to use @HostBinding decorator
 * together with @HostListener decorator. @HostBinding doesnt require you to use the Renderer2 and is also more convenient.
 *
 * Directives also support custom properties and events just like components. Lets add custom properties to allow us to choose color and
 * backgroundColor from the template instead of hard coding it. See the template file also how we use the custom properties.
 */

import {Directive, ElementRef, HostBinding, HostListener, OnInit, Renderer2} from '@angular/core';

@Directive({
    selector: '[appDropdown]'
})
export class DropdownDirective implements OnInit {
    // @HostListener('click') onClicked(eventData: Event): void {
    //     this.elRef.nativeElement.classList.toggle('open');
    // }

    @HostBinding('class.open') isOpen = false;
    @HostListener('document:click', ['$event']) onClicked(event: Event): void {
        /**
         * event.target refers to the element which triggered the event.
         * so when you click anywhere on the page, the this.elRef.nativeElement.contains(event.target) will return false.
         * as event.target will be somewhere else in the document and nativeElement will be the element on which this directive is.
         *
         * and when somebody clicks the button then this.elRef.nativeElement.contains(event.target) returns true, so the value will be toggled.
         */
        this.isOpen = this.elRef.nativeElement.contains(event.target) ? !this.isOpen : false;
    }

    constructor(private elRef: ElementRef, private renderer: Renderer2) {}

    ngOnInit(): void{}
}

/**
 * or better use @HostBinding('class.open') isOpen = false; and
 *    @HostListener('click') onClicked(eventData: Event): void {
 *      this.isOpen = !this.isOpen;
 *    }
 *
 *    to toggle the class when clicked anywhere on the document, use:
 *    @HostListener('document:click', ['$event']) toggleOpen(event: Event) {
 *       this.isOpen = this.elRef.nativeElement.contains(event.target) ? !this.isOpen : false;
 *    }
 */

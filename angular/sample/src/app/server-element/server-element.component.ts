import {
  Component, OnInit, Input, OnChanges, SimpleChanges, DoCheck,
  AfterContentInit, AfterContentChecked, AfterViewChecked, AfterViewInit, OnDestroy
} from '@angular/core';

@Component({
  selector: 'app-server-element',
  templateUrl: './server-element.component.html',
  styleUrls: ['./server-element.component.css']
})
export class ServerElementComponent implements OnInit, OnChanges, DoCheck, AfterContentInit, AfterContentChecked,
AfterViewChecked, AfterViewInit, OnDestroy {
  /**
   * creating an input property which we bind to a TSExpression in app.component.html
   * here the {type: string, name: string, content: string} is a way to tell TS that element is a javascript object
   * with type, name and content keys.
   *
   * 'srvElement' is just an alias by which the property will be known outside (in the app Component). It is optional.
   * If we dont give alias, then outside also it will be known by the same name.
   */
  @Input('srvElement') element: { type: string, name: string, content: string };
  @Input('elementName') name: string;

  constructor() {
    console.log('ctor called');
  }

  ngOnChanges(changes: SimpleChanges): void {
    console.log('onChanges called', changes);
  }

  ngOnInit(): void {
    console.log('ngOnInit called');
  }

  ngDoCheck(): void {
    console.log('ngDoCheck called');
  }

  ngAfterContentInit() {
    console.log('ngAfterContentInit called');
  }

  ngAfterContentChecked() {
    console.log('ngAfterContentChecked called');
  }

  ngAfterViewInit() {
    console.log('ngAfterViewInit called');
  }

  ngAfterViewChecked() {
    console.log('ngAfterViewChecked called');
  }

  ngOnDestroy() {
    console.log('ngOnDestroy called');
  }
}

import { Component, OnInit, Input } from '@angular/core';

@Component({
  selector: 'app-server-element',
  templateUrl: './server-element.component.html',
  styleUrls: ['./server-element.component.css']
})
export class ServerElementComponent implements OnInit {
  /**
   * creating an input property which we bind to a TSExpression in app.component.html
   * here the {type: string, name: string, content: string} is a way to tell TS that element is a javascript object
   * with type, name and content keys.
   *
   * 'srvElement' is just an alias by which the property will be known outside (in the app Component). It is optional.
   * If we dont give alias, then outside also it will be known by the same name.
   */
  @Input('srvElement') element: {type: string, name: string, content: string};
  constructor() { }

  ngOnInit(): void {
  }

}

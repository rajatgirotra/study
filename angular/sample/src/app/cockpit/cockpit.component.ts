import {Component, OnInit, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-cockpit',
  templateUrl: './cockpit.component.html',
  styleUrls: ['./cockpit.component.css']
})
export class CockpitComponent implements OnInit {
  @Output() serverCreated = new EventEmitter<{serverName: string, serverContent: string}>();
  @Output() blueprintCreated = new EventEmitter<{serverName: string, serverContent: string}>();
  newServerName = '';
  newServerContent = '';

  constructor() { }

  ngOnInit(): void {
  }

  // tslint:disable-next-line:typedef
  onAddServer(inputElement: HTMLInputElement) {
    this.serverCreated.emit({serverName: inputElement.value, serverContent: this.newServerContent});
  }

  // tslint:disable-next-line:typedef
  onAddBlueprint(inputElement: HTMLInputElement) {
    this.blueprintCreated.emit({serverName: inputElement.value, serverContent: this.newServerContent});  }
}

import {Component, OnInit, Output, EventEmitter, ViewChild, ElementRef} from '@angular/core';

@Component({
  selector: 'app-cockpit',
  templateUrl: './cockpit.component.html',
  styleUrls: ['./cockpit.component.css']
})
export class CockpitComponent implements OnInit {
  @Output() serverCreated = new EventEmitter<{serverName: string, serverContent: string}>();
  @Output() blueprintCreated = new EventEmitter<{serverName: string, serverContent: string}>();
  @ViewChild('serverContentElement', {static: true}) serverContent: ElementRef;
  // newServerName = '';
  // newServerContent = '';

  constructor() { }

  ngOnInit(): void {
  }

  // tslint:disable-next-line:typedef
  onAddServer(serverNameElement: HTMLInputElement) {
    this.serverCreated.emit({serverName: serverNameElement.value, serverContent: this.serverContent.nativeElement.value});
  }

  // tslint:disable-next-line:typedef
  onAddBlueprint(serverNameElement: HTMLInputElement) {
    this.blueprintCreated.emit({serverName: serverNameElement.value, serverContent: this.serverContent.nativeElement.value});
  }
}

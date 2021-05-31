import {Input, OnInit, Output, EventEmitter, Component} from '@angular/core';

@Component({
    selector: 'app-alert',
    templateUrl: './alert.component.html',
    styleUrls: ['./alert.component.css']
})
export class AlertComponent implements OnInit {

    @Input() message: string = null;
    @Output() closeError = new EventEmitter<void>();

    ngOnInit(): void {
    }

    onClose(): void {
        this.closeError.emit();
    }
}

/**
 * This is just a simple component to display an overlay page with an error. We can show this overlay depending on whether we get any error
 * on login from firebase. this can be done easily using *ngIf. However there is also a way to add/remove components dynamically i.e
 * from typescript code.
 * We are only showing the way for completeness though practically most uses cases can be solved just using *ngIf.
 */

import {Component, OnInit, EventEmitter, Output} from '@angular/core';

@Component({
    selector: 'app-header',
    templateUrl: './header.component.html',
    styleUrls: ['./header.component.css']
})
export class HeaderComponent implements OnInit {
    @Output() showRecipesComponent = new EventEmitter<boolean>();
    constructor() {
    }

    ngOnInit(): void {
        this.showRecipesComponent.emit(true);
    }

    onHeaderSelect(event: boolean) {
        this.showRecipesComponent.emit(event);
    }
}

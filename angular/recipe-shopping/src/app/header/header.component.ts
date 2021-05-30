import {Component, OnInit, EventEmitter, Output, OnDestroy} from '@angular/core';
import {DataStorageService} from '../shared/data-storage.service';
import {Observable, Subscription} from 'rxjs';
import {AuthService} from '../auth/auth.service';
import {userError} from '@angular/compiler-cli/src/transformers/util';
import {User} from '../auth/user.model';

@Component({
    selector: 'app-header',
    templateUrl: './header.component.html',
    styleUrls: ['./header.component.css']
})
export class HeaderComponent implements OnInit, OnDestroy {
    private userSub = new Subscription();
    isAuthenticated = false;
    constructor(private httpRecipeService: DataStorageService, private authService: AuthService) {
    }

    ngOnInit(): void {
         this.userSub = this.authService.user.subscribe(
             user => {
                 this.isAuthenticated = !!user;
             }
         );
    }

    ngOnDestroy(): void {
        if (this.userSub) {
            this.userSub.unsubscribe();
        }
     }

    onSaveData(): void {
         this.httpRecipeService.saveRecipes();
    }

    onFetchData(): void {
         this.httpRecipeService.fetchRecipes().subscribe();
     }

    onLogout(): void {
        this.authService.logout();
    }
}

import {ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot, UrlTree} from '@angular/router';
import {Observable} from 'rxjs';
import {AuthService} from './auth.service';
import {map, take} from 'rxjs/operators';
import {Injectable} from '@angular/core';

@Injectable({
    providedIn: 'root'
})
export class AuthGuard implements CanActivate {
    constructor(private authService: AuthService, private router: Router) {
    }

    canActivate(route: ActivatedRouteSnapshot, state: RouterStateSnapshot):
        Observable<boolean | UrlTree> | Promise<boolean | UrlTree> | boolean | UrlTree {
        /**
         * if authService.user is not null, we canActivate can return tree, otherwise we return a UrlTree created using router object.
         * UrlTree takes a list of routes that this request can be re-routed to.
         */
        return this.authService.user.pipe(take(1), map(
            user => {
                const isAuth = !!user; // user is BehaviourSubject with initial value as null.
                console.log('isAuth', isAuth);
                if (isAuth) {
                    return true;
                } else {
                    return this.router.createUrlTree(['/auth']); // redirect to auth page
                }
            }
        ));
    }
}

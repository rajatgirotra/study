import {Router, RouterModule, Routes} from '@angular/router';
import {HomeComponent} from './home/home.component';
import {UsersComponent} from './users/users.component';
import {UserComponent} from './users/user/user.component';
import {ServersComponent} from './servers/servers.component';
import {ServerComponent} from './servers/server/server.component';
import {EditServerComponent} from './servers/edit-server/edit-server.component';
import {PageNotFoundComponent} from './page-not-found/page-not-found.component';
import {NgModule} from '@angular/core';
import {AuthGuard} from './auth-guard.service';
import {CanDeactivateGuard} from './servers/edit-server/can-deactivate-guard.service';
import {ErrorPageComponent} from './error-page/error-page.component';
import {ServerResolver} from './servers/server/server-resolver.service';

const appRoutes: Routes = [
    { path: '', component: HomeComponent },
    { path: 'users', component: UsersComponent, children: [
            { path: ':id/:name', component: UserComponent }
        ] },
    { path: 'servers', canActivateChild: [AuthGuard], component: ServersComponent, children: [
            { path: ':id', component: ServerComponent, resolve: {server: ServerResolver} },
            { path: ':id/edit', component: EditServerComponent, canDeactivate: [CanDeactivateGuard]}
        ] },
    // { path: 'not-found', component: PageNotFoundComponent },
    { path: 'not-found', component: ErrorPageComponent, data: {message: 'This page is not found!'} },
    { path: '**', redirectTo: '/not-found' }, /** Read about pathMatch option also */

];

@NgModule({
    imports: [
        // RouterModule.forRoot(appRoutes, {useHash: true})
        RouterModule.forRoot(appRoutes)
    ],

    exports: [
        RouterModule
    ]
})
export class AppRoutingModule {}

/**
 * what is RouterModule.forRoot(appRoutes, {useHash: true})
 * When you run your app in a production web server, the web server only sees your apps index.html file. That's because all routes are managed
 * by angular, not the webserver. So when you go to http://yourwebdomain.com/servers, the production web server like nginx will say i dont know
 * this route, so it will return the 404 error page.
 * The way around this is that always configure your web server to return the index.html for 404 error. that way the web server will find the
 * index.html and angular will take over.
 *
 * But if your web server doesnt support it, you can use the {useHash: true} technique. what this does is that angular converts all your routes to like
 * http://yourwebdomain.com/#/servers , i.e it introduces a #. Now all web servers know that if there is a # in the route they will only parse
 * everything before the route and everything after the route will be parsed by the application. So that's another way.
 */

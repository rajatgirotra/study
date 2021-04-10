import {Component} from '@angular/core';

/**
 * need to add a Component decorator to tell angular that ServerComponent is not just a normal TypeScript class, its a component. The
 * component decorator needs to be passed some metadata as a javascript object so that angular knows what to do with it or how to use it.
 *
 * selector: some unique element with which you are able to load your component html.
 */
@Component({
    selector: 'app-server',
    // selector: '[app-server]', // selector is not an element now, it is an html tag attribute
    templateUrl: './server.component.html',
    styles: [`
        .online {
            color: white;
        }
    `]
})
export class ServerComponent {
    serverId: number = 10;
    serverStatus: string = Math.random() > 0.5 ? 'offline' : 'online';

    // tslint:disable-next-line:typedef
    getServerStatus() {
        return this.serverStatus;
    }

    getColor() {
        return this.serverStatus === 'online' ? 'green' : 'red';
    }
}
/**
 * just a TypeScript class. the reason we need to export it is so angular can find an instantiate it.
 */


/**
 * Now that our component is ready, we need to add it to our module. i.e the AppModule.
 * an angular module is a way for angular to pack certain feature and functionality. So here we want to bundle up our ServerComponent in our AppModule.
 */

/**
 * Also the selector doesnt have to only as HTML element.
 * a selector can also be an XML tag attribute or even a css class.
 */

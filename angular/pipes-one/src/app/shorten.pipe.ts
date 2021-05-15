/**
 * creating a user defined pipe is trivial just implement transform() function from PipeTransform interface
 */
import {Pipe, PipeTransform} from '@angular/core';

@Pipe({
    name: 'shorten'
})
export class ShortenPipe implements PipeTransform {
    transform(value: any, ...args): any {
        if (value.length > 10) {
            return value.substr(0, 10) + ' ...';
        } else {
            return value;
        }
    }
}

/**
 * Add it to declarations in app.module.ts
 */

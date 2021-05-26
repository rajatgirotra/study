import {HttpEvent, HttpEventType, HttpHandler, HttpInterceptor, HttpRequest} from "@angular/common/http";
import {Observable} from "rxjs";
import {tap} from "rxjs/operators";

export class LoggingInterceptorService implements HttpInterceptor {
    intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
        // just log and dont touch the request
        console.log('outgoing request', req.url);
        return next.handle(req).pipe(tap(event => {
            if(event.type === HttpEventType.Response) {
                console.log('incoming response', event.body);
            }
        }));
    }
}

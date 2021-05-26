import {HttpEvent, HttpEventType, HttpHandler, HttpInterceptor, HttpRequest} from "@angular/common/http";
import {Observable} from "rxjs";
import {tap} from "rxjs/operators";

export class AuthInterceptorService implements HttpInterceptor {
    intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
        // console.log('request is on its way!');
        // req object is immutable
        const modifiedRequest = req.clone({
            headers: req.headers.append('Auth', 'XYZ')
        });
        return next.handle(modifiedRequest).pipe(tap(event => {
            /**
             * with interceptor, remember no matter what is the responseType set on the request. body, response, event.
             * interceptors will always return event.
             */
            console.log(event);
            if(event.type === HttpEventType.Response) {
                ;
                // console.log('response arrived', event.body);
            }
        }));
    }
}

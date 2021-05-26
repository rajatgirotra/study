import {Injectable} from "@angular/core";
import {HttpClient, HttpEventType, HttpHeaders, HttpParams} from "@angular/common/http";
import {Post} from "./post.model";
import {map, catchError, tap} from "rxjs/operators";
import {Observable, Subject, throwError} from "rxjs";

@Injectable({
    providedIn: 'root'
})
export class PostsService {
    errorObservable = new Subject<string>();
    constructor(private http: HttpClient) {
    }

    fetchPosts() {
        let searchParams = new HttpParams();
        searchParams = searchParams.append('print', 'pretty');
        searchParams = searchParams.append('custom', 'key');
        return this.http
            .get<{[key: string]: Post}>('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json',
                {
                    headers: new HttpHeaders({
                        'Custom-Header': 'Hello'
                    }),
                    params: searchParams,
                    observe: 'response'
                }
            )
            .pipe(
                map(responseData => {
                    const postsArray: Post[] = [];
                    for (const key in responseData.body) {
                        if (responseData.body.hasOwnProperty(key)) {
                            postsArray.push({ ...responseData.body[key], id: key});
                        }
                    }
                    return postsArray;
                }),
                // Just like map is an operator to transform responseData, catchError is an operator used to transform error messages.
                catchError(errorResponse => {
                    // do whatever. some analytics etc. may be just log it and then throwError again to be caught by the caller.
                    console.log(errorResponse);
                    // throwError is a function which yields an Observable that wraps an error.
                    return throwError(errorResponse);
                })
            );
    }

    createPost(postData: Post) {
        this.http
            .post<{name: string}>('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json',
                postData).subscribe(
            (responseData) => {
                // resoponseData is the response body. Lets log it for now.
                console.log(responseData);
            },
            error => {
                this.errorObservable.next(error.message);
            }
        );
    }

    deletePosts() {
        return this.http.delete('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json',
            {
                observe: 'events'
            })
            .pipe(tap(event => {
                console.log(event);
                if(event.type === HttpEventType.Sent) {

                } else if(event.type === HttpEventType.Response) {
                    // console.log(event.body);
                }
            }));
    }
}

/**
 * Setting headers on http get, put, post, delete etc is trivial. All these methods take an object as an "options" argument
 * and there you can set the headers as shown above. Similarly you can set query string parameters as well.
 *
 * When you make an HTTP request, by default angular pulls out the response body and returns you that inside the Observable.
 * However you can pass extra arguments to http request and get back the full response including the header.
 * this argument is observe: and its value can be "body", "response" or "events"
 *
 * tap() is just another operator that doesnt alter/transform its argument. So this operator doesnt need to return anything.
 * Just use it but dont alter it.
 *
 * similar to observe, you have responseType property which can be json, text, blob which tells what will be the return type
 * of the response body. Use it in cases where you expect text, or blob in return. Default is json.
 *
 * Interceptors
 * ============
 * Interceptors are Services that you write and which can modify your outgoing HTTP requests in a non-intrusive way.
 * The way it works is that you create a class which derives from HttpInterceptor and override the intercept() method
 * the intercept(req, next) gets two arguments. the HTTP request and an HTTPHandler object. You must modify the req
 * and call next.handle(req) for the request to travel further out. otherwise your API will fail.
 *
 * To use it now, you need to register your Interceptor Service in app.module.ts in providers array but slightly differently.
 * You need to register it like
 * {
 *     provide: HTTP_INTERCEPTORS, // this is a tag which tells Angular that the useClass below is an HTTP Interceptor so I must apply it
 *     useClass: <Your Service class name>,
 *     multi: true // to tell angular that there can be multiple such interceptors.
 * }
 *
 * The most common use case is for SingleSignOn. All your requests should be routed to SSO first and authenticated from there.
 *
 * Just like Request Interceptors, you have Response Interceptor.
 * the next.handle(request) return an Observable. You can think of this as the observable on which you will get back response.
 */

import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { map } from 'rxjs/operators';
import {Post} from "./pos.model";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  loadedPosts: Post[] = [];
  isFetching = false;

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.fetchPosts();
  }

  onCreatePost(postData: { title: string; content: string }) {
    // Send Http request
    // const url = 'https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/'

    // nothing happens if you dont subscribe
    // this.http.post('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json', postData);

    this.http
        .post<{name: string}>('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json',
        postData).subscribe(
        (responseData) => {
          // resoponseData is the response body. Lets log it for now.
          console.log(responseData);
        }
    );
    // console.log(postData);
  }

  onFetchPosts() {
    // Send Http request
    this.fetchPosts();
  }

  onClearPosts() {
    // Send Http request
  }

  private fetchPosts() {
      this.isFetching = true;
      this.http
        .get<{[key: string]: Post}>('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json')
        .pipe(
            map(responseData => {
                const postsArray: Post[] = [];
                for (const key in responseData) {
                    if (responseData.hasOwnProperty(key)) {
                        postsArray.push({ ...responseData[key], id: key});
                    }
                }
                return postsArray;
            })
        )
        .subscribe(posts => {
            // simulate sleep to see Loading.. on front end
            this.isFetching = false;
            this.loadedPosts = posts;
            // console.log(posts);
        }
    );
  }
}

/**
 * To send http requests to a server, you need to import the HttpClientModule in app.module.ts. After that you need to
 * import HttpClient service in your TypeScript file and inject it in your class constructor. Then use the this.http.get/post/put/delete etc
 * functions to send an http request. all these methods are named after the http verb (i.e. request type).
 * Also these functions return you an Observable. If you dont subscribe to the observables, Angular assumes that you are not
 * interested in the request, so it never sends a request. You can see that in Network tab in developer tools.
 *
 * Also in our case, since we are working with firebase backend, you dont need to create any explicit endpoints.
 * whichever end point you send a post request to, firebase will create a folder with that endpoint name in the firebase
 * database you created for your project. Lets try now.
 *
 * Angular will also by default look at your javascript object postData and automatically convert to Json and the post request
 * will be sent. Also there are two posts requests being made(you can view in your browser). First is request type OPTIONS
 * which is sent to check if POST request is allowed. Then the second request with request type POST is sent.
 *
 * Also note that post<> is a generic function so we specify the return type of the responseData there.
 *
 * To make a GET request, we use this.http.get(). We use that here to get all the posts that we have originally stored using
 * this.http.post(). We do that inside a private method of the class to make it re-usable. Firebase returns the posts as
 * a javascript object where key is the unique key for your post as created by firebase and value is another javascript object
 * with title and content. example: {key1: {title: '', content: ''}, key2: {title: '', content: ''}}
 *
 * We need to flatten this out and create an array instead like: [ {id: key1, title: '', content: ''}, {id: key2, title: '', content: ''}]
 * So what we do is use a map() operator to transform the responseData and store the posts in an array.
 * Note that get<> is a template function so we specify the return type of responseData inside the <> brackets in get() function call.
 *
 */

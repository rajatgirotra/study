import {Injectable} from "@angular/core";
import {HttpClient} from "@angular/common/http";
import {Post} from "./pos.model";
import {map} from "rxjs/operators";
import {Observable} from "rxjs";

@Injectable({
    providedIn: 'root'
})
export class PostsService {
    constructor(private http: HttpClient) {
    }

    fetchPosts() {
        return this.http
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
            );
    }

    createPost(postData: Post) {
        this.http
            .post<{name: string}>('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json',
                postData).subscribe(
            (responseData) => {
                // resoponseData is the response body. Lets log it for now.
                console.log(responseData);
            }
        );
    }

    deletePosts() {
        return this.http.delete('https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/posts.json');
    }
}

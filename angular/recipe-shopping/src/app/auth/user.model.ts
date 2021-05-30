export class User {
    constructor(public email: string, public userId: string,
                private _token: string, private _tokenExpiryDate: Date) {
    }

    /**
     * writing get infront of a function makes it a property. just like python property. you can read its value using
     * let token = user.token
     * This is a getter property. later we will see how to get setter properties also.
     */
    get token() {
        if (!this._tokenExpiryDate || new Date() >= this._tokenExpiryDate) {
            return null;
        }
        return this._token;
    }
}

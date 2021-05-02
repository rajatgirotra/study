import {Injectable} from '@angular/core';

@Injectable({
    providedIn: 'root'
})
export class CounterService {
    activeCount = 0;
    inactiveCount = 0;

    incrementActiveCount(): void {
        ++this.activeCount;
        console.log('active count ' + this.activeCount);
    }

    incrementInactiveCount(): void {
        ++this.inactiveCount;
        console.log('inactive count ' + this.inactiveCount);
    }
}

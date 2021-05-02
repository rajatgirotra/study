import {Component, OnInit, Output, EventEmitter} from '@angular/core';

@Component({
  selector: 'app-game-control',
  templateUrl: './game-control.component.html',
  styleUrls: ['./game-control.component.css']
})
export class GameControlComponent implements OnInit {
  gameOn = false;
  game = 0;
  eventNumber = 0;

  @Output() gameEvent = new EventEmitter<{eventNumber: number}>();
  constructor() { }

  ngOnInit(): void {
  }

  onGameStart() {
      this.game = setInterval(() => {
          // console.log(++this.eventNumber);
          this.gameEvent.emit({eventNumber: ++this.eventNumber});
      }, 1000);
      this.gameOn = true;
  }

  onGameStop() {
    clearInterval(this.game);
    this.gameOn = false;
  }
}

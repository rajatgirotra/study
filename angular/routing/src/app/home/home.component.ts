import { Component, OnInit } from '@angular/core';
import {Router} from '@angular/router';
import {AuthService} from '../auth.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {

  constructor(private router: Router, private authService: AuthService) { }

  ngOnInit(): void {
  }

  onLoadServers(id: number): void {
    this.router.navigate(['/servers', id, 'edit'], {queryParams: {allowEdit: 1}, fragment: 'loading'});
  }

  onLogin(): void {
    this.authService.login();
  }

  onLogout(): void {
    this.authService.logout();
  }
}

/**
 * We will also learn about Routing Guards. Routing Guards are functions which can be executed before you enter a route and after you exit
 * a route. You can execute any code here. Like you only want users to enter a route after they have successfully logged in.
 * We need to implement CanActivate interface for that. lets do that for the servers main component and the servers child components
 * using CanActivateChild.
 *
 * After you implement CanActivate we will also implement CanDeactivate which is used to decide if a user can leave a route safely.
 * This is used when say a user modifies some data on a form but hasn't saved the changes. Then if he tries to navigate away you can alert
 * the user that his changes would be lost.
 */

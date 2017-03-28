var person = 'Tony';

//logPerson(); /* When logPerson is called, it has already overriden person variable in 4_steve.js */
             /* To solve this use namespaces. */

stevesApp.logPerson(); // This should show steve in console.

#!/usr/bin/env python3
## Handling exceptions. Very trivial. Use a try except block as shown below.

while True :
   try :
      x = int(input('Enter a valid integer: '))
      break;
   except ValueError:
      print("Oops.. that wasn't a vadlid integer.. try again.. or Control-C to exit !")
   except KeyboardInterrupt:
      break;



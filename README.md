# eduroam
Script that checks the internet connection every 15 seconds. If the test fails, the script disconnets the laptop from eduroam and connects to it again. This script has only one aim : fix the Italian eduroam who crashs often.

To compile :
```console
g++ -o eduroam.exe eduroam.cpp
```

## Known problems
Sometimes, disconnecting and connecting from eduroam isn't engouh. The script should be able to forget the network and to log in again (a fix was implemented but has not been tested yet).


## Releases
### Version 1
The script functions (ping google.com and writes the result in `eduroam.tmp`) but doesn't prompt anything. The script stops itself after 6 PM because we stop to work after 5 PM.

### Version 2
The script prompts whatever he does. The number of ping to Google went done from 4 to 1 (the scripts could take some times before to understand that it wasn't connected to the internet before).

### Version 3
Change the ping by curl, because it is faster and more reliable. 

If the connection test fails five times in a row, it will forget the eduroam network and log in to it again thanks to `eduraom.xml` (**feature not tested !**).
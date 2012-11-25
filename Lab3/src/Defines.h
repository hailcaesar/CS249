/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _DEFINES_H
#define _DEFINES_H

#ifdef DEBUG_1
#define debug  cout
#else
#define debug  cerr
#endif

#ifdef DEBUG_2
#define debug2 cerr
#else
#define debug2 0 && cout
#endif

#ifdef DEBUG
#define DCOUT(stream) (cerr << stream)
#else
#define DCOUT(stream)
#endif


#endif

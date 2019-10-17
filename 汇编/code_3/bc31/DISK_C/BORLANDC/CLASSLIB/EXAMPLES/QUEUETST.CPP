#ifndef __LTIME_H
#include <LTime.h>
#endif	// __LTIME_H

#ifndef __QUEUE_H
#include <Queue.h>
#endif	// __QUEUE_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

#ifndef __DOS_H
#include <dos.h>
#endif

#ifndef __STDLIB_H
#include <stdlib.h>
#endif


int main()

{


    int k;
    Queue timeLine;
    cout << "\nSampling";
    for( int i = 0; i < 7; i++ )
	{
	struct time snapShot;
	gettime( &snapShot );
	Time sample( snapShot.ti_hour,
		     snapShot.ti_min,
		     snapShot.ti_sec,
		     snapShot.ti_hund );
	timeLine.put ( *(new Time( sample )) );
	cout << ".";
	randomize();
	k = rand();
	for(int j = 0; j < k; ++j )  // Delay loop
	     {
	     cout << "";
	     }
	}
    cout << "\nThe timing samples are:\n\n";
    while( !timeLine.isEmpty() )
	{
	Time& sampleTime = (Time&)timeLine.get();
	cout << sampleTime << "\n";
	delete &sampleTime;
	}
    return 0;
}

/*
 * event.h
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_


typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
Event (IVTNo ivtNo);
~Event();
void wait ();

friend class KernelEv;

void signal(); // can call KernelEv
private:
KernelEv* myImpl;

};
//Prepareentry za zamjenu ulaza zaljenom rutinom
#define PREPAREENTRY(numEntry,callOld)\
void interrupt inter##numEntry(...);\
IVTEntry newEntry##numEntry(numEntry,inter##numEntry);\
void interrupt inter##numEntry(...){\
		newEntry##numEntry.signal();\
		if(callOld==1)\
			newEntry##numEntry.callOldRoutine();\
		}


#endif /* EVENT_H_ */

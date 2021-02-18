/*
 * Semafor.h
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_



typedef unsigned int Time;
class Kersem;
class Semaphore {
public:
 Semaphore (int init=1);
virtual ~Semaphore ();
 virtual int wait (Time maxTimeToWait=0);
 virtual int signal(int n=0);
 int val () const; // Returns the current value of the semaphore
private:
 Kersem* myImpl;
};

#endif /* SEMAPHOR_H_ */

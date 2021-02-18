/*
 * PCB.h
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
class Thread;
class List;
class Kersem;
class PCB {
friend class IVTEntry;
public:
	PCB(const unsigned long ssize,unsigned int time, Thread * myThread);
	virtual ~PCB();
	int getId();
	static int getRunningId();
private:
	friend void inic();
	void put(PCB*p);
	int fleg;
	unsigned long size;
	unsigned scs,sip;
	unsigned int infinity;
	unsigned int wasSignal;

	unsigned int time;
	Thread *myThread;
	unsigned *stack;
	unsigned sp,ss;
	PCB* parent;
	static PCB* running;
	static int idGive;
	static PCB* allPCBs[105];
	int Id;
	Kersem *blockOnSem;
	List *waitFor;
	static void wrapper();
	static void sigwrapper();
	friend class Thread;
	friend class Kersem;
	friend class Sleep;
	friend class Semaphore;
	friend void interrupt timer();
};

#endif /* PCB_H_ */

/*
 * thread.h
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef void(*SignalHandler)();
typedef unsigned SignalId;
struct sig{//Pomocna lista za smijestanje signala;
	SignalId id;
	SignalHandler sh;
	struct sig* next;
	sig(SignalId i,SignalHandler s):id(i),sh(s),next(0){}
};
struct listSig{
	int id;
	struct listSig*next;
	listSig(int i):id(i),next(0){

	}

};
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB; // Kernel's implementation of a user's thread
class Thread {
public:
	friend void inic();
 void start();
 void waitToComplete();
 virtual ~Thread();
 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id);
protected:
 friend class PCB;
 Thread (StackSize stackSize = defaultStackSize, Time timeSlice =
defaultTimeSlice);
 virtual void run() {}
public:
 void unblockSignal(SignalId signal);
 void blockSignal(SignalId signal){
	 mysignal[signal]=0;
 }
 static void blockSignalGlobally(SignalId signal){

	 globalsignal[signal]=0;
 }
  static void unblockSignalGlobally(SignalId signal);
  void doSignals();
  void signal(SignalId signal);
  void registerHandler(SignalId signal,SignalHandler handler);
  void swap(SignalId signal,SignalHandler hand1,SignalHandler hand2);
  void unregisterAllHandlers(SignalId id);
private:
  struct listSig *prvi,*poslednji;
  struct listSig *prviCek,*poslednjiCek;
  friend void interrupt timer();
 PCB* myPCB;
 int mysignal[16];
    static int globalsignal[16];

  struct sig *first[16],*last[16];
};
void dispatch ();



#endif /* THREAD_H_ */

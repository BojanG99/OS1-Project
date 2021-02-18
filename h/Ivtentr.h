/*
 * Ivtpentr.h
 *
 *  Created on: Apr 15, 2020
 *      Author: OS1
 */

#ifndef IVTENTR_H_
#define IVTENTR_H_
#include"Kernelev.h"
#include"Kersem.h"

class Kersem;
class IVTEntry;
class KernelEv;



typedef void interrupt(*pInterrupt)(...);

class IVTEntry{
public:

static IVTEntry *allIVTEntry[257];
	IVTEntry(IVTNo ivtn,void interrupt (*internum)(...));
void signal();

~IVTEntry();
pInterrupt old;
void callOldRoutine();
friend class KernelEv;
private:
void wait();




IVTNo num;
KernelEv *mzke;
Kersem *ks;
PCB *myPcb;
};


#endif /* IVTENTR_H_ */

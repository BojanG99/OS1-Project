/*
 * Kernelev.h
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include <iostream.h>
#include"event.h"
#include <dos.h>

class PCB;



class KernelEv {
public:
KernelEv(IVTNo ivtnum);
~KernelEv(){}

void wait();
void signal();
private:
IVTNo numEntry;
PCB * myPcb;
};




#endif /* KERNELEV_H_ */

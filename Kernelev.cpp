/*
 * Kernelev.cpp
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */
#include"Kernelev.h"
#include"Ivtentr.h"


KernelEv::KernelEv(unsigned char ivtnum):numEntry(ivtnum){
	//PREPEEREENTRY(ivtnum,0);
IVTEntry::allIVTEntry[numEntry]->mzke=this;






	//unsigned tcs=FP_SEG(inter##ivtnum);
//	unsigned tip=FP_OFF(inter##ivtnum);


}

void KernelEv::signal(){
	IVTEntry::allIVTEntry[numEntry]->signal();

}
void KernelEv::wait(){
	IVTEntry::allIVTEntry[numEntry]->wait();

}

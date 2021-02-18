/*
 * Ivtpentr.cpp
 *
 *  Created on: Apr 15, 2020
 *      Author: OS1
 */


#include "Ivtentr.h"
#include"Pcb.h"
#include<dos.h>
#include"thread.h"


IVTEntry * IVTEntry::allIVTEntry[257]={0};

IVTEntry::IVTEntry(IVTNo ivtn,void interrupt (*internum)(...)):num(ivtn){

	myPcb=PCB::running;
	ks=new Kersem(0);

allIVTEntry[num]=this;
	//niz(num)=this;
 old=getvect(num);
 setvect(num,internum);


}
void IVTEntry::wait(){
if(PCB::running==myPcb)
	ks->wait();
}
void IVTEntry::signal(){
//	if(PCB::running==myPcb)
	ks->signal();
}
IVTEntry::~IVTEntry () {



	setvect(num,old);
allIVTEntry[num]=0;
	//niz(num)=0;
	delete mzke;
//	delete Thread::allThreads[myPcb->getpcbID()];

}


void IVTEntry::callOldRoutine(){

old();
}





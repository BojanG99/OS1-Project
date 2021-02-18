/*
 * PCB.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include"thread.h"
#include<dos.h>
#include"List.h"
#include<iostream.h>
#include"SCHEDULE.H"
PCB* PCB::running=0;
int PCB::idGive=0;

PCB::PCB(const unsigned long ssize1,unsigned int time,Thread * myThread) {
	// TODO Auto-generated constructor stub
	infinity=0;
	wasSignal=0;
fleg=2;
sip=FP_OFF(sigwrapper);
scs=FP_SEG(sigwrapper);
this->myThread=myThread;
const unsigned long ssize=ssize1/sizeof(unsigned);
stack=new unsigned[ssize];
parent=PCB::running;
Id=idGive++;
waitFor=0;
blockOnSem=0;
size=ssize;
this->time=time;
sp=FP_OFF(stack+ssize-16);
ss=FP_SEG(stack+ssize-16);
stack[ssize-5]=0x200;
stack[ssize-6]=FP_SEG(wrapper);
stack[ssize-7]=FP_OFF(PCB::wrapper);
stack[ssize-8]=0;//ax
stack[ssize-9]=0;//bx
stack[ssize-10]=0;//cx
stack[ssize-11]=0;//dx
stack[ssize-12]=0;//es
stack[ssize-13]=0;//ds
stack[ssize-14]=0;//si
stack[ssize-15]=0;//di
stack[ssize-16]=sp;//bp
allPCBs[Id]=this;

}
PCB* PCB::allPCBs[105]={0};
PCB::~PCB() {
	// TODO Auto-generated destructor stub
	delete []stack;
}
void PCB::sigwrapper(){
	PCB::running->myThread->doSignals();

	PCB::running->wasSignal=1;
	dispatch();
}

void PCB::wrapper(){

	PCB::running->myThread->run();
	PCB::running->myThread->signal(2);
	if(PCB::running->parent)PCB::running->parent->myThread->signal(1);
	asm cli




	        PCB::running->fleg=(4);

	        if(PCB::running->waitFor){//oslobadja sve niti koji su je cekali
	        	List *pom=PCB::running->waitFor->next;
	        	while(PCB::running->waitFor){
	        		PCB::running->waitFor->pcb->fleg=(2);
	        		Scheduler::put(PCB::running->waitFor->pcb);
	     //   		cout<<"Ubacen\n";
	        		delete PCB::running->waitFor;

	        		PCB::running->waitFor=pom;
	        		if(pom)pom=pom->next;
	        	}

	        }



//cout<<"gotovo";
				dispatch();

		asm sti
}
int PCB::getId(){
	return Id;
}
int PCB::getRunningId(){
	return running->getId();
}
void PCB::put(PCB *p){
	List *l=new List(p);
	l->next=this->waitFor;
	this->waitFor=l;

}

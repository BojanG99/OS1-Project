/*
 * Kersem.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: OS1
 */




#include "Kersem.h"

#include"Pcb.h"
#include<schedule.h>
#include <iostream.h>
#include <dos.h>
#include"thread.h"
Kersem::Kersem(int  init):val(init),first(0),last(0){}

int Kersem::get_val()const{
	return this->val;
}
void Kersem::put(PCB *p){
	struct cvor *novi=new cvor(p);


	if(first==0){

		first=novi;
		last=novi;

	}
	else{
		last->next=novi;
		last=novi;
	}


}

PCB* Kersem::get(){
	if(first!=0){
	struct cvor *old=0;
	struct cvor* vrati=first;
	first=first->next;
	if(first==0)last=0;//alokaciju treba odraditi
  PCB* ret=vrati->pcb;
  vrati->pcb=0;
  vrati->next=0;
  delete vrati;
	return ret;
	}

	return 0;
}


void Kersem::delFromSem(PCB *p){
	struct cvor *old=0;
	struct cvor *pom=first;

	while(pom->pcb!=p){
		old=pom;
		pom=pom->next;
	}
	if(old){
		old->next=pom->next;
	}else first=first->next;//delokacija

	if (pom==last)last=old;
	this->val++;
	pom->next=0;
	pom->pcb=0;
	delete pom;
	p->blockOnSem=0;

}


int Kersem::wait(){
asm cli


	if(--(this->val)<0){

		PCB::running->blockOnSem=this;
		put(PCB::running);
        PCB::running->fleg=(3);
        //cout<<"trece cekanje"<<endl;
        dispatch();
if (PCB::running->fleg==5){


	PCB::running->fleg=(1);

	asm sti

        return 0;

}
	}



asm sti

return 1;
}

int Kersem::signal(){
	asm cli

int ret=0;

	if(++(this->val)<=0){

  PCB*n=get();

  n->fleg=(1);
  n->blockOnSem=0;
   Scheduler::put(n);



asm sti

return ret;

	}else {

		asm sti
		return 0;
	}



}

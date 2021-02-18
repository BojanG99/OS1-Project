/*
 * thread.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */
#include"thread.h"
#include"PCB.h"
#include<iostream.h>
#include"SCHEDULE.H"
#include"List.h"
extern int onDemand;
int Thread::globalsignal[16]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
Thread::Thread(StackSize sS,Time timeSlice){
	prvi=0;
	prviCek=0;
	poslednjiCek=0;
	poslednji=0;
	myPCB=new PCB(sS,timeSlice,this);
	for(int i=0;i<16;i++){
		first[i]=0;
		last[i]=0;

		mysignal[i]=1;
	}
}

void Thread::start(){
Scheduler::put(myPCB);
}
void Thread::waitToComplete(){
if(myPCB->fleg!=4){
	myPCB->put(PCB::running);
//	cout<<"Izbacen";
	PCB::running->fleg=3;
	dispatch();
}
}
ID Thread::getId(){
	return myPCB->getId();
}
ID Thread::getRunningId(){
	return PCB::getRunningId();
}
Thread* Thread::getThreadById(ID id){
	return PCB::allPCBs[id]->myThread;
}
Thread::~Thread(){
delete myPCB;
}


void dispatch(){
	asm cli
onDemand=1;
	timer();

	asm sti

}

void Thread::unblockSignalGlobally(SignalId sig){//otkljucava sve signale globalno i poziva one koji su bili na cekanju
	Thread::globalsignal[sig]=1;
	for(int i=0;i< PCB::idGive;i++)
		if(PCB::allPCBs[i]->myThread->mysignal[sig]==1 ){
		if(PCB::allPCBs[i]->myThread->prviCek){
			if(PCB::allPCBs[i]->myThread->prvi==0)PCB::allPCBs[i]->myThread->prvi=PCB::allPCBs[i]->myThread->prviCek;
			else PCB::allPCBs[i]->myThread->poslednji=PCB::allPCBs[i]->myThread->prviCek;

			PCB::allPCBs[i]->myThread->poslednji=PCB::allPCBs[i]->myThread->poslednjiCek;

			PCB::allPCBs[i]->myThread->prviCek=0;
			PCB::allPCBs[i]->myThread->poslednjiCek=0;
		}
		}

	 }


void Thread::signal(SignalId signal){//provjerava da li se moze odraditi signal
if(mysignal[signal]==1 && globalsignal[signal]==1){
struct listSig *s=new listSig(signal);
if(prvi==0){
	prvi=s;
}
else{
	poslednji->next=s;
}
poslednji=s;
}
else
{
	struct listSig *s=new listSig(signal);
	if(prviCek==0){
		prviCek=s;
	}
	else{
		poslednjiCek->next=s;
	}
	poslednjiCek=s;
}
}
void Thread::doSignals(){//iyvrsava signale
while(prvi){
	int a=prvi->id;
	if(a==0){
		asm cli

		signal(2);
		if(myPCB->parent)
			myPCB->parent->myThread->signal(1);

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

	}else{
	struct sig*tmp=Thread::first[a];
					while (tmp){
						(*(tmp->sh))();
						tmp=tmp->next;
					}
	}

	prvi=prvi->next;

}


			//dozvoli promjenu konteksa
}

void Thread::unregisterAllHandlers(SignalId id){//brise sve hendlere za neki signal
	  struct sig *old=0;

	  while(first[id]){
		  old=first[id];
		  first[id]=first[id]->next;
		  old->sh=0;
		  delete old;
	  }
	  last[id]=0;

}
void Thread::registerHandler(SignalId signal,SignalHandler handler){//ubacuje handler u listu signala signal
asm cli

int a;

	  struct sig * novi=new struct sig(signal,handler);
	  if(first[signal]){
     last[signal]->next=novi;
     last[signal]=novi;
	  	}else{
	  		first[signal]=last[signal]=novi;
	  	}

asm sti
 }

void Thread::swap(SignalId signal,SignalHandler hand1,SignalHandler hand2){//zamjenjuje 2 signala
	  struct sig*oldh1,*oldh2,*tmp,*ph1,*ph2,*pom;
	 oldh1=oldh2= tmp=first[signal];

	 int h1=0,h2=0;
	 if(hand2==hand1)return;
	  while(tmp){
		  if(h1&&h2){
			  if((ph1==oldh2)){

				  if(oldh1){
					  oldh1->next=ph2;
				  }else first[signal]=ph2;

				  ph1->next=ph2->next;
				  ph2->next=ph1;

			  }
			  else if(ph2==oldh1){
				  if(oldh2){
									  oldh2->next=ph1;
								  }else first[signal]=ph1;

								  ph2->next=ph1->next;
								  ph1->next=ph2;

			  }
			  else{
				  if(oldh1){
					  oldh1->next=ph2;
				  }
				  else first[signal]=ph2;
				  if(oldh2){
					  oldh2->next=ph1;
				  }
				  else first[signal]=ph1;
				  pom=ph1->next;
				  ph1->next=ph2->next;
				  ph2->next=pom;

				  if(last[signal]==ph1)last[signal]==ph2;
				  if(last[signal]==ph2)last[signal]==ph1;
			  }


			  break;
		  }
		  else{
		  if(tmp->id==signal){
			  if(tmp->sh==hand1){
				  ph1=tmp;
				  h1=1;
			  }
			  if(tmp->sh==hand2){
				  ph2=tmp;
			 	  h2=1;
			  }

			  if(h1==0){
				  oldh1=tmp;
			  }
			  if(h1==0){
				 oldh2=tmp;
			  }
		  }
		  }

		  tmp=tmp->next;
	  }


  }

void Thread::unblockSignal(SignalId sig){
	mysignal[sig]=1;
	if(mysignal[sig]==1 && globalsignal[sig]==1){
	if(prviCek){
		if(prvi==0)prvi=prviCek;
		else poslednji=prviCek;

		poslednji=poslednjiCek;

		prviCek=0;
		poslednjiCek=0;
	}
	}
}


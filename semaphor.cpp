/*
 * Semafor.cpp
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */
#include"Kersem.h"
#include"Sleep.h"
#include"Pcb.h"
#include "semaphor.h"
class Sleep;
struct sleep1;
Semaphore::Semaphore (int init){//konstruktor

	myImpl=new Kersem(init);


}
int Semaphore::val()const{//vraca vrijednost semafora

	return myImpl->get_val();
}
 Semaphore::~Semaphore(){//destruktor

	 delete myImpl;
 }

 int Semaphore::wait(Time maxTimeToWait){
	 int ret;
	 asm cli

	 if((myImpl->get_val()-1)<0){//ako se nit blokira

if(maxTimeToWait>0){//ubacujemo u sleep
	sleep1 *s=new sleep1(PCB::running,maxTimeToWait);

Sleep::ubaci(s);
}
ret=myImpl->wait();//blokiramo na seemaforu
	 }else{
	//	 cout<<"drugo cekanje";
		ret= myImpl->wait();//smanji za 1 vrijednost
	 }


asm sti
return ret;
 }

 int Semaphore::signal(int n){

if(n==0){//ako je n=0 signal se ponasa uobicajno

	myImpl->signal();
	return 0;
}
else if(n>0){

	int m=0;//broj niti koji se izbaci iz semafora
	for	(int i=0;i<n;i++)if(myImpl->signal())m++;
	return m;
}

return n;
 }

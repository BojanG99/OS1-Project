/*
 * event.cpp
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */


#include"event.h"
#include"Kernelev.h"

Event::Event(IVTNo ivtnum){

	myImpl=new KernelEv(ivtnum);



}
Event::~Event(){
	delete myImpl;
	myImpl=0;
}

void Event::signal(){

	myImpl->signal();
}

void Event::wait(){
	myImpl->wait();
}


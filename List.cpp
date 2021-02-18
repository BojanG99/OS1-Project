/*
 * List.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#include "List.h"

List::List(PCB* pcb) {
	this->pcb=pcb;
	this->opt=0;
		next=0;
	// TODO Auto-generated constructor stub

}
List::List(PCB* pcb,int opt) {
	this->pcb=pcb;
	this->opt=opt;
	next=0;
	// TODO Auto-generated constructor stub

}
List::~List() {
	// TODO Auto-generated destructor stub
	pcb=0;
	next=0;

}


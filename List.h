/*
 * List.h
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
class PCB;
class Thread;
class List {
	List *next;
	int opt;
	PCB*pcb;
public:
friend class PCB;
friend class Thread;
	List(PCB *p);
	List(PCB *p,int opt);
	virtual ~List();
};

#endif /* LIST_H_ */

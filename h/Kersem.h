/*
 * KerSem.h
 *
 *  Created on: Apr 13, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

class PCB;

struct cvor{
	PCB *pcb;
	struct cvor *next;

	cvor(PCB*p):pcb(p),next(0){}

};


class Kersem {
public:
	 struct cvor *first;
	 struct cvor *last;


	Kersem(int init);


	int wait();
	int signal();

int get_val()const;
protected:
	void put(PCB *p);
		PCB* get();
   void delFromSem(PCB *p);
   friend class Sleep;
private:
	int val;


};



#endif /* KERSEM_H_ */

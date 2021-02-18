/*
 * Sleep.h
 *
 *  Created on: Apr 12, 2020
 *      Author: OS1
 */

#ifndef SLEEP_H_
#define SLEEP_H_
class PCB;
struct sleep1{//lista za niti koje cekaju tajmer
	PCB* slp;
	int t;
	struct sleep1 *next;
	sleep1(PCB *pc,int t1):slp(pc),t(t1),next(0){

	}
};
class Sleep{
public:
	friend class PCB;

	static struct sleep1 *first;
	static struct sleep1 *last;

	static void ubaci(sleep1 *s);//ubacuje pcb da ceka
	static void izbacuj();//smanjuje cekanje svih niti za 1

};


#endif /* SLEEP_H_ */

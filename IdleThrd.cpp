/*
 * IdleThrd.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#include "IdleThrd.h"
#include<iostream.h>
IdleThrd::IdleThrd():Thread(1024,1) {
	// TODO Auto-generated constructor stub

}
void IdleThrd::run() {
	while(1);/*{
		for(int i=0;i<30000;i++)
			for(int j=0;j<30000;j++);


		asm cli
		cout<<"i";
		asm sti
	}*/
}
IdleThrd::~IdleThrd() {
	// TODO Auto-generated destructor stub
}


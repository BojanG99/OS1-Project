/*
 * Sleep.cpp
 *
 *  Created on: Apr 12, 2020
 *      Author: OS1
 */
#include"Sleep.h"
#include"schedule.h"
#include"Pcb.h"
#include <iostream.h>
#include <dos.h>
#include"Kersem.h"
void Sleep::izbacuj(){

		struct sleep1 *old=0,*del;
		struct sleep1 *pom=first;
		while (pom!=0){//prolazi korz listu
			if(--(pom->t)==0){//ako je tajmer dosao do 0

				if(old)old->next=pom->next;
				else {
					first=pom->next;

				}
				if (pom==last)last=old;
				//
				if(pom->slp->fleg==3){//ako se odblokirao radi isteka vremena

				pom->slp->fleg=(5);//stavljamo fleg koji oynacava da je odblokiran vremenom
				pom->slp->blockOnSem->delFromSem(pom->slp);//iybrisemo ga iz semafora
				Scheduler::put(pom->slp);//ubacim ga u scheduler
				}
				del=pom;
				pom=pom->next;//predjemo na sledeci i obrisemo clan liste
                del->slp=0;
                del->next=0;
                delete del;
			}
			else{
            old=pom;
			pom=pom->next;
			}

		}


}
struct sleep1* Sleep::last=0;
struct sleep1* Sleep::first=0;


void Sleep::ubaci(sleep1 *s){//ubacuje u listu
	if(s->t==0){
		s->slp->fleg=1;
	}
	else{

		if(last==0){
			first=s;
			last=s;
		}else{
			last->next=s;
			last=s;
		}

	}

}

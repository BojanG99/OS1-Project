/*
 * Kernel.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */


#include <iostream.h>
#include <dos.h>
#include"Sleep.h"
#include"PCB.h"
#include"thread.h"
#include"SCHEDULE.H"

#include"IdleThrd.h"
int onDemand=0;
volatile int inf=1;
extern int userMain(int argc, char* argv[]);
// zabranjuje prekide
#define lock asm cli

// dozvoljava prekide
#define unlock asm sti

// potpis interrupt rutine za rad sa setvect() i getvect()
//typedef void interrupt (*pInterrupt)(...);

// stara prekidna rutina
//pInterrupt oldISR;
void interrupt timer();




// 5s X 18.2tic/s =~ 100tic
volatile int cntr = 100;

unsigned oldTimerOFF, oldTimerSEG;
void inic(){
	PCB::running=(new Thread(10,0))->myPCB;
	asm{
		cli			// zabranjuju se prekidi
		push es
		push ax

		mov ax,0	// inicijalizuje rutinu za tajmer
		mov es,ax	// es = 0

		// pamti staru rutinu
		// oldTimerSEG = [00072h]; - 1Ch*4h+2h=72h
		mov ax, word ptr es:0072h
		mov word ptr oldTimerSEG, ax
		// oldTimerOFF = [00072h]; - 1Ch*4h=70h
		mov ax, word ptr es:0070h
		mov word ptr oldTimerOFF, ax

		// postavlja novu rutinu
		mov word ptr es:0072h, seg timer
		mov word ptr es:0070h, offset timer


		mov ax, oldTimerSEG
				mov word ptr es:0182h, ax
				mov ax, oldTimerOFF
				mov word ptr es:0180h, ax

		pop ax
		pop es
		sti			// dozvoljavaju se prekidi
	}
}

// restauira staru prekidnu rutinu
// u Interrupt vektor tabeli
void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		// vraca originalnu rutinu
		mov ax, word ptr oldTimerSEG
		mov word ptr es:0072h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0070h, ax

		pop ax
		pop es
		sti
	}
}




// prekidna rutina
volatile unsigned tsp,tss;

void interrupt timer() {
	if (!onDemand){
		if(cntr)//smanjujemo tajmer za 1
			cntr--;
			Sleep::izbacuj();//i one niti koje cekaju tajmer

		}


	if (((cntr == 0) && inf)|| (onDemand==1  )) {//ako je isteklo vrijem  ili dispatch


if(PCB::running->wasSignal){

	PCB::running->wasSignal=0;
}else{

	        asm{



				mov tsp,sp//cuvamo ss i sp
				mov tss,ss
	          }


			PCB::running->ss=(tss);
			PCB::running->sp=(tsp);
}
         //  cout<<PCB::running->fleg<<endl;
			if(PCB::running->fleg!=4 &&PCB::running->fleg!=3 && PCB::running->getId()>0)//ako nit nije zavrsila
				{
			Scheduler::put(PCB::running);//ubacimo u scheduler

				}
			PCB::running = Scheduler::get();//dohvatimo novu nit



	        if(PCB::running==0)PCB::running=PCB::allPCBs[0];//ako nema nijedna nit ubacujemo onu koja ne radi nista


	        			tsp = PCB::running->sp;
	        	        tss= PCB::running->ss;

	        	        cntr = PCB::running->time;


	        			asm {

	        	        	mov ss,tss//podmecemo novi sp i ss
	        	        	mov sp,tsp

	        			}
	        if(PCB::running->myThread->prvi!=0){
            PCB::running->infinity=1;
            tsp=0x200;
            asm push tsp
			tsp=PCB::running->scs;
			asm push tsp
			tsp=PCB::running->sip;
			asm push tsp
            tsp=0;
			asm push tsp
			asm push tsp
			asm push tsp
			asm push tsp
			asm push tsp
			asm push tsp
			asm push tsp
			asm push tsp
			asm push tsp


	        }

	        if(cntr==0 || PCB::running->infinity==1)inf=0;//ako je cntr 0 to znaci da nit ima neodredjeno vrijeme izvrsavanja
	        else inf=1;







		}

if(!onDemand)
	asm int 60h

onDemand=0;
}

int main(){


IdleThrd idle;
inic();

	 char *c[4];//pravljenje parametara za userMain
	c[0]="main.exe";
	c[1]="100";
	c[2]="100";
	c[3]="0";



			//t2.signal(5);
	userMain(4,c);




	restore();


}
// stara prekidna rutina



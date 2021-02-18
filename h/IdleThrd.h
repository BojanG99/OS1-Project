/*
 * IdleThrd.h
 *
 *  Created on: Jul 30, 2020
 *      Author: OS1
 */

#ifndef IDLETHRD_H_
#define IDLETHRD_H_

#include "thread.h"

class IdleThrd: public Thread {
public:
	IdleThrd();
	virtual ~IdleThrd();
	void run();
};

#endif /* IDLETHRD_H_ */

/*
 * Writer.h
 *
 *  Created on: 23 de jul. de 2016
 *      Author: oscar
 */

#ifndef WRITER_H_
#define WRITER_H_

#include "PololuMaestro.h"
#define TIME_DELAY 100

class Writer {
public:
	Writer() {
		time = 0;
		timeThreshold = 0;
		master = nullptr;
	}
	Writer(MicroMaestro * mast, unsigned long threshold) {
		master = mast;
		time = millis();
		timeThreshold = threshold;
	}
	bool setTarget(unsigned char servo, unsigned int pos) {

		if ((millis() - time) >= timeThreshold) {
			master->setTarget(servo, pos);
			time = millis() / 100;
			return true;
		}
		Serial.print(millis());

		time = millis();
		return false;
	}
private:
	unsigned long time;
	unsigned long timeThreshold;
	MicroMaestro * master;
};

#endif /* WRITER_H_ */

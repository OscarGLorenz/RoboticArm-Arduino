/*
 * Button.cpp
 *
 *  Created on: 5 de ago. de 2016
 *      Author: oscar
 */

#include "Button.h"
#include "Writer.h"

	Button::Button(unsigned char n, ServoConfig * servoConfig, Writer * writerO) {
		num = n;
		state = false;
		servo = servoConfig;
		writer = writerO;
	}
	void Button::switchButton() {
		if(state) {
			writer->setTarget(num, servo->getMin());
		} else {
			writer->setTarget(num, servo->getMax());
		}
		state = !state;
	}


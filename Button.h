/*
 * Button.h
 *
 *  Created on: 5 de ago. de 2016
 *      Author: oscar
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "ServoConfig.h"
#include "Writer.h"

class Button {
public:
	Button(unsigned char n, ServoConfig * servoConfig, Writer * writerO);
	void switchButton();
private:
	unsigned char num;
	bool state;
	ServoConfig * servo;
	Writer * writer;
};

#endif /* BUTTON_H_ */

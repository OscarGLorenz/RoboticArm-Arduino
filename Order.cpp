/*
 * Order.cpp
 *
 *  Created on: 5 de ago. de 2016
 *      Author: oscar
 */

#include "Order.h"

Order::Order() {
	_servo = 0;
	_pos = 0;
	_time = 0;
}
Order::Order(unsigned char servo, unsigned short pos, unsigned long time) {
	_servo = servo;
	_pos = pos;
	_time = time;
}
unsigned char Order::getServo() {
	return _servo;
}
unsigned short Order::getPos() {
	return _pos;
}
unsigned long Order::getTime() {
	return _time;
}


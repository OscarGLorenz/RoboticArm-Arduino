/*
 * Order.cpp
 *
 *  Created on: 20 de jul. de 2016
 *      Author: oscar
 */
#include "Arduino.h"

#include "Order.h"

char Order::getType() {
	return type;
}
char Order::getServo() {
	return servoNum;
}
int Order::getValue() {
	return value;
}
void Order::setValue(int newvalue) {
	value = newvalue;
}
Order::Order(char newtype, char newservo, int newvalue) {
	type = newtype;
	servoNum = newservo;
	value = newvalue;
}
Order::Order() {
	type = 0;
	servoNum = 0;
	value = 0;
}

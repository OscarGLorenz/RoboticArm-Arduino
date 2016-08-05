/*
 * Order.h
 *
 *  Created on: 5 de ago. de 2016
 *      Author: oscar
 */

#ifndef ORDER_H_
#define ORDER_H_

class Order {
public:
	Order();
	Order(unsigned char servo, unsigned short pos, unsigned long time);
	unsigned char getServo();
	unsigned short getPos();
	unsigned long getTime();
private:
	unsigned char _servo;
	unsigned short _pos;
	unsigned long _time;
};


#endif /* ORDER_H_ */

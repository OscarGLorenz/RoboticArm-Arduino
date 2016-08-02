/*
 * Order.h
 *
 *  Created on: 20 de jul. de 2016
 *      Author: oscar
 */

#ifndef ORDER_H_
#define ORDER_H_


class Order {
  public:
	Order();
    char getType();
    char getServo();
    int getValue();
    void setValue(int newvalue);
    Order(char newtype, char newservo, int newvalue);
    char type;
    char servoNum;
    int value;
};

#endif /* ORDER_H_ */

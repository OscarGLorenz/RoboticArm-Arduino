#include "SoftwareSerial.h"
#include "PololuMaestro.h"
#include "Queue.h"
#include "Writer.h"
#include "Order.h"

/*
 *
 #define MAX_VEL 20
 #define MAX_ACC 5

 #define MAP_RANGE 200
 #define SERIAL_MAP_RANGE 200

 #define AX_SERVOS {0,2,3}
 #define AX_N 3

 #define INITIAL_VALUES { 6000, 0, 5000, 7000 }
 #define LIMIT_VALUES { { 4000, 8000 }, { 5000, 6500 }, { 5000, 7000 }, { 6000, 8000 } }

 SoftwareSerial servoSerial(10, 11);

 Servos control(servoSerial, (unsigned int[] ) INITIAL_VALUES,
 (unsigned int[][2] ) LIMIT_VALUES, 4, 100);

 void setup() {
 Serial.setTimeout(10);
 servoSerial.begin(9600);
 Serial.begin(9600);
 control.setSpeed((const unsigned char[] ) AX_SERVOS, AX_N, MAX_VEL);
 control.setAcceleration((const unsigned char[] ) AX_SERVOS, AX_N, MAX_ACC);
 control.goHome((const unsigned char[] ) AX_SERVOS, AX_N);
 }

 void loop() {
 while (Serial.available() > 0) {
 char buffer[10];
 Serial.readBytesUntil(' ', buffer, 10);
 switch (buffer[0]) {
 case 'G':
 if (toInt(buffer[1]) == 1) {
 if (toInt(buffer[2]) == 0)
 control.position(1, 0, 1);
 else if (toInt(buffer[2]) == 1)
 control.position(1, 1, 1);
 }
 break;
 case 'H':
 control.goHome((const unsigned char[] ) AX_SERVOS, AX_N);
 break;
 case 'A':
 control.insertOrder(toInt(buffer[1]),
 (int) map(atoi(buffer + 2), 0, SERIAL_MAP_RANGE, -MAP_RANGE,
 MAP_RANGE));
 }
 }
 control.check((const unsigned char[] ) AX_SERVOS, AX_N);
 }

 int toInt(char c) {
 return c - '0';
 }*/

#define MAX_VEL 20
#define MAX_ACC 5
#define TOLERANCE 200

template class Queue<Order> ;
template class Node<Order> ;

Queue<Order> orders[4];

SoftwareSerial servoSerial(10, 11);
MicroMaestro maestro(servoSerial);
Writer writer(&maestro, 0);

const int configValues[][2] = { { 2800, 8000 }, { 5000, 6500 }, { 5000, 7000 },
		{ 6000, 8000 } };

const int positions[] = { 6000, 0, 5000, 7000 };

int positionsNow[] = { 6000, 0, 5000, 7000 };

void serialEvent() {
	while (Serial.available() > 0) {
		char buffer[20];
		Serial.readBytesUntil(' ', buffer, 10);
		switch (buffer[0]) {
		case 'G':
			if (toInt(buffer[1]) == 1) {
				if (toInt(buffer[2]) == 0)
					writer.setTarget(1, configValues[1][0]);
				else if (toInt(buffer[2]) == 1)
					writer.setTarget(1, configValues[1][1]);
			}
			break;
		case 'H':
			maestro.setTarget(0, positions[0]);
			maestro.setTarget(2, positions[2]);
			maestro.setTarget(3, positions[3]);
			break;
		case 'A':
			orders[toInt(buffer[1])].pushBack(
					Order('A', toInt(buffer[1]),
							(int) map(atoi(buffer + 2), 0, 400, -TOLERANCE,
									TOLERANCE)));
			break;
		case 'R':
			Serial.print(positionsNow[toInt(buffer[1])]);
		}
	}
}

void setup() {

	Serial.setTimeout(10);
	servoSerial.begin(9600);
	Serial.begin(9600);
	for (int i = 0; i < 4; i++) {
		if (i == 1)
			continue;
		maestro.setSpeed(i, MAX_VEL);
		maestro.setAcceleration(i, MAX_ACC);
	}

	maestro.setTarget(0, positions[0]);
	maestro.setTarget(1, configValues[1][1]);
	maestro.setTarget(2, positions[2]);
	maestro.setTarget(3, positions[3]);
}

void loop() {
	for (int i = 0; i < 4; i++) {
		if (i == 1)
			continue;
		if (!orders[i].isEmpty()) {
			if (writer.setTarget(i,
					positionsNow[i] += orders[i].getFront().getValue()))
				orders[i].popFront();
		}
	}
}

int toInt(char c) {
	return c - '0';
}

/*	if (positions[toInt(buffer[1])]
 + (int) map(atoi(buffer + 2), 0, 400, -500, 500)
 > configValues[toInt(buffer[1])][1]) {
 positionsNow[toInt(buffer[1])] =
 configValues[toInt(buffer[1])][1];
 } else if (positions[toInt(buffer[1])]
 - (int) map(atoi(buffer + 2), 0, 400, -500, 500)
 < configValues[toInt(buffer[1])][0]) {
 positionsNow[toInt(buffer[1])] =
 configValues[toInt(buffer[1])][0];
 } else {
 positionsNow[toInt(buffer[1])] += (int) map(atoi(buffer + 2), 0,
 400, -200, 200);
 }

 if (millis() - time > 200) {
 maestro.send(toInt(buffer[1]),
 positionsNow[toInt(buffer[1])]);
 time = millis();
 }
 }*/

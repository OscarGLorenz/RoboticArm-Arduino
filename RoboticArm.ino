#include "SoftwareSerial.h"
#include "PololuMaestro.h"
#include "Queue.h"
#include "Order.h"
#include "ServoConfig.h"
#include "Button.h"
#include "Writer.h"
#include "XBOXUSB.h"

USB Usb;
XBOXUSB Xbox(&Usb);

#define MAX_VEL 20
#define MAX_ACC 5
#define TOLERANCE 200
#define THRESHOLD_TIME 0

template class Queue<Order> ;
template class Node<Order> ;

Queue<Order> orders[4];

SoftwareSerial servoSerial(2, 3);
MicroMaestro maestro(servoSerial);
Writer writer(&maestro, THRESHOLD_TIME);

ServoConfig servoConfig[4] = { { 5400, 2800, 8000 }, { 7000, 5000, 7000 }, {
		6000, 5000, 7000 }, { 7000, 6000, 8000 } };

Button button(1, &servoConfig[1], &writer);

void setup() {

	Serial.setTimeout(10);
	servoSerial.begin(9600);
	Serial.begin(9600);
	Usb.Init();

	for (int i = 0; i < 4; i++) {
		if (i == 1)
			continue;
		maestro.setSpeed(i, MAX_VEL);
		maestro.setAcceleration(i, MAX_ACC);
	}

	for (int i = 0; i < 4; i++) {
		maestro.setTarget(i, servoConfig[i].getHome());
	}
}

bool pull = false;

void loop() {
	Usb.Task();
	if (Xbox.Xbox360Connected) {
		if (Xbox.getButtonPress(R2) > 0 && !pull) {
			button.switchButton();
			pull = !pull;
		} else if (Xbox.getButtonPress(R2) == 0 && pull){
			pull = !pull;
		}
		if (Xbox.getButtonPress(XBOX)) {
			maestro.setTarget(0, servoConfig[0].getHome());
			maestro.setTarget(2, servoConfig[2].getHome());
			maestro.setTarget(3, servoConfig[3].getHome());
		}
	/*	if (Xbox.getAnalogHat(RightHatY) > 7500
				|| Xbox.getAnalogHat(RightHatY) < 7500) {
			writer.setTarget(2,
					servoConfig[2].add(
							map(Xbox.getAnalogHat(RightHatY), -32768, 32768,
									-TOLERANCE, TOLERANCE)));
		}
		if (Xbox.getAnalogHat(RightHatX) > 7500
				|| Xbox.getAnalogHat(RightHatX) < 7500) {
			writer.setTarget(0,
					servoConfig[0].add(
							map(Xbox.getAnalogHat(RightHatX), -32768, 32768,
									-TOLERANCE, TOLERANCE)));
		}
		if (Xbox.getAnalogHat(LeftHatY) > 7500
				|| Xbox.getAnalogHat(LeftHatY) < 7500) {
			writer.setTarget(3,
					servoConfig[3].add(
							map(Xbox.getAnalogHat(LeftHatY), -32768, 32768,
									-TOLERANCE, TOLERANCE)));
		}*/

	}
	delay(1);

}

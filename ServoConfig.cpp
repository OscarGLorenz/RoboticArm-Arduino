/*
 * ServoConfig.cpp
 *
 *  Created on: 5 de ago. de 2016
 *      Author: oscar
 */

#include "Arduino.h"
#include "ServoConfig.h"

ServoConfig::ServoConfig() {
	now = 0;
	min = 0;
	max = 0;
	initial = 0;
}
ServoConfig::ServoConfig(unsigned short initialPos, unsigned short minPos,
		unsigned short maxPos) {
	now = initialPos;
	min = minPos;
	max = maxPos;
	initial = initialPos;
}
unsigned short ServoConfig::getMin() {
	return min;
}
unsigned short ServoConfig::getMax() {
	return max;
}
unsigned short ServoConfig::mapValue(int value, int minV, int maxV) {
	return map(value, minV, maxV, min, max);
}
unsigned short ServoConfig::update(int value) {
	now = value;
	return now;
}
unsigned short ServoConfig::add(int amount) {
	now += amount;
	return now;
}
unsigned short ServoConfig::getPos() {
	return now;
}
unsigned short ServoConfig::getHome() {
	return initial;
}


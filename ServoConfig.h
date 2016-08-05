/*
 * ServoConfig.h
 *
 *  Created on: 5 de ago. de 2016
 *      Author: oscar
 */

#ifndef SERVOCONFIG_H_
#define SERVOCONFIG_H_


class ServoConfig {
public:
	ServoConfig();
	ServoConfig(unsigned short initialPos, unsigned short minPos,
			unsigned short maxPos);
	unsigned short getMin();
	unsigned short getMax();
	unsigned short mapValue(int value, int minV, int maxV);
	unsigned short update(int value);
	unsigned short add(int amount);
	unsigned short getPos();
	unsigned short getHome();
private:
	unsigned short now;
	unsigned short initial;
	unsigned short min;
	unsigned short max;
};

#endif /* SERVOCONFIG_H_ */

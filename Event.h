/*
 * Event.h
 *
 *  Created on: 5 de ago. de 2016
 *      Author: oscar
 */

#ifndef EVENT_H_
#define EVENT_H_

enum EventType {
	SLIDER, BUTTON
};

class Event {
public:
	Event();
	void check();
private:
	EventType type;
	unsigned char number;
};

#endif /* EVENT_H_ */

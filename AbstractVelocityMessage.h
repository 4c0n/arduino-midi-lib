#ifndef AbstractVelocityMessage_h
#define AbstractVelocityMessage_h

#include "Arduino.h"

class AbstractVelocityMessage {
	protected:
		byte velocity;
	public:
		AbstractVelocityMessage(byte velocity) {
			this->velocity = velocity;
		}


		virtual ~AbstractVelocityMessage() {
		}


		byte getVelocity() {
			return this->velocity;
		}
};

#endif

#ifndef AbstractValueMessage_h
#define AbstractValueMessage_h

#include "Arduino.h"

class AbstractValueMessage {
	protected:
		byte value;
	public:
		AbstractValueMessage(byte value) {
			this->value = value;
		}


		virtual ~AbstractValueMessage() {
		}


		byte getValue() {
			return this->value;
		}
};

#endif

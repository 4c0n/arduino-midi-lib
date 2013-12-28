#ifndef AbstractCombinedValueMessage_h
#define AbstractCombinedValueMessage_h

#include "Arduino.h"

class AbstractCombinedValueMessage {
	protected:
		short value;
	public:
		AbstractCombinedValueMessage(byte data1, byte data2) {
			this->value = data1 + data2;
		}

	
		virtual ~AbstractCombinedValueMessage() {
		}


		short getValue() {
			return this->value;
		}
};

#endif

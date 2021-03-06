#ifndef AbstractMIDIMessage_h
#define AbstractMIDIMessage_h

#include "Arduino.h"

class AbstractMIDIMessage {
	protected:
		byte status;
	public:
		AbstractMIDIMessage(byte status) {
			this->status = status;
		}


		virtual ~AbstractMIDIMessage() {
		}


		byte getStatus() {
			return this->status;
		}
};

#endif

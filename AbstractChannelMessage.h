#ifndef AbstractChannelMessage_h
#define AbstractChannelMessage_h

#include "Arduino.h"

class AbstractChannelMessage {
	protected:
		byte channel;
	public:
		AbstractChannelMessage(byte status) {
			this->channel = status & 0x0F;
		}


		virtual ~AbstractChannelMessage() {
		}


		byte getChannel() {
			return this->channel;
		}
};

#endif

#ifndef ATChannelMessage_h
#define ATChannelMessage_h

#include "Arduino.h"
#include "AbstractMIDIMessage.h"
#include "AbstractChannelMessage.h"
#include "AbstractValueMessage.h"

class ATChannelMessage : public AbstractMIDIMessage, public AbstractChannelMessage, public AbstractValueMessage {
	public:
		ATChannelMessage(byte status, byte data1) : AbstractMIDIMessage(status), AbstractChannelMessage(status), AbstractValueMessage(data1) {
		}

		
		virtual ~ATChannelMessage() {
		}
};

#endif 

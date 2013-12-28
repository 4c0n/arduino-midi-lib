#ifndef ControlChangeMessage_h
#define ControlChangeMessage_h

#include "Arduino.h"
#include "AbstractMIDIMessage.h"
#include "AbstractChannelMessage.h"
#include "AbstractValueMessage.h"

class ControlChangeMessage : public AbstractMIDIMessage, public AbstractChannelMessage, public AbstractValueMessage {
	private:
		byte controller;
	public:
		ControlChangeMessage(byte status, byte controller, byte value) : AbstractMIDIMessage(status), AbstractChannelMessage(status), AbstractValueMessage(value) {
			this->controller = controller;
		}


		virtual ~ControlChangeMessage() {
		}


		byte getController() {
			return this->controller;
		}
};

#endif

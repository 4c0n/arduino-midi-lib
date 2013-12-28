#ifndef ProgramChangeMessage_h
#define ProgramChangeMessage_h

#include "Arduino.h"
#include "AbstractMIDIMessage.h"
#include "AbstractChannelMessage.h"

class ProgramChangeMessage : public AbstractMIDIMessage, public AbstractChannelMessage {
	private:
		byte program;
	public:
		ProgramChangeMessage(byte status, byte program) : AbstractMIDIMessage(status), AbstractChannelMessage(status) {
			this->program = program;
		}


		virtual ~ProgramChangeMessage() {
		}


		byte getProgram() {
			return this->program;
		}
};

#endif

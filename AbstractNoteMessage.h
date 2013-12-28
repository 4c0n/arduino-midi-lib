#ifndef AbstractNoteMessage_h
#define AbstractNoteMessage_h

#include "Arduino.h"
#include "AbstractMIDIMessage.h"
#include "AbstractVelocityMessage.h"
#include "AbstractChannelMessage.h"

class AbstractNoteMessage : public AbstractMIDIMessage, public AbstractChannelMessage, public AbstractVelocityMessage {
	protected:
		byte note;
	public:
		AbstractNoteMessage(byte status, byte note, byte velocity) : AbstractMIDIMessage(status), AbstractChannelMessage(status), AbstractVelocityMessage(velocity) {
			this->note = note;
		}


		virtual ~AbstractNoteMessage() {
		}


		byte getNote() {
			return this->note;
		}
};

#endif

#ifndef TimingClockMessage_h
#define TimingClockMessage_h

#include "Arduino.h"
#include "AbstractMIDIMessage.h"

class TimingClockMessage : public AbstractMIDIMessage {
	public:
		TimingClockMessage() : AbstractMIDIMessage(0xF8) {
		}

		virtual ~TimingClockMessage() {
		}
};

#endif

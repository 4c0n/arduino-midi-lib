#ifndef PitchBendMessage_h
#define PitchBendMessage_h

#include "Arduino.h"
#include "AbstractMIDIMessage.h"
#include "AbstractChannelMessage.h"
#include "AbstractCombinedValueMessage.h"

class PitchBendMessage : public AbstractMIDIMessage, public AbstractChannelMessage, public AbstractCombinedValueMessage {
	public:
		PitchBendMessage(byte status, byte data1, byte data2) : AbstractMIDIMessage(data1), AbstractChannelMessage(data2), AbstractCombinedValueMessage(data1, data2) {
		}


		virtual ~PitchBendMessage() {
		}
};

#endif

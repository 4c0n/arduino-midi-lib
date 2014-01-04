#ifndef MIDI_h
#define MIDI_h

#include "Arduino.h"
#include "AbstractNoteMessage.h"
#include "ControlChangeMessage.h"
#include "ProgramChangeMessage.h"
#include "PitchBendMessage.h"
#include "ATChannelMessage.h"

typedef AbstractNoteMessage NoteOnMessage;
typedef AbstractNoteMessage NoteOffMessage;
typedef AbstractNoteMessage ATPolyMessage;

enum message_t {
	NoteOn,
	NoteOff,
	ATPoly,
	CC,
	PC,
	ATChannel,
	PitchBend,
	System,
	TimingClock,
	Unsupported
};

struct Midimsg {
	byte status;
	byte data1;
	byte data2;
	unsigned int size;
	unsigned int type;
};

class MIDI {
	private:
		Midimsg msg;
		bool handleMessage(byte status);
		byte getNextByte();
		void clearMessage();
		MIDI();
		MIDI(MIDI const&);
		void operator=(MIDI const&);
	public:
		static MIDI& getInstance() {
			static MIDI instance;
			return instance;
		}
		bool read();
		bool read(byte channel, bool sys);
		void send(byte status, byte data1, byte data2);
		void send(byte status, byte data1);
		void send(byte status);
		byte getStatus();
		byte getData1();
		byte getData2();
		unsigned int getSize();
		byte getChannelFromStatus(byte status);
		int getMessageSize(byte status);
		message_t getType(byte status);
		NoteOnMessage * getNoteOnMessage();
		NoteOffMessage * getNoteOffMessage();
		ATPolyMessage * getATPolyMessage();
		ControlChangeMessage * getControlChangeMessage();
		ProgramChangeMessage * getProgramChangeMessage();
		PitchBendMessage * getPitchBendMessage();
		ATChannelMessage * getATChannelMessage();
};

#endif

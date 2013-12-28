#ifndef MIDI_h
#define MIDI_h

#include "Arduino.h"

#define NoteOff 0
#define NoteOn 1
#define ATPoly 2
#define CC 3
#define PC 4
#define ATChannel 5
#define	PitchBend 6
#define System 7

struct Midimsg {
	byte status;
	byte data1;
	byte data2;
	int size;
};

class MIDI {
	private:
		Midimsg msg;
		bool handleMessage(byte status);
		byte getNextByte();
		void clearMessage();
	public:
		MIDI();
		bool read();
		bool read(int channel, bool sys);
		void send(byte status, byte data1, byte data2);
		void send(byte status, byte data1);
		void send(byte status);
		byte getStatus();
		byte getData1();
		byte getData2();
		int getSize();
		byte getChannelFromStatus(byte status);
		int getMessageSize(byte status);
		int getType(byte status);
};

#endif

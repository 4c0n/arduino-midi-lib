#include "Arduino.h"
#include "MIDI.h"

MIDI::MIDI() {
	Serial.begin(31250);
}


/**
 * read any kind of message
**/
bool MIDI::read() {
	clearMessage();

	if (Serial.available() > 0) {
		byte sts = Serial.read();
		return handleMessage(sts);
	}

	return false;
}


bool MIDI::read(int channel, bool sys) {
	clearMessage();

	if (Serial.available() > 0) {
		byte sts = Serial.read();

		if (sts > 0x7F && sts < 0xF0) { // channel bound messages

			if (channel == getChannelFromStatus(sts)) {
				return handleMessage(sts);
			}
		}	
		else if (sts > 0xEF && sys) { // non channel bound messages
			return handleMessage(sts);
		}		
	}
	return false;
}


bool MIDI::handleMessage(byte status) {
	int size = getMessageSize(status);
	switch (size) {
		case 1: {
			msg.status = status;
			msg.size = size;
		}
		return true;
		
		case 2: {
			byte dat1 = getNextByte();
			if (dat1 != -1) {
				msg.status = status;
				msg.data1 = dat1;
				msg.size = size;
			}
		}
		return true;
		
		case 3: {
			byte dat1 = getNextByte();
			if (dat1 != -1) {
				byte dat2 = getNextByte();
				if (dat2 != -1) {
					msg.status = status;
					msg.data1 = dat1;
					msg.data2 = dat2;
					msg.size = size;
				}
			}
		}
		return true;
		
		case -1:
		return false; // invalid status byte
	}

	return false; // shouldn't happen but here for the form
}


void MIDI::send(byte status, byte data1, byte data2) {
	Serial.write(status);
	Serial.write(data1);
	Serial.write(data2);
}


void MIDI::send(byte status, byte data1) {
	Serial.write(status);
	Serial.write(data1);
}


void MIDI::send(byte status) {
	Serial.write(status);
}


byte MIDI::getStatus() {
	return msg.status;
}


byte MIDI::getData1() {
	return msg.data1;
}


byte MIDI::getData2() {
	return msg.data2;
}


unsigned int MIDI::getSize() {
	return msg.size;
}


byte MIDI::getChannelFromStatus(byte status) {
	return (status & 0x0F);
}


int MIDI::getMessageSize(byte status) {
	if (status > 0xF5  || (status == 0xF0)) { // 1 byte msg
		return 1;
	}
	else if ((status > 0xC0 && status < 0xE0) || (status == 0xF3)) { // 2 byte msg
		return 2;
	}
	else if ((status > 0x7F && status < 0xC0) || (status > 0xDF && status < 0xF0)) { // 3 byte msg
		return 3;
	}
	else {
		return -1; // invalid/unsupported message
	}
}


int MIDI::getType(byte status) {
	if (status > 0xEF) {
		return System;
	}
	else if (status > 0x7F && status < 0x90) {
		return NoteOff;
	}
	else if (status > 0x8F && status < 0xA0) {
		return NoteOn;
	}
	else if (status > 0x9F && status < 0xB0) {
		return ATPoly;
	}
	else if (status > 0xAF && status < 0xC0) {
		return CC;
	}
	else if (status > 0xBF && status < 0xD0) {
		return PC;
	}
	else if (status > 0xCF && status < 0xE0) {
		return ATChannel;
	}
	else if (status > 0xDF && status < 0xF0) {
		return PitchBend;
	}
	return -1; // invalid/unsupported message
}


byte MIDI::getNextByte() {
	delayMicroseconds(325); // 325 TODO: 
	//delay(5);
	int i = 3;
	while ((Serial.available() < 1) && (i > 0)) { // wait for the 2nd byte if it isn't already available
		//digitalWrite(13, HIGH);
		delayMicroseconds(325);
		//digitalWrite(13, LOW);
		i--;
	}

	return Serial.read();
}

										void MIDI::clearMessage() {
	msg.status = 0;
	msg.data1 = 0;
	msg.data2 = 0;
	msg.size = 0;
}

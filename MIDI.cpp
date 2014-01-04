#include "Arduino.h"
#include "MIDI.h"

MIDI::MIDI() {
	Serial.begin(31250);
}


/**
 * read any kind of message
**/
bool MIDI::read() {
	this->clearMessage();

	if (Serial.available() > 0) {
		byte sts = Serial.read();
		return this->handleMessage(sts);
	}

	return false;
}


bool MIDI::read(byte channel, bool sys) {
	this->clearMessage();

	if (Serial.available() > 0) {
		byte sts = Serial.read();

		if (sts > 0x7F && sts < 0xF0) { // channel bound messages

			if (channel == this->getChannelFromStatus(sts)) {
				return this->handleMessage(sts);
			}
		}	
		else if (sts > 0xEF && sys) { // non channel bound messages
			return this->handleMessage(sts);
		}		
	}
	return false;
}


bool MIDI::handleMessage(byte status) {
	int size = this->getMessageSize(status);
	switch (size) {
		case 1: {
			this->msg.status = status;
			this->msg.size = size;
		}
		return true;
		
		case 2: {
			byte dat1 = this->getNextByte();
			if (dat1 != -1) {
				this->msg.status = status;
				this->msg.data1 = dat1;
				this->msg.size = size;
			}
		}
		return true;
		
		case 3: {
			byte dat1 = this->getNextByte();
			if (dat1 != -1) {
				byte dat2 = this->getNextByte();
				if (dat2 != -1) {
					this->msg.status = status;
					this->msg.data1 = dat1;
					this->msg.data2 = dat2;
					this->msg.size = size;
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
	return this->msg.status;
}


byte MIDI::getData1() {
	return this->msg.data1;
}


byte MIDI::getData2() {
	return this->msg.data2;
}


unsigned int MIDI::getSize() {
	return this->msg.size;
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

message_t MIDI::getType(byte status) {
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
	return Unsupported; // invalid/unsupported message
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
	this->msg.status = 0;
	this->msg.data1 = 0;
	this->msg.data2 = 0;
	this->msg.size = 0;
}


NoteOnMessage * MIDI::getNoteOnMessage() {
	if(this->msg.size > 0 && this->getType(this->msg.status) == NoteOn) {
		return new NoteOnMessage(this->msg.status, this->msg.data1, this->msg.data2);
	}

	return NULL;
}


NoteOffMessage * MIDI::getNoteOffMessage() {
	if(this->msg.size > 0 && this->getType(this->msg.status) == NoteOff) {
		return new NoteOffMessage(this->msg.status, this->msg.data1, this->msg.data2);
	}

	return NULL;
}


ATPolyMessage * MIDI::getATPolyMessage() {
	if(this->msg.size > 0 && this->getType(this->msg.status) == ATPoly) {
		return new ATPolyMessage(this->msg.status, this->msg.data1, this->msg.data2);
	}

	return NULL;
}


ControlChangeMessage * MIDI::getControlChangeMessage() {
	if(this->msg.size > 0 && this->getType(this->msg.status) == CC) {
		return new ControlChangeMessage(this->msg.status, this->msg.data1, this->msg.data2);
	}

	return NULL;
}

ProgramChangeMessage * MIDI::getProgramChangeMessage() {
	if(this->msg.size > 0 && this->getType(this->msg.status) == PC) {
		return new ProgramChangeMessage(this->msg.status, this->msg.data1);
	}
	
	return NULL;
}

PitchBendMessage * MIDI::getPitchBendMessage() {
	if(this->msg.size > 0 && this->getType(this->msg.status) == PitchBend) {
		return new PitchBendMessage(this->msg.status, this->msg.data1, this->msg.data2);
	}
	
	return NULL;
}

ATChannelMessage * MIDI::getATChannelMessage() {
	if(this->msg.size > 0 && this->getType(this->msg.status) == ATChannel) {
		return new ATChannelMessage(this->msg.status, this->msg.data1);
	}

	return NULL;
}

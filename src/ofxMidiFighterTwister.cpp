//
//  ofxMidiFighterTwister.cpp
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 27/3/15.
//
//

#include "ofxMidiFighterTwister.h"


void ofxMidiFighterTwister::setup(){

	midiOut.listPorts(); // via instance
	midiOut.openPort("Midi Fighter Twister");
	midiIn.openPort("Midi Fighter Twister");
	midiIn.addListener(this);
}

void ofxMidiFighterTwister::draw(){
}


void ofxMidiFighterTwister::newMidiMessage(ofxMidiMessage& msg){

	cout << msg.toString() << endl;
	switch (msg.channel) {

		case 1: //encoders
			if(msg.status == MIDI_CONTROL_CHANGE){
				EncoderEventArgs args;
				args.ID = msg.control;
				args.value = msg.value;
				ofNotifyEvent(eventEncoder, args, this);
			}
			break;

		case 2: //pushSwitches
			if(msg.status == MIDI_CONTROL_CHANGE){
				PushSwitchEventArgs args;
				args.ID = msg.control;
				args.value = msg.value;
				ofNotifyEvent(eventPushSwitch, args, this);
			}
			break;

		case 4: //side buttons
			break;
	}
}

void ofxMidiFighterTwister::setEncoderRingValue(int encoder, float value){
	midiOut.sendControlChange(1, encoder, ofMap(value, 0, 1, 0, 127, true));
}


void ofxMidiFighterTwister::setEncoderColor(int encoder, float hue){
	midiOut.sendControlChange(2, encoder, ofMap(hue, 0, 1, 0, 127, true));
}


void ofxMidiFighterTwister::setEncoderRingAnimationStrobe(int encoder, unsigned char strobe){
	midiOut.sendControlChange(3, encoder, clamp(strobe + 49 , 49, 56));
}


void ofxMidiFighterTwister::setEncoderRingAnimationPulse(int encoder, unsigned char pulse){
	midiOut.sendControlChange(3, encoder, clamp(pulse + 57 , 57, 64));
}


void ofxMidiFighterTwister::setEncoderRingBrightness(int encoder, float brightness){
	midiOut.sendControlChange(3, encoder, clamp(65 + 30 * brightness , 65, 95));
}


void ofxMidiFighterTwister::setEncoderColorAnimationStrobe(int encoder, unsigned char strobe){
	midiOut.sendControlChange(3, encoder, clamp(strobe , 1, 8));
}

void ofxMidiFighterTwister::setEncoderColorAnimationPulse(int encoder, unsigned char pulse){
	midiOut.sendControlChange(3, encoder, clamp(pulse + 8, 9, 16));
}

void ofxMidiFighterTwister::setEncoderColorBrightness(int encoder, float brightness){
	midiOut.sendControlChange(3, encoder, clamp(17 + 30 * brightness , 17, 47));
}

void ofxMidiFighterTwister::setEncoderColorAnimationRainbow(int encoder){
	midiOut.sendControlChange(3, encoder, 127);
}

void ofxMidiFighterTwister::setEncoderAnimationsOff(int encoder){
	midiOut.sendControlChange(3, encoder, 0);
}





unsigned char ofxMidiFighterTwister::clamp(unsigned char val, unsigned char min, unsigned char max){
	if(val < min) val = min;
	else if (val > max) val = max;
	return val;
}


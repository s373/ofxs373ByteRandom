#include "ofxs373ByteRandom.h"

ofxs373ByteRandom ofxs373ByteRandom::byteRng;

bool ofxs373ByteRandom::ofxs373BRinit = false;

void ofxs373ByteRandom::initByteRandom(std::string fn){
	if(ofxs373BRinit) return;
	ofxs373BRinit = true;
	byteRng.setup(fn);
}

float byteRandom(int idx, float minimum, float maximum){
	ofxs373ByteRandom::initByteRandom();
	return ofxs373ByteRandom::byteRng.rnd(idx, minimum, maximum);
}

float byteRandom(float minimum, float maximum){
	ofxs373ByteRandom::initByteRandom();
	return ofxs373ByteRandom::byteRng.rnd(minimum, maximum);
}

float byteRandom(float maximum){
	ofxs373ByteRandom::initByteRandom();
	return ofxs373ByteRandom::byteRng.rnd( maximum);
}

void byteRandomSeed(float seed){
	ofxs373ByteRandom::initByteRandom();
	return ofxs373ByteRandom::byteRng.seed((int)seed);
}

void byteRandomSeed(int seed){
	ofxs373ByteRandom::initByteRandom();
	return ofxs373ByteRandom::byteRng.seed(seed);
}

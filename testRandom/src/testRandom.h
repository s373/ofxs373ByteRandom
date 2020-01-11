#pragma once

#include "ofMain.h"
#include "ofxs373ByteRandom.h"

#define NUMHIST	(256)
#define NUMAVG	(8)

struct testRandom : public ofBaseApp {
public:

	ofxs373ByteRandom 				byterandom;

	string  								rnddata;

	vector<float>						rndhistory;
	int									histhead;


	vector<float> 								avgs;
	int 											avghead;


	void setup(){

		ofSetVerticalSync(false);
		ofSetFrameRate(1000);

		byterandom.setup( ofToDataPath("daedalus.exe") 	,    2);

		byterandom.setPool(1);
		byterandom.setPool(0);

		rnddata = "";

		for(int i=0; i<100; i++){
			cout << " " << i << "  BYTE RNG: " <<  byterandom.rnd(0,1) << endl;
		}

		byterandom.setPool(0);

		rndhistory.assign ( NUMHIST, 0.0f );
		avgs.assign ( NUMAVG, 0.0f );

		avghead = 0;

		histhead = 0;

	}

	void update(){


		rnddata += byterandom.nxtByte();

		if( rnddata.size() > 1000 ) rnddata = "";

		int phisthead = histhead;
		histhead = (histhead + 1) % NUMHIST ;
		if( histhead < phisthead ) {

			// calc averages

			avgs [ avghead ] = 0.0f;

			for(int i=0; i<NUMHIST;i++){

				avgs [ avghead ] += rndhistory[i];

			}

			avgs [ avghead ] /= (float) NUMHIST;

			avghead = (avghead+1) % NUMAVG;


		}

		rndhistory [ histhead ] = byterandom.rnd ( 0, ofGetHeight() );


	}




	// er/.gitignoreUT
	void draw(){

		// zero

		ofSetColor( ofRandom(255) , ofRandom(255) ,ofRandom(255)  );

		ofLine(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);


		// history

		ofSetColor( 0 );

		for(int i=0; i<(NUMHIST-1);i++){

				float x = ofMap( i, 0, NUMHIST, 0, ofGetWidth() );
				float x1 = ofMap( i+1, 0, NUMHIST, 0, ofGetWidth() );

				ofLine ( x,  rndhistory[i], x1, rndhistory[i+1] );

		}



		// averages

		for(int i=0; i<(NUMAVG);i++){

			ofSetColor( ofRandom(255) , ofRandom(255) ,ofRandom(255)  );

			ofLine(0, avgs [ i ], ofGetWidth(), avgs [ i ] );


		}






		ofSetColor( ofRandom(255) , ofRandom(255) ,ofRandom(255)  );
		ofDrawBitmapString(rnddata, 10, 10);
		ofDrawBitmapString(ofGetFrameRate(), 10, ofGetHeight()-20);

	}

};

//		ofxs373ByteRandom
//		cross platform random number generator byte sequence based
//		(c) s373.net/x art codex studios 2017
//		coded by André Sier, under a tree, 2017.4493291 ( June 14 2017 )
//		MIT Licensed


#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// using these, byterng loads "data/rnd.dat"
float byteRandom(int idx, float minimum, float maximum);
float byteRandom(float minimum, float maximum);
float byteRandom(float maximum);
void byteRandomSeed(float seed);
void byteRandomSeed(int seed);


struct ofxs373ByteRandom {
	private:
		std::string 			bytefilename;
		std::string 			bytedata;
		std::ifstream      		bytebasefile;
		long					bytenum;
		bool					bufferedread;

		long					rngnumbytes;
		long					rngbytehead;

		int						numpools,  activepool;
		std::vector<int>		poolheads;

	public:
		ofxs373ByteRandom(){}
		~ofxs373ByteRandom(){}

		void setup(const std::string & fn, int npools=1,  int numbytes = 1){
			if(numbytes < 1) numbytes = 1;
			rngnumbytes = numbytes;

			if(npools < 1) npools = 1;
			numpools = npools;
			poolheads . assign(  npools, 0 );
			activepool = 0;

			rngbytehead = 0; // replaced with pools
			bytedata = "";

			bytefilename = fn;
			bytebasefile.open(
				bytefilename.c_str(), std::ios::in | std::ios::binary
			);

			if(!bytebasefile.is_open()){
				std::cout << " error reading file " << bytefilename << std::endl;
			} else {
				rngnumbytes = 0;
				char c = '\0';
				while(!bytebasefile.eof()){
					rngnumbytes++;
					bytebasefile.read((char *)&c, sizeof(char));
					bytedata += c;
				}
				std::cout << "ofxs373ByteRandom read file " << bytefilename << " numbytes " << rngnumbytes << std::endl;
			}
			bytebasefile.close();
		}


		void setPool(int pool){
			if(pool == -1) activepool = -1;
			else activepool =  ( pool <  poolheads.size() ) ? pool : 0;
		}


		void seed(int s) {    			//, int pool = -1){

			int baseseed = s % rngnumbytes ;
			if( activepool < 0 ) {
				for(int i=0; i<poolheads.size();  i++){
					poolheads[i] = baseseed;
				}
			} else {
				int idpool = ( activepool <  poolheads.size() ) ? activepool : 0;
				poolheads[idpool] = baseseed;
			}

		}

		float scale(char a, float mn, float mx){
			return ( (a+127)*0.00392156862745*(mx-mn)+mn  );
		}


		float rnd(int idx, float mn, float mx){
			return scale(getByte(idx),mn,mx);
		}

		float rnd(float mn, float mx){
			return scale(nxtByte(),mn,mx);
		}

		float rnd(float mx){
			return scale(nxtByte(),0.f,mx);
		}


		char getByte(int idx){
			return bytedata.at(  idx % bytedata.size()  );
		}

		char nxtByte(){

			char rnd = 	0;				//	'\0'; 		//				'o'    ;

			int rnghead = 0;

			if(activepool < 0) {

					rnghead = poolheads [   0    ];

					while (  		rnd ==0		) {

							rnd = bytedata.at(  rnghead  );

							rnghead =  ( rnghead + 1 ) % rngnumbytes ;

							poolheads [   0    ] = rnghead;

					}


			}

			else {

					int idpool = ( activepool <  poolheads.size() ) ? activepool : 0;

					rnghead = poolheads [   idpool   ];

					while (  		rnd ==0		) {

							rnd = bytedata.at(  rnghead  );

							rnghead =  ( rnghead + 1 ) % rngnumbytes ;

							poolheads [   idpool    ] = rnghead;
					}
			}


			return rnd;
		}


		static ofxs373ByteRandom byteRng;
		static void initByteRandom(std::string fn="data/rnd.dat");
		static bool ofxs373BRinit;
};

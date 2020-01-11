#include "ofMain.h"
#include "testRandom.h"

int main( ){
	ofSetupOpenGL(1024,600,OF_WINDOW);
	testRandom * app = new testRandom();
	ofRunApp(app);
	return (int)app->byterandom.rnd(10.0f);
}

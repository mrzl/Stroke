#include "ofMain.h"
#include "ofApp.h"

//#define DEVELOP

//========================================================================
/************************************************************************/
/* 1. set add to 1280
/* 2. compile and copy 
/* 3. set add to 0
/* 4. run both*/
/************************************************************************/
int main( ){
#ifdef DEVELOP
	ofSetupOpenGL( 1920, 1080, OF_WINDOW );
#else
	ofSetupOpenGL( 1280, 800, OF_WINDOW );
	int add = 1280; // 1280
	ofSetWindowPosition(1920 + add, 0);
#endif
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:	ofRunApp(new ofApp());
	ofRunApp(new ofApp());
}

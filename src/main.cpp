#include "ofMain.h"
#include "ofApp.h"

#define DEVELOP

//========================================================================
int main( ){
#ifdef DEVELOP
	ofSetupOpenGL( 1920, 1080, OF_WINDOW );
#else
	ofSetupOpenGL( 1280, 800, OF_WINDOW );
	ofSetWindowPosition(1920, 0);
#endif
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

#pragma once

//#include 

#include "ofxState.h"
#include "ofxUI.h"

#include "SharedData.h"

struct data {
	std::vector< ofVec2f > pointData;
	std::vector< ofVec2f > mouseData;
};

class BaseStrokeState : public itg::ofxState<SharedData>
{
public:
	virtual void setupIdea( int pointNum ) = 0;
	virtual void setupImplementation() = 0;
	virtual std::string getName() = 0;
	std::string getTimestampForToday( std::string prefix );

protected:
	// data
	data data;

	// gui
	ofxUISuperCanvas * gui;
	virtual void setupGUI() = 0;
	virtual void guiEvent( ofxUIEventArgs &e ) = 0;

	// logic
	float pointNum;
	bool running;

	// misc
	float lerp( float start, float stop, float amt );
};


#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "ofxState.h"

#include "SharedData.h"

class DrawingState : public itg::ofxState<SharedData>
{
public:
	void stateEnter();
	void stateExit();
	void update();
	void draw();
	void mouseMoved(int x, int y );
	void mouseReleased( int x, int y, int button );
	void keyPressed( int key );

	std::string getName();

private:
	void saveRecordedMouseMovement();
	void savePoints();
	std::string getTimestampForToday( std::string prefix );
};


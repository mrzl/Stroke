#pragma once

#include "ofxState.h"
#include "SharedData.h"

class FollowBallState : public itg::ofxState<SharedData>
{
public:
	void stateEnter();
	void stateExit();
	void update();
	void draw();

	void keyPressed( int key );

	std::string getName();

private:
	void loadPoints();

	wng::ofxCsv pointsCsv;
	std::vector< ofVec2f > points;

	int currentPointIndex, currentPercentage;
};


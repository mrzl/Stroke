#pragma once

#include "ofxCsv.h"

class SharedData
{
public:
	std::string ANIMATION_STATE, FOLLOW_BALL_STATE, RECREATE_STATE;
	std::string MOUSE_MOVEMENT_FILENAME, POINTS_FILENAME;
	wng::ofxCsv mouseMovementCsvRecorder, pointsCsvExporter;

	ofVec2f currentMousePos;
	std::vector< ofVec2f > points;
	ofTrueTypeFont font;
};
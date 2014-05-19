#pragma once

#include "ofxCsv.h"

class SharedData
{
public:
	std::string FOLLOW_BALL_STATE, DRAWING_STATE, RECREATE_STATE;
	std::string MOUSE_MOVEMENT_FILENAME, POINTS_FILENAME;
	wng::ofxCsv mouseMovementCsvRecorder, pointsCsvExporter;

	ofVec2f currentMousePos;
	std::vector< ofVec2f > points;
	ofTrueTypeFont font;

	std::string COMPUTER_COMPUTER, COMPUTER_HUMAN, HUMAN_COMPUTER, HUMAN_HUMAN;

	std::string stateSelectionRadioButton;

	ofColor backgroundColor, lineColor;
	int strokeWeight;
};
#pragma once

#include "BaseStrokeState.h"

class HumanComputerState : public BaseStrokeState
{
public:
	void stateEnter();
	void stateExit();

	void update();
	void draw();
	void debugDraw();

	std::string getName();
	void setupIdea( int pointNum );
	void setupImplementation();
	void setupGUI();
	void guiEvent( ofxUIEventArgs &e );

	void mouseMoved( int x, int y );
	void mouseReleased( int x, int y, int button );
	void keyPressed( int key );

private:
	bool recording, allowParallels;
	std::string setupIdeaButtonLabel, setupImplementationButtonLabel, startAnimationButtonLabel, allowParallelsButtonLabel;
	float animationSpeed;

	ofVec2f currentMouse;
	ofVec2f getCurrentMouse();

	// animation
	int currentPointIndex;
	float currentPercentageX, currentPercentageY;
};


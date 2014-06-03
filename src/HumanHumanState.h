#pragma once

#include "BaseStrokeState.h"

class HumanHumanState : public BaseStrokeState
{
public:
	HumanHumanState();
	~HumanHumanState();
	void stateEnter();
	void stateExit();

	void update();
	void draw();
	void debugDraw();

	void setupIdea( int pointNum );
	void setupImplementation();

	std::string getName();
	void setupGUI();
	void guiEvent( ofxUIEventArgs &e );
	void mouseMoved( int x, int y );
	void mousePressed( int x, int y, int key );
	void mouseReleased( int x, int y, int button );
	void keyPressed( int key );
	void end();

private:
	bool allowParallels;
	std::string setupIdeaButtonLabel, setupImplementationButtonLabel, startAnimationButtonLabel, allowParallelsButtonLabel;
	float animationSpeed;
	int currentPointIndex;
	float currentDrawingIndex, currentMouseDataIndex;

	ofVec2f currentMouse;
	ofVec2f getCurrentMouse();
};


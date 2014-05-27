#pragma once

#include "BaseStrokeState.h"
#include <string>

class ComputerHumanState : public BaseStrokeState
{
public:
	ComputerHumanState();
	~ComputerHumanState();
	void stateEnter();
	void stateExit();
	void update();
	void draw();
	void mouseMoved(int x, int y );
	void mouseReleased( int x, int y, int button );
	void keyPressed( int key );
	void end();

	std::string getName();

private:
	void setupGUI();
	void setupIdea( int numPoints );
	void setupImplementation();
	void guiEvent( ofxUIEventArgs &e );

	std::string setupIdeaButtonLabel, setupImplementationButtonLabel;

	int currentPointIndex, currentDrawingIndex, currentMouseDataIndex;
	float animationSpeed;
};


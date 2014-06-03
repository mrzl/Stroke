#pragma once

#include "BaseStrokeState.h"

class ComputerComputerState : public BaseStrokeState
{
public:
	ComputerComputerState();
	~ComputerComputerState();
	void stateEnter();
	void stateExit();
	void update();
	void draw();
	void debugDraw();
	void mouseMoved(int x, int y );
	void mouseReleased( int x, int y, int button );
	void keyPressed( int key );
	std::string getName();

	// idea from computer can not be im/ex-ported, they're always live.
	void setupIdea( int pointNum );
	void importIdea( std::string filePath );
	void exportIdea( std::string fileName );

	// implementations are not im/ex-ported, they're always live.
	void setupImplementation();

	void end();

private:
	// gui
	void setupGUI();
	void guiEvent( ofxUIEventArgs &e );
	ofxUIDropDownList * importFileNameDropDownList;
	ofxUITextInput * exportFileNameTextInput;
	std::string setupIdeaButtonLabel, importIdeaButtonLabel, exportIdeaButtonLabel, exportFileNameButtonLabel, importFileNameDropdownLabel, startAnimationButtonLabel;

	// animation
	int currentPointIndex;
	float currentPercentageX, currentPercentageY;

	float animationSpeed;

	// misc
	std::vector< std::string > getAvailableSavedIdeas();

	// mapping
	ofxQuadWarp         warper;
	ofFbo               fbo;
	bool isCursorVisible;
	void beforeDrawing();
	void afterDrawing();
	void setupColors();
};


#pragma once

#ifdef _WIN32
#define FILE_SEPARATOR   "\\"
#else
#define FILE_SEPARATOR   "/"
#endif

#include "ofxState.h"
#include "ofxUI.h"
#include "ofxCsv.h"
#include "ofxQuadWarp.h"

#include "SharedData.h"

class BaseStrokeState : public itg::ofxState<SharedData>
{
public:
    struct currentData {
        std::vector< ofVec2f > pointData;
        std::vector< std::vector< ofVec2f > > currMouseData;
    };
	void keyPressed( int key );

	virtual void setupIdea( int pointNum ) = 0;
	virtual void setupImplementation() = 0;
	virtual std::string getName() = 0;
	virtual void end() = 0;
	void setupPointCount( int pointCount );
	void beforeDrawing();
	void afterDrawing();
	void setupColors();
	void exportPointData();
	void importPointData();
	void exportMouseData();
	void importMouseData();

	enum STATE { INIT, RUNNING, RECORDING, DONE };

protected:
	// data
	currentData currentData;

	// gui
	ofxUISuperCanvas * gui;
	virtual void setupGUI() = 0;
	virtual void guiEvent( ofxUIEventArgs &e ) = 0;

	// logic
	float * getPointCount( void );
	STATE state;
	//bool running;

	// misc
	float lerp( float start, float stop, float amt );

	// export/import
	static const int filesToLoad = 17;
	int currentMouseImportExportIndex, currentPointsImportExportIndex;
	std::string createFileNameAccordingToCurrentExportAndImportIndex( int index, std::string identifyingString );

	// mapping
	ofxQuadWarp         warper;
	ofFbo               fbo;
	bool isCursorVisible;

private:
	float pointNum;
};


#include "DrawingState.h"

void DrawingState::stateEnter()
{
	getSharedData().mouseMovementCsvRecorder = wng::ofxCsv();
	getSharedData().pointsCsvExporter = wng::ofxCsv();

	getSharedData().mouseMovementCsvRecorder.clear();
	getSharedData().pointsCsvExporter.clear();
}

void DrawingState::stateExit()
{

}


void DrawingState::update()
{

}

void DrawingState::draw()
{
	ofBackground( ofColor( 0 ) );
	ofSetColor( ofColor( 255 ) );
	glLineWidth( 5 );

	std::vector<ofVec2f> *points = &getSharedData().points;	

	if( points->size() > 1 )
	{
		ofVec2f from = points->back();
		ofLine( from, getSharedData().currentMousePos );
	}

	for( size_t i = 0; i < points->size() - 1 && points->size() > 1; i++ ) 
	{
		ofVec2f from = points->at( i );
		ofVec2f to = points->at( i + 1 );
		ofLine( from, to );
	}

	ofDrawBitmapString("csv rows: " + ofToString(getSharedData().mouseMovementCsvRecorder.numRows), 500, 370);
}

std::string DrawingState::getName()
{
	return getSharedData().FOLLOW_BALL_STATE;
}

void DrawingState::mouseMoved( int x, int y )
{
	getSharedData().currentMousePos.x = x;
	getSharedData().currentMousePos.y = y;

	int row = getSharedData().mouseMovementCsvRecorder.numRows;
	getSharedData().mouseMovementCsvRecorder.setInt(row, 0, x);
	getSharedData().mouseMovementCsvRecorder.setInt(row, 1, y);
}

void DrawingState::mouseReleased( int x, int y, int button )
{
	getSharedData().points.push_back( getSharedData().currentMousePos );
}

void DrawingState::keyPressed( int key )
{
	switch( key )
	{
	case 's':
		saveRecordedMouseMovement();
		break;
	case 'p':
		savePoints();
		break;
	case 'f':
		changeState( getSharedData().FOLLOW_BALL_STATE );
		break;
	case 'r':
		changeState( getSharedData().RECREATE_STATE );
		break;
	}
}

void DrawingState::saveRecordedMouseMovement()
{
	//std::string fileName = getTimestampForToday( "mouse_recording" );
	std::string fileName = getSharedData().MOUSE_MOVEMENT_FILENAME;
	getSharedData().mouseMovementCsvRecorder.saveFile( ofToDataPath( fileName ) );
}

void DrawingState::savePoints()
{
	for( auto it = getSharedData().points.begin(); it != getSharedData().points.end(); ++it ) 
	{
		ofVec2f recordedPoints = *it;
		int row = getSharedData().pointsCsvExporter.numRows;
		getSharedData().pointsCsvExporter.setFloat(row, 0, recordedPoints.x );
		getSharedData().pointsCsvExporter.setFloat(row, 1, recordedPoints.y );
	}
	//std::string fileName = getTimestampForToday( "points_recording" );
	std::string fileName = getSharedData().POINTS_FILENAME;
	getSharedData().pointsCsvExporter.saveFile( ofToDataPath( fileName ) );
}

std::string DrawingState::getTimestampForToday( std::string prefix )
{
	std::stringstream ss;
	ss << prefix;
	ss << ofGetTimestampString("%e%n%y-%H%M%S");
	ss << ".csv";
	return ss.str();
}

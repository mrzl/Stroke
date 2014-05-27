#include "BaseStrokeState.h"

float BaseStrokeState::lerp( float start, float stop, float amt )
{
	return start * ( 1 - amt ) + stop * amt;
}

void BaseStrokeState::keyPressed( int key )
{
	switch( key )
	{
	case 'g':
		gui->toggleVisible();
		break;
	case 'e':
		this->exportPointData();
		this->exportMouseData();
		break;
	case 'w':
		this->importPointData();
		this->importMouseData();
		this->state = DONE;
		break;
	case 'q':
		warper.toggleShow();
		break;
	case 'c':
		isCursorVisible = !isCursorVisible;
		if ( isCursorVisible == true) 
			ofShowCursor(); 
		else
			ofHideCursor();
	break;
	case '1':
		changeState( getSharedData().COMPUTER_COMPUTER );
		break;
	case '2':
		changeState( getSharedData().COMPUTER_HUMAN );
		break;
	case '3':
		changeState( getSharedData().HUMAN_COMPUTER );
		break;
	case '4':
		changeState( getSharedData().HUMAN_HUMAN );
		break;
	}
}

float * BaseStrokeState::getPointCount( void )
{
	return &this->pointNum;
}

void BaseStrokeState::setupPointCount(int pointCount)
{
	*this->getPointCount() = pointNum;
}

void BaseStrokeState::setupColors()
{
	ofClear( getSharedData().backgroundColor.r, getSharedData().backgroundColor.g, getSharedData().backgroundColor.b, 255 );
	ofBackground( getSharedData().backgroundColor );
	ofSetColor( getSharedData().backgroundColor );
	//ofRect( 0, 0, 200, ofGetWindowHeight() );
	ofSetColor( getSharedData().lineColor );
	glLineWidth( getSharedData().strokeWeight );
	fbo.begin();
	
}

void BaseStrokeState::beforeDrawing()
{
	ofBackground( getSharedData().backgroundColor );
	
}

void BaseStrokeState::afterDrawing()
{
	fbo.end();

	ofMatrix4x4 mat = warper.getMatrix();

	glPushMatrix();
	ofSetLineWidth( 1 );
	glMultMatrixf( mat.getPtr() );
	{
		fbo.draw( 0, 0 );
	}
	glPopMatrix();
	ofSetLineWidth( getSharedData().strokeWeight );
	warper.draw();
	fbo.begin();
	ofClear( getSharedData().backgroundColor.r, getSharedData().backgroundColor.g, getSharedData().backgroundColor.b );
	fbo.end();
}

void BaseStrokeState::exportPointData()
{
	wng::ofxCsv csvExporter;
	for( std::vector< ofVec2f >::iterator it = currentData.pointData.begin(); it != currentData.pointData.end(); ++it )
	{
		ofVec2f recordedPoint = *it;
		int row = csvExporter.numRows;
		csvExporter.setFloat(row, 0, recordedPoint.x );
		csvExporter.setFloat(row, 1, recordedPoint.y );
	}
	//std::string fileName = getTimestampForToday( "points_recording" );
	std::string fileName = createFileNameAccordingToCurrentExportAndImportIndex( currentPointsImportExportIndex, "POINTS" );
	csvExporter.saveFile( ofToDataPath( fileName ) );
	currentPointsImportExportIndex++;
	if( currentPointsImportExportIndex >= filesToLoad )
	{
		currentPointsImportExportIndex = 666;
	}
	this->currentData.pointData.clear();
	csvExporter.clear();
}

void BaseStrokeState::exportMouseData()
{
	wng::ofxCsv csvExporter;
	csvExporter.numRows = 0;
	int inde = 0;
	for( std::vector< std::vector< ofVec2f > >::iterator it = this->currentData.currMouseData.begin(); it != this->currentData.currMouseData.end(); ++it )
	{
		std::vector< ofVec2f > points = *it;
		for( std::vector< ofVec2f >::iterator itp = points.begin(); itp != points.end(); itp++ )
		{
			ofVec2f recordedPoint = *itp;
			int row = csvExporter.numRows;
			csvExporter.setFloat(row, 0, inde );
			csvExporter.setFloat(row, 1, recordedPoint.x );
			csvExporter.setFloat(row, 2, recordedPoint.y );
		}
		inde++;
	}
	inde = 0;
	//std::string fileName = getTimestampForToday( "points_recording" );
	std::string fileName = createFileNameAccordingToCurrentExportAndImportIndex( currentMouseImportExportIndex, "MOUSE" );
	csvExporter.saveFile( ofToDataPath( fileName ) );
	currentMouseImportExportIndex++;
	if( currentMouseImportExportIndex >= filesToLoad )
	{
		currentMouseImportExportIndex = 666;
	}
	this->currentData.currMouseData.clear();
	csvExporter.clear();
	this->state = STATE::INIT;
}

void BaseStrokeState::importPointData()
{
	wng::ofxCsv csvExporter;
	csvExporter.clear();
	this->currentData.pointData.clear();
	csvExporter.loadFile( ofToDataPath( createFileNameAccordingToCurrentExportAndImportIndex( currentPointsImportExportIndex, "POINTS" ) ) );
	for( std::vector< std::vector< std::string > >::iterator it = csvExporter.data.begin(); it != csvExporter.data.end(); ++it )
	{
		std::vector< std::string > * pointS = &( * it );
		std::string xS, yS;
		int x, y;

		xS = pointS->at( 0 );
		yS = pointS->at( 1 );

		x = atoi( xS.c_str() );
		y = atoi( yS.c_str() );

		x = ofMap( x, 0, 1920, 0, 1280 );
		y = ofMap( y, 0, 1080, 0, 800 );

		ofVec2f point( x, y );
		this->currentData.pointData.push_back( point );
	}
	this->currentPointsImportExportIndex++;
	if( this->currentPointsImportExportIndex >= filesToLoad )
	{
		this->currentPointsImportExportIndex = 0;
	}
}

std::string BaseStrokeState::createFileNameAccordingToCurrentExportAndImportIndex( int index, std::string identifyingString )
{
	std::stringstream ss;
	ss << this->getName();
	ss << FILE_SEPARATOR;
	ss << index;
	ss << identifyingString;
	ss << ".csv";
	return ss.str();
}

void BaseStrokeState::importMouseData()
{
	wng::ofxCsv csvExporter;
	csvExporter.numRows = 0;
	csvExporter.clear();
	this->currentData.currMouseData.clear();
	csvExporter.loadFile( ofToDataPath( createFileNameAccordingToCurrentExportAndImportIndex( currentMouseImportExportIndex, "MOUSE" ) ) );
	this->currentData.currMouseData.resize( 200 );
	for( std::vector< std::vector< std::string > >::iterator it = csvExporter.data.begin(); it != csvExporter.data.end(); ++it )
	{
		std::vector< std::string > * pointS = &( * it );
		std::string mouseIndexS, xS, yS;
		int x, y, mouseIndex;

		mouseIndexS = pointS->at( 0 );
		xS = pointS->at( 1 );
		yS = pointS->at( 2 );

		mouseIndex = atoi( mouseIndexS.c_str() );
		//mouseIndex += 1;
		x = atoi( xS.c_str() );
		y = atoi( yS.c_str() );

		x = ofMap( x, 0, 1920, 0, 1280 );
		y = ofMap( y, 0, 1080, 0, 800 );

		ofVec2f point( x, y );
		this->currentData.currMouseData.at( mouseIndex ).push_back( point );
	}
	this->currentMouseImportExportIndex++;
	if( this->currentMouseImportExportIndex >= filesToLoad )
	{
		this->currentMouseImportExportIndex = 0;
	}
	this->currentData.currMouseData.shrink_to_fit();
}
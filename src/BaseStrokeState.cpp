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
	ofBackground( getSharedData().backgroundColor );
	ofSetColor( getSharedData().lineColor );
	glLineWidth( getSharedData().strokeWeight );
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
	std::cout << "started this export" << std::endl;
	//csvExporter.data.
	for( std::vector< std::vector< ofVec2f > >::iterator it = this->currentData.currMouseData.begin(); it != this->currentData.currMouseData.end(); ++it )
	{
		std::vector< ofVec2f > points = *it;
		for( std::vector< ofVec2f >::iterator itp = points.begin(); itp != points.end(); itp++ )
		{
			ofVec2f recordedPoint = *itp;
			int row = csvExporter.numRows;
			std::cout << "point to save --------------" << recordedPoint << std::endl;
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

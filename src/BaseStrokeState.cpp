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
		this->state = RUNNING;
		this->state = RECORDING;
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
	for( auto it = data.pointData.begin(); it != data.pointData.end(); ++it ) 
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
	if( currentPointsImportExportIndex >= 17 )
	{
		currentPointsImportExportIndex = 666;
	}
	this->data.pointData.clear();
	this->csvExporter.clear();
}

void BaseStrokeState::importPointData()
{
	this->csvExporter.clear();
	this->data.pointData.clear();
	this->csvExporter.loadFile( ofToDataPath( createFileNameAccordingToCurrentExportAndImportIndex( currentPointsImportExportIndex, "POINTS" ) ) );
	for( auto it = this->csvExporter.data.begin(); it != this->csvExporter.data.end(); ++it ) 
	{
		std::vector< std::string > * pointS = &( * it );
		std::string xS, yS;
		int x, y;

		xS = pointS->at( 0 );
		yS = pointS->at( 1 );

		x = atoi( xS.c_str() );
		y = atoi( yS.c_str() );

		ofVec2f point( x, y );
		this->data.pointData.push_back( point );
	}
	this->currentPointsImportExportIndex++;
	if( this->currentPointsImportExportIndex >= 17 )
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

void BaseStrokeState::exportMouseData()
{
	int inde = 0;
	for( auto it = data.mouseData.begin(); it != data.mouseData.end(); ++it ) 
	{
		std::vector< ofVec2f > points = *it;
		for( auto itp = points.begin(); itp != points.end(); itp++ )
		{
			ofVec2f recordedPoint = *itp;
			int row = csvExporter.numRows;
			csvExporter.setFloat(row, 0, inde );
			csvExporter.setFloat(row, 1, recordedPoint.x );
			csvExporter.setFloat(row, 2, recordedPoint.y );
		}
		inde++;
	}
	//std::string fileName = getTimestampForToday( "points_recording" );
	std::string fileName = createFileNameAccordingToCurrentExportAndImportIndex( currentMouseImportExportIndex, "MOUSE" );
	csvExporter.saveFile( ofToDataPath( fileName ) );
	currentMouseImportExportIndex++;
	if( currentMouseImportExportIndex >= 17 )
	{
		currentMouseImportExportIndex = 666;
	}
	this->data.mouseData.clear();
	this->csvExporter.clear();
}

void BaseStrokeState::importMouseData()
{
	this->csvExporter.clear();
	this->data.mouseData.clear();
	this->csvExporter.loadFile( ofToDataPath( createFileNameAccordingToCurrentExportAndImportIndex( currentMouseImportExportIndex, "MOUSE" ) ) );
	this->data.mouseData.resize( 200 );
	for( auto it = this->csvExporter.data.begin(); it != this->csvExporter.data.end(); ++it ) 
	{
		std::vector< std::string > * pointS = &( * it );
		std::string mouseIndexS, xS, yS;
		int x, y, mouseIndex;

		mouseIndexS = pointS->at( 0 );
		xS = pointS->at( 1 );
		yS = pointS->at( 2 );

		mouseIndex = atoi( mouseIndexS.c_str() );
		x = atoi( xS.c_str() );
		y = atoi( yS.c_str() );

		ofVec2f point( x, y );
		this->data.mouseData.at( mouseIndex ).push_back( point );
	}
	this->currentMouseImportExportIndex++;
	if( this->currentMouseImportExportIndex >= 17 )
	{
		this->currentMouseImportExportIndex = 0;
	}
}

#include "RecreateState.h"

void RecreateState::stateEnter()
{
	loadPoints();
	currentPointIndex = currentPercentageX = currentPercentageY = 0;
}

void RecreateState::loadPoints()
{
	this->pointsCsv.loadFile( ofToDataPath( getSharedData().POINTS_FILENAME ) );
	for( auto it = this->pointsCsv.data.begin(); it != this->pointsCsv.data.end(); ++it ) 
	{
		std::vector<std::string> * pointS = &( * it );
		std::string xS, yS;
		int x, y;

		xS = pointS->at( 0 );
		yS = pointS->at( 1 );

		x = atoi( xS.c_str() );
		y = atoi( yS.c_str() );

		ofVec2f point( x, y );
		this->points.push_back( point );
	}
}

void RecreateState::stateExit()
{

}

void RecreateState::update()
{
	ofVec2f fromPoint = points.at( currentPointIndex );
	ofVec2f toPoint = points.at( currentPointIndex + 1 );
	float distance = fromPoint.distance( toPoint );
	int toAdd = ofMap( distance, 0, 3000, 3, 1 );
	

	if( currentPercentageX >= 100 )
	{
		if( currentPercentageY >= 100 )
		{
			currentPercentageX = 0;
			currentPercentageY = 0;
			currentPointIndex++;
			if( currentPointIndex == points.size() - 1 )
			{
				currentPointIndex = 0;
			}
		} else
		{
			currentPercentageY += toAdd;
		}
	} else
	{
		currentPercentageX += toAdd;
	}
}

void RecreateState::draw()
{
	glLineWidth( 2 );
	ofSetColor( ofColor( 255 ) );
	ofVec2f fromPoint = points.at( currentPointIndex );
	ofVec2f toPoint = points.at( currentPointIndex + 1 );
	float percentageX = currentPercentageX / 100.0;
	float percentageY = currentPercentageY / 100.0;
	float lerpedX, lerpedY;
	lerpedX = lerp( fromPoint.x, toPoint.x, percentageX );
	lerpedY = lerp( fromPoint.y, toPoint.y, percentageY );
	ofLine( fromPoint, ofVec2f( lerpedX, lerpedY ) );

	for( size_t i = 0; i < currentPointIndex && points.size() > 1; i++ ) 
	{
		ofVec2f from = points.at( i );
		ofVec2f to = points.at( i + 1 );
		ofLine( from, to );
	}
}

std::string RecreateState::getName()
{
	return getSharedData().RECREATE_STATE;
}

float RecreateState::lerp( float start, float stop, float amt )
{
	return start * ( 1 - amt ) + stop * amt;
}

void RecreateState::keyPressed( int key )
{

}

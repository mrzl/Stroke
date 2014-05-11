#include "FollowBallState.h"

void FollowBallState::stateEnter()
{
	std::cout << "FollowBallState" << std::endl;
	loadPoints();

	currentPointIndex = currentPercentage = 0;
}

void FollowBallState::loadPoints()
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

void FollowBallState::stateExit()
{

}

void FollowBallState::update()
{
	ofVec2f fromPoint = points.at( currentPointIndex );
	ofVec2f toPoint = points.at( currentPointIndex + 1 );
	float distance = fromPoint.distance( toPoint );
	int toAdd = ofMap( distance, 0, 3000, 5, 1 );
	currentPercentage += toAdd;

	if( currentPercentage >= 100 )
	{
		currentPercentage = 0;
		currentPointIndex++;
		if( currentPointIndex == points.size() - 1 )
		{
			currentPointIndex = 0;
		}
	}
}

void FollowBallState::draw()
{
	ofSetColor( ofColor( 255 ) );
	ofVec2f fromPoint = points.at( currentPointIndex );
	ofVec2f toPoint = points.at( currentPointIndex + 1 );
	float percentage = currentPercentage / 100.0;
	ofVec2f pointToDraw = fromPoint.getInterpolated(toPoint, percentage );
	ofCircle( pointToDraw, 5 );

	glLineWidth( 1 );
	ofSetColor( ofColor( 255, 255, 255, 90 ) );

	for( size_t i = 0; i < points.size() - 1 && points.size() > 1; i++ ) 
	{
		ofVec2f from = points.at( i );
		ofVec2f to = points.at( i + 1 );
		ofLine( from, to );
	}
}

std::string FollowBallState::getName()
{
	return getSharedData().FOLLOW_BALL_STATE;
}

void FollowBallState::keyPressed( int key )
{
	switch( key ) 
	{
	case 'r':
		changeState( getSharedData().RECREATE_STATE );
		break;
	}
}
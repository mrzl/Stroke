#include "BaseStrokeState.h"

std::string BaseStrokeState::getTimestampForToday( std::string prefix )
{
	std::stringstream ss;
	ss << prefix;
	ss << ofGetTimestampString("%e%n%y-%H%M%S");
	ss << ".csv";
	return ss.str();
}

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

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

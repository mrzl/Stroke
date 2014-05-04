#include "ComputerHumanState.h"
#include "ComputerComputerState.h"

void ComputerHumanState::stateEnter()
{
	pointNum = 100.0f;
	running = false;
	//delete ComputerComputerState::gui;
	setupGUI();

	gui->setVisible( true );
}

void ComputerHumanState::stateExit()
{
	// delete gui;
	this->gui->setVisible( false );
}

void ComputerHumanState::update()
{

}

void ComputerHumanState::draw()
{
	ofBackground( 0 );
}

void ComputerHumanState::mouseMoved( int x, int y )
{

}

void ComputerHumanState::mouseReleased( int x, int y, int button )
{

}

void ComputerHumanState::keyPressed( int key )
{
	switch( key )
	{
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

std::string ComputerHumanState::getName()
{
	return getSharedData().COMPUTER_HUMAN;
}

void ComputerHumanState::setupIdea( int numPoints )
{
	this->data.pointData.clear();
	for( int i = 0; i < pointNum; i++ ) 
	{
		float x = ofRandom( 0, ofGetWidth() );
		float y = ofRandom( 0, ofGetHeight() );

		this->data.pointData.push_back( ofVec2f( x, y ) );
	}
}

void ComputerHumanState::setupGUI()
{

	gui = new ofxUISuperCanvas( getSharedData().COMPUTER_HUMAN ); //shared_ptr<ofxUISuperCanvas>(new ofxUISuperCanvas( "COMPUTER_HUMAN" ) );

	std::vector<std::string> stateNames;
	stateNames.push_back( getSharedData().COMPUTER_COMPUTER + " (1)" );
	stateNames.push_back( getSharedData().COMPUTER_HUMAN + " (2)" );
	stateNames.push_back( getSharedData().HUMAN_COMPUTER + " (3)" );
	stateNames.push_back( getSharedData().HUMAN_HUMAN + " (4)" );

	gui->addRadio( getSharedData().stateSelectionRadioButton, stateNames, OFX_UI_ORIENTATION_VERTICAL );

	gui->setGlobalButtonDimension( OFX_UI_GLOBAL_BUTTON_DIMENSION );
	gui->autoSizeToFitWidgets();
	ofAddListener( gui->newGUIEvent, this, &ComputerHumanState::guiEvent );
}

void ComputerHumanState::setupImplementation()
{

}

void ComputerHumanState::guiEvent( ofxUIEventArgs &e )
{
	std::string name = e.getName();
	if( name == getSharedData().stateSelectionRadioButton )
	{
		ofxUIRadio *radio = ( ofxUIRadio *) e.widget;
		changeState( radio->getActiveName() );
	}
}

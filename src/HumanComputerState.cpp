#include "HumanComputerState.h"
#include "SharedData.h"

void HumanComputerState::stateEnter()
{
	this->recording = false;
	running = false;
	this->allowParallels = true;
	animationSpeed = 0.0f;
	this->currentMouse = ofVec2f( ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 );

	currentPercentageX = currentPercentageY = 0.0f;
	currentPointIndex = 0;

	setupGUI();
	gui->setVisible( true );
}

void HumanComputerState::stateExit()
{
	this->gui->setVisible( false );
}

void HumanComputerState::update()
{
	if( running && this->data.pointData.size() > currentPointIndex + 1 )
	{
		ofVec2f fromPoint = this->data.pointData.at( currentPointIndex );
		ofVec2f toPoint = this->data.pointData.at( currentPointIndex + 1 );
		float distance = fromPoint.distance( toPoint );
		int toAdd = ofMap( distance, 0, 3000, animationSpeed, 1 );


		if( currentPercentageX >= 100 )
		{

			if( currentPercentageY >= 100 )
			{
				currentPercentageX = 0;
				currentPercentageY = 0;
				currentPointIndex++;
				if( currentPointIndex == this->data.pointData.size() - 1 )
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
}

void HumanComputerState::draw()
{
	if( running && this->data.pointData.size() > currentPointIndex + 1)
	{
		ofBackground( ofColor( 0 ) );
		glLineWidth( 2 );
		ofSetColor( ofColor( 255 ) );
		ofVec2f fromPoint = this->data.pointData.at( currentPointIndex );
		ofVec2f toPoint = this->data.pointData.at( currentPointIndex + 1 );
		float percentageX = currentPercentageX / 100.0;
		float percentageY = currentPercentageY / 100.0;
		float lerpedX, lerpedY;
		lerpedX = lerp( fromPoint.x, toPoint.x, percentageX );
		lerpedY = lerp( fromPoint.y, toPoint.y, percentageY );
		ofLine( fromPoint, ofVec2f( lerpedX, lerpedY ) );

		for( size_t i = 0; i < currentPointIndex && this->data.pointData.size() > 1; i++ ) 
		{
			ofVec2f from = this->data.pointData.at( i );
			ofVec2f to = this->data.pointData.at( i + 1 );
			ofLine( from, to );
		}
	}

	if( allowParallels && recording && !running )
	{
		debugDraw();
		std::cout << "0" << std::endl;
		if( this->data.pointData.size() > 0 )
		{
			std::cout << "1/2" << std::endl;
			ofVec2f from = this->data.pointData.at( this->data.pointData.size() - 1 );
			std::cout << "1" << std::endl;
			ofVec2f to = this->getCurrentMouse();
			std::cout << "2" << std::endl;
			ofLine( from, to );
		}

	} 
	if(recording && !running ) 
	{
		debugDraw();
	}
}

void HumanComputerState::debugDraw()
{
	//ofBackground( ofColor( 0 ) );
	ofSetColor( ofColor( 255, 255, 255, 100 ) );
	glLineWidth( 1 );

	for( size_t i = 0; i < this->data.pointData.size() - 1 && this->data.pointData.size() > 1; i++ ) 
	{
		ofVec2f from = this->data.pointData.at( i );
		ofVec2f to = this->data.pointData.at( i + 1 );
		ofLine( from, to );
	}
}


std::string HumanComputerState::getName()
{
	return getSharedData().HUMAN_COMPUTER;
}

void HumanComputerState::setupIdea( int pointNum )
{
	recording = true;
}

void HumanComputerState::setupImplementation()
{
	this->recording = false;
	this->running = true;
}

void HumanComputerState::setupGUI()
{
	setupIdeaButtonLabel = "SETUP_IDEA";
	setupImplementationButtonLabel = "SETUP IMPLEMENTATION (f)";
	startAnimationButtonLabel = "START ANIMATION";
	allowParallelsButtonLabel = "ALLOW_PARALLELS (p)";

	gui = new ofxUISuperCanvas( getSharedData().HUMAN_COMPUTER ); //shared_ptr<ofxUISuperCanvas>(new ofxUISuperCanvas( "COMPUTER_HUMAN" ) );

	gui->addSlider("POINTNUM", 5, 200, getPointCount() );
	gui->addSpacer();
	gui->addLabelButton( this->setupIdeaButtonLabel, false );
	gui->addSpacer();
	gui->addLabelButton( this->setupImplementationButtonLabel, false );
	gui->addSpacer();

	gui->addSpacer();
	gui->addLabelButton( this->startAnimationButtonLabel, false );
	gui->addSpacer();
	gui->addLabelButton( this->allowParallelsButtonLabel, false );
	gui->addSpacer();

	gui->addSlider( "ANIMATIONSPEED", 1, 50, &animationSpeed );
	gui->addSpacer();

	std::vector<std::string> stateNames;
	stateNames.push_back( getSharedData().COMPUTER_COMPUTER + " (1)" );
	stateNames.push_back( getSharedData().COMPUTER_HUMAN + " (2)" );
	stateNames.push_back( getSharedData().HUMAN_COMPUTER + " (3)" );
	stateNames.push_back( getSharedData().HUMAN_HUMAN + " (4)" );

	gui->addRadio( getSharedData().stateSelectionRadioButton, stateNames, OFX_UI_ORIENTATION_VERTICAL );

	gui->setGlobalButtonDimension( OFX_UI_GLOBAL_BUTTON_DIMENSION );
	gui->autoSizeToFitWidgets();
	ofAddListener( gui->newGUIEvent, this, &HumanComputerState::guiEvent );
}

void HumanComputerState::guiEvent( ofxUIEventArgs &e )
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();

	if( kind == OFX_UI_WIDGET_LABELBUTTON && e.getButton()->getValue() == 0 )
	{
		if( name == this->setupIdeaButtonLabel )
		{
			this->data.pointData.clear();
			setupIdea( *this->getPointCount() );
		}
		
		else if ( name == this->startAnimationButtonLabel )
		{
			running = !running;
			currentPercentageX = currentPercentageY = 0.0f;
			currentPointIndex = 0;
		}
		else if( name == this->allowParallelsButtonLabel )
		{
			this->allowParallels = !allowParallels;
		}
	}

	if( name == getSharedData().stateSelectionRadioButton )
	{
		ofxUIRadio *radio = ( ofxUIRadio *) e.widget;
		changeState( radio->getActiveName() );
	}
}

void HumanComputerState::mouseMoved( int x, int y )
{
	this->currentMouse = ofVec2f( x, y );
}

void HumanComputerState::mouseReleased( int x, int y, int button )
{
	this->data.pointData.push_back( ofVec2f( x, y ) );
	if( this->data.pointData.size() > *this->getPointCount() )
	{
		//recording = false;
	}
}

void HumanComputerState::keyPressed( int key )
{
	BaseStrokeState::keyPressed( key );
	switch( key )
	{
	case 'f':
		setupImplementation();
		break;
	case 'p':
		this->allowParallels = !allowParallels;
		break;
	}
}

ofVec2f HumanComputerState::getCurrentMouse()
{
	return currentMouse;
}


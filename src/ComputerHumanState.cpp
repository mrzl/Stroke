#include "ComputerHumanState.h"
#include "ComputerComputerState.h"

void ComputerHumanState::stateEnter()
{
	currentPointIndex = 0;
	currentDrawingIndex = 0;
	currentMouseDataIndex = 0;
	animationSpeed = 1;
	*getPointCount() = 100.0f;
	running = false;
	recording = false;
	
	if( this->data.mouseData.empty() )
	{
		recorded = false;
	}

	setupGUI();
	gui->setVisible( true );

	this->mouseData.resize( *getPointCount() );
}

void ComputerHumanState::stateExit()
{
	gui->setVisible( false );
}

void ComputerHumanState::update()
{
	currentMouseDataIndex += animationSpeed;
}

void ComputerHumanState::draw()
{
	std::cout << "draw" << std::endl;
	ofBackground( 0 );

	if( recording )
	{
		ofSetColor( 0, 255, 0 );
		glLineWidth( 5 );
		ofCircle( this->data.pointData.at( currentPointIndex ).x, this->data.pointData.at( currentPointIndex ).y, 10, 10 );
	}	
	else if( recorded )
	{
		ofSetColor( ofColor( 255, 255, 255, 100 ) );
		glLineWidth( 1 );

		for( size_t i = 0; i < currentDrawingIndex; i++ ) 
		{
			ofVec2f from = this->data.pointData.at( i );
			ofVec2f to = this->data.pointData.at( i + 1 );
			ofLine( from, to );
		}
		
		ofVec2f from = this->data.pointData.at( currentDrawingIndex );
		if( currentMouseDataIndex > this->mouseData.at(currentDrawingIndex).size() - 1 )
		{
			currentDrawingIndex++;
			if( currentDrawingIndex + 1 >= this->data.pointData.size() )
			{
				currentDrawingIndex = 0;
			}
			currentMouseDataIndex = 0;
		}
		if( currentMouseDataIndex > 0)
		{
			ofVec2f to = this->mouseData.at( currentDrawingIndex ).at( currentMouseDataIndex - 1 );
			ofLine( from , to );
		}
		
		/*
		for( size_t i = 0; i < this->data.mouseData.size() - 1 && this->data.mouseData.size() > 1; i++ ) 
		{
			//ofVec2f from = this->data.mouseData.at( i );
			ofVec2f from = this->data.pointData.at(currentDrawingIndex );
			
			ofVec2f to = this->data.mouseData.at( i + 1 );

			ofLine( from, to );
		}
		*/
	}
	if( !recorded )
	{
		ofSetColor( ofColor( 255, 255, 255, 100 ) );
		glLineWidth( 1 );

		for( size_t i = 0; i < this->data.pointData.size() - 1 && this->data.pointData.size() > 1; i++ ) 
		{
			ofVec2f from = this->data.pointData.at( i );
			ofVec2f to = this->data.pointData.at( i + 1 );
			ofLine( from, to );
		}
	}
}

void ComputerHumanState::mouseMoved( int x, int y )
{
	if( recording )
	{
		ofVec2f v( x, y );
		if( currentPointIndex > 0 )
		{
			this->data.mouseData.push_back( v );
			this->mouseData[currentPointIndex - 1].push_back( v );
		}

		float dist = v.distance( this->data.pointData.at( currentPointIndex ) );
		if( dist < 10 ) 
		{
			if( currentPointIndex == this->data.pointData.size() - 1 )
			{
				recording = false;
				recorded = true;
			}
			else 
			{
				currentPointIndex++;
			}
		}
	}
}

void ComputerHumanState::mouseReleased( int x, int y, int button )
{

}

void ComputerHumanState::keyPressed( int key )
{
	BaseStrokeState::keyPressed( key );
}

std::string ComputerHumanState::getName()
{
	return getSharedData().COMPUTER_HUMAN;
}

void ComputerHumanState::setupIdea( int numPoints )
{
	this->recorded = false;
	this->recording = false;
	this->data.pointData.clear();
	this->mouseData.clear();
	currentMouseDataIndex = 0;
	currentPointIndex = 0;
	currentDrawingIndex = 0;
	this->mouseData.resize( numPoints );

	for( int i = 0; i < *getPointCount(); i++ ) 
	{
		float x = ofRandom( 0, ofGetWidth() );
		float y = ofRandom( 0, ofGetHeight() );

		this->data.pointData.push_back( ofVec2f( x, y ) );
	}
}

void ComputerHumanState::setupGUI()
{
	setupIdeaButtonLabel = "SETUP_IDEA";
	setupImplementationButtonLabel = "SETUP IMPLEMENTATION";

	gui = new ofxUISuperCanvas( getSharedData().COMPUTER_HUMAN ); //shared_ptr<ofxUISuperCanvas>(new ofxUISuperCanvas( "COMPUTER_HUMAN" ) );

	gui->addSlider("POINTNUM", 5, 200, getPointCount() );
	gui->addSpacer();
	gui->addLabelButton( this->setupIdeaButtonLabel, false );
	gui->addSpacer();
	gui->addLabelButton( this->setupImplementationButtonLabel, false );
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
	ofAddListener( gui->newGUIEvent, this, &ComputerHumanState::guiEvent );
}

void ComputerHumanState::setupImplementation()
{
	recording = true;
	recorded = false;
	this->data.mouseData.clear();
}

void ComputerHumanState::guiEvent( ofxUIEventArgs &e )
{
	std::string name = e.getName();
	int kind = e.widget->getKind();

	if( name == getSharedData().stateSelectionRadioButton )
	{
		ofxUIRadio *radio = ( ofxUIRadio *) e.widget;
		changeState( radio->getActiveName() );
	}

	if( kind == OFX_UI_WIDGET_LABELBUTTON && e.getButton()->getValue() == 0 )
	{
		if( name == this->setupIdeaButtonLabel )
		{
			setupIdea( *this->getPointCount() );
		}
		if( name == this->setupImplementationButtonLabel )
		{
			setupImplementation();
		}
	}
}

#include "HumanComputerState.h"
#include "SharedData.h"

void HumanComputerState::stateEnter()
{
	BaseStrokeState::setupPointCount( 100 );
	//this->recording = false;
	this->state = INIT;
	this->allowParallels = true;
	animationSpeed = 1.0f;
	this->currentMouse = ofVec2f( ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 );
	this->currentMouseImportExportIndex = currentPointsImportExportIndex = 0;

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
	if( (this->state == RUNNING || this->state == DONE ) && this->currentData.pointData.size() > currentPointIndex + 1 )
	{
		ofVec2f fromPoint = this->currentData.pointData.at( currentPointIndex );
		ofVec2f toPoint = this->currentData.pointData.at( currentPointIndex + 1 );
		float distance = fromPoint.distance( toPoint );
		int toAdd = ofMap( distance, 0, 3000, animationSpeed, 1 );


		if( currentPercentageX >= 100 )
		{

			if( currentPercentageY >= 100 )
			{
				currentPercentageX = 0;
				currentPercentageY = 0;
				currentPointIndex++;
				if( currentPointIndex == this->currentData.pointData.size() - 1 )
				{
					currentPointIndex = 0;
					importPointData();
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
	BaseStrokeState::beforeDrawing();
	BaseStrokeState::setupColors();
	if( (this->state == RUNNING || this->state == DONE ) && this->currentData.pointData.size() > currentPointIndex + 1)
	{
		ofVec2f fromPoint = this->currentData.pointData.at( currentPointIndex );
		ofVec2f toPoint = this->currentData.pointData.at( currentPointIndex + 1 );
		float percentageX = currentPercentageX / 100.0;
		float percentageY = currentPercentageY / 100.0;
		float lerpedX, lerpedY;
		lerpedX = lerp( fromPoint.x, toPoint.x, percentageX );
		lerpedY = lerp( fromPoint.y, toPoint.y, percentageY );
		ofVec2f toLerped( lerpedX, lerpedY );
		ofLine( fromPoint, toLerped );
		fromPoint.limited( fromPoint.length() - 2 );
		fromPoint += (toLerped - fromPoint).getNormalized() * 2 / 2;
		toLerped += (fromPoint - toLerped).getNormalized() * 2;
		ofLine( fromPoint, toLerped );
		ofEllipse( fromPoint, getSharedData().strokeWeight, getSharedData().strokeWeight );
		ofEllipse( toLerped, getSharedData().strokeWeight, getSharedData().strokeWeight );

		for( size_t i = 0; i < currentPointIndex && this->currentData.pointData.size() > 1; i++ ) 
		{
			ofVec2f from = this->currentData.pointData.at( i );
			ofVec2f to = this->currentData.pointData.at( i + 1 );
			from.limited( from.length() - 2 );
			from += (to - from).getNormalized() * 2 / 2;
			to += (from - to).getNormalized() * 2;
			ofLine( from, to );
			ofEllipse( from, getSharedData().strokeWeight, getSharedData().strokeWeight );
			ofEllipse( to, getSharedData().strokeWeight, getSharedData().strokeWeight );
		}
	}

	if( allowParallels && this->state == RECORDING )
	{
		debugDraw();
		if( this->currentData.pointData.size() > 0 )
		{
			ofVec2f from = this->currentData.pointData.at( this->currentData.pointData.size() - 1 );
			ofVec2f to = this->getCurrentMouse();
			from.limited( from.length() - 2 );
			from += (to - from).getNormalized() * 2 / 2;
			to += (from - to).getNormalized() * 2;
			ofLine( from, to );
			ofEllipse( from, getSharedData().strokeWeight, getSharedData().strokeWeight );
			ofEllipse( to, getSharedData().strokeWeight, getSharedData().strokeWeight );
		}

	} 
	if( this->state == RECORDING ) 
	{
		debugDraw();
	}

	BaseStrokeState::afterDrawing();
}

void HumanComputerState::debugDraw()
{
	for( size_t i = 0; i < this->currentData.pointData.size() - 1 && this->currentData.pointData.size() > 1; i++ ) 
	{
		ofVec2f from = this->currentData.pointData.at( i );
		ofVec2f to = this->currentData.pointData.at( i + 1 );
		from.limited( from.length() - 2 );
		from += (to - from).getNormalized() * 2 / 2;
		to += (from - to).getNormalized() * 2;
		ofLine( from, to );
		ofEllipse( from, getSharedData().strokeWeight, getSharedData().strokeWeight );
		ofEllipse( to, getSharedData().strokeWeight, getSharedData().strokeWeight );
	}
}


std::string HumanComputerState::getName()
{
	return getSharedData().HUMAN_COMPUTER;
}

void HumanComputerState::setupIdea( int pointNum )
{
	this->state = RECORDING;
}

void HumanComputerState::setupImplementation()
{
	this->state = RUNNING;
}

void HumanComputerState::setupGUI()
{
	setupIdeaButtonLabel = "SETUP_IDEA";
	setupImplementationButtonLabel = "SETUP IMPLEMENTATION (a)";
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
			this->currentData.pointData.clear();
			setupIdea( *this->getPointCount() );
		}
		
		else if ( name == this->startAnimationButtonLabel )
		{
			switch( this->state )
			{
			case RUNNING:
				this->state = INIT;
				break;
			case INIT:
				this->state = RECORDING;
			}
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
	if( this->state == RECORDING )
	{
		this->currentData.pointData.push_back( ofVec2f( x, y ) );
	}
	
	if( this->currentData.pointData.size() > *this->getPointCount() )
	{
		//recording = false;
	}
}

void HumanComputerState::keyPressed( int key )
{
	BaseStrokeState::keyPressed( key );
	switch( key )
	{
	case 'a':
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


#include "ComputerComputerState.h"

void ComputerComputerState::stateEnter()
{
	BaseStrokeState::setupPointCount( 100 );
	//running = false;
	this->state = INIT;
	animationSpeed = 10.0f;


	currentPercentageX = currentPercentageY = 0.0f;
	currentPointIndex = 0;

	setupGUI();

	gui->setVisible( true );
}

void ComputerComputerState::setupGUI()
{
	setupIdeaButtonLabel = "SETUP_IDEA";
	importIdeaButtonLabel = "LOAD_IDEA";
	exportIdeaButtonLabel = "EXPORT";

	exportFileNameButtonLabel = "EXPORT FILE";
	importFileNameDropdownLabel = "SELECT FILE";

	startAnimationButtonLabel = "START ANIMATION";

	if( gui )
	{
		//gui->clearWidgets();
		//gui->removeWidgets();
	}

	gui = new ofxUISuperCanvas( getSharedData().COMPUTER_COMPUTER ); //shared_ptr<ofxUISuperCanvas>(new ofxUISuperCanvas( "COMPUTER_HUMAN" ) );

	gui->addSlider("POINTNUM", 5, 200, getPointCount() );
	gui->addSpacer();
	gui->addLabelButton( this->setupIdeaButtonLabel, false );
	gui->addSpacer();
	exportFileNameTextInput = gui->addTextInput( exportFileNameButtonLabel, "REMOVETHIS" );
	gui->addLabelButton( this->exportIdeaButtonLabel, false );
	gui->addSpacer();
	importFileNameDropDownList = gui->addDropDownList( this->importFileNameDropdownLabel, getAvailableSavedIdeas() );
	gui->addLabelButton( this->importIdeaButtonLabel, false );

	gui->addSpacer();
	gui->addLabelButton( this->startAnimationButtonLabel, false );
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
	ofAddListener( gui->newGUIEvent, this, &ComputerComputerState::guiEvent );
}

void ComputerComputerState::stateExit()
{
	//this->gui->removeWidgets();
	this->gui->setVisible( false );
	// this->gui->clearWidgets();
}

void ComputerComputerState::update()
{
	if( this->state == RUNNING && this->data.pointData.size() >= currentPointIndex + 1 )
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

void ComputerComputerState::draw()
{
	BaseStrokeState::setupColors();

	if( this->state == RUNNING && this->data.pointData.size() >= currentPointIndex + 1)
	{
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
			from.limited( from.length() - 2 );
			from += (to - from).getNormalized() * 2 / 2;
			to += (from - to).getNormalized() * 2;
			ofLine( from, to );
			ofEllipse( from, getSharedData().strokeWeight, getSharedData().strokeWeight );
			ofEllipse( to, getSharedData().strokeWeight, getSharedData().strokeWeight );
		}
	}
	else
	{
		debugDraw();
	}
}

void ComputerComputerState::debugDraw()
{
	for( size_t i = 0; i < this->data.pointData.size() - 1 && this->data.pointData.size() > 1; i++ )
	{
		ofVec2f from = this->data.pointData.at( i );
		ofVec2f to = this->data.pointData.at( i + 1 );
		from.limited( from.length() - 2 );
		from += (to - from).getNormalized() * 2 / 2;
		to += (from - to).getNormalized() * 2;
		ofLine( from, to );
		ofEllipse( from, getSharedData().strokeWeight, getSharedData().strokeWeight );
		ofEllipse( to, getSharedData().strokeWeight, getSharedData().strokeWeight );
	}
}


void ComputerComputerState::mouseMoved( int x, int y )
{

}

void ComputerComputerState::mouseReleased( int x, int y, int button )
{

}

void ComputerComputerState::keyPressed( int key )
{
	BaseStrokeState::keyPressed( key );
}

void ComputerComputerState::setupIdea( int pointNum )
{
	this->data.pointData.clear();
	for( int i = 0; i < pointNum; i++ )
	{
		float x = ofRandom( 0, ofGetWidth() );
		float y = ofRandom( 0, ofGetHeight() );

		this->data.pointData.push_back( ofVec2f( x, y ) );
	}
}

void ComputerComputerState::setupImplementation()
{

}

std::string ComputerComputerState::getName()
{
	return getSharedData().COMPUTER_COMPUTER;
}

void ComputerComputerState::guiEvent( ofxUIEventArgs &e )
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();

	if( kind == OFX_UI_WIDGET_LABELBUTTON && e.getButton()->getValue() == 0 )
	{
		if( name == this->setupIdeaButtonLabel )
		{
			setupIdea( *this->getPointCount() );
		}
		else if ( name == this->exportIdeaButtonLabel )
		{
			exportIdea( exportFileNameTextInput->getTextString() );
			exportFileNameTextInput->recalculateDisplayString();
		}
		else if ( name == this->importIdeaButtonLabel )
		{
			if( !importFileNameDropDownList->getSelectedNames().empty() )
			{
				std::string selectedFileName = importFileNameDropDownList->getSelectedNames().at( 0 );
				importIdea( selectedFileName );
			}
		}
		else if ( name == this->startAnimationButtonLabel )
		{
			switch( this->state )
			{
			case RUNNING:
				this->state = INIT;
				break;
			case INIT:
				this->state = RUNNING;
			}
			currentPercentageX = currentPercentageY = 0.0f;
			currentPointIndex = 0;
		}
	}

	if( name == getSharedData().stateSelectionRadioButton )
	{
		ofxUIRadio *radio = ( ofxUIRadio *) e.widget;
		changeState( radio->getActiveName() );
	}
}

void ComputerComputerState::importIdea( std::string filePath )
{
	wng::ofxCsv * pointDataImporter = new wng::ofxCsv();
	pointDataImporter->loadFile( ofToDataPath( "saved/" + filePath ) );
	this->data.pointData.clear();
	for( std::vector< std::vector< std::string > >::iterator it = pointDataImporter->data.begin(); it != pointDataImporter->data.end(); ++it )
	{
		std::vector<std::string> * pointS = &( * it );
		std::string xS, yS;
		int x, y;

		xS = pointS->at( 0 );
		yS = pointS->at( 1 );

		x = atoi( xS.c_str() );
		y = atoi( yS.c_str() );

		ofVec2f point( x, y );
		this->data.pointData.push_back( point );
	}

	*this->getPointCount() = this->data.pointData.size();
	delete pointDataImporter;
}

void ComputerComputerState::exportIdea( std::string fileName )
{
	wng::ofxCsv * pointDataExporter = new wng::ofxCsv();
	this->data.pointData.clear();
	//this->data.mouseData.clear();
	for( std::vector< ofVec2f >::iterator it = this->data.pointData.begin(); it != this->data.pointData.end(); ++it )
	{
		ofVec2f recordedPoints = *it;
		int row = pointDataExporter->numRows;
		pointDataExporter->setFloat(row, 0, recordedPoints.x );
		pointDataExporter->setFloat(row, 1, recordedPoints.y );
	}

	std::stringstream ss;
	ss << "saved/";
	ss << fileName;
	pointDataExporter->saveFile( ofToDataPath( ss.str() ) );
	delete pointDataExporter;
}

std::vector< std::string > ComputerComputerState::getAvailableSavedIdeas()
{
	std::vector< std::string > ideas;

	ofDirectory dir( ofToDataPath( "saved" ) );
	dir.allowExt( "csv" );
	dir.listDir();

	for( int i = 0; i < dir.numFiles(); i++ )
	{
		ideas.push_back( dir.getFile( i ).getFileName() );
	}

	return ideas;
}

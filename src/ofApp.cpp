#include "ofApp.h"
#include "DrawingState.h"
#include "FollowBallState.h"
#include "RecreateState.h"

#include "ComputerComputerState.h"
#include "ComputerHumanState.h"
#include "HumanComputerState.h"
#include "HumanHumanState.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);

	stateMachine.getSharedData().COMPUTER_COMPUTER = "COMPUTER_COMPUTER";
	stateMachine.getSharedData().COMPUTER_HUMAN = "COMPUTER_HUMAN";
	stateMachine.getSharedData().HUMAN_COMPUTER = "HUMAN_COMPUTER";
	stateMachine.getSharedData().HUMAN_HUMAN = "HUMAN_HUMAN";

	stateMachine.getSharedData().MOUSE_MOVEMENT_FILENAME = "MOUSE_MOVEMENT_RECORDING.csv";
	stateMachine.getSharedData().POINTS_FILENAME = "POINTS_RECORDING.csv";

	stateMachine.getSharedData().stateSelectionRadioButton = "STATE";

	stateMachine.getSharedData().backgroundColor = ofColor( 255, 255, 255 );
	stateMachine.getSharedData().lineColor = ofColor( 0, 0, 0 );
	stateMachine.getSharedData().strokeWeight = 5;

	stateMachine.addState<ComputerComputerState>();
	stateMachine.addState<ComputerHumanState>();
	stateMachine.addState<HumanComputerState>();
	stateMachine.addState<HumanHumanState>();

	stateMachine.changeState(stateMachine.getSharedData().COMPUTER_COMPUTER);

	//ofSetFullscreen( true );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key)
	{
	case 'f':
		ofToggleFullscreen();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#include "ofApp.h"
#include "DrawingState.h"
#include "FollowBallState.h"
#include "RecreateState.h"

#include "ComputerComputerState.h"
#include "ComputerHumanState.h"
#include "HumanComputerState.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);

	stateMachine.getSharedData().DRAWING_STATE = "DRAWING_STATE";
	stateMachine.getSharedData().FOLLOW_BALL_STATE = "FOLLOW_BALL_STATE";
	stateMachine.getSharedData().RECREATE_STATE= "RECREATE_STATE";

	stateMachine.getSharedData().COMPUTER_COMPUTER = "COMPUTER_COMPUTER";
	stateMachine.getSharedData().COMPUTER_HUMAN = "COMPUTER_HUMAN";
	stateMachine.getSharedData().HUMAN_COMPUTER = "HUMAN_COMPUTER";
	stateMachine.getSharedData().HUMAN_HUMAN = "HUMAN_HUMAN";

	stateMachine.getSharedData().MOUSE_MOVEMENT_FILENAME = "MOUSE_MOVEMENT_RECORDING.csv";
	stateMachine.getSharedData().POINTS_FILENAME = "POINTS_RECORDING.csv";

	stateMachine.getSharedData().stateSelectionRadioButton = "STATE";

	//stateMachine.addState<DrawingState>();
	//stateMachine.addState<FollowBallState>();
	//stateMachine.addState<RecreateState>();

	stateMachine.addState<ComputerComputerState>();
	stateMachine.addState<ComputerHumanState>();
	stateMachine.addState<HumanComputerState>();

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

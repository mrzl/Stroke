#include "ofApp.h"
#include "DrawingState.h"
#include "FollowBallState.h"
#include "RecreateState.h"

//--------------------------------------------------------------
void ofApp::setup(){
	stateMachine.getSharedData().FOLLOW_BALL_STATE = "DRAWING_STATE";
	stateMachine.getSharedData().ANIMATION_STATE = "ANIMATION_STATE";
	stateMachine.getSharedData().RECREATE_STATE= "RECREATE_STATE";

	stateMachine.getSharedData().MOUSE_MOVEMENT_FILENAME = "MOUSE_MOVEMENT_RECORDING.csv";
	stateMachine.getSharedData().POINTS_FILENAME = "POINTS_RECORDING.csv";

	stateMachine.addState<DrawingState>();
	stateMachine.addState<FollowBallState>();
	stateMachine.addState<RecreateState>();
	stateMachine.changeState(stateMachine.getSharedData().FOLLOW_BALL_STATE);

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
	std::cout << "original mouseReleased" << std::endl;
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

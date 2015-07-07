/*
 *  LedCostumeApp.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 07/07/15.
 *
 */

#include "AppManager.h"

#include "LedCostumeApp.h"

//--------------------------------------------------------------
void LedCostumeApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void LedCostumeApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void LedCostumeApp::draw(){
    AppManager::getInstance().draw();
}

void LedCostumeApp::exit()
{
    ofLogNotice() <<"LedCostumeApp::exit";

}

//--------------------------------------------------------------
void LedCostumeApp::keyPressed(int key){

}

//--------------------------------------------------------------
void LedCostumeApp::keyReleased(int key){

}

//--------------------------------------------------------------
void LedCostumeApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void LedCostumeApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void LedCostumeApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void LedCostumeApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void LedCostumeApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void LedCostumeApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void LedCostumeApp::dragEvent(ofDragInfo dragInfo){

}

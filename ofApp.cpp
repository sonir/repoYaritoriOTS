#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){        
    
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);
//    ofEnableSmoothing();

    network.setup();
    network.setShapePtr(vsyn.ag_shapes);
    
    vsyn.initWindowSize();
    vsyn.setup();

    network.setup();

    
}

//--------------------------------------------------------------
void ofApp::update(){

    vsyn.update();
    network.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    vsyn.draw();
#ifdef DEBUG_MODE
    ofDrawBitmapString("fps = " + ofToString(ofGetFrameRate()), 10, 20);
#endif
//    ofDrawBitmapString("fps = " + ofToString(ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    vsyn.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    GismoManager& gismo = GismoManager::getInstance();
    int flg = 0;
    
    switch(key){
            
        case 'f':
            ofToggleFullscreen();
            break;
        case 'a':
            flg = 1;
            break;
        case 's':
            flg=2;
            break;
            
    }
    
    
    
    if(flg==1)
    {
        performer_e pfmr = GUITAR;
        gismo.bang("/performance/atk" , &pfmr);
        
        
    }else if(flg==2){
        
        performer_e pfmr = DRUMS;
        gismo.bang("/performance/atk" , &pfmr);

        
    }
    

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
#ifdef DEBUG_MODE
    vsyn.initWindowSize();
#endif
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

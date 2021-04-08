#include "ofApp.h"

using namespace glm;

ofImage img;

ofMesh mesh;

vec2 xLimits(-0.75, 0.75);
vec2 zLimits(0, 2.25);
vec2 yLimits(-0.9, 0.75);

union packedfloat {
  float f;
  unsigned char bytes[4];
};

float unpackFloat(ofColor c) {
    packedfloat p;
    p.bytes[0] = c.r;
    p.bytes[1] = c.g;
    p.bytes[2] = c.b;
    p.bytes[3] = c.a;
    
    return p.f;
}

bool isWithinBounds(float x, float y, float z) {
    if (x < xLimits.x || x > xLimits.y) {
        return false;
    }
    
    if (y < yLimits.x || y > yLimits.y) {
        return false;
    }
    
    if (z < zLimits.x || z > zLimits.y) {
        return false;
    }
    
    return true;
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();

	ofSetCircleResolution(64);
	bHelpText = true;
    
    img.load("test0.png");
    
    mesh.clear();
    
    // Create mesh from image
    const int w = img.getWidth();
    const int h = img.getHeight();
    for (int i = 0; i < w; i += 4) {
        for (int j = 0; j < h; j++) {
            // Four consecutive pixels form one depth pixel
            // Pixel 1's rgb forms x
            ofColor p1 = img.getColor(i, j);
            ofColor p2 = img.getColor(i + 1, j);
            ofColor p3 = img.getColor(i + 2, j);
            ofColor p4 = img.getColor(i + 3, j);
            
            float x = unpackFloat(p1);
            float y = unpackFloat(p2);
            float z = unpackFloat(p3);
            
            if (isWithinBounds(x, y, z)) {
                mesh.addVertex(glm::vec3(x, y, z));
            }
        }
    }
    
    // Setup camera params
    cam.setNearClip(0.01f);
    cam.setFarClip(100.0f);
    cam.setPosition(-2,2,-2);
    cam.setTarget(glm::vec3(0,0,0));
    cam.setDistance(2);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(20);
	cam.begin();
    ofEnableDepthTest();

    
    ofDrawGrid(0.25, 10,true,true,true,true);
    
    ofSetColor(255);
    
    mesh.drawVertices();
    
    ofDisableDepthTest();
    
    cam.end();
    
	drawInteractionArea();
    
    

    if (bHelpText) {
        stringstream ss;
        ss << "Very helpful help text TODO" << endl;
        
        ofDrawBitmapString(ss.str().c_str(), 20, 20);
    }

}
//--------------------------------------------------------------
void ofApp::drawInteractionArea(){
	ofRectangle vp = ofGetCurrentViewport();
	float r = std::min<float>(vp.width, vp.height) * 0.5f;
	float x = vp.width * 0.5f;
	float y = vp.height * 0.5f;

	ofPushStyle();
	ofSetLineWidth(3);
	ofSetColor(255, 255, 0);
	ofNoFill();
	glDepthMask(false);
	ofDrawCircle(x, y, r);
	glDepthMask(true);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
      case ' ':
    	    cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
            break;
	    case 'C':
	    case 'c':
            cam.getMouseInputEnabled() ? cam.disableMouseInput() : cam.enableMouseInput();
            break;
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'H':
		case 'h':
			bHelpText ^=true;
			break;
        case 'I':
        case 'i':
		    cam.getInertiaEnabled() ? cam.disableInertia() : cam.enableInertia();
            break;
        case 'Y':
        case 'y':
            cam.setRelativeYAxis(!cam.getRelativeYAxis());
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

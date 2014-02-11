/* Spencer Barton
 *
 * Got help from http://forum.openframeworks.cc/t/earth-iphone-app/2324/4 for image map to sphere
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// ofSettings
	ofBackgroundHex(0); // black
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetVerticalSync(true);
	//ofDisableAntiAliasing();

	// Box2d
	box2d.init();
	box2d.setGravity(0, 10);
    box2d.createGround();
	box2d.setFPS(30.0);
    box2d.registerGrabbing();

    testRect = ofPtr<ofxBox2dRect>(new ofxBox2dRect());

    testRect.get()->setPhysics(0.3, 0.5, 0.1);
    testRect.get()->setup( box2d.getWorld(), ofRectangle(100,100,10,10) );

    generateEdges();

	// load soap image widthtexture
	texture.loadImage(TEXTURE_FILENAME);

    cout << "Img at :" << ofToString(&texture)<< endl;

    // csv load and parse
	csv.loadFile(ofToDataPath(DATA_FILENAME), CSV_SEPERATOR);

	// populate data vector
	for(int i=0; i < csv.numRows; i++) {

		string countryName = csv.getString(i, 0);
		float capacity = csv.getFloat(i, 1);

        cout << countryName << ": " << ofToString(capacity)<< endl;

		// generate rectangle bar of soap
		ofPtr<SoapBar> soapBar = ofPtr<SoapBar>(new SoapBar(countryName, capacity));
		soapBars.push_back(soapBar);
		soapBars.back().get()->setPhysics(BOX_DENSITY, BOX_BOUNCE, BOX_FRICTION);
		soapBars.back().get()->setTexture(&texture);
		soapBars.back().get()->setup(box2d.getWorld());

	}

	cout << "Done loading: " << ofToString(box2d.getBodyCount()) << endl;

}

//--------------------------------------------------------------
void testApp::update(){

	box2d.update();

	//cout << ofToString(box2d.getBodyCount()) << endl;

}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(255,255,255);
	for (int i=0; i < soapBars.size(); i++) {
        soapBars[i].get()->draw();
    }

    ofSetColor(255,255,0);
    // testRect.get()->draw();
    texture.draw(0,0);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	generateEdges();
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void testApp::generateEdges(){

	// empty edges to repopulate
	edges.clear();

    // add edges at sides of screen
    ofPtr<ofxBox2dEdge> rightEdge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	rightEdge.get()->addVertex( ofGetWidth(), ofGetHeight() );
	rightEdge.get()->addVertex( ofGetWidth(), 0 );
	rightEdge.get()->setPhysics(-1, 0, 0); // immovable
	rightEdge.get()->create( box2d.getWorld() );

    ofPtr<ofxBox2dEdge> leftEdge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	leftEdge.get()->addVertex( 0, ofGetHeight() );
	leftEdge.get()->addVertex( 0, 0 );
	leftEdge.get()->setPhysics(-1, 0, 0); // immovable
	leftEdge.get()->create( box2d.getWorld() );

    ofPtr<ofxBox2dEdge> topEdge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	topEdge.get()->addVertex( ofGetWidth(), 0 );
	topEdge.get()->addVertex( 0, 0 );
	topEdge.get()->setPhysics(-1, 0, 0); // immovable
	topEdge.get()->create( box2d.getWorld() );

    box2d.createGround();

	edges.push_back(rightEdge);
	edges.push_back(leftEdge);
	edges.push_back(topEdge);

}

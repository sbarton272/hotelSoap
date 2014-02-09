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
	ofDisableAntiAliasing();

	// Box2d
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createGround();
	box2d.setFPS(30.0);
    box2d.registerGrabbing(); // TODO needed?

    // add edges at sides of screen
    ofPtr<ofxBox2dEdge> rightEdge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	rightEdge.get()->addVertex( ofGetWidth(), ofGetHeight() );
	rightEdge.get()->addVertex( ofGetWidth(), 0 );
	rightEdge.get()->create( box2d.getWorld() );

    ofPtr<ofxBox2dEdge> leftEdge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	leftEdge.get()->addVertex( 0, ofGetHeight() );
	leftEdge.get()->addVertex( 0, 0 );
	leftEdge.get()->create( box2d.getWorld() );

    ofPtr<ofxBox2dEdge> topEdge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	topEdge.get()->addVertex( ofGetWidth(), 0 );
	topEdge.get()->addVertex( 0, 0 );
	topEdge.get()->create(box2d.getWorld());

	edges.push_back(rightEdge);
	edges.push_back(leftEdge);
	edges.push_back(topEdge);

	// load soap image texture
	texture.loadImage(TEXTURE_FILENAME);

    // csv load and parse
	csv.loadFile(ofToDataPath(DATA_FILENAME), CSV_SEPERATOR);

	// populate data vector
	for(int i=0; i < csv.numRows; i++) {

		string countryName = csv.getString(i, 0);
		float capacity = csv.getFloat(i, 1);

		// generate rectangle bar of soap
		ofPtr<SoapBar> soapBar = ofPtr<SoapBar>(new SoapBar(countryName, capacity));
		soapBar.get()->setPhysics(BOX_DENSITY, BOX_BOUNCE, BOX_FRICTION);
		//s.soapBar.get()->setTexture(texture);
		soapBar.get()->setup(box2d);
		soapBars.push_back(soapBar);

	}

	cout << "Done loading" << endl;

}

//--------------------------------------------------------------
void testApp::update(){

	box2d.update();

}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0);
	for (int i=0; i < edges.size(); i++) {
		edges[i].get()->draw();
	}

    ofSetColor(255,255,255);
	for (int i=0; i < soapBars.size(); i++) {
        soapBars[i].get()->draw();
    }


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
	// TODO redraw constraints
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}


//  Started from by Todd Vanderlin's TextureShape.h (7/16/13).
//  https://github.com/vanderlin/ofxBox2d/blob/c09ea8796647a3b162de677f498f5fe26b8b5a3d/example-ShapeTexturing/src/TextureShape.h

//--------------------------------------------------------------
SoapBar::SoapBar(string name, float cap) {
    texturePtr = NULL;
    countryName = name;
    capacity = cap;
}

//--------------------------------------------------------------
void SoapBar::setup(ofxBox2d &world) {


	// random starting locations
	float x = ofRandom(0, ofGetWidth());
	float y = ofRandom(0, ofGetHeight()/2);
	// capacity maps to area, so take sqrt of capacity
	float l = SOAP_BAR_SIZE * sqrt( capacity / MAX_CAPACITY );
	float w = GOLDEN_RATIO*l;
	float h = l/GOLDEN_RATIO;

	rect = ofxBox2dRect();
    rect.setup( world.getWorld(), ofRectangle(x,y,w,h) );

}

//--------------------------------------------------------------
void SoapBar::setPhysics(float density, float bounce, float friction) {
    rect.setPhysics(density, bounce, friction);
}

//--------------------------------------------------------------
void SoapBar::setTexture(ofImage * texture) {
    texturePtr = texture;
    texturePtr->getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST); // TODO rescaling
}

//--------------------------------------------------------------
void SoapBar::draw() {

    // display mesh with texture
    texturePtr->bind();
    rect.draw();
    texturePtr->unbind();

}

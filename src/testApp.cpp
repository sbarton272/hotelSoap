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

}

//--------------------------------------------------------------
void testApp::draw(){

	string countryInfo = "";

    ofSetColor(255,255,255);
	for (int i=0; i < soapBars.size(); i++) {
        SoapBar* b = soapBars[i].get();
        b->draw();

        // determine if mouse is over bar (couldn't get events to work)
        ofVec2f v = b->rect.get()->getPosition();
        // normalize position to bring origin to corner of box
        float x = mouseX - v.x;
        float y = mouseY - v.y;
        // store mouse loc relative to rect
        ofVec2f normMouse = ofVec2f(x,y);
        // calculate rotation of rect
		float angle = b->rect.get()->getRotation();
		// rotate mouse pos back by the rotation
		normMouse.rotate( -angle );
		// normalize mouse to pos value if inside
		normMouse.x = normMouse.x + b->width/2;
		normMouse.y = normMouse.y + b->height/2;
		// mouse pos has been rotated enough for these tests to see if inside rect:
		// There is probably a much much better way to do this but whatever.

        // for testing
		if( b->countryName == "United States" ) {
			ofSetColor(255,0,255);
			ofCircle(normMouse.x, normMouse.y, 10);
			ofCircle(v.x, v.y, 10);
			ofSetColor(255,0,0);
			ofCircle(0, 0, 10);
			ofCircle(b->width, b->height, 10);
		}

        if( (normMouse.x >= 0) && (normMouse.x <= b->width) &&
        	(normMouse.y >= 0) && (normMouse.y <= b->height) )  {
        	// mouse is pointing inside rect
        	cout << "Mouse over: " << b->countryName << endl;
        	countryInfo += b->countryName + " uses approximately " + ofToString(b->capacity * LBS_BAR) + "lbs of soap daily";
        }
    }

	string info = "";
	info += "Every day hotels worldwide replace the soap in their bathrooms.\n";
	info += "The bars of soap below are proportional in area to the soup replaced by country.\n";
	info += "Approximatively " + ofToString(WORLD_CAPACITY * LBS_BAR) + " lbs of soap used worldwide daily.\n";
	info += countryInfo;

	ofSetHexColor(0xF1F1FD);
	ofDrawBitmapString(info, 30, 30);

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

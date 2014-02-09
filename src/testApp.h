#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxBox2d.h"
//#include "SoapBar.h"

using namespace wng;

class SoapBar {

public:

    ofImage*        texturePtr;
    ofMesh          mesh;
    ofxBox2dRect    rect;
    string          countryName;
    float           capacity;

    SoapBar(string name, float cap);

    void setup(ofxBox2d &world);
    void setPhysics(float density, float bounce, float friction);
    void setTexture(ofImage * texture);
    void draw();

    const float GOLDEN_RATIO = 1.61803398875;
    const float SOAP_BAR_SIZE = 100;
    const float MAX_CAPACITY = 4480838;

};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);

        ofxCsv csv;
        ofImage texture;
        vector < ofPtr<SoapBar> > soapBars;
        vector < ofPtr<ofxBox2dEdge> > edges;
        ofxBox2d box2d;

		// country name, country capacity
        const string DATA_FILENAME = "countrySize.txt";
        const string CSV_SEPERATOR = "\t";

        const string TEXTURE_FILENAME = "barSoap.jpg";

        const float BOX_DENSITY = 3.0;
        const float BOX_BOUNCE = 0.5;
        const float BOX_FRICTION = 0.1;

};

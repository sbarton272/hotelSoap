#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxBox2d.h"
#include "SoapBar.h"

#define LBS_BAR .225
#define WORLD_CAPACITY 25075286


using namespace wng;

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

        private:

                void generateEdges();

                ofxCsv csv;
                ofImage texture;
                vector < ofPtr<SoapBar> > soapBars;
                vector < ofPtr<ofxBox2dEdge> > edges;
                ofxBox2d box2d;

                ofPtr<ofxBox2dRect> testRect;

        	// country name, country capacity
                const string DATA_FILENAME = "countrySize.txt";
                const string CSV_SEPERATOR = "\t";

                const string TEXTURE_FILENAME = "barSoap.png";

                const float BOX_DENSITY = .3;
                const float BOX_BOUNCE = 0.5;
                const float BOX_FRICTION = 0.1;

};

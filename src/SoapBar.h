//  Started from by Todd Vanderlin's TextureShape.h (7/16/13).
//  https://github.com/vanderlin/ofxBox2d/blob/c09ea8796647a3b162de677f498f5fe26b8b5a3d/example-ShapeTexturing/src/TextureShape.h

#pragma once
#include <math.h>
#include "ofMain.h"
#include "ofxBox2d.h"

#define GOLDEN_RATIO    1.61803398875
#define SOAP_BAR_SIZE   100.0
#define MAX_CAPACITY    4480838.0

class SoapBar {

public:

    SoapBar(string name, float cap);
	
    void setup(b2World* world);
    void setPhysics(float density, float bounce, float friction);
    void setTexture(ofImage * tex);
    void draw();

    ofImage             texture;
    ofPtr<ofxBox2dRect> rect;
    string              countryName;
    float               capacity;
    float				width;
    float				height;


};

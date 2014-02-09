//  Started from by Todd Vanderlin's TextureShape.h (7/16/13).
//  https://github.com/vanderlin/ofxBox2d/blob/c09ea8796647a3b162de677f498f5fe26b8b5a3d/example-ShapeTexturing/src/TextureShape.h

#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class SoapBar {

public:

    ofImage*        texturePtr;
    ofMesh          mesh;
    ofxBox2dRect    rect;

    SoapBar();

    void setup(b2World * world, ofRectangle r, string countryName, float capacity);
    void setPhysics(float density, float bounce, float friction);
    void setTexture(ofImage * texture);
    void draw();

};

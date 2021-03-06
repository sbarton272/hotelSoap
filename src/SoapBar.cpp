//  Started from by Todd Vanderlin's TextureShape.h (7/16/13).
//  https://github.com/vanderlin/ofxBox2d/blob/c09ea8796647a3b162de677f498f5fe26b8b5a3d/example-ShapeTexturing/src/TextureShape.h

#include "SoapBar.h"


//--------------------------------------------------------------
SoapBar::SoapBar(string name, float cap) {
    countryName = name;
    capacity = cap;
    rect = ofPtr<ofxBox2dRect>(new ofxBox2dRect());

    float l = SOAP_BAR_SIZE * sqrt( capacity / MAX_CAPACITY );
    float w = ceil(GOLDEN_RATIO*l);
    float h = ceil(l/GOLDEN_RATIO);

    this->width = w;
    this->height = h;

}


//--------------------------------------------------------------
void SoapBar::setup(b2World* world) {

    // random starting locations
    float x = ofRandom(0, ofGetWidth());
    float y = ofRandom(0, ofGetHeight()/2);
    // capacity maps to area, so take sqrt of capacity
    float l = SOAP_BAR_SIZE * sqrt( capacity / MAX_CAPACITY );
    float w = ceil(GOLDEN_RATIO*l);
    float h = ceil(l/GOLDEN_RATIO);

    rect.get()->setup( world,x,y,w,h );

}

//--------------------------------------------------------------
void SoapBar::setPhysics(float density, float bounce, float friction) {
    rect.get()->setPhysics(density, bounce, friction);
}

//--------------------------------------------------------------
void SoapBar::setTexture(ofImage * tex) {
    texture.clone(*tex);
    texture.resize(width, height);
}

//--------------------------------------------------------------
void SoapBar::draw() {

    ofPushMatrix();
    ofTranslate(rect.get()->getPosition());
    ofRotate(rect.get()->getRotation());
    texture.draw( -width/2, -height/2);
    ofPopMatrix();


}

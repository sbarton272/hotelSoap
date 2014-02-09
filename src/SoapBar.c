//  Started from by Todd Vanderlin's TextureShape.h (7/16/13).
//  https://github.com/vanderlin/ofxBox2d/blob/c09ea8796647a3b162de677f498f5fe26b8b5a3d/example-ShapeTexturing/src/TextureShape.h

#include "SoapBar.h"

//--------------------------------------------------------------
SoapBar::SoapBar() {
    texturePtr = NULL;
}

//--------------------------------------------------------------
void SoapBar::setup(b2World &world, ofRectangle r, string countryName, float capacity) {

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    int   nPts  = 8;
    float scale = r / (float)texturePtr->getWidth();
    for (int i=0; i<nPts; i++) {
        float n = ofMap(i, 0, nPts-1, 0.0, TWO_PI);
        float x = cos(n);
        float y = sin(n);
        float d = ofRandom(-r/2, r/2);
        polyShape.addVertex(ofPoint(cx + (x * r + d), cy + (y * r + d)));
        mesh.addTexCoord(ofPoint(0, 0));
        mesh.addTexCoord(ofPoint(x * scale, y * scale));
    }

	rect.create(world.getWorld());


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

    // generate mesh
    mesh.clearVertices();
    vector<ofPoint> &pts = rect.getPoints();
    ofPoint center       = rect.getCentroid2D();

    for (int i=0; i<pts.size(); i++) {
        mesh.addVertex(center);
        mesh.addVertex(pts[i]);
    }

    mesh.addVertex(center);
    mesh.addVertex(pts.front());

    // display mesh with texture
    texturePtr->bind();
    mesh.draw();
    texturePtr->unbind();

}
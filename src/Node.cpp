#include "Node.h"

#define COLOUR_WHITE 255

#define DEFAULT_RADIUS 10
#define DEFAULT_COLOUR COLOUR_WHITE

//--------------------------------------------------------------
Node::Node(){

    radius = DEFAULT_RADIUS;
    colour = DEFAULT_COLOUR;
}

//--------------------------------------------------------------
Node::~Node(){

}

//--------------------------------------------------------------
void Node::setup(){

}

//--------------------------------------------------------------
void Node::update(){

}

//--------------------------------------------------------------
void Node::draw(float x, float y){

    xPos = x;
    yPos = y;

    ofSetColor(colour);
    ofDrawCircle(xPos, yPos, radius);
}

//--------------------------------------------------------------
uint8_t Node::getRadius(){

    return radius;
}

//--------------------------------------------------------------
float Node::getXPos(){

    return xPos;
}

//--------------------------------------------------------------
float Node::getYPos(){

    return yPos;
}

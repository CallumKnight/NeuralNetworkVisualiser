#include "Connection.h"

#define COLOUR_WHITE 255

#define DEFAULT_COLOUR COLOUR_WHITE

//--------------------------------------------------------------
Connection::Connection(){

    colour = DEFAULT_COLOUR;
}

//--------------------------------------------------------------
Connection::~Connection(){

}

//--------------------------------------------------------------
void Connection::setup(){

}

//--------------------------------------------------------------
void Connection::update(){

}

//--------------------------------------------------------------
void Connection::draw(float xStart, float yStart, float xEnd, float yEnd){

    xPosStart = xStart;
    yPosStart = yStart;
    xPosEnd = xEnd;
    yPosEnd = yEnd;

    ofSetColor(colour);
    ofDrawLine(xPosStart, yPosStart, xPosEnd, yPosEnd);
}

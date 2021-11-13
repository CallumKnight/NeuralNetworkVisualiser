#include "Layer.h"

#define DEFAULT_NUM_NODES 5
#define NODE_SPACING 15

//--------------------------------------------------------------
Layer::Layer(){

    nodes.resize(DEFAULT_NUM_NODES);
}

//--------------------------------------------------------------
Layer::~Layer(){

}

//--------------------------------------------------------------
void Layer::setup(uint8_t size){

    nodes.resize(size);
}

//--------------------------------------------------------------
void Layer::update(){

}

//--------------------------------------------------------------
void Layer::draw(float x, float y){

    xPos = x;
    yPos = y;

    float offset = 0;

    for(Node node : nodes){
        node.draw(xPos, yPos + offset);
        offset += (2*node.getRadius()) + NODE_SPACING;
    }
}

//--------------------------------------------------------------
uint8_t Layer::getWidth(){

    return 2*nodes[0].getRadius();
}

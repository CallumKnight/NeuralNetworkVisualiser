#include "Network.h"

#define DEFAULT_NUM_LAYERS 5
#define LAYER_SPACING 30

//--------------------------------------------------------------
Network::Network(){

    numLayers = DEFAULT_NUM_LAYERS;
    layers.resize(numLayers);
}

//--------------------------------------------------------------
Network::~Network(){

}

//--------------------------------------------------------------
void Network::update(){

}

//--------------------------------------------------------------
void Network::draw(float x, float y){

    xPos = x;
    yPos = y;

    float offset = 0;

    for(Layer layer : layers){
        layer.draw(xPos + offset, yPos);
        offset += layer.getWidth() + LAYER_SPACING;
    }
}

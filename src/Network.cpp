#include "Network.h"

#define DEFAULT_NUM_LAYERS 5
#define LAYER_SPACING 40

//--------------------------------------------------------------
Network::Network(){

    layers.resize(DEFAULT_NUM_LAYERS);
}

//--------------------------------------------------------------
Network::~Network(){

}

//--------------------------------------------------------------
void Network::setup(std::vector<uint8_t> layerSizes){

    layers.resize(layerSizes.size());

    uint8_t index = 0;

    for(uint8_t size : layerSizes){
        layers[index].setup(size);
        index++;
    }
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

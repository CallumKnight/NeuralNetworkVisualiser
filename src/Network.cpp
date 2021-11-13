#include "Network.h"

#define DEFAULT_NUM_LAYERS 5
#define LAYER_SPACING 100

//--------------------------------------------------------------
Network::Network(){

    layers.resize(DEFAULT_NUM_LAYERS);
}

//--------------------------------------------------------------
Network::~Network(){

}

//--------------------------------------------------------------
void Network::setup(std::vector<uint8_t> layerSizes){

    uint8_t numLayers = layerSizes.size();
    uint8_t index = 0;
    
    layers.resize(numLayers);
    connectionsTensor.resize(numLayers - 1);

    for(Layer &layer : layers){

        layer.setup(layerSizes[index]);
        
        if(index != numLayers - 1){

            connectionsTensor[index].resize(layerSizes[index + 1]);

            for(std::vector<Connection> &connectionVector : connectionsTensor[index]){
                
                connectionVector.resize(layerSizes[index]);
            }
        }

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
    uint8_t index = 0;

    uint8_t numLayers = layers.size();

    for(Layer &layer : layers){
        
        layer.draw(xPos + offset, yPos);

        if(index != numLayers - 1){ 
            
            uint8_t vectorIndex = 0;

            for(std::vector<Connection> &connectionVector : connectionsTensor[index]){
                
                uint8_t connectionIndex = 0;

                for(Connection &connection : connectionVector){
                    
                    connection.draw(layer.getNodes()[connectionIndex].getXPos(), 
                                    layer.getNodes()[connectionIndex].getYPos(), 
                                    layers[index + 1].getNodes()[vectorIndex].getXPos(),
                                    layers[index + 1].getNodes()[vectorIndex].getYPos());
                                    
                    connectionIndex++;
                }
                
                vectorIndex++;
            }
        }

        offset += layer.getWidth() + LAYER_SPACING;
        index++;
    }
}

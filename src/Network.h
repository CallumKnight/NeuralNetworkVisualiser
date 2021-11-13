#pragma once

#include "ofMain.h"
#include "Layer.h"

class Network{

	public:
		Network();
		~Network();
		void update();
		void draw(float x, float y);

	private:
		float xPos;
		float yPos;
		uint8_t numLayers;
		std::vector<Layer> layers;
};

#pragma once

#include "ofMain.h"
#include "Layer.h"
#include "Connection.h"

class Network{

	public:
		Network();
		~Network();
		void setup(std::vector<uint8_t> layerSizes);
		void update();
		void draw(float x, float y);

	private:
		float xPos;
		float yPos;
		std::vector<Layer> layers;
		std::vector<std::vector<std::vector<Connection>>> connectionsTensor;
};

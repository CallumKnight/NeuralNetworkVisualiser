#pragma once

#include "ofMain.h"
#include "Node.h"

class Layer{

	public:
		Layer();
		~Layer();
		void update();
		void draw(float x, float y);
		uint8_t getWidth();

	private:
		float xPos;
		float yPos;
		uint8_t numNodes;
		std::vector<Node> nodes;
};

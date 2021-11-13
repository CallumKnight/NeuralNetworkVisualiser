#pragma once

#include "ofMain.h"
#include "Node.h"

class Layer{

	public:
		Layer();
		~Layer();
		void setup(uint8_t size);
		void update();
		void draw(float x, float y);
		uint8_t getWidth();
		std::vector<Node> getNodes();

	private:
		float xPos;
		float yPos;
		std::vector<Node> nodes;
};

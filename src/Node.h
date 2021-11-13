#pragma once

#include "ofMain.h"

class Node{

	public:
		Node();
		~Node();
		void update();
		void draw(float x, float y);
		uint8_t getRadius();

	private:
		float xPos;
		float yPos;
		uint8_t radius;
		uint8_t colour;	
};

#pragma once

#include "ofMain.h"

class Node{

	public:
		Node();
		~Node();
		void setup();
		void update();
		void draw(float x, float y);
		uint8_t getRadius();
		float getXPos();
		float getYPos();

	private:
		float xPos;
		float yPos;
		uint8_t radius;
		uint8_t colour;	
};

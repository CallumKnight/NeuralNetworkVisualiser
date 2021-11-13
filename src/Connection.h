#pragma once

#include "ofMain.h"
#include "Node.h"

class Connection{

	public:
		Connection();
		~Connection();
		void setup();
		void update();
		void draw(float xStart, float yStart, float xEnd, float yEnd);

	private:
		float xPosStart;
		float yPosStart;
		float xPosEnd;
		float yPosEnd;
		uint8_t colour;
};

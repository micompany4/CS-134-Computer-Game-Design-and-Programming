#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		//implement test for point inside a shape
		//in this particular case, a triangle
		bool insideShape(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
		void buildDeck();

		ofImage board;
		vector<glm::vec3> verts;
		vector<glm::vec3> pos, posB, posR, posY, posG;
		glm::vec3 inital;
		float width, height;
		int initalX, initalY, prevDX, prevDY, distance, maxD, minD; // data to help with mouse movement
		int piece= -1, counter = -1;		//in-game data for game pieces and deck of cards
		bool bHit = false;

		float rand = 0;

		vector<string> deck;
		

		glm::vec3 position;
		

};
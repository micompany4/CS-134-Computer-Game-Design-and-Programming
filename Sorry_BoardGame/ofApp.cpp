#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	width = 80;
	height = 80;
	counter = -1;

	//initial position of the mouse click
	initalX = 0;
	initalY = 0;
	//position of the mouse before it is dragged
	prevDX = 0;
	prevDY = 0;

	//used to find the distance between a drag and a click
	distance = 0;
	maxD = 0;
	minD = 0;

	board.loadImage("img/board.jpg");
	
	//sets the positions for the blue pieces 0-3
	pos.push_back(glm::vec3(1080, 100, 0));
	pos.push_back(glm::vec3(1155, 100, 0));
	pos.push_back(glm::vec3(1230, 100, 0));
	pos.push_back(glm::vec3(1305, 100, 0));

	//sets the positions for the red pieces 4-7
	pos.push_back(glm::vec3(1080, 200, 0));
	pos.push_back(glm::vec3(1155, 200, 0));
	pos.push_back(glm::vec3(1230, 200, 0));
	pos.push_back(glm::vec3(1305, 200, 0));

	//sets the positions for the green pieces 8-11
	pos.push_back(glm::vec3(1080, 300, 0));
	pos.push_back(glm::vec3(1155, 300, 0));
	pos.push_back(glm::vec3(1230, 300, 0));
	pos.push_back(glm::vec3(1305, 300, 0));

	//sets the positions for the yellow pieces 12-15
	pos.push_back(glm::vec3(1080, 400, 0));
	pos.push_back(glm::vec3(1155, 400, 0));
	pos.push_back(glm::vec3(1230, 400, 0));
	pos.push_back(glm::vec3(1305, 400, 0));

	position = glm::vec3(1080, 600, 0);  

	verts.push_back(glm::vec3(0, -25, 0));
	verts.push_back(glm::vec3(-25, 25, 0));
	verts.push_back(glm::vec3(25, 25, 0));

	//deck.push_back("");
	buildDeck();
	std::random_shuffle(deck.begin(), deck.end());
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (counter >= 45)
	{
		std::random_shuffle(deck.begin(), deck.end());
		counter = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetBackgroundColor(255, 255, 255);

	ofSetColor(255, 255, 255);
	board.draw(0, 0);

	ofSetColor(ofColor::blue);
	ofDrawTriangle(pos[0] + verts[0], pos[0] + verts[1], pos[0] + verts[2]);
	ofDrawTriangle(pos[1] + verts[0], pos[1] + verts[1], pos[1] + verts[2]);
	ofDrawTriangle(pos[2] + verts[0], pos[2] + verts[1], pos[2] + verts[2]);
	ofDrawTriangle(pos[3] + verts[0], pos[3] + verts[1], pos[3] + verts[2]);

	ofSetColor(ofColor::red);
	ofDrawTriangle(pos[4] + verts[0], pos[4] + verts[1], pos[4] + verts[2]);
	ofDrawTriangle(pos[5] + verts[0], pos[5] + verts[1], pos[5] + verts[2]);
	ofDrawTriangle(pos[6] + verts[0], pos[6] + verts[1], pos[6] + verts[2]);
	ofDrawTriangle(pos[7] + verts[0], pos[7] + verts[1], pos[7] + verts[2]);

	ofSetColor(ofColor::green);
	ofDrawTriangle(pos[8] + verts[0], pos[8] + verts[1], pos[8] + verts[2]);
	ofDrawTriangle(pos[9] + verts[0], pos[9] + verts[1], pos[9] + verts[2]);
	ofDrawTriangle(pos[10] + verts[0], pos[10] + verts[1], pos[10] + verts[2]);
	ofDrawTriangle(pos[11] + verts[0], pos[11] + verts[1], pos[11] + verts[2]);

	ofSetColor(ofColor::yellow);
	ofDrawTriangle(pos[12] + verts[0], pos[12] + verts[1], pos[12] + verts[2]);
	ofDrawTriangle(pos[13] + verts[0], pos[13] + verts[1], pos[13] + verts[2]);
	ofDrawTriangle(pos[14] + verts[0], pos[14] + verts[1], pos[14] + verts[2]);
	ofDrawTriangle(pos[15] + verts[0], pos[15] + verts[1], pos[15] + verts[2]);

	ofSetColor(ofColor::aquamarine);
	ofDrawRectangle(1080, 600, 150, 300);

	ofSetColor(0, 0, 0);
	if (counter < 0)
	{
		ofDrawBitmapString("Press Space to draw a card!", ofPoint(1240, 875));
	}
	else
	{
		ofDrawBitmapString(deck[counter], ofPoint(1240, 875));
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case 'f':
			ofToggleFullscreen();
			break;
		case ' ':
			counter++;
			break;
		case 's':
			std::random_shuffle(deck.begin(), deck.end());
		case 'c':
			cout << counter << endl;
		default:
			break;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	//sets the position of the mouse before it's dragged
	prevDX = x;
	prevDY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	glm::vec3 moused(x, y, 0);

	//glm::vec3 inital(initalX, initalY, 0); //sets a vec3 for the initial mouse press before it's dragged
	int distance = x - prevDX; //sets the distance between the inital mouse click and the current mouse drag


	//sets the min and max distances between the inital click and the current drag amount
	if (distance > maxD)
	{
		maxD = distance;
	}
	if (distance < minD)
	{
		minD = distance;
	}

	if (bHit)
	{
		pos[piece] = glm::vec3(x, y, 0);
	}


	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	//pos = glm::vec3(x, y, 0);
	glm::vec3 mousep(x, y, 0);
	inital = glm::vec3(x, y, 0);
	//sets the initial mouse pressed coordinates
	initalX = x;
	initalY = y;

	/*if (insideShape(mousep, pos, width, height))
	{
		cout << "Square: HIT" << endl;
	}
	else
	{
		cout << "Square: MISS" << endl;
	}*/

	rand = ofRandom(52);
	for (int i = 0; i < 16; i++)
	{
		if (insideShape(mousep, pos[i] + verts[0], pos[i] + verts[1], pos[i] + verts[2]))
		{
			
			piece = i;
			bHit = true;
			break;
		}
		else
		{
			
			bHit = false;
		}
	}


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 

}

//I used the area of the main triangle versus its interior sub triangles method 
bool ofApp::insideShape(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	//finds the area of the whole triangle
	int totalArea = abs((p1.x*(p2.y - p3.y) + p2.x*(p3.y - p1.y) + p3.x*(p1.y - p2.y)) / 2);

	//finds the areas of the three sub triangles
	int areaA = abs((p.x*(p2.y - p3.y) + p2.x*(p3.y - p.y) + p3.x*(p.y - p2.y)) / 2);
	int areaB = abs((p1.x*(p.y - p3.y) + p.x*(p3.y - p1.y) + p3.x*(p1.y - p.y)) / 2);
	int areaC = abs((p1.x*(p2.y - p.y) + p2.x*(p.y - p1.y) + p.x*(p1.y - p2.y)) / 2);

	int threeAreas = areaA + areaB + areaC;

	//there seems to be a issue with rounding so that the area of the three triangles inside the main triangle 
	//is either equal to or off by -1 or -2 of the main triangle's area, so I did a cheap fix 
	if (totalArea == threeAreas || totalArea - 1 == threeAreas || totalArea - 2 == threeAreas)
	{
		return true;
	}
	else
	{
		return false;
	}


	//Professor Smith showed me his code during office hours, but I had to switch around the variables
	//for orientedAngle in order for it to work
	//ex) instead of orientedAngle(v1, v2, glm::vec3(0, 0, 1), it became orientedAngle(v2, v1, glm::vec3(0, 0, 1)
	//I was using this until I debugged my original way of doing it
	/*glm::vec3 v1 = glm::normalize(p1 - p);
	glm::vec3 v2 = glm::normalize(p2 - p);
	glm::vec3 v3 = glm::normalize(p3 - p);
	float a1 = glm::orientedAngle(v2, v1, glm::vec3(0, 0, 1));
	float a2 = glm::orientedAngle(v3, v2, glm::vec3(0, 0, 1));
	float a3 = glm::orientedAngle(v1, v3, glm::vec3(0, 0, 1));

	if (a1 < 0 && a2 < 0 && a3 < 0)
	{
		return true;
	}
	else
	{
		return false;
	}*/

}

//a very grueling method that builds the deck for the game
//deck is a string vector that will contain all the cards in the deck
void ofApp::buildDeck()
{
	deck.push_back("1: Move a pawn from start or one pawn one space.");
	deck.push_back("1: Move a pawn from start or one pawn one space.");
	deck.push_back("1: Move a pawn from start or one pawn one space.");
	deck.push_back("1: Move a pawn from start or one pawn one space.");
	deck.push_back("1: Move a pawn from start or one pawn one space.");
	deck.push_back("2: Move a pawn from start or two spaces. Draw again.");
	deck.push_back("3: Move three spaces.");
	deck.push_back("4: Move four spaces backwards.");
	deck.push_back("5: Move five spaces.");
	deck.push_back("7: Move one pawn seven spaces or split the seven spaces amongst two pawns.");
	deck.push_back("8: Move eight spaces.");
	deck.push_back("10: Move ten spaces foreward or one space backwards.");
	deck.push_back("11: Move eleven spaces or switch one of your pawns with an opponents pawn.");
	deck.push_back("12: Move a pawn twelve spaces.");
	deck.push_back("Sorry!: Take a pawn from Start and move directly to a space occupied by an opponent,\nsending it back to its own Start.");
	deck.push_back("2: Move a pawn from start or two spaces. Draw again.");
	deck.push_back("3: Move three spaces.");
	deck.push_back("4: Move four spaces backwards.");
	deck.push_back("5: Move five spaces.");
	deck.push_back("7: Move one pawn seven spaces or split the seven spaces amongst two pawns.");
	deck.push_back("8: Move eight spaces.");
	deck.push_back("10: Move ten spaces foreward or one space backwards.");
	deck.push_back("11: Move eleven spaces or switch one of your pawns with an opponents pawn.");
	deck.push_back("12: Move a pawn twelve spaces.");
	deck.push_back("Sorry!: Take a pawn from Start and move directly to a space occupied by an opponent,\nsending it back to its own Start.");
	deck.push_back("2: Move a pawn from start or two spaces. Draw again.");
	deck.push_back("3: Move three spaces.");
	deck.push_back("4: Move four spaces backwards.");
	deck.push_back("5: Move five spaces.");
	deck.push_back("7: Move one pawn seven spaces or split the seven spaces amongst two pawns.");
	deck.push_back("8: Move eight spaces.");
	deck.push_back("10: Move ten spaces foreward or one space backwards.");
	deck.push_back("11: Move eleven spaces or switch one of your pawns with an opponents pawn.");
	deck.push_back("12: Move a pawn twelve spaces.");
	deck.push_back("Sorry!: Take a pawn from Start and move directly to a space occupied by an opponent,\nsending it back to its own Start.");
	deck.push_back("2: Move a pawn from start or two spaces. Draw again.");
	deck.push_back("3: Move three spaces.");
	deck.push_back("4: Move four spaces backwards.");
	deck.push_back("5: Move five spaces.");
	deck.push_back("7: Move one pawn seven spaces or split the seven spaces amongst two pawns.");
	deck.push_back("8: Move eight spaces.");
	deck.push_back("10: Move ten spaces foreward or one space backwards.");
	deck.push_back("11: Move eleven spaces or switch one of your pawns with an opponents pawn.");
	deck.push_back("12: Move a pawn twelve spaces.");
	deck.push_back("Sorry!: Take a pawn from Start and move directly to a space occupied by an opponent,\nsending it back to its own Start.");


	
}
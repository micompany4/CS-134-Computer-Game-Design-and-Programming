#pragma once
//----------------------------------------------------------------------------------
//
// Basic Sprite Class
//
//
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject();
	ofVec2f position, scale;
	float	rot;
	bool	bSelected;
	void setPosition(ofVec3f);
};


class Sprite : public BaseObject
{
public:
	Sprite();
	float birth, lifespan, speed, x, y;
	//glm::vec2 position;
	glm::vec3 velocity;
	bool bimg, fire, moving, bull = false;
	ofImage img;
	void setImage(ofImage);
	void draw();
	float age(float currentTime);
	string name;
	
	
};

class SpriteSystem
{
public:
	SpriteSystem();
	void add(Sprite);
	void remove(int);
	void draw();
	void update();
	vector<Sprite> sprites;
	float removeNear(ofVec3f point, float dist, bool h);
	bool bandage = false;
	int c = 0;
	ofSoundPlayer destr, heal;
	

};
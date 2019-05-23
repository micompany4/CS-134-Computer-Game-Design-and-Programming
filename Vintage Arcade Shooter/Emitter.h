#pragma once
//----------------------------------------------------------------------------------

#include "Sprite.h"


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject
{
public:
	Emitter(SpriteSystem*);
	float birth, lifespan, lastSpawn, rate;
	bool bfImage, bsImage;
	bool fire = false;
	bool started = false;
	void draw();
	void update();
	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setRate(float);
	void setImage(ofImage);
	void fireImage(ofImage);
	ofImage prim;
	ofImage secondary;
	glm::vec2 pos = glm::vec2(350, 350);
	glm::vec2 offset = glm::vec2(0, -80); //sets the offset for the laser to be fired by the ship so that it can be fired from the center
	glm::vec3 velocity;
	SpriteSystem *syst;
	
	int hits = 1;
	float maxDistPerFrame();
	ofSoundPlayer player; //sound player to play the sound effects
};

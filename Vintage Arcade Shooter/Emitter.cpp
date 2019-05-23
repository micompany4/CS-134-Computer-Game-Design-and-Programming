#include "ofMain.h"
#include "Emitter.h"


Emitter::Emitter(SpriteSystem *f)
{
	hits = 1;
	syst = f;
	birth = 0;
	lifespan = 5000;
	lastSpawn = 0;
	rate = 1;
	bfImage = false;
	bsImage = false;
	pos = glm::vec2(350, 350);  //inital position for the spaceship
	velocity = glm::vec3(0, -100, 0); //inital velocity 
	player.load("images/pew.wav"); //loads the sound file for the laser's sound effect
}

void Emitter::start()
{
	//checks if the emitter has already started
	if (started)
	{
		return;
	}
	started = true;
	lastSpawn = ofGetElapsedTimeMillis();
}

void Emitter::stop()
{
	//syst->sprites.clear();
	started = false;
}


void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(ofVec3f v) 
{
	velocity = v;
}

void Emitter::setRate(float r) {
	rate = r;
}

void Emitter::setImage(ofImage i)
{
	prim = i;
	bfImage = true;
}

void Emitter::fireImage(ofImage img)
{
	secondary = img;
	bsImage = true;
}

//draws the emitter with the provided image or a rectangle if none avaliable
void Emitter::draw()
{
	if (bfImage)
	{
		prim.draw(pos, 100, 100);

	}
	else
	{
		ofDrawRectangle(pos, 70, 70);
	}

	//draws the sprites in the sprite system
	syst->draw();
}

void Emitter::update()
{
	//makes sure that the lasers that are already spawned still travel until they die
	if (!started)
	{
		syst->update();
		return;
	}

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawn) > (1000.0 / rate))
	{
		// spawn a new sprite
		Sprite sprite;
		if (bsImage)
		{
			sprite.setImage(secondary);

		}
		sprite.velocity = velocity;
		sprite.lifespan = lifespan;
		sprite.setPosition(pos + offset);
		sprite.birth = time;
		//cout << "number of sprites: " << syst->sprites.size() << endl;
		syst->add(sprite);
		//cout << "number of sprites: " << syst->sprites.size() << endl;
		lastSpawn = time;
		//cout << "fire" << endl;
		if (fire)
		{
			player.play(); //plays the laser sound effect when a laser is fired
		}

	}
	syst->update();
}

float Emitter::maxDistPerFrame()
{
	return  velocity.length() / ofGetFrameRate();
}

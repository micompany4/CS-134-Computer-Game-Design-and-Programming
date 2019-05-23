#include "Sprite.h"

BaseObject::BaseObject() 
{
	position = ofVec3f(0, 0, 0);
	scale = ofVec3f(1, 1, 1);
	rot = 0;
}

void BaseObject::setPosition(ofVec3f pos) {
	position = pos;
}

Sprite::Sprite()
{
	lifespan = -1;
	speed = 0;
	birth = 0;
	bimg = false;
	velocity = glm::vec3(0, 0, 0);
	position = glm::vec2(500, 500);
	fire = false;
	name = "Blank";
}

void Sprite::setImage(ofImage pic)
{
	img = pic;
	if (img.getWidth() == 50)
	{
		bull = true;
	}
	bimg = true;
}

void Sprite::draw()
{
	//sets the sprite to be an image, unless there is no image
	//in that case, it becomes a rectangle
	if (bimg)
	{
		if (bull)
		{
			img.draw(position, 50, 100);
		}
		else
		{
			img.draw(position, 100, 100);
		}
		
	}
	else
	{
		ofDrawRectangle(position, 10, 50);
	}

	//ofSetColor(ofColor::black);
	//ofDrawRectangle(position, 10, 50);

}

float Sprite::age(float currentTime)
{
	return currentTime - birth;

}

SpriteSystem::SpriteSystem()
{
	destr.load("images/boom.wav");
	heal.load("images/heal.mp3");
	int c = 0;
}

void SpriteSystem::add(Sprite s)
{
	sprites.push_back(s);
	//cout << "sprite added" << endl;
}

void SpriteSystem::remove(int i)
{
	sprites.erase(sprites.begin() + i);
}

void SpriteSystem::draw() {
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i].draw();
		//cout << "drawn" << endl;
	}
}

void SpriteSystem::update()
{
	//cout << "sprites in system: " << sprites.size() << endl;

	if (sprites.size() == 0)
	{
		//cout << "no sprites" << endl;
		return;
	}
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sprites.end())
	{
		if (s->lifespan != -1 && s->age(ofGetElapsedTimeMillis()) > s->lifespan) {
			//cout << "deleting sprite: " << s->name << endl;
			tmp = sprites.erase(s);
			s = tmp;
		}
		else
		{
			s++;
		}
	}

	//  Move sprite
	//
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i].position += sprites[i].velocity / ofGetFrameRate();
		c++;  
		//cout << sprites[i].age(ofGetElapsedTimeMillis()) << endl;
	}

}

//checks if two sprites are near each other an removes sprite spawned by its respected emitter
//code recieved from the minigame example 
float SpriteSystem::removeNear(ofVec3f point, float dist, bool h)
{
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;
	float count = 0;

	while (s != sprites.end()) {
		ofVec3f v = s->position - point;
		if (v.length() < dist) {
			tmp = sprites.erase(s);

			//plays a certain sound depending on what the collision was
			if (!h)
			{
				destr.play();
			}
			else
			{
				heal.play();
			}
			count++;
			s = tmp;
		}
		else s++;
	}
	return count;
}
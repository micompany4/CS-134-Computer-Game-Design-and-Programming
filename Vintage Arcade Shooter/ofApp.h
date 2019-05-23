#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "Emitter.h"
#include "ParticleEmitter.h"

//class Emitter;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void checkCollision();				//checks for collisions between sprites

	bool bStart = false;
	bool bGUI = false;
	vector<Emitter *> emit;				//using this to spawn the enemies
	ofImage decal, proj, bad1, bad2, craft, creep, healthBox, background; //images for the laser, enemies and ship
	//a bunch of floats and ints for the games mechanics
	float fighterX, fighterY, laserX, laserY, rateUp, speedUp, semi = 0.05, stdRate = 1, angle = 0; 
	int counter = 0, health = 100, coolDown = 0, level = 1;
	float score = 0, radius = 0;
	int fix = 20;
	

	Emitter *emitt = new Emitter(new SpriteSystem());	//designating this emitter for the player figther
	Emitter *aid = new Emitter(new SpriteSystem());		//for the healthBox

	ofxPanel gui;
	ofxFloatSlider rateSlider;
	ofxFloatSlider lifeSlider;
	ofxVec3Slider velocitySlider;

	ofxPanel guie;
	ofxFloatSlider rateSliderE;
	ofxFloatSlider lifeSliderE;
	ofxVec3Slider velocitySliderE;

	//particle emitters for explosions and jet streams
	ParticleEmitter explosion;
	ParticleEmitter thrust;

	//forces for the explosion
	TurbulenceForce *t;
	GravityForce *g;
	ImpulseRadialForce *imp;

	//forces for the thrusters
	GravityForce *gfuel; 
	TurbulenceForce *tfuel;
};   

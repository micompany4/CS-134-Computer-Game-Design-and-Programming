#include "ofApp.h"
#include "Emitter.h"

void ofApp::setup()
{
	//inital settings
	fighterX = 350;
	fighterY = 800;
	rateUp = 1;
	speedUp = 200;

	emitt->pos = glm::vec2(fighterX, fighterY); //sets inital position for the fighter
	emit.push_back(new Emitter(new SpriteSystem()));
	emit.push_back(new Emitter(new SpriteSystem()));
	emit.push_back(new Emitter(new SpriteSystem()));

	//sets up the particle emitter for the explosions
	explosion.setOneShot(true);
	explosion.setVelocity(ofVec3f(80, 80, 0));
	explosion.setGroupSize(35);
	explosion.setEmitterType(RadialEmitter);
	explosion.setLifespan(0.75);
	explosion.setParticleRadius(3);

	//sets up the particle emitter for the jet stream
	thrust.setOneShot(false);
	thrust.setVelocity(ofVec3f(0, 150, 0));
	thrust.setGroupSize(20);
	thrust.setEmitterType(SphereEmitter);
	thrust.setLifespan(1);
	thrust.setParticleRadius(2.5);
	thrust.setRate(7);
	thrust.setPosition(ofVec3f(fighterX + 50, fighterY + 100, 0));

	//forces for the two particle emitters
	g = new GravityForce(ofVec3f(0, 30, 0));
	t = new TurbulenceForce(ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20));
	imp = new ImpulseRadialForce(1500);
	gfuel = new GravityForce(ofVec3f(0, 30, 0));
	tfuel = new TurbulenceForce(ofVec3f(-10, 10, 0), ofVec3f(10, 10, 0));

	//adds the forces to the particle emitters
	explosion.sys->addForce(g);
	explosion.sys->addForce(t);
	explosion.sys->addForce(imp);

	thrust.sys->addForce(gfuel);
	//thrust.sys->addForce(tfuel);
	thrust.sys->addForce(imp);

	//starts the thrusters 
	thrust.sys->reset();
	thrust.start();

	//sets the images for the emitter figther and its laser
	if (decal.load("images/ship.png"))
	{
		//emitt->bfImage = true;
		emitt->setImage(decal);
	}
	if (proj.load("images/laser.png"))
	{
		//emitt->bsImage = true;
		emitt->fireImage(proj);
		//cout << "loaded" << endl;
	}
	//sets the image for the blue fighter to spawn
	if (bad1.load("images/enemy1.png"))
	{
		emit[0]->fireImage(bad1);
	}
	//sets the image for the aircraft to spawn creepers
	if (craft.load("images/portal.png"))
	{

		emit[1]->setImage(craft);
		if (creep.load("images/Creeper.png"))
		{
			emit[1]->fireImage(creep);
		}
	}

	if (bad2.load("images/Bullet.png"))
	{
		emit[2]->fireImage(bad2);
		
	}

	if (healthBox.load("images/health.png")) 
	{
		aid->fireImage(healthBox);
	}
	
	background.load("images/background.png");

	emit[0]->pos = ofVec2f(ofRandom(0, 650), -70);		//sets position of the blue fighter
	emit[1]->pos = ofVec2f(375, 0);						//sets position of the craft to spawn creepers
	emit[2]->pos = ofVec2f(ofRandom(0, 650), 40);		//sets position of the bullet enemy 

	//sets up the health package 
	aid->pos = ofVec2f(ofRandom(0, 650), -70);
	aid->setRate(0.05);
	aid->setVelocity(ofVec3f(0, 100, 0));

	//there are two GUI sliders on top of each other, move one of them out of the way of the other to access both of them
	//sets up the GUI for the fighter and the enemies
	gui.setup();
	gui.add(rateSlider.setup("rate", 7, 1, 20));
	gui.add(lifeSlider.setup("life", 4020, 1000, 10000));
	gui.add(velocitySlider.setup("velocity", ofVec3f(0, -500, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));

	//this slider is for the blue enemy. The green enemy's velocity can not be affected by the slider, except for lifespan
	guie.setup();
	guie.add(rateSliderE.setup("rate", 2, .01, 6));
	guie.add(lifeSliderE.setup("life", 6600, 1000, 10000));
	guie.add(velocitySliderE.setup("velocity", ofVec3f(0, 150, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
}

//--------------------------------------------------------------
void ofApp::update()
{
	//resets the game
	if (health <= 0)
	{
		bStart = false;
		level = 1;
		fix = 20;
		semi = 0.05;
		stdRate = 1;
	}


	//allows the changes from the sliders to be implemented and updates the emitter
	emitt->update();
	emitt->setVelocity(ofVec3f(velocitySlider));
	emitt->setLifespan(float(lifeSlider));
	emitt->setRate(float(rateSlider));
	explosion.update();
	thrust.update();

	//starts or stops the game depending on the start boolean
	if (bStart)
	{
		checkCollision();
		//creeper enemy spawn functionality is that after every 20 seconds, they spawn faster, for 10 seconds and then go back to their default spawn rate
		counter++;
		//checks if 20 seconds has elapsed
		if (counter % 1200 == 0)
		{
	
			rateUp = float(rateSliderE) + 3; //increases the rate and speed of the green enemy
			speedUp = 320;
		}

		//checks if 30 seconds has elapsed, levels last 30 seconds  with difficulty 
		if (counter % 1800 == 0)
		{
			level++;
			rateUp = float(rateSliderE); //increases the rate and speed of the green enemy
			speedUp = 200;
			stdRate += 0.5;				//increases the rate of the blue enemy
			semi += 0.04;				//increases the rate of the bullet enemy
			

			//decreases the health that the health box gives the player until the minimun 5
			if (fix != 5) 
			{
				fix -= 4;
			}
		}

		//makes the thrusting emitter follow the player fighter
		thrust.setPosition(ofVec3f(fighterX + 50, fighterY + 100, 0));

		//sets the angles for the blue fighter
		angle += glm::radians(5.0);
		if (angle >= 120)
		{
			while (angle >= -120)
			{
				angle -= glm::radians(5.0);
			}
		}

	}
	else
	{
		for (int j = 0; j < emit.size(); j++)
		{
			emit[j]->stop();
			aid->stop();
		}
	}
	
	//updates the enemies
	for (int i = 0; i < emit.size(); i++)
	{
		
		emit[0]->pos = ofVec2f(ofRandom(0, 650), -70);		//randomizes the position of the blue enemy
		aid->pos = ofVec2f(ofRandom(0, 650), -70);			//randomizes the position of the healthBox
		emit[2]->pos = ofVec2f(emitt->pos.x, -70);			//allows the bullet enemy to follow the player

		

		//changes the velocity settings for the enemies
		ofVec3f v = emit[1]->velocity;		
		emit[1]->setVelocity(ofVec3f(ofRandom(-v.y, v.y), speedUp, v.z));
		emit[2]->setVelocity(ofVec3f(0, 1250, 0));
		
		//increases the difficulty after level 3
		if (level < 3)
		{
			emit[0]->setVelocity(ofVec3f(velocitySliderE));
		}
		else
		{
			for (int i = 0; i < emit[0]->syst->sprites.size(); i++)
			{
				emit[0]->syst->sprites[i].velocity = glm::vec3(emit[0]->syst->sprites[i].position.x * cos(angle), 225, 0);
			}
			aid->setVelocity(ofVec3f(0, 50, 0));		//slows down the health box speed
		}
		


		//emit[2]->setVelocity(ofVec3f(velocitySliderE));
		//aid->setVelocity(ofVec3f(velocitySliderE));

		emit[i]->setLifespan(float(lifeSliderE));

		//set the rates for the enemies
		emit[0]->setRate(stdRate);
		emit[1]->setRate(rateUp);
		emit[2]->setRate(semi);   

		emit[i]->update();
		aid->update();
	}
	
	
	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//the use of ofSetColor is so that the original color scheme for each individal 
	//element in the game is kept and not painted over with the particles

	ofSetColor(255, 255, 255);
	background.draw(0, 0);
	//presents a start screen until the user presses the spacebar
	if (!bStart)
	{
		//checks what image to display 
		ofImage s;
		if (health <= 0)
		{
			s.load("images/gameover.jpg");
			ofSetColor(255, 255, 255);
			s.draw(150, 225);
			
			score = 0;
			
			
		}
		else
		{
			s.load("images/space2.png");
			ofSetColor(255, 255, 255);
			s.draw(275, 325);
		}

	}
	else
	{
		explosion.draw();
		thrust.draw();

		ofSetColor(255, 255, 255);
		emitt->draw(); //draws the spaceship
		
		for (int i = 0; i < emit.size(); i++)
		{
			ofSetColor(255, 255, 255);
			emit[i]->draw();	//draws the enemies
		}
		ofSetColor(255, 255, 255);
		aid->draw();

		//ui interface to provid information to the player
		//creates the score box to keep track of the player's score
		string scoreBox;
		scoreBox += "Score: " + std::to_string(score);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(scoreBox, ofPoint(10, 50));			//the score is hidden by the GUI sliders in the top left corner

		string healthBox;
		healthBox += "Health: " + std::to_string(health);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(healthBox, ofPoint(625, 955));

		//menu for cool down 
		string gun;
		gun += "Cool Down: " + std::to_string(coolDown);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(gun, ofPoint(625, 925));

		string currentLevel;									//the level is hidden by the GUI sliders in teh top left corner
		currentLevel += "Level: " + std::to_string(level);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(currentLevel, ofPoint(10, 20));
	}

	//emitt->syst->draw();

	if (bGUI)
	{
		gui.draw();
		guie.draw();
	}

}

//checks the collision between two objects 
void ofApp::checkCollision()
{
	//checks the player fighter against enemy that are spawned by an emitter, emitter v sprite detector
	//damge taken is determined by what enemy you hit
	for (int i = 0; i < emit.size(); i++)
	{
		float damage = 15;
		if (i == 2)
		{
			damage = 40;
		}
		if (i == 1)
		{
			damage = 5;
		}

		health -= emit[i]->syst->removeNear(emitt->pos, 100, false) * damage;
	}

	
	health += aid->syst->removeNear(emitt->pos, 100, true) * fix;
	
	//checks the enemy sprites against the player's lasers, sprite v sprite detector
	//universal hitbox for this game is 100, expect for the bullet enemy
	for (int j = 0; j < emitt->syst->sprites.size(); j++)
	{
		int prevs = score;
		//loops thorugh every enemy to find a collision
		for (int k = 0; k < emit.size(); k++)
		{
			float multi = 0, multib = 200, hitbox = 100;	//different points for different enemies
			if (k == 0 || k == 2 || k == 3)
			{
				multi = 100;
				if (k == 2)
				{
					//requires more precision to take out the bullet enemy after level 5, trying to make it harder here... 
					if (level >= 5)
					{
						hitbox = 38;
					}
					else
					{
						hitbox = 75;
					}
					
				}
			}
			else if (k == 1)
			{
				multi = 25;
			}
			else
			{
				multi = 300;
			}
			
			score += emit[k]->syst->removeNear(emitt->syst->sprites[j].position, hitbox, false) * multi;	
			//if there is a hit, the score goes up
		}
		
		score += emitt->syst->removeNear(emit[1]->pos, 100, false) * 300;		//never got a chance to implement destruction of spawning enemy

		if (score > prevs)
		{
			emitt->syst->sprites[j].lifespan = 0; //eliminates the laser after hitting an enemy
			
			//creates the explosion effect
			explosion.setPosition(emitt->syst->sprites[j].position);
			explosion.sys->reset();
			explosion.start();
			
			if (score == prevs+300)		//was suppose to be used if you hit the alien craft spawning creepers, ran out of time :(
			{
				emit[1]->stop();
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//the game has started or resets the game
	if (key == ' ' && bStart == false)
	{
		bStart = true;
		if (health <= 0)
		{
			health = 100;
			emitt->pos = glm::vec2(fighterX, fighterY);
		}
	}

	//player has the option of using the arrow keys or the mouse, mouse preferably
	if (bStart)
	{
		for (int k = 0; k < emit.size(); k++)
		{
			emit[k]->start();
		}
		aid->start();
		//movemnet is done by changing the position vector for the spaceship
		//movement is incremented by 10 units per key press
		//checking for out of bounds is done here by checking each edge of the screen
		switch (key)
		{
		case 'f':				
			ofToggleFullscreen();
			break;
		case ' ':
			//starts the emitter, but it requires to hold the spacebar for a moment on a low rate of fire
			//higher rates of fire will result in quicker response times
			emitt->fire = true;
			emitt->start();
			//can only shoot 10 at a time without taking damage
			if (coolDown > 9)
			{
				emitt->stop();
				health--;
			}
			coolDown++;
			break;
		case OF_KEY_UP:
			if (fighterY > 2)
			{
				emitt->pos = glm::vec2(fighterX, fighterY -= 10);
			}
			break;
		case OF_KEY_DOWN:
			if (fighterY < 890)
			{
				emitt->pos = glm::vec2(fighterX, fighterY += 10);
			}
			break;
		case OF_KEY_LEFT:
			if (fighterX > 2)
			{
				emitt->pos = glm::vec2(fighterX -= 10, fighterY);
			}
			break;
		case OF_KEY_RIGHT:
			if (fighterX < 673)
			{
				emitt->pos = glm::vec2(fighterX += 10, fighterY);
			}
			break;
		case 'h':
			bGUI = !bGUI;
		default:
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key) {
	case OF_KEY_LEFT:
	case OF_KEY_RIGHT:
	case OF_KEY_UP:
	case OF_KEY_DOWN:
		break;
	case ' ':
		if (emitt->started) //checks to see if the emitter is running
		{
			emitt->fire = false;
			emitt->stop(); //stops the spawning of new sprites
		}
		
		while (coolDown > 0)	//revitalizes the cooldown
		{
			coolDown--;
		}
		
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	fighterX = x;
	fighterY = y;
	//When I was playing around with the movement there didn't seem to be a way to go out of bounds for the top corners so I didn't check them
	//Checks for the play area boundaries and prevents the ship from moving out of bounds; since I know the dimensions of the screen I just hard coded it
	if (bStart)
	{
		if (y >= 890 && x >= 673) //checks for the lower right corner
		{
			emitt->pos = glm::vec2(673, 890); //gives a fixed position for the corner
		}
		else if (x <= 2 && y >= 890) //checks for the lower right corner
		{
			emitt->pos = glm::vec2(2, 890); //gives a fixed position for that corner
		}
		else if (x <= 2)
		{
			emitt->pos = glm::vec2(2, fighterY);
		}
		else if (x >= 673)
		{
			emitt->pos = glm::vec2(673, fighterY);
		}
		else if (y <= 2)
		{
			emitt->pos = glm::vec2(fighterX, 2);
		}
		else if (y >= 890)
		{
			emitt->pos = glm::vec2(fighterX, 890);
		}
		else
		{
			emitt->pos = glm::vec2(fighterX, fighterY);
		}
	}

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	//cout << "X: " << fighterX << " Y: " << fighterY << endl;
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
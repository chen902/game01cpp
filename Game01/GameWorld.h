#pragma once
#include <vector>
#include "GraphicsManager.h"
#include "PhysicsManager.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void init();
	void run();
	void stop();
	void setGraphicsManager(GraphicsManager& gm);
	void setPhysicsManager(PhysicsManager& pm);

private:
	void mainLoop();
	double calcFrameTimeDeltaMs();
	void cleanUp();
	void handleUserInput();
	void update();
	void render();
};


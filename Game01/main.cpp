#include "GameWorld.h"

int main(void)
{
	//RawModel& floor_model = OBJLoader::loadObjModel("res\\floor_tile.obj", loader);
	//ModelTexture& floor_texture = *(new ModelTexture(loader.loadTexture("res\\checker.png")));
	//TexturedModel& floor = *(new TexturedModel(floor_texture, floor_model));

	//Entity floor_entity(floor, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 50.0f);
	GameWorld world;
	world.init();
	world.run();


	return 0;
}

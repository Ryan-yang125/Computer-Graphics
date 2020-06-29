#include "Scene.h"





/*
 * Initializes the ambient, diffuse, and specular components of the scene's objects
 * as well as setting the specular hotspot size (smaller number = wider hotspot).
 * Also initialize the lights for the scene as well as their ADS components.
 */
Scene::Scene() : 
	grid(vec3(0.6f, 0.4f, 0.4f), vec3(0.6f, 0.4f, 0.4f), vec3(0.1f, 0.1f, 0.1f), 15.0f),
	ceiling(vec3(0.6f, 0.6f, 0.6f), vec3(0.6f, 0.6f, 0.6f), vec3(0.1f, 0.1f, 0.1f), 15.0f),
	wallFar(vec3(0.3f, 0.4f, 0.3f), vec3(0.5f, 0.6f, 0.5f), vec3(0.05f, 0.05f, 0.05f), 1.0f),
	wallLeft(vec3(0.3f, 0.4f, 0.3f), vec3(0.5f, 0.6f, 0.5f), vec3(0.05f, 0.05f, 0.05f), 1.0f),
	stoolModel(vec3(0.2f, 0.1f, 0.1f), vec3(0.3f, 0.2f, 0.2f), vec3(1.0f, 0.8f, 0.8f)),
	tableModel(vec3(0.2f, 0.1f, 0.1f), vec3(0.3f, 0.2f, 0.2f), vec3(1.0f, 0.8f, 0.8f)),
	vaseModel(vec3(0.4f, 0.5f, 0.4f), vec3(0.7f, 0.8f, 0.7f), vec3(0.3f, 0.3f, 0.3f), 
			14.0f, 2.5f, 1.0f, 2 * PI / 14.0f, 0.0f, 20, 10),
	bowl(vec3(0.4f, 0.4f, 0.5f), vec3(0.7f, 0.7f, 0.8f), vec3(0.3f, 0.3f, 0.3f),
			4.0f, 3.0f, 3.0f, 2 * PI / 14.0f, 0.0f, 20, 10),
	goblet(vec3(0.5f, 0.4f, 0.4f), vec3(0.8f, 0.7f, 0.7f), vec3(0.3f, 0.3f, 0.3f),
			6.0f, 1.5f, 1.0f, 2 * PI / 8.0f, 4.0f, 32, 10),
	fountain(100000),
	fireplace(vec3(0.0f, 0.0f, -WALL_DIST + FP_BLOCK_THICKNESS / 2 * METERS_PER_INCH), vec3(0.9f, 0.9f, 0.9f), vec3(0.9f, 0.9f, 0.9f), vec3(0.9f, 0.9f, 0.9f)),
	paintingfloor("floorpaper"),
	paintingnear("wallnear"),
	paintingleft("wallleft"),
	paintingfar("wallfar"),
	paintingright("wallright"),
	paintingceiling("ceilingpaper")
{
	// light position in world space
	lightPos = vec4(0.0f, 0.3f, -WALL_DIST + FP_BLOCK_THICKNESS / 2 * METERS_PER_INCH + 0.2f, 1.0f);
	lightDiffuse = vec3(0.7f, 0.5f, 0.3f);
	//lightAmbient = vec3(0.1f, 0.1f, 0.1f);
	lightAmbient = vec3(0.1f, 0.1f, 0.1f);
	lightSpecular = vec3(0.65f, 0.5f, 0.5f);//try to adjust the heavy of light, although it sounds stupid

	// add stools to surround the table
	stools.push_back(Stool(&stoolModel, vec3(0.0f, 0.0f, 30.0f)));
	stools.push_back(Stool(&stoolModel, vec3(0.0f, 0.0f, -30.0f)));
	stools.push_back(Stool(&stoolModel, vec3(30.0f, 0.0f, 0.0f)));
	stools.push_back(Stool(&stoolModel, vec3(-30.0f, 0.0f, 0.0f)));
}

/*
 * Release any pointers allocated for the scene
 */
Scene::~Scene() {
}


/*
 * Initialize the meshes/particles for the objects in the scene.
 */
bool Scene::init() {
	bool success = stoolModel.initMesh();
	if (!success) return false;

	success = tableModel.initMesh();
	if (!success) return false;

	success = vaseModel.initMesh();
	if (!success) return false;
	
	success = bowl.initMesh();
	if (!success) return false;

	success = goblet.initMesh();
	if (!success) return false;

	success = grid.init(GRID_SIZE, GRID_SIZE);
	if (!success) return false;

	success = ceiling.init(GRID_SIZE, GRID_SIZE);
	if (!success) return false;

	success = wallFar.init(WALL_LENGTH, WALL_HEIGHT);
	if (!success) return false;

	success = wallLeft.init(WALL_HEIGHT, WALL_LENGTH);
	if (!success) return false;

	success = fountain.initGL();
	if (!success) return false;

	success = fireplace.initMesh();
	if (!success) return false;

	success = paintingfloor.init(); 
	if (!success) return false;

	success = paintingnear.init();
	if (!success) return false;
	
	success = paintingleft.init();
	if (!success) return false;

	success = paintingfar.init();
	if (!success) return false;

	success = paintingright.init();
	if (!success) return false;
	
	success = paintingceiling.init();
	if (!success) return false;
	
	return true;
}


void Scene::update(float elapsedTime) {
	fountainShader->use();
	fountainShader->setUniform("elapsedTime", elapsedTime);
}


bool Scene::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, 
				 const ivec2 &size, const float time, const float picture_size,
					bool options_fountain, float firesize, bool lightmove, bool lightset,
					bool bowlrotate) {

	shader.use();
	shader.setUniform("time", time);
	shader.setUniform("size", size);

	mvs.push();
	mvs.active = scale(mvs.active, vec3(WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER));
	mvs.push();
	if (lightset) {
		mvs.active = rotate(mvs.active, 36.0f, vec3(1.0f, 0.0f, 0.0f));
	}
	else if (lightmove) {
		mvs.active = rotate(mvs.active, 25 * time, vec3(1.0f, 0.0f, 0.0f));
	}
	else {}
	vec4 eyeLightPos = mvs.active * lightPos;
	mvs.pop();
	//TODO camera rotate
	//mvs.active = rotate(mvs.active, 30 * time, vec3(0.0f, 1.0f, 0.0f));

	// on random intervals change the light color slightly to emulate the
	// flickering of light given off by flames
	if (rand() % 10 < 5) {
		adjLightAmb = lightAmbient;
		adjLightDiff = lightDiffuse;
		adjLightSpec = lightSpecular;

		float adjustment = mix(-0.02f, 0.02f, float(rand()) / RAND_MAX);
		adjLightAmb += adjustment;
		adjLightDiff += adjustment;
		adjLightSpec += adjustment;
	}


	// push the light properties to the shader
	shader.setUniform("lightPosition", eyeLightPos);
	shader.setUniform("La", adjLightAmb);
	shader.setUniform("Ld", adjLightDiff);
	shader.setUniform("Ls", adjLightSpec);

	// push light properties to the texture shader
	textureShader->use();
	textureShader->setUniform("lightPosition", eyeLightPos);
	textureShader->setUniform("Ld", lightDiffuse);
	textureShader->setUniform("La", lightAmbient);
	textureShader->setUniform("Ls", lightSpecular);

	// draw the grid in meters
	grid.draw(shader, mvs.active, proj);

	// draw a ceiling
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT - 1, 0.0f));
	mvs.active = rotate(mvs.active, 180.0f, vec3(1.0f, 0.0f, 0.0f));
	ceiling.draw(shader, mvs.active, proj);
	mvs.pop();

	//draw ceiling paper
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT - 1.0001, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(1.0f, 0.0f, 0.0f));
	mvs.active = scale(mvs.active, vec3(8.0f * picture_size, 8.0f * picture_size, 1.0f));
	paintingceiling.draw(*textureShader, mvs, proj);
	mvs.pop();

	// transform far wall and draw it
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, 0.0f, -WALL_DIST));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(1.0f, 0.0f, 0.0f));
	wallFar.draw(shader, mvs.active, proj);
	mvs.pop();
	
	//draw far wallpaper
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, -WALL_DIST + 0.001f));
	mvs.active = rotate(mvs.active, 180.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = scale(mvs.active, vec3(10.0f, 4.0f, 1.0f));
	paintingfar.draw(*textureShader, mvs, proj);
	mvs.pop();
	
	// transform near wall and draw it
	mvs.push();
	mvs.active = rotate(mvs.active, 180.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(0.0f, 0.0f, -WALL_DIST));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(1.0f, 0.0f, 0.0f));
	wallFar.draw(shader, mvs.active, proj);
	mvs.pop();
	
	//draw near wallpaper
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, WALL_DIST - 0.001f));
	mvs.active = rotate(mvs.active, 180.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = scale(mvs.active, vec3(10.0f, 4.0f, 1.0f));
	paintingnear.draw(*textureShader, mvs, proj);
	mvs.pop();
	
	// draw fireplace
	fireplace.draw(*textureShader, mvs, proj, time * firesize);
	
	//draw painting floor
	mvs.push();
	mvs.active = translate(mvs.active, vec3(WALL_DIST/3, 0.0001f, -1.5f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = rotate(mvs.active, -90.0f, vec3(1.0f, 0.0f, 0.0f));
	mvs.active = scale(mvs.active, vec3(12.0f, 12.0f , 1.0f));
	paintingfloor.draw(*textureShader, mvs, proj);
	mvs.pop(); 

	// transform right wall and draw it
	mvs.push();
	mvs.active = translate(mvs.active, vec3(WALL_DIST, 0.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(0.0f, 0.0f, 1.0f));
	wallLeft.draw(shader, mvs.active, proj);
	mvs.pop();
	
	//draw painting right
	mvs.push();
	mvs.active = translate(mvs.active, vec3(WALL_DIST - 0.0001f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = scale(mvs.active, vec3(10.0f, 4.0f, 1.0f));
	paintingleft.draw(*textureShader, mvs, proj);
	mvs.pop();
	
	// transform left wall and draw it
	mvs.push();
	mvs.active = rotate(mvs.active, 180.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(WALL_DIST, 0.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(0.0f, 0.0f, 1.0f));
	wallLeft.draw(shader, mvs.active, proj);
	mvs.pop();
	
	//draw painting left
	mvs.push();
	mvs.active = translate(mvs.active, vec3(-WALL_DIST + 0.0001f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, -90.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = scale(mvs.active, vec3(10.0f, 4.0f, 1.0f));
	paintingleft.draw(*textureShader, mvs, proj);
	mvs.pop();
	
	// TODO draw fountain - DEBUGGING
	//if (options_fountain) {
	//	mvs.push();
	//	fountain.draw(*fountainShader, mvs, proj, time);
	//	mvs.active = translate(mvs.active, vec3(0.0f, 1.0f, 0.0f));
	//	mvs.pop();
	//}

	bool success = true;
	// scale stools
	mvs.active = scale(mvs.active, vec3(METERS_PER_INCH, METERS_PER_INCH, METERS_PER_INCH));
	// draw stools
	for (auto i = stools.begin(); i != stools.end(); i++) {
		success = i->draw(shader, mvs, proj);
		if (!success) return false;
	}

	// draw table
	success = tableModel.draw(shader, mvs, proj);
	if (!success) return false;
	
	//translate to the table
	mvs.active = translate(mvs.active, vec3(0.0f, TABLE_HEIGHT, 0.0f));
	if (bowlrotate)
		mvs.active = rotate(mvs.active, 30 * time, vec3(0.0f, 1.0f, 0.0f));

	// draw vase
	mvs.push();
	mvs.active = translate(mvs.active, vec3(12.0f, 0.0f, 6.0f));
	success = vaseModel.draw(shader, mvs, proj);
	if (!success) return false;
	mvs.pop();
	// draw bowl
	mvs.push();
	mvs.active = translate(mvs.active, vec3(-10.0f, 0.0f, -5.0f));
	success = bowl.draw(shader, mvs, proj);
	if (!success) return false;
	mvs.pop();
	// draw goblet
	mvs.push();
	mvs.active = translate(mvs.active, vec3(-6.0f, 0.0f, 8.0f));
	success = goblet.draw(shader, mvs, proj);	
	if (!success) return false;
	//mvs.pop();

	// scale back up to meters and draw particle fountain
	if (options_fountain) {
		mvs.active = translate(mvs.active, vec3(0.0f, 5.0f, 0.0f));
		mvs.active = scale(mvs.active, vec3(1 / METERS_PER_INCH * 2.0, 1 / METERS_PER_INCH * 2.0, 1 / METERS_PER_INCH * 2.0));
		success = fountain.draw(*fountainShader, mvs, proj, time);
		if (!success) return false;
	}
	mvs.pop();
	//draw the loaded obj model
	mvs.push();
	//{
	//	// build and compile shaders
	//	O_Shader ourShader("ModelLoading.vert", "ModelLoading.frag");
	//	// load model
	//	O_Model ourModel("bookcase.obj");
	//	ourShader.Use();
	//	// view/projection transformations
	//	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//	//glm::mat4 view = camera.GetViewMatrix();
	//	ourShader.setMat4("projection", proj);
	//	ourShader.setMat4("view", mvs.active);

	//	// render the loaded model
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	//	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	//	ourShader.setMat4("model", model);
	//	ourModel.Draw(ourShader);
	//}
	mvs.pop();


	mvs.pop();


	
	return true;
}

void Scene::moveLight(float x, float z) {
	lightPos.z += z;
	lightPos.x += x;
}

void Scene::adjustStoolHeight(float amount) {
	stoolModel.adjustHeight(amount);
}

void Scene::setFountainShader(ParticleShader *shader) {
	fountainShader = shader;	
	fireplace.setFireShader(shader);
}

void Scene::setTextureShader(Shader *shader) {
	textureShader = shader;	
}
/*#include "DemoApp3.h"

#include "Nanosuit.h"
#include <PointLight.h>

GLfloat cameraX = 0.0F, cameraY = 0.0F, cameraZ = 5.0F;
GLfloat lookX = 0.0F, lookY = 0.0F, lookZ = 0.0F;

GLfloat lightRot = 0.0F;

Nanosuit* suit;
GameObject* lightParent; // to rotate it around a point easily
PointLight* light1;

void DemoApp3::Initialize() {
	GameEngine::Initialize();

	suit = new Nanosuit(m_resources);
	suit->SetLocalPosition(glm::vec3(0.0F, -1.75F, 0.0F));
	//suit->SetScale(glm::vec3(0.2F, 0.2F, 0.2F));

	lightParent = new GameObject();
	light1 = new PointLight();
	light1->SetLocalPosition(glm::vec3(3.0f, 3.0f, 3.0f));

	Add(suit);
	Add(lightParent);
	Add(light1, lightParent);
}

void DemoApp3::Update(GameTime& gameTime) {
	SDL_Event e;

	float CAM_SPEED = 25 * gameTime.deltaTime;

	if (m_input->KeyDown(SDLK_a)) { // left
		cameraX -= CAM_SPEED;
		lookX -= CAM_SPEED;
	} else if (m_input->KeyDown(SDLK_d)) { // right
		cameraX += CAM_SPEED;
		lookX += CAM_SPEED;
	} else if (m_input->KeyDown(SDLK_w)) { // up
		cameraY += CAM_SPEED;
		lookY += CAM_SPEED;
	} else if (m_input->KeyDown(SDLK_s)) { // down
		cameraY -= CAM_SPEED;
		lookY -= CAM_SPEED;
	}

	lightRot += 25 * gameTime.deltaTime;

	lightParent->SetRotationAngle(lightRot);

	m_mainCamera->SetLocalPosition(glm::vec3(cameraX, cameraY, cameraZ));
	m_mainCamera->SetLookAt(glm::vec3(lookX, lookY, lookZ));

	m_scene->Update(gameTime);
}

void DemoApp3::Render() {
	m_scene->Render(m_renderer);
}*/
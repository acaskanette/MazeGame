#include "DemoApp3.h"

#include "Cube.h"

GLfloat cameraX = 0.0F, cameraY = 0.0F, cameraZ = 15.0F;
GLfloat lookX = 0.0F, lookY = 0.0F, lookZ = 0.0F;

GLfloat parentAngle = 0.0F, child1Angle = 0.0F, child2Angle = 0.0F;

Cube* pikachuParent, *pikachuChild1, *pikachuChild2;

void DemoApp3::Initialize() {
	GameEngine::Initialize();

	pikachuParent = new Cube(m_renderer);
	pikachuChild1 = new Cube(m_renderer);
	pikachuChild2 = new Cube(m_renderer);

	Add(pikachuParent); // Add a game object to the scene
	Add(pikachuChild1, pikachuParent); // Add as a child of pikachuParent
	Add(pikachuChild2, pikachuParent);

	pikachuParent->SetLocalPosition(glm::vec3(0.0F, 1.0F, 0.0F));   // Positioned 0, 1, 0 in world space
	pikachuChild1->SetLocalPosition(glm::vec3(-4.0F, -4.0F, 0.0F)); // Positioned -4, -2, 0 relative to the parent
	pikachuChild2->SetLocalPosition(glm::vec3(4.0F, 4.0F, 0.0F));

	pikachuParent->SetRotationAxis(glm::vec3(1, 0, 0));
}

void DemoApp3::Update() {
	SDL_Event e;

	const float CAM_SPEED = 10.0F * 0.0333F;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			Exit();
			break;
			// Keydown events
		case SDL_KEYDOWN:
		{
			SDL_Keycode key = e.key.keysym.sym;
			// Move the camera and have it look the same direction always
			if (key == SDLK_a) {
				cameraX += CAM_SPEED;
				lookX += CAM_SPEED; // left
			}
			if (key == SDLK_d) {
				cameraX -= CAM_SPEED;
				lookX -= CAM_SPEED; // right
			}
			if (key == SDLK_w) {
				cameraY += CAM_SPEED;
				lookY += CAM_SPEED; // up
			}
			if (key == SDLK_s) {
				cameraY -= CAM_SPEED;
				lookY -= CAM_SPEED; // down
			}
			break;
		}
		// Window events
		case SDL_WINDOWEVENT:
		{
			SDL_WindowEvent win = e.window;
			if (win.event == SDL_WINDOWEVENT_RESIZED)
				ResizeWindow(win.data1, win.data2);
			break;
		}
		}
	}

	parentAngle += 25 * 0.0333F;
	child1Angle += 50 * 0.0333F;
	child2Angle -= 50 * 0.0333F;

	pikachuParent->SetRotationAngle(parentAngle);
	pikachuChild1->SetRotationAngle(child1Angle);
	pikachuChild2->SetRotationAngle(child2Angle);

	m_camera->SetPosition(glm::vec3(cameraX, cameraY, cameraZ));
	m_camera->SetLookAt(glm::vec3(lookX, lookY, lookZ));

	// TODO: Move this
	m_camera->UpdateFrustum(m_renderer);

	// Testing frustum culling
	glm::vec3 parentPos = pikachuParent->GetWorldPosition(), leftPos = pikachuChild1->GetWorldPosition(), rightPos = pikachuChild2->GetWorldPosition();
	bool parentInView = m_camera->IsInView(parentPos, 1.0F); // arbitrary radius for the cube
	bool leftInView = m_camera->IsInView(leftPos, 1.0F);
	bool rightInView = m_camera->IsInView(rightPos, 1.0F);
	printf("PARENT POSITION X:%f Y:%f Z:%f | In view? %s\n", parentPos.x, parentPos.y, parentPos.z, parentInView ? "YES" : "NO");
	printf("LEFT CHILD POSITION X:%f Y:%f Z:%f | In view? %s\n", leftPos.x, leftPos.y, leftPos.z, leftInView ? "YES" : "NO");
	printf("RIGHT CHILD POSITION X:%f Y:%f Z:%f | In view? %s\n", rightPos.x, rightPos.y, rightPos.z, rightInView ? "YES" : "NO");

	m_scene->Update();
}

void DemoApp3::Render() {
	m_scene->Render(m_renderer);
}
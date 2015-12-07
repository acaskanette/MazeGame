#pragma once
#include <GameObject.h>
#include <Mesh.h>

class Wall : public GameObject {
public:
	void UpdateMe() override;
	void RenderMe(AbstractRenderer* renderer) override;

	Wall(AbstractRenderer* renderer);
};


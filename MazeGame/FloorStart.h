#pragma once
#include <GameObject.h>
#include <Mesh.h>

class FloorStart :public GameObject
{
public:
	void UpdateMe() override;
	void RenderMe(AbstractRenderer* renderer) override;

	FloorStart(AbstractRenderer* renderer);
};


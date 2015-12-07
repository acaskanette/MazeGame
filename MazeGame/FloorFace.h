#pragma once
#include <GameObject.h>
#include <Mesh.h>

class FloorFace : public GameObject
{
public:
	void UpdateMe() override;
	void RenderMe(AbstractRenderer* renderer) override;

	FloorFace(AbstractRenderer* renderer);
};


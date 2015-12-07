#pragma once
#include <GameObject.h>
#include <Mesh.h>

class FloorEnd : public GameObject
{
public:
	void UpdateMe() override;
	void RenderMe(AbstractRenderer* renderer) override;

	FloorEnd(AbstractRenderer* renderer);
};


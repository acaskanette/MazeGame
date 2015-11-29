#pragma once
#include <GameObject.h>
#include <Mesh.h>

class Cube : public GameObject {
public:
	void UpdateMe() override;
	void RenderMe(AbstractRenderer* renderer) override;

	Cube(AbstractRenderer* renderer);
};
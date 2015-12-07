#pragma once
#include <GameObject.h>
#include <Mesh.h>

class Cube2 : public GameObject {
public:
	void UpdateMe() override;
	void RenderMe(AbstractRenderer* renderer) override;

	Cube2(AbstractRenderer* renderer);
};
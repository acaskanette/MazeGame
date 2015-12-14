#pragma once
#include <GameEngine.h>

class MazeGameApp : public GameEngine {
	virtual void Initialize() override;
	virtual void Update(GameTime&) override;
	virtual void Render() override;
};
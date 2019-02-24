#pragma once

class IGameObject
{
public:
	IGameObject() {};

	~IGameObject() {};

	bool Update(float deltaTime) { return true; };
	bool PostUpdate() {};
};
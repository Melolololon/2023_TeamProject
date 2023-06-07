#pragma once
#include<GuiValue.h>
#include<Sprite2D.h>

class Game final
{
private:
	const bool EDITER_FLAG = false;
private:
	Game();
	~Game();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

public:
	Game(const Game& g) = delete;
	Game& operator=(const Game& g) = delete;

	static Game* GetInstance();
	void Run();
};


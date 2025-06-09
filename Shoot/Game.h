#pragma once
#include "Field.h"

class Game {
private:
    Field* field;

public:
    int score, timeLeft;
    int framesPassed;

    Game();
    ~Game();

    void Start(int width, int height);
    void Draw(System::Drawing::Graphics^ g);
    void OnClick(int mx, int my);
    void Tick();
    void Restart(int width, int height);
};

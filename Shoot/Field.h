#pragma once
#include <vector>
#include "Target.h"

class Field {
private:
    std::vector<Target*> targets;
    int width, height;

public:
    Field();
    ~Field();

    void Init(int count, int width, int height);
    void Draw(System::Drawing::Graphics^ g);
    bool TryHit(int mx, int my, int& score);
};

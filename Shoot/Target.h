#pragma once

class Target {
public:
    int x, y, radius;
    bool active;

    Target(int x, int y, int radius);

    void Draw(System::Drawing::Graphics^ g);
    bool Contains(int mx, int my);
};

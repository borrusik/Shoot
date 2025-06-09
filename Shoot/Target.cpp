#include "Target.h"

using namespace System::Drawing;

Target::Target(int x, int y, int radius)
    : x(x), y(y), radius(radius), active(true) {
}

void Target::Draw(Graphics^ g) {
    if (!active) return;

    g->FillEllipse(Brushes::Red,
        x - radius, y - radius,
        radius * 2, radius * 2);
}

bool Target::Contains(int mx, int my) {
    int dx = x - mx;
    int dy = y - my;
    return active && (dx * dx + dy * dy <= radius * radius);
}

#include "Field.h"
#include <cstdlib>
#include <ctime>

Field::Field() {
    std::srand((unsigned)std::time(0));
}

Field::~Field() {
    for (auto t : targets) delete t;
    targets.clear();
}

void Field::Init(int count, int w, int h) {
    width = w;
    height = h;
    targets.clear();
    int radius = 20;

    for (int i = 0; i < count; ++i) {
        int x, y, attempts = 0;
        bool ok = false;

        while (!ok && attempts < 100) {
            x = rand() % (width - 2 * radius) + radius;
            y = rand() % (height - 2 * radius) + radius;
            ok = true;

            for (auto other : targets) {
                int dx = other->x - x;
                int dy = other->y - y;
                if (dx * dx + dy * dy < (2 * radius) * (2 * radius)) {
                    ok = false;
                    break;
                }
            }
            ++attempts;
        }

        targets.push_back(new Target(x, y, radius));
    }
}

void Field::Draw(System::Drawing::Graphics^ g) {
    for (auto t : targets) t->Draw(g);
}

bool Field::TryHit(int mx, int my, int& score) {
    for (auto t : targets) {
        if (t->Contains(mx, my)) {
            score++;

            // Respawn target
            int attempts = 0;
            int radius = t->radius;
            int new_x = t->x, new_y = t->y;
            bool ok = false;

            while (!ok && attempts < 100) {
                new_x = rand() % (width - 2 * radius) + radius;
                new_y = rand() % (height - 2 * radius) + radius;
                ok = true;

                for (auto other : targets) {
                    if (other != t && other->active) {
                        int dx = other->x - new_x;
                        int dy = other->y - new_y;
                        if (dx * dx + dy * dy < (2 * radius) * (2 * radius)) {
                            ok = false;
                            break;
                        }
                    }
                }
                ++attempts;
            }

            t->x = new_x;
            t->y = new_y;
            return true;
        }
    }
    return false;
}

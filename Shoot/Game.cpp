#include "Game.h"

Game::Game() : score(0), timeLeft(30), framesPassed(0) {
    field = new Field();
}

Game::~Game() {
    delete field;
	field = nullptr;
}

void Game::Start(int width, int height) {
    score = 0;
    timeLeft = 30;
    field->Init(5, width, height);
}

void Game::Draw(System::Drawing::Graphics^ g) {
    field->Draw(g);
}

void Game::OnClick(int mx, int my) {
    if (timeLeft > 0) {
        field->TryHit(mx, my, score);
    }
}

void Game::Tick() {
    if (timeLeft > 0) {
        framesPassed++;
        if (framesPassed >= 30) {
            timeLeft--;
            framesPassed = 0;
        }
    }
}

void Game::Restart(int width, int height) {
    Start(width, height);
}


#include "GameObject.h"

GAME_OBJECT::GAME_OBJECT(class GAME* game) {
    Game = game;
}
GAME_OBJECT::~GAME_OBJECT() {
    Game = nullptr;
}



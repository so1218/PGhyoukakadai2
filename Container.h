#pragma once
#include "Player.h"

class CONTAINER
{
private:
    struct DATA {
       
        Player::Data player;
        
    };
    DATA Data;
    void CreateData();
    void LoadGraphics();
public:
    ~CONTAINER();
    void load();
    const DATA& data() { return Data; }
};

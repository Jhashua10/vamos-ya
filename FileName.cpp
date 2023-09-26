#include "funciones.h"
#include "player.h"
using namespace sf;



int main() {
    UNO.create(VideoMode(1380, 720), "UNO!");
    initializeGame();
    startMenu(); 
    return 0;
}




#include "linklist.hpp"
#include "start.hpp"
#include "energy.hpp"
#include "game.hpp"

Start start("users.txt");
Game game;

int main() {
    initgraph(WID, HEI);
    BeginBatchDraw();

    start.startup();
    game.gaming();

    EndBatchDraw();
    closegraph();
    return 0;
}
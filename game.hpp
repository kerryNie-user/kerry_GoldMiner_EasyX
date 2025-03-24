#ifndef GAME_H
#define GAME_H

#include "start.hpp"
#include "energy.hpp"
#include "linklist.hpp"

class Game {
private:
    //全局元素信息
    Miner miner{(WID - 90) / 2, 10, 90, 70};
    Clock clocking{10};
    Score scoring{0, 600};
    Hook hook{miner.x + miner.w * 4 / 10, miner.y + miner.h * 6 / 10, HOOK_LENGTH, HOOK_SPEED, SLEEP_TIME * 0.15};
    Stage staging{1};

    //图片素材
    IMAGE img_game_background;
    IMAGE img_goldminer_1;
    IMAGE mask_goldminer_1;
    IMAGE img_goldminer_2;
    IMAGE mask_goldminer_2;
    IMAGE img_brick;
    IMAGE img_gold_big;
    IMAGE mask_gold_big;
    IMAGE img_gold_small;
    IMAGE mask_gold_small;

    LinkedList<Gold> golds;

    // 更新游戏状态
    void updateGame();

    // 渲染游戏画面
    void renderGame();

    // 处理用户输入
    void handleInput();

public:
    Game();

    void updateWithoutInput();
    void updateWithInput();
    void gaming();
    void endGame();
};
// Game
Game::Game () {
    loadimage(&img_game_background, imgPath_game_background.c_str(), WID, HEI, true);

    loadimage(&img_goldminer_1, imgPath_goldminer_1.c_str(), miner.w, miner.h, true);
    loadimage(&mask_goldminer_1, maskPath_goldminer_1.c_str(), miner.w, miner.h, true);
    loadimage(&img_goldminer_2, imgPath_goldminer_2.c_str(), miner.w, miner.h, true);
    loadimage(&mask_goldminer_2, maskPath_goldminer_2.c_str(), miner.w, miner.h, true);

    loadimage(&img_brick, imgPath_brick.c_str(), WID, 10, true);

    loadimage(&img_gold_big, imgPath_gold_big.c_str(), 120, 120, true);
    loadimage(&mask_gold_big, maskPath_gold_big.c_str(), 120, 120, true);
    loadimage(&img_gold_small, imgPath_gold_small.c_str(), 30, 30, true);
    loadimage(&mask_gold_small, maskPath_gold_small.c_str(), 30, 30, true);

    std::unique_ptr<GameObject> obj_big = GameObjectFactory::createGameObject("gold", 200, 200, 3, img_gold_big, mask_gold_big);
    std::unique_ptr<GameObject> obj_sma = GameObjectFactory::createGameObject("gold", 500, 150, 1, img_gold_small, mask_gold_small);

    Gold* gold_big = dynamic_cast<Gold*>(obj_big.get());
    Gold* gold_small = dynamic_cast<Gold*>(obj_sma.get());
    
    if (gold_big) golds.push_back(*gold_big);
    if (gold_small) golds.push_back(*gold_small);

    miner.setImage(img_goldminer_1, mask_goldminer_1, img_goldminer_2, mask_goldminer_2);
}

void Game::updateWithoutInput() {
    clocking.update();
    miner.update();
    hook.update();
    for (int i = 0; i < golds.size(); ++i) {
        if (golds[i].isRetracting) {
            golds[i].move(hook.angle);
            if (golds[i].isRetracting && !hook.isRetracting) {
                scoring.get(golds[i].getScore());
                golds.removeAt(i);
            }
        } else if (golds[i].isHooked(hook.endX, hook.endY)) {
            hook.isRetracting = true;
            golds[i].isRetracting = true;
            hook.speed = golds[i].speed;
            miner.usingEnergy = true;
        }
    }
    if (!hook.isMoving) {
        miner.working = false;
        miner.usingEnergy = false;
    }
    if (scoring.reachGoal()) {
        clocking.gameContinue = false;
    }
}

void Game::updateWithInput() {
    MOUSEMSG m;
    if (MouseHit()) {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            hook.isMoving = true;
            miner.working = true;
        }
    }
}

void Game::renderGame() {
    putimage(0, 0, &img_game_background);
    putimage(0, miner.y + miner.h, &img_brick);
    for (Gold gold : golds) {
        gold.draw();
    }
    miner.draw();
    hook.draw();
    clocking.draw();
    scoring.draw();
    staging.draw();
    FlushBatchDraw();
}

void Game::endGame() {
    std::string gameover = scoring.reachGoal() ? "You Did It!" : "YOU LOOOOOSE!!!";

    cleardevice();
    setbkcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(60, 0, _T("宋体"));
    settextcolor(WHITE);

    int textWidth = textwidth(gameover.c_str());
    int textHeight = textheight(gameover.c_str());

    int textX = (WID - textWidth) / 2;
    int textY = (HEI - textHeight) / 2;

    outtextxy(textX, textY, _T(gameover.c_str()));

    FlushBatchDraw();
    Sleep(1000);
}

void Game::gaming() {
    while (clocking.gameContinue) {
        updateWithoutInput();
        updateWithInput();
        renderGame();
        Sleep(SLEEP_TIME);
        std::cout << staging.getS() << std::endl;
    }
    endGame();
}

#endif // GAME_H
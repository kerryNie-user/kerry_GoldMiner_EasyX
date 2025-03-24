#include "newGame.hpp"
#include <conio.h>
#include <locale>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <memory>
#include <chrono>
#include <functional>

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)

void putimgwithmask(IMAGE& img, IMAGE& mask, int x, int y) {
    putimage(x, y, &mask, NOTSRCERASE);
    putimage(x, y, &img, SRCINVERT);
}

Clock::Clock(int total) : start(0), gameContinue(true), display("Time: 0"), total(total) {}
void Clock::draw() {
    int textWidth = textwidth(display.c_str());
    int textHeight = textheight(display.c_str());
    int textX = (WID - textWidth - WID / 50);
    int textY = (50 - textHeight) / 2;
    outtextxy(textX, textY, display.c_str());
}
void Clock::update() {
    current = clock();
    if (start == 0) {
        start = current;
    } else {
        int elapsed = (current - start) / CLOCKS_PER_SEC;
        remain = total - elapsed;
        if (remain <= 0) {
            remain = 0;
            gameContinue = false;
        }
    }
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << remain;
    display = "Time: " + oss.str();
}
bool Clock::isContinue() {
    return gameContinue;
}

Score::Score(int goal) : score(0), goal(goal), displayScore("Score: 0"), displayGoal("Goal: " + std::to_string(goal)) {}
void Score::draw() {
    int textWidth1 = textwidth(displayScore.c_str());
    int textHeight1 = textheight(displayScore.c_str());
    int textWidth2 = textwidth(displayGoal.c_str());
    int textHeight2 = textheight(displayGoal.c_str());
    int textX = WID / 50;
    int textY1 = (50 - textHeight1) / 2;
    int textY2 = (50 + textHeight2) / 2;
    outtextxy(textX, textY1, displayScore.c_str());
    outtextxy(textX, textY2, displayGoal.c_str());
}
void Score::get(int newScore) {
    score += newScore;
    update();
}
void Score::los(int loseScore) {
    score -= loseScore;
    if (score < 0) {
        score = 0;
    }
    update();
}
bool Score::reachGoal() {
    return score >= goal;
}
void Score::update() {
    displayScore = "Score: " + std::to_string(score);
}

Stage::Stage(int stage) : stage(stage), display("Stage: " + std::to_string(stage)) {}
int Stage::getStage() {
    return stage;
}
void Stage::draw() {
    int textWidth = textwidth(display.c_str());
    int textHeight = textheight(display.c_str());
    int textX = (WID - textWidth - WID / 50);
    int textY = (50 + textHeight) / 2;
    outtextxy(textX, textY, display.c_str());
}

CButton::CButton(int x, int y, int width, int height, const std::string& buttonText, ButtonCallBack callback)
    : x(x), y(y), width(width), height(height), buttonText(buttonText), callback(callback) {}
void CButton::simulateMouseClick(int mouseX, int mouseY) {
    if (isMouseInButton(mouseX, mouseY)) {
        if (callback) {
            callback();
        }
    }
}
void CButton::draw() {
    setfillcolor(WHITE);
    fillrectangle(x, y, x + width, y + height);
    setbkmode(TRANSPARENT);
    settextstyle(40, 0, _T("宋体"));
    settextcolor(BLACK);
    int textWidth = textwidth(_T(buttonText).c_str());
    int textHeight = textheight(_T(buttonText).c_str());
    int textX = x + (width - textWidth) / 2;
    int textY = y + (height - textHeight) / 2;
    outtextxy(textX, textY, _T(buttonText).c_str());
}
bool CButton::isMouseInButton(int mouseX, int mouseY) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
}

CInputBox::CInputBox(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), isFocused(false) {}
std::string CInputBox::getInputText() const {
    return inputText;
}
void CInputBox::simulateMouseClick(int mouseX, int mouseY) {
    if (isMouseInButton(mouseX, mouseY)) {
        isFocused = true;
        handleEvent();
    }
}
void CInputBox::draw() {
    setfillcolor(isFocused ? RGB(100, 100, 100) : WHITE);
    fillrectangle(x, y, x + width, y + height);
    setbkmode(TRANSPARENT);
    settextstyle(40, 0, _T("宋体"));
    settextcolor(BLACK);
    int textWidth = textwidth(_T(inputText).c_str());
    int textHeight = textheight(_T(inputText).c_str());
    int textX = x + (width - textWidth) / 2;
    int textY = y + (height - textHeight) / 2;
    outtextxy(textX, textY, _T(inputText).c_str());
}
void CInputBox::handleEvent() {
    while (true) {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (isMouseInButton(m.x, m.y)) {
                    isFocused = true;
                } else {
                    isFocused = false;
                    break;
                }
            }
        }
        if (kbhit()) {
            wchar_t ch = _getwch();
            if (ch == L'\r') {
                isFocused = false;
                break;
            } else if (ch == L'\b') {
                if (!inputText.empty()) {
                    inputText.pop_back();
                }
            } else {
                inputText += ch;
            }
        }
        draw();
        FlushBatchDraw();
    }
    Sleep(SLEEP_TIME);
}
bool CInputBox::isMouseInButton(int mouseX, int mouseY) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
}

CMiner::CMiner() : x(MINER_X), y(MINER_Y), w(MINER_W), h(MINER_H) {}
void CMiner::setImage(IMAGE& img1, IMAGE& mask1, IMAGE& img2, IMAGE& mask2) {
    this->img1 = img1;
    this->mask1 = mask1;
    this->img2 = img2;
    this->mask2 = mask2;
}
void CMiner::update() {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastTime;
    double interval = usingEnergy ? 0.5 : 0.25;
    if (elapsedTime.count() >= interval) {
        showSecondImage = !showSecondImage;
        lastTime = currentTime;
    }
}
void CMiner::draw() {
    if (working && showSecondImage) {
        putimgwithmask(img2, mask2, x, y);
    } else {
        putimgwithmask(img1, mask1, x, y);
    }
}
void CMiner::work() {
    working = true;
}
void CMiner::useEnergy() {
    working = true;
    usingEnergy = true;
}
void CMiner::stop() {
    working = false;
    usingEnergy = false;
}

CHook::CHook() : x(HOOK_X), y(HOOK_Y), length(HOOK_LENGTH), speed(HOOK_SPEED), angleSpeed(SLEEP_TIME * 0.15), angle(90) {}
double CHook::getAngle() const {
    return angle;
}
int CHook::getLength() const {
    return length;
}
void CHook::draw() {
    setcolor(BLACK);
    setlinestyle(PS_SOLID, 2);
    line(x, y, endX, endY);
    circle(endX, endY, 5);
}
void CHook::update() {
    endX = x + length * cos(degreesToRadians(angle));
    endY = y + length * sin(degreesToRadians(angle));
    if (!isMoving) {
        angle += angleSpeed;
        if (angle >= 160) {
            angleSpeed = -angleSpeed;
            angle = 160;
        } else if (angle <= 20) {
            angleSpeed = -angleSpeed;
            angle = 20;
        }
    } else {
        if (!isRetracting) {
            length += speed;
            if (endX <= 0 || endX >= WID || endY >= HEI) {
                isRetracting = true;
            }
        } else {
            length -= speed;
            if (length <= HOOK_LENGTH) {
                length = HOOK_LENGTH;
                speed = HOOK_SPEED;
                isMoving = false;
                isRetracting = false;
            }
        }
    }
}
bool CHook::isStop() {
    return !isMoving && !isRetracting;
}
void CHook::setSpeed(int speed) {
    this->speed = speed;
}
int CHook::getEndX() const {
    return endX;
}
int CHook::getEndY() const {
    return endY;
}
void CHook::move() {
    isMoving = true;
}
void CHook::retract() {
    isRetracting = true;
}

GameObject::GameObject(double x, double y, int size, IMAGE img, IMAGE mask)
    : x(x), y(y), size(size), img(img), mask(mask) {}
void GameObject::draw() {
    putimage(x, y, &mask, NOTSRCERASE);
    putimage(x, y, &img, SRCINVERT);
}
void GameObject::retract() {
    isRetracting = true;
}
bool GameObject::retracted() {
    return isRetracting;
}
bool GameObject::isHooked(int hookX, int hookY) {
    int distanceSquared = std::pow((x + radius - hookX), 2) + std::pow((y + radius - hookY), 2);
    return distanceSquared <= radius * radius;
}
void GameObject::move(int moveangle) {
    x -= speed * cos(degreesToRadians(moveangle));
    y -= speed * sin(degreesToRadians(moveangle));
}
bool GameObject::operator==(const GameObject& other) const {
    return this->x == other.x && this->y == other.y && this->size == other.size;
}
int GameObject::getScore() const {
    return score;
}
int GameObject::getSpeed() const {
    return speed;
}

Gold::Gold(int x, int y, int size, IMAGE img, IMAGE mask) 
    : GameObject(x, y, size, img, mask) {
    setRadiusAndSpeed();
}
void Gold::setRadiusAndSpeed() {
    static const int radii[] = {0, 15, 40, 60};
    static const int speeds[] = {0, 4, 2, 1};
    static const int scores[] = {0, 100, 300, 500};
    this->radius = radii[size];
    this->speed = speeds[size];
    this->score = scores[size];
}

Rock::Rock(int x, int y, int size, IMAGE img, IMAGE mask) 
    : GameObject(x, y, size, img, mask) {
    setRadiusAndSpeed();
}
void Rock::setRadiusAndSpeed() {
    static const int radii[] = {0, 18, 40};
    static const int speeds[] = {0, 3, 1};
    static const int scores[] = {0, 50, 100};
    this->radius = radii[size];
    this->speed = speeds[size];
    this->score = scores[size];
}

Diamond::Diamond(int x, int y, IMAGE img, IMAGE mask)
    : GameObject(x, y, 1, img, mask) {
    setRadiusAndSpeed();
}
void Diamond::setRadiusAndSpeed() {
    this->radius = 15;
    this->speed = 4;
    this->score = 1000;
}

std::unique_ptr<GameObject> GameObjectFactory::createGameObject(GameObjectType type, int x, int y, int size, IMAGE img, IMAGE mask) {
    switch (type) {
        case GameObjectType::GOLD:
            return std::make_unique<Gold>(x, y, size, img, mask);
        case GameObjectType::ROCK:
            return std::make_unique<Rock>(x, y, size, img, mask);
        case GameObjectType::DIAMOND:
            return std::make_unique<Diamond>(x, y, img, mask);
        default:
            return nullptr;
    }
}

CScene::CScene(std::function<void(int)> setGameScene) : setGameScene(setGameScene) {}
void CScene::outputStatus(std::string text) {
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    setbkcolor(WHITE);
    settextstyle(40, 0, _T("宋体"));
    fillrectangle(0.12 * WID, 0.37 * HEI, 0.88 * WID, 0.8 * HEI);
    int textX = 0.5 * WID - (textwidth(_T(text).c_str())) / 2;
    int textY = 0.59 * HEI - (textheight(_T(text).c_str())) / 2;
    outtextxy(textX, textY, _T(text).c_str());
    FlushBatchDraw();
    Sleep(1000);
}

CMenu::CMenu(std::function<void(int)> setGameScene) : CScene(setGameScene),
    m_button_signin(0.1 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, "signin", std::bind(&CMenu::callbackSignin, this)), 
    m_button_login(0.6 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, "login", std::bind(&CMenu::callbackLogin, this)) {}
void CMenu::update() {
    MOUSEMSG m;
    if (MouseHit()) {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            m_button_signin.simulateMouseClick(m.x, m.y);
            m_button_login.simulateMouseClick(m.x, m.y);
        }
    }
}
void CMenu::render() {
    cleardevice();
    putimage(0, 0, &img_startup);
    m_button_login.draw();
    m_button_signin.draw();
    FlushBatchDraw();
}
void CMenu::callbackSignin() {
    setGameScene(game_scene_signin);
}
void CMenu::callbackLogin() {
    setGameScene(game_scene_login);
}

CSignin::CSignin(std::function<void(int)> setGameScene) : CScene(setGameScene), confirm(false), 
    m_input_username(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI), 
    m_input_password(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI), 
    m_input_confirm(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI), 
    m_button_ok(0.8 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "OK", std::bind(&CSignin::callbackOk, this)), 
    m_button_cancel(0.04 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "CANCEL", std::bind(&CSignin::callbackCancel, this)) {}
void CSignin::update() {
    MOUSEMSG m;
    if (MouseHit()) {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (confirm) {
                m_input_confirm.simulateMouseClick(m.x, m.y);
            } else {
                m_input_username.simulateMouseClick(m.x, m.y);
                m_input_password.simulateMouseClick(m.x, m.y);
            }
            m_button_ok.simulateMouseClick(m.x, m.y);
            m_button_cancel.simulateMouseClick(m.x, m.y);
        }
    }
}
void CSignin::render() {
    cleardevice();
    putimage(0, 0, &img_signin);
    setbkmode(TRANSPARENT);
    setfillcolor(RGB(224, 243, 225));
    fillrectangle(0.12 * WID, 0.37 * HEI, 0.88 * WID, 0.8 * HEI);
    settextstyle(40, 0, _T("宋体"));
    settextcolor(BLACK);
    m_input_username.draw();
    if (confirm) {
        m_input_confirm.draw();
    } else {
        m_input_password.draw();
    }
    m_button_ok.draw();
    m_button_cancel.draw();
    FlushBatchDraw();
}
void CSignin::callbackOk() {
    if (confirm) {
        std::string passwordOld = m_input_password.getInputText();
        std::string passwordNew = m_input_confirm.getInputText();
        if (passwordOld == passwordNew) {
            storedUsername.push_back(m_input_username.getInputText());
            storedPassword.push_back(m_input_password.getInputText());
            storedStage.push_back(1);
            userIndex = storedUsername.size() - 1;
            outputStatus("Welcome in...");
            setGameScene(game_scene_game);
        } else {
            outputStatus("Password incorrect");
        }
    } else {
        std::string username = m_input_username.getInputText();
        std::string password = m_input_password.getInputText();
        if (username.empty()) {
            outputStatus("Username cannot be empty");
            return;
        } else if (password.empty()) {
            outputStatus("Password cannot be empty");
            return;
        }
        auto itUser = storedUsername.begin();
        for (userIndex = 0; itUser != storedUsername.end(); ++itUser, ++userIndex) {
            if (username == *itUser) {
                outputStatus("Username has been used");
                return;
            }
        }
        outputStatus("Please confirm your password");
        confirm = true;
    }
}
void CSignin::callbackCancel() {
    if (confirm) {
        confirm = false;
    } else {
        setGameScene(game_scene_menu);
    }
}

CLogin::CLogin(std::function<void(int)> setGameScene) : CScene(setGameScene),
    m_button_ok(0.8 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "OK", std::bind(&CLogin::callbackOk, this)),
    m_button_cancel(0.04 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "CANCEL", std::bind(&CLogin::callbackCancel, this)),
    m_input_username(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI),
    m_input_password(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI) {}
void CLogin::update() {
    MOUSEMSG m;
    if (MouseHit()) {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            m_input_username.simulateMouseClick(m.x, m.y);
            m_input_password.simulateMouseClick(m.x, m.y);
            m_button_ok.simulateMouseClick(m.x, m.y);
            m_button_cancel.simulateMouseClick(m.x, m.y);
        }
    }
}
void CLogin::render() {
    cleardevice();
    putimage(0, 0, &img_signin);
    setbkmode(TRANSPARENT);
    setfillcolor(RGB(224, 243, 225));
    fillrectangle(0.12 * WID, 0.37 * HEI, 0.88 * WID, 0.8 * HEI);
    settextstyle(40, 0, _T("宋体"));
    settextcolor(BLACK);
    m_input_username.draw();
    m_input_password.draw();
    m_button_ok.draw();
    m_button_cancel.draw();
    FlushBatchDraw();
}
void CLogin::callbackOk() {
    std::string username = m_input_username.getInputText();
    std::string password = m_input_password.getInputText();
    auto itUser = storedUsername.begin();
    auto itPass = storedPassword.begin();
    for (userIndex = 0; itUser != storedUsername.end() && itPass != storedPassword.end(); ++itUser, ++itPass, ++userIndex) {
        if (username == *itUser && password == *itPass) {
            outputStatus("Welcome back...");
            setGameScene(game_scene_game);
            return;
        }
    }
    outputStatus("Username or Password incorrect");
}
void CLogin::callbackCancel() {
    setGameScene(game_scene_menu);
}

CGame::CGame(std::function<void(int)> setGameScene) : 
    CScene(setGameScene),
    m_clock(GAME_TIME),
    m_score(SCORE_GOAL_FACTOR * storedStage[userIndex]),
    m_stage(storedStage[userIndex]),
    m_miner(),
    m_hook() {
    initGameObjects();
}
void CGame::update() {
    m_clock.update();
    for (auto& obj : m_gameObjects) {
        obj->move(m_hook.getAngle());
    }
    m_hook.update();
    for (auto& obj : m_gameObjects) {
        if (obj->retracted()) {
            obj->move(m_hook.getAngle());
        }
    }
    if (m_clock.isContinue()) {
        if (m_hook.isStop()) {
            if (kbhit()) {
                int key = _getch();
                if (key == ' ') {
                    m_hook.move();
                    m_miner.work();
                }
            }
        }
        auto it = m_gameObjects.begin();
        int index = 0;
        while (it != m_gameObjects.end()) {
            if ((*it)->isHooked(m_hook.getEndX(), m_hook.getEndY())) {
                m_hook.setSpeed((*it)->getSpeed());
                m_hook.retract();
                (*it)->retract();
                if (m_hook.getLength() <= HOOK_LENGTH) {
                    m_score.get((*it)->getScore());
                    it = m_gameObjects.erase(it); // 使用 erase 方法并更新迭代器
                    m_miner.stop();
                    continue;
                }
            }
            ++it;
            ++index;
        }
    } else {
        if (m_score.reachGoal()) {
            outputStatus("Stage Clear!");
            storedStage[userIndex]++;
        } else {
            outputStatus("Stage Failed!");
        }
        setGameScene(game_scene_menu);
    }
}
void CGame::render() {
    cleardevice();
    putimage(0, 0, &img_game_background);
    putimage(0, MINER_Y + MINER_H, &img_brick);
    m_clock.draw();
    m_score.draw();
    m_stage.draw();
    m_miner.draw();
    m_hook.draw();
    for (const auto& obj : m_gameObjects) {
        obj->draw();
    }
    FlushBatchDraw();
}
void CGame::initGameObjects() {
    m_gameObjects.push_back(GameObjectFactory::createGameObject(GameObjectType::GOLD, 100, 200, 1, img_gold_small, mask_gold_small));
    m_gameObjects.push_back(GameObjectFactory::createGameObject(GameObjectType::GOLD, 200, 300, 2, img_gold_big, mask_gold_big));
}

Game::Game() : m_game_scene(game_scene_menu),
               m_menu([this](int scene) { this->m_game_scene = scene; }),
               m_signin([this](int scene) { this->m_game_scene = scene; }),
               m_login([this](int scene) { this->m_game_scene = scene; }),
               m_game([this](int scene) { this->m_game_scene = scene; }) {}
void Game::run() {
    loadIMAGE();
    loadTEXT();
    initgraph(WID, HEI);
    BeginBatchDraw();
    while (true) {
        switch (m_game_scene) {
            case game_scene_menu:
                m_menu.update();
                m_menu.render();
                break;
            case game_scene_signin:
                m_signin.update();
                m_signin.render();
                break;
            case game_scene_login:
                m_login.update();
                m_login.render();
                break;
            case game_scene_game:
                m_game.update();
                m_game.render();
                break;
                return;
            default:
                EndBatchDraw();
                writeTEXT();
                closegraph();
                return;
        }
        FlushBatchDraw();
        Sleep(SLEEP_TIME);
    }
    EndBatchDraw();
    writeTEXT();
    closegraph();
}
bool Game::loadTEXT() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << " for checking username." << std::endl;
        return false;
    }
    std::string username, password;
    int stage;
    if (file.peek() == std::ifstream::traits_type::eof()) {
        file.close();
        return true;
    }
    while (file >> username >> password >> stage) {
        storedUsername.push_back(username);
        storedPassword.push_back(password);
        storedStage.push_back(stage);
    }
    file.close();
    if (storedUsername.size() != storedPassword.size() || storedUsername.size() != storedStage.size()) {
        std::cerr << "Linked list sizes are inconsistent!" << std::endl;
        return false;
    }
    return true;
}
void Game::loadIMAGE() {
    loadimage(&img_startup, imgPath_startup.c_str(), WID, HEI, true);
    loadimage(&img_signin, imgPath_signin.c_str(), WID, HEI, true);
    loadimage(&img_login, imgPath_login.c_str(), WID, HEI, true);
    loadimage(&img_game_background, imgPath_game_background.c_str(), WID, HEI, true);
    loadimage(&img_goldminer_1, imgPath_goldminer_1.c_str(), 90, 70, true);
    loadimage(&mask_goldminer_1, maskPath_goldminer_1.c_str(), 90, 70, true);
    loadimage(&img_goldminer_2, imgPath_goldminer_2.c_str(), 90, 70, true);
    loadimage(&mask_goldminer_2, maskPath_goldminer_2.c_str(), 90, 70, true);
    loadimage(&img_brick, imgPath_brick.c_str(), WID, 10, true);
    loadimage(&img_gold_big, imgPath_gold_big.c_str(), 120, 120, true);
    loadimage(&mask_gold_big, maskPath_gold_big.c_str(), 120, 120, true);
    loadimage(&img_gold_small, imgPath_gold_small.c_str(), 30, 30, true);
    loadimage(&mask_gold_small, maskPath_gold_small.c_str(), 30, 30, true);

    auto obj_gold_big = GameObjectFactory::createGameObject(GameObjectType::GOLD, 200, 200, 3, img_gold_big, mask_gold_big);
    auto obj_gold_small = GameObjectFactory::createGameObject(GameObjectType::GOLD, 500, 150, 1, img_gold_small, mask_gold_small);
}
bool Game::writeTEXT() {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << " for signing in." << std::endl;
        return false;
    }
    auto itUser = storedUsername.begin();
    auto itPass = storedPassword.begin();
    auto itStag = storedStage.begin();
    for (; itUser != storedUsername.end(); ++itUser, ++itPass, ++itStag) {
        file << *itUser << " " << *itPass << " " << *itStag << std::endl;
    }
    file.close();
    return true;
}

int main() {
    Game game;
    game.run();
    return 0;
}
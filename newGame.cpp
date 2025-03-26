#include <memory>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <locale>
#include <codecvt>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <memory>
#include <iomanip>
#include "linklist.hpp"

LinkedList<std::string> storedUsername;
LinkedList<std::string> storedPassword;
LinkedList<int> storedStage;
std::string username = "kerry";
std::string password = "kerry";
int stage = 1;

std::string filePath = "users.txt";
std::string imgPath_startup = "res/img_startup.jpg";
std::string imgPath_signin = "res/img_signin.jpg";
std::string imgPath_login = "res/img_login.jpg";
std::string imgPath_game_background = "res/img_game_background.jpg";
std::string imgPath_goldminer_1 = "res/img_goldminer_1.jpg";
std::string maskPath_goldminer_1 = "res/img_goldminer_mask_1.jpg";
std::string imgPath_goldminer_2 = "res/img_goldminer_2.jpg";
std::string maskPath_goldminer_2 = "res/img_goldminer_mask_2.jpg";
std::string imgPath_brick = "res/img_brick.jpg";
std::string imgPath_gold_big = "res/img_gold_big.jpg";
std::string maskPath_gold_big = "res/img_gold_big_mask.jpg";
std::string imgPath_gold_small = "res/img_gold_small.jpg";
std::string maskPath_gold_small = "res/img_gold_small_mask.jpg";

IMAGE img_startup;
IMAGE img_signin;
IMAGE img_login;
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

enum class GameSceneType {
    END,
    MENU,
    SIGNIN,
    LOGIN,
    GAME
};

#define BIG 3
#define MID 2
#define SML 1

const int SLEEP_TIME = 10;
const int LENGTH_INDEX = 300;
const int WID = 3 * LENGTH_INDEX;
const int HEI = 2 * LENGTH_INDEX;
const int HOOK_LENGTH = 30;
const int HOOK_SPEED = SLEEP_TIME * 6 / 10;
const int MINER_X = (WID - 90) / 2;
const int MINER_Y = 10;
const int MINER_W = 90;
const int MINER_H = 70;
const int HOOK_X = MINER_X + MINER_W * 4 / 10;
const int HOOK_Y = MINER_Y + MINER_H * 6 / 10;
const int GAME_TIME = 60;
const int SCORE_GOAL_FACTOR = 800;

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)

enum class GameObjectType {
    GOLD,
    ROCK,
    DIAMOND
};

class Clock {
public:
    Clock(int total) : start(0), gameContinue(true), display("Time: 0"), total(total) {}
    void draw() {
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
        int textX = (WID - textWidth - WID / 50);
        int textY = (50 - textHeight) / 2;
        outtextxy(textX, textY, display.c_str());
    }
    void update () {
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
    bool isContinue() {
        return gameContinue;
    }
private:
    int start;
    int total;
    int current;
    int remain;
    bool gameContinue;
    std::string display;
};

class Score {
public:
    Score(int goal) : score(0), goal(goal), displayScore("Score: 0"), displayGoal("Goal: " + std::to_string(goal)) {}
    void draw() {
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
    void get(int newScore) {
        score += newScore;
        update();
    }
    void los(int loseScore) {
        score -= loseScore;
        if (score < 0) {
            score = 0;
        }
        update();
    }
    bool reachGoal() {
        return score >= goal;
    }
private:
    int score;
    int goal;
    std::string displayScore;
    std::string displayGoal;
    void update() {
        displayScore = "Score: " + std::to_string(score);
    }
};

class Stage {
public:
    Stage(int stage) : stage(stage), display("Stage: " + std::to_string(stage)) {}
    int getStage() {
        return stage;
    }
    void draw() {
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
        int textX = (WID - textWidth - WID / 50);
        int textY = (50 + textHeight) / 2;
        outtextxy(textX, textY, display.c_str());
    }
private:
    int stage;
    std::string display;
};

using ButtonCallBack = std::function<void()>;

class CControl {
public:
    virtual void draw() = 0;
    virtual ~CControl() {}
};

class CButton : public CControl {
public:
    CButton(int x, int y, int width, int height, const std::string& buttonText, ButtonCallBack callback) 
        : x(x), y(y), width(width), height(height), buttonText(buttonText), callback(callback) {}
    void simulateMouseClick(int mouseX, int mouseY) {
        if (isMouseInButton(mouseX, mouseY)) {
            if (callback) {
                callback();
            }
        }
    }
    void draw() {
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
private:
    int x, y;
    int width, height;
    std::string buttonText;
    ButtonCallBack callback;
    bool isMouseInButton(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }
};

class CInputBox : public CControl {
public:
    CInputBox(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), isFocused(false) {}
    std::string getInputText() const {
        return inputText;
    }
    void simulateMouseClick(int mouseX, int mouseY) {
        if (isMouseInButton(mouseX, mouseY)) {
            isFocused = true;
            handleEvent();
        }
    }
    void draw() {
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
private:
    int x, y;
    int width, height;
    std::string inputText;
    bool isFocused;
    void handleEvent() {
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
    bool isMouseInButton(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }
};

class CObject {
public:
    virtual void draw() = 0;
    void putimgwithmask(IMAGE& img, IMAGE& mask, int x, int y) {
        putimage(x, y, &mask, NOTSRCERASE);
        putimage(x, y, &img, SRCINVERT);
    }
};

class CMiner : public CObject {
private:
    int x, y;
    int w, h;
    bool working = false;
    bool usingEnergy = false;
    bool showSecondImage = false;
    std::chrono::time_point<std::chrono::system_clock> lastTime;
    IMAGE img1;
    IMAGE mask1;
    IMAGE img2;
    IMAGE mask2;
public:
    CMiner() : x(MINER_X), y(MINER_Y), w(MINER_W), h(MINER_H) {}
    void setImage(IMAGE& img1, IMAGE& mask1, IMAGE& img2, IMAGE& mask2) {
        this->img1 = img1;
        this->mask1 = mask1;
        this->img2 = img2;
        this->mask2 = mask2;
    }
    void draw() {
        if (working && showSecondImage) {
            putimgwithmask(img2, mask2, x, y);
        } else {
            putimgwithmask(img1, mask1, x, y);
        }
    }
    void work() {
        working = true;
    }
    void useEnergy() {
        working = true;
        usingEnergy = true;
    }
    void stop() {
        working = false;
        usingEnergy = false;
    }
    void update() {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - lastTime;
        double interval = usingEnergy ? 0.5 : 0.25;
        if (elapsedTime.count() >= interval) {
            showSecondImage = !showSecondImage;
            lastTime = currentTime;
        }
    }
};

class CHook : public CObject {
private:
    int x, y;
    int endX, endY;
    int length;
    int speed;
    double angle;
    double angleSpeed;
    bool isMoving;
    bool isRetracting;
public:
    CHook() : x(HOOK_X), y(HOOK_Y), length(HOOK_LENGTH), speed(HOOK_SPEED), angleSpeed(SLEEP_TIME * 0.15), angle(90) {}
    void draw() {
        setcolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        line(x, y, endX, endY);
        circle(endX, endY, 5);
    }
    void update() {
        endX = x + length * cos(degreesToRadians(angle));
        endY = y + length * sin(degreesToRadians(angle));
        if (isStop()) {
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
                    setSpeed(HOOK_SPEED);
                    stop();
                }
            }
        }
    }
    bool isStop() {
        return (!isMoving) && (!isRetracting) && (length <= HOOK_LENGTH);
    }
    void setSpeed(int speed) {
        this->speed = speed;
    }
    int getEndX() const {
        return endX;
    }
    int getEndY() const {
        return endY;
    }
    int getLength() const {
        return length;
    }
    double getAngle() const {
        return angle;
    }
    void move() {
        isMoving = true;
    }
    void retract() {
        isRetracting = true;
    }
    void stop() {
        isMoving = false;
        isRetracting = false;
    }
};

class GameObject : public CObject {
protected:
    double x;
    double y;
    int size;
    int radius;
    int speed;
    int score;
    bool isRetracting = false;
    IMAGE img;
    IMAGE mask;
public:
    GameObject(double x, double y, int size, IMAGE& img, IMAGE& mask)
        : x(x), y(y), size(size), img(img), mask(mask) {}
    virtual void setRadiusAndSpeed() = 0;
    void draw() {
        putimgwithmask(img, mask, x, y);
    }
    void retract() {
        isRetracting = true;
    }
    bool retracted() {
        return isRetracting;
    }
    bool isHooked(int hookX, int hookY) {
        int distanceSquared = std::pow((x + radius - hookX), 2) + std::pow((y + radius - hookY), 2);
        return distanceSquared <= radius * radius;
    }
    void move(int moveangle) {
        x -= speed * cos(degreesToRadians(moveangle));
        y -= speed * sin(degreesToRadians(moveangle));
    }
    bool operator==(const GameObject& other) const {
        return this->x == other.x && this->y == other.y && this->size == other.size;
    }
    int getScore() const {
        return score;
    }
    int getSpeed() const {
        return speed;
    }
};

class Gold : public GameObject {
public:
    Gold(int x, int y, int size, IMAGE& img, IMAGE& mask) 
        : GameObject(x, y, size, img, mask) {
        setRadiusAndSpeed();
    }
    void setRadiusAndSpeed() override {
        static const int radii[] = {0, 15, 40, 60};
        static const int speeds[] = {0, 4, 2, 1};
        static const int scores[] = {0, 100, 300, 500};
        this->radius = radii[size];
        this->speed = speeds[size];
        this->score = scores[size];
    }
};

class Rock : public GameObject {
public:
    Rock(int x, int y, int size, IMAGE& img, IMAGE& mask) 
        : GameObject(x, y, size, img, mask) {
        setRadiusAndSpeed();
    }
    void setRadiusAndSpeed() override {
        static const int radii[] = {0, 18, 40};
        static const int speeds[] = {0, 3, 1};
        static const int scores[] = {0, 50, 100};
        this->radius = radii[size];
        this->speed = speeds[size];
        this->score = scores[size];
    }
};

class Diamond : public GameObject {
public:
    Diamond(int x, int y, IMAGE& img, IMAGE& mask)
        : GameObject(x, y, 1, img, mask) {
        setRadiusAndSpeed();
    }
    void setRadiusAndSpeed() override {
        this->radius = 15;
        this->speed = 4;
        this->score = 1000;
    }
};

class GameObjectFactory {
public:
    static std::unique_ptr<GameObject> createGameObject(GameObjectType type, int x, int y, int size, IMAGE& img, IMAGE& mask) {
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
};

LinkedList<std::unique_ptr<GameObject>> m_gameObjects;

class CScene {
protected:
    int m_scene;
    std::function<void(GameSceneType)> setGameScene;
public:
    CScene(const std::function<void(GameSceneType)>& setGameScene) : setGameScene(setGameScene) {}
    virtual void update() = 0;
    virtual void render() = 0;
protected:
    void outputStatus(std::string text) {
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
};

class CMenu : public CScene {
private:
    CButton m_button_signin;
    CButton m_button_login;
public:
    CMenu(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_signin(0.1 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, "signin", std::bind(&CMenu::callbackSignin, this)), 
        m_button_login(0.6 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, "login", std::bind(&CMenu::callbackLogin, this)) {}
    void update() override{
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                m_button_signin.simulateMouseClick(m.x, m.y);
                m_button_login.simulateMouseClick(m.x, m.y);
            }
        }
    }
    void render() override {
        cleardevice();
        putimage(0, 0, &img_startup);
        m_button_login.draw();
        m_button_signin.draw();
        FlushBatchDraw();
    }
private:
    void callbackSignin() {
        setGameScene(GameSceneType::SIGNIN);
    }
    void callbackLogin() {
        setGameScene(GameSceneType::LOGIN);
    }
};

class CSignin : public CScene {
private:
    bool confirm;    
    CInputBox m_input_username;
    CInputBox m_input_password;
    CInputBox m_input_confirm;
    CButton m_button_ok;
    CButton m_button_cancel;
public:
    CSignin(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene), confirm(false), 
        m_input_username(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI), 
        m_input_password(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI), 
        m_input_confirm(0.34 * WID, 0.78 * HEI, 0.48 * WID, 0.12 * HEI), 
        m_button_ok(0.8 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "OK", std::bind(&CSignin::callbackOk, this)), 
        m_button_cancel(0.04 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "CANCEL", std::bind(&CSignin::callbackCancel, this)) {}
    void update() override {
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
    void render() override {
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
private:
    void callbackOk() {
        if (confirm) {
            std::string passwordOld = m_input_password.getInputText();
            std::string passwordNew = m_input_confirm.getInputText();
            if (passwordOld == passwordNew) {
                stage = 1;
                storedUsername.push_back(username);
                storedPassword.push_back(password);
                storedStage.push_back(stage);
                outputStatus("Welcome in...");
                setGameScene(GameSceneType::GAME);
            } else {
                outputStatus("Password incorrect");
            }
        } else {
            username = m_input_username.getInputText();
            password = m_input_password.getInputText();
            if (username.empty()) {
                outputStatus("Username cannot be empty");
                return;
            } else if (password.empty()) {
                outputStatus("Password cannot be empty");
                return;
            }
            for (std::string user : storedUsername) {
                if (username == user) {
                    outputStatus("Username has been used");
                    return;
                }
            }
            outputStatus("Please confirm your password");
            confirm = true;
        }
    }
    void callbackCancel() {
        if (confirm) {
            confirm = false;
        } else {
            setGameScene(GameSceneType::MENU);
        }
    }
};

class CLogin : public CScene {
private:
    CInputBox m_input_username;
    CInputBox m_input_password;
    CButton m_button_ok;
    CButton m_button_cancel;
public:
    CLogin(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_ok(0.8 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "OK", std::bind(&CLogin::callbackOk, this)),
        m_button_cancel(0.04 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "CANCEL", std::bind(&CLogin::callbackCancel, this)),
        m_input_username(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI),
        m_input_password(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI) {}
    void update() override {
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
    void render() override {
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
    void callbackOk() {
        username = m_input_username.getInputText();
        password = m_input_password.getInputText();
        for (int i = 0; i < storedUsername.size(); ++i) {
            if (username == storedUsername[i] && password == storedPassword[i]) {
                stage = storedStage[i];
                outputStatus("Welcome back...");
                setGameScene(GameSceneType::GAME);
                return;
            }
        }
        outputStatus("Username or Password incorrect");
    }
    void callbackCancel() {
        setGameScene(GameSceneType::MENU);
    }
};

class CGame : public CScene {
private:
    Clock m_clock;
    Score m_score;
    Stage m_stage;
    CMiner m_miner;
    CHook m_hook;
public:
    CGame(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_clock(GAME_TIME), m_score(SCORE_GOAL_FACTOR * stage), m_stage(stage), m_miner(), m_hook() {}
    void initGameObjects() {
        m_gameObjects.clear();
        m_miner.setImage(img_goldminer_1, mask_goldminer_1, img_goldminer_2, mask_goldminer_2);
        std::unique_ptr<GameObject> obj_gold_big;
        std::unique_ptr<GameObject> obj_gold_small;
        std::cout << "init w = " << img_gold_big.getwidth() << " h = " << img_gold_big.getheight() << std::endl;
        std::cout << "init w = " << mask_gold_big.getwidth() << " h = " << mask_gold_big.getheight() << std::endl;
        obj_gold_small = GameObjectFactory::createGameObject(GameObjectType::GOLD, 300, 150, SML, img_gold_small, mask_gold_small);
        m_gameObjects.push_back(std::move(obj_gold_small));
        obj_gold_small = GameObjectFactory::createGameObject(GameObjectType::GOLD, 500, 150, SML, img_gold_small, mask_gold_small);
        m_gameObjects.push_back(std::move(obj_gold_small));
        obj_gold_big = GameObjectFactory::createGameObject(GameObjectType::GOLD, 200, 200, BIG, img_gold_big, mask_gold_big);
        m_gameObjects.push_back(std::move(obj_gold_big));
    }
    void update() override {
        if (!m_clock.isContinue()) {
            if (m_score.reachGoal()) {
                outputStatus("Stage Clear!");
                ++stage;
            } else {
                outputStatus("Stage Failed!");
            }
            setGameScene(GameSceneType::END);
        } else if (m_gameObjects.empty()) {
            outputStatus("WOW,AMAZING!");
            ++stage;
            setGameScene(GameSceneType::END);
        } else {
            m_clock.update();
            m_hook.update();
            m_miner.update();
            if (m_hook.isStop()) {
                m_miner.stop();
                if (kbhit()) {
                    int key = _getch();
                    if (key == ' ' || key == '\r') {
                        m_hook.move();
                        m_miner.work();
                    }
                } else if (MouseHit()) {
                    MOUSEMSG m = GetMouseMsg();
                    if (m.uMsg == WM_LBUTTONDOWN) {
                        m_hook.move();
                        m_miner.work();
                    }
                }
            }
            for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
                if ((*it)->retracted()) {
                    if (m_hook.isStop()) {
                        m_score.get((*it)->getScore());
                        it = m_gameObjects.erase(it);
                        m_miner.stop();
                        break;
                    }
                    (*it)->move(m_hook.getAngle());
                }else if ((*it)->isHooked(m_hook.getEndX(), m_hook.getEndY())) {
                    m_miner.useEnergy();
                    m_hook.setSpeed((*it)->getSpeed());
                    m_hook.retract();
                    (*it)->retract();
                }
            }
        }
    }
    void render() override {
        cleardevice();
        putimage(0, 0, &img_game_background);
        putimage(0, MINER_Y + MINER_H, &img_brick);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
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
};

class Game {
private:
    GameSceneType m_game_scene;
    CMenu m_menu;
    CSignin m_signin;
    CLogin m_login;
    CGame m_game;
public:
    Game(): m_game_scene(GameSceneType::GAME),
            m_menu([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_signin([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_login([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_game([this](GameSceneType scene) { this->m_game_scene = scene; }) {
                loadTEXT();
                loadIMAGE();
                m_game.initGameObjects();
            }
    void run() {
        initgraph(WID, HEI);
        BeginBatchDraw();
        while (true) {
            switch (m_game_scene) {
                case GameSceneType::MENU:
                    m_menu.update();
                    m_menu.render();
                    break;
                case GameSceneType::SIGNIN:
                    m_signin.update();
                    m_signin.render();
                    break;
                case GameSceneType::LOGIN:
                    m_login.update();
                    m_login.render();
                    break;
                case GameSceneType::GAME:
                    m_game.update();
                    m_game.render();
                    break;
                default:
                    EndBatchDraw();
                    writeTEXT();
                    closegraph();
                    return;
            }
            FlushBatchDraw();
            Sleep(SLEEP_TIME);
        }
    }
private:
    bool loadTEXT() {
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
    void loadIMAGE() {
        loadimage(&img_startup, imgPath_startup.c_str(), WID, HEI, true);
        loadimage(&img_signin, imgPath_signin.c_str(), WID, HEI, true);
        loadimage(&img_login, imgPath_login.c_str(), WID, HEI, true);
        loadimage(&img_game_background, imgPath_game_background.c_str(), WID, HEI, true);
        loadimage(&img_goldminer_1, imgPath_goldminer_1.c_str(), MINER_W, MINER_H, true);
        loadimage(&mask_goldminer_1, maskPath_goldminer_1.c_str(), MINER_W, MINER_H, true);
        loadimage(&img_goldminer_2, imgPath_goldminer_2.c_str(), MINER_W, MINER_H, true);
        loadimage(&mask_goldminer_2, maskPath_goldminer_2.c_str(), MINER_W, MINER_H, true);
        loadimage(&img_brick, imgPath_brick.c_str(), WID, 10, true);
        loadimage(&img_gold_big, imgPath_gold_big.c_str(), 120, 120, true);
        loadimage(&mask_gold_big, maskPath_gold_big.c_str(), 120, 120, true);
        loadimage(&img_gold_small, imgPath_gold_small.c_str(), 30, 30, true);
        loadimage(&mask_gold_small, maskPath_gold_small.c_str(), 30, 30, true);
        std::cout << "load w = " << img_gold_big.getwidth() << " h = " << img_gold_big.getheight() << std::endl;
        std::cout << "load w = " << mask_gold_big.getwidth() << " h = " << mask_gold_big.getheight() << std::endl;
    }
    bool writeTEXT() {
        for (int i = 0; i < storedUsername.size(); ++i) {
            if (username == storedUsername[i]) {
                storedStage[i] = stage;
                break;
            }
        }
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
};

int main() {
    Game game;
    game.run();
    return 0;
}
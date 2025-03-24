#include <memory>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <graphics.h>
#include "linklist.hpp"

LinkedList<std::string> storedUsername;
LinkedList<std::string> storedPassword;
LinkedList<int> storedStage;
int userIndex;

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

#define game_scene_end 0
#define game_scene_menu 1
#define game_scene_signin 2
#define game_scene_login 4
#define game_scene_game 5   

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
const int SCORE_GOAL_FACTOR = 500;

enum class GameObjectType {
    GOLD,
    ROCK,
    DIAMOND
};

class Clock {
public:
    Clock(int total);
    void draw();
    void update();
    bool isContinue();
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
    Score(int goal);
    void draw();
    void get(int newScore);
    void los(int loseScore);
    bool reachGoal();
private:
    int score;
    int goal;
    std::string displayScore;
    std::string displayGoal;
    void update();
};

class Stage {
public:
    Stage(int stage);
    int getStage();
    void draw();
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
    CButton(int x, int y, int width, int height, const std::string& buttonText, ButtonCallBack callback);
    void simulateMouseClick(int mouseX, int mouseY);
    void draw() override;
private:
    int x, y;
    int width, height;
    std::string buttonText;
    ButtonCallBack callback;
    bool isMouseInButton(int mouseX, int mouseY);
};

class CInputBox : public CControl {
public:
    CInputBox(int x, int y, int width, int height);
    std::string getInputText() const;
    void simulateMouseClick(int mouseX, int mouseY);
    void draw() override;
private:
    int x, y;
    int width, height;
    std::string inputText;
    bool isFocused;
    void handleEvent();
    bool isMouseInButton(int mouseX, int mouseY);
};

class CObject {
public:
    virtual void draw() = 0;
};

class CMiner : public CObject {
public:
    CMiner();
    void setImage(IMAGE& img1, IMAGE& mask1, IMAGE& img2, IMAGE& mask2);
    void update();
    void draw();
    void work();
    void useEnergy();
    void stop();
private:
    int x, y;
    int w, h;
    bool working;
    bool usingEnergy;
    bool showSecondImage;
    std::chrono::time_point<std::chrono::system_clock> lastTime;
    IMAGE img1;
    IMAGE mask1;
    IMAGE img2;
    IMAGE mask2;
};

class CHook : public CObject {
public:
    CHook();  // 修改构造函数，移除 CMiner& 参数
    void draw();
    void update();
    bool isStop();
    void setSpeed(int speed);
    int getEndX() const;
    int getEndY() const;
    int getLength() const;
    double getAngle() const;
    void move();
    void retract();
private:
    int x, y;
    int endX, endY;
    int length;
    int speed;
    double angle;
    double angleSpeed;
    bool isMoving;
    bool isRetracting;
};

class GameObject : public CObject {
public:
    GameObject(double x, double y, int size, IMAGE img, IMAGE mask);
    virtual void setRadiusAndSpeed() = 0;
    void draw();
    void retract();
    bool retracted();
    bool isHooked(int hookX, int hookY);
    void move(int moveangle);
    bool operator==(const GameObject& other) const;
    int getScore() const;
    int getSpeed() const;
protected:
    double x;
    double y;
    int size;
    int radius;
    int speed;
    int score;
    bool isRetracting;
    IMAGE img;
    IMAGE mask;
};

class Gold : public GameObject {
public:
    Gold(int x, int y, int size, IMAGE img, IMAGE mask);
    void setRadiusAndSpeed() override;
};

class Rock : public GameObject {
public:
    Rock(int x, int y, int size, IMAGE img, IMAGE mask);
    void setRadiusAndSpeed() override;
};

class Diamond : public GameObject {
public:
    Diamond(int x, int y, IMAGE img, IMAGE mask);
    void setRadiusAndSpeed() override;
};

class GameObjectFactory {
public:
    static std::unique_ptr<GameObject> createGameObject(GameObjectType type, int x, int y, int size, IMAGE img, IMAGE mask);
};

class CScene {
public:
    CScene(std::function<void(int)> setGameScene);
    virtual void update() = 0;
    virtual void render() = 0;
protected:
    int m_scene;
    std::function<void(int)> setGameScene;
    void outputStatus(std::string text);
};

class CMenu : public CScene {
public:
    CMenu(std::function<void(int)> setGameScene);
    void update() override;
    void render() override;
private:
    CButton m_button_signin;
    CButton m_button_login;
    void callbackSignin();
    void callbackLogin();
};

class CSignin : public CScene {
public:
    CSignin(std::function<void(int)> setGameScene);
    void update() override;
    void render() override;
protected:
    CInputBox m_input_username;
    CInputBox m_input_password;
    CInputBox m_input_confirm;
private:
    CButton m_button_ok;
    CButton m_button_cancel;
    bool confirm;
    void callbackOk();
    void callbackCancel();
};

class CLogin : public CScene {
public:
    CLogin(std::function<void(int)> setGameScene);
    void update() override;
    void render() override;
private:
    CInputBox m_input_username;
    CInputBox m_input_password;
    CButton m_button_ok;
    CButton m_button_cancel;
    void callbackOk();
    void callbackCancel();
};

class CGame : public CScene {
public:
    CGame(std::function<void(int)> setGameScene);
    void update() override;
    void render() override;
private:
    Clock m_clock;
    Score m_score;
    Stage m_stage;
    CMiner m_miner;
    CHook m_hook;
    void initGameObjects();
}; 

class Game {
private:
    int m_game_scene;
    CMenu m_menu;
    CSignin m_signin;
    CLogin m_login;
    CGame m_game;

public:
    Game();
    void run();

private:
    bool loadTEXT();
    void loadIMAGE();
    bool writeTEXT();
};
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
int stage = 2;

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
std::string imgPath_gold_mid = "res/img_gold_mid.jpg";
std::string maskPath_gold_mid = "res/img_gold_mid_mask.jpg";
std::string imgPath_gold_small = "res/img_gold_small.jpg";
std::string maskPath_gold_small = "res/img_gold_small_mask.jpg";
std::string imgPath_rock_mid = "res/img_rock_mid.jpg";
std::string maskPath_rock_mid = "res/img_rock_mid_mask.jpg";
std::string imgPath_rock_small = "res/img_rock_small.jpg";
std::string maskPath_rock_small = "res/img_rock_small_mask.jpg";
std::string imgPath_diamond = "res/img_diamond.jpg";
std::string maskPath_diamond = "res/img_diamond_mask.jpg";
std::string imgPath_hook = "res/img_hook.jpg";
std::string maskPath_hook = "res/img_hook_mask.jpg";
std::string imgPath_bomb = "res/img_bomb.jpg";
std::string maskPath_bomb = "res/img_bomb_mask.jpg";
std::string imgPath_explosive = "res/img_explosive.jpg";
std::string maskPath_explosive = "res/img_explosive.jpg";
std::string imgPath_game_end = "res/img_game_end.png";

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
IMAGE img_gold_mid;
IMAGE mask_gold_mid;
IMAGE img_gold_small;
IMAGE mask_gold_small;
IMAGE img_rock_mid;
IMAGE mask_rock_mid;
IMAGE img_rock_small;
IMAGE mask_rock_small;
IMAGE img_diamond;
IMAGE mask_diamond;
IMAGE img_hook;
IMAGE mask_hook;
IMAGE img_bomb;
IMAGE mask_bomb;
IMAGE img_explosive;
IMAGE mask_explosive;
IMAGE img_game_end;

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
const int BOMB_W = 15;
const int BOMB_H = 30;
const int GAME_TIME = 60;

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)

enum class GameSceneType {
    MENU,
    SIGNIN,
    LOGIN,
    GAME,
    WIN,
    LOSE,
    OVER
};

enum class GameObjectType {
    GOLD,
    ROCK,
    DIAMOND
};

class Clock {
private:
    int start;
    int total;
    int current;
    int remain;
    bool gameContinue;
    std::string display;
public:
    Clock () {}
    void init(int total) {
        start = 0;
        this->total = total;
        gameContinue = true;
        display = "Time: 0";
    }
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
};

class Score {
public:
    Score () {}
    void init(int goal) {
        score = 0;
        this->goal = goal;
        displayScore = "Score: 0";
        displayGoal = "Goal: " + std::to_string(goal);
    }
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
private:
    int stage;
    std::string display;
public:
    Stage () {}
    void init(int stage) {
        this->stage = stage;
        display = "Stage: " + std::to_string(stage);
    }
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
};

using ButtonCallBack = std::function<void()>;

class CControl {
protected:
    int x, y, w, h;
    CControl(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    virtual void draw() = 0;
    virtual ~CControl() {}
    bool isMouseInButton(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h;
    }
};

class CButton : public CControl {
private:
    int X, Y, W, H;
    bool down = false;
    bool up = false;
    int textSize = 40;
    std::string buttonText;
    ButtonCallBack callback;
public:
    CButton(int x, int y, int w, int h, const std::string& buttonText, ButtonCallBack callback) 
        : CControl(x, y, w, h), X(x), Y(y), W(w), H(h), buttonText(buttonText), callback(callback) {}
    void simulateMouseMSG(MOUSEMSG m) {
        if (isMouseInButton(m.x, m.y)) {
            if (m.uMsg == WM_LBUTTONDOWN) {
                press();
            } else if (m.uMsg == WM_LBUTTONUP) {
                release();
            }
        } else {
            unpress();
        }
        if (down) {
            x = X + W * 1 / 20;
            y = Y + H * 1 / 20;
            w = W * 9 / 10;
            h = H * 9 / 10;
        } else if (up) {
            x = X;
            y = Y;
            w = W;
            h = H;
            up = false;
            callback();
        }
    }
    void draw() {
        setfillcolor(down ? RGB(200, 200, 200) : WHITE);
        fillrectangle(x, y, x + w, y + h);
        setbkmode(TRANSPARENT);
        settextstyle(textSize, 0, _T("宋体"));
        settextcolor(BLACK);
        int textWidth = textwidth(_T(buttonText).c_str());
        int textHeight = textheight(_T(buttonText).c_str());
        int textX = x + (w - textWidth) / 2;
        int textY = y + (h - textHeight) / 2;
        outtextxy(textX, textY, _T(buttonText).c_str());
    }
private:
    void press() {
        down = true;
    }
    void unpress() {
        down = false;
    }
    void release() {
        up = true;
        down = false;
    }
};

class CInputBox : public CControl {
private:
    std::string inputText;
    bool isFocused = false;
public:
    CInputBox(int x, int y, int w, int h) : CControl(x, y, w, h) {}
    std::string getInputText() const {
        return inputText;
    }
    void simulateMouseClick(int mouseX, int mouseY) {
        if (isMouseInButton(mouseX, mouseY)) {
            isFocused = true;
            handleEvent();
        }
    }
    void simulateMouseMSG(MOUSEMSG m) {
        if (isMouseInButton(m.x, m.y)) {
            if (m.uMsg == WM_LBUTTONDOWN) {
                isFocused = true;
                handleEvent();
            }
        }
    }
    void draw() {
        setfillcolor(isFocused ? RGB(100, 100, 100) : WHITE);
        fillrectangle(x, y, x + w, y + h);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        int textWidth = textwidth(_T(inputText).c_str());
        int textHeight = textheight(_T(inputText).c_str());
        int textX = x + (w - textWidth) / 2;
        int textY = y + (h - textHeight) / 2;
        outtextxy(textX, textY, _T(inputText).c_str());
    }
private:
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
};

class CObject {
protected:
    virtual void draw() = 0;
    void putimgwithmask(IMAGE& img, IMAGE& mask, int x, int y) const {
        putimage(x, y, &mask, NOTSRCERASE);
        putimage(x, y, &img, SRCINVERT);
    }
};

class CMiner : public CObject {
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
public:
    CMiner() : x(MINER_X), y(MINER_Y), w(MINER_W), h(MINER_H) {}
    void init(IMAGE& img1, IMAGE& mask1, IMAGE& img2, IMAGE& mask2) {
        this->working = false;
        this->usingEnergy = false;
        this->showSecondImage = false;
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
    bool isMoving = false;
    bool isRetracting = false;
    IMAGE img;
    IMAGE mask;
    IMAGE img_rotate;
    IMAGE mask_rotate;
public:
    CHook() : x(HOOK_X), y(HOOK_Y), length(HOOK_LENGTH), speed(HOOK_SPEED), angleSpeed(SLEEP_TIME * 0.15) {}
    void init(IMAGE& img, IMAGE& mask) {
        angle = 90;
        this->img = img;
        this->mask = mask;
    }
    void draw() {
        setcolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        line(x, y, endX, endY);
        rotateimage(&img_rotate, &img, degreesToRadians(90 - angle), WHITE, true);
        rotateimage(&mask_rotate, &mask, degreesToRadians(90 - angle), BLACK, true);
        int imageX = endX - img.getwidth() * std::sin(degreesToRadians(angle)) / 2 - img.getheight() * (1 - std::cos(degreesToRadians(angle))) / 2;
        int imageY = endY - img.getwidth() * std::abs(std::cos(degreesToRadians(angle))) / 2;
        putimgwithmask(img_rotate, mask_rotate, imageX, imageY);
    }
    void update() {
        if (isRetracting && !isMoving) {
            std::cerr << "There's something wrong with hook update" << std::endl;
        }
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
    bool isRetract() {
        return isRetracting;
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

class CBomb : public CObject {
private:
    int x, y;
    bool blowUp;
    IMAGE imgB;
    IMAGE maskB;
public:
    CBomb() : blowUp(false) {}
    void init(IMAGE& imgB, IMAGE& maskB) {
        this->imgB = imgB;
        this->maskB = maskB;
    }
    void setXY(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void draw() override {
        putimgwithmask(imgB, maskB, x, y);
    }
    void blow() {
        blowUp = true;
    }
    bool blowed() {
        return blowUp;
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
    bool isBombed = false;
    bool isRetracting = false;
    IMAGE img;
    IMAGE mask;
public:
    GameObject(double x, double y, int size, IMAGE& img, IMAGE& mask) : x(x), y(y), size(size), img(img), mask(mask) {}
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
        return distanceSquared - radius * radius <= 28;
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
    void bomb() {
        isBombed = true;
    }
    bool bombed() const {
        return isBombed;
    }
};

class Gold : public GameObject {
public:
    Gold(int x, int y, int size, IMAGE& img, IMAGE& mask) : GameObject(x, y, size, img, mask) { setRadiusAndSpeed(); }
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
    Rock(int x, int y, int size, IMAGE& img, IMAGE& mask) : GameObject(x, y, size, img, mask) { setRadiusAndSpeed(); }
    void setRadiusAndSpeed() override {
        static const int radii[] = {0, 15, 40};
        static const int speeds[] = {0, 3, 1};
        static const int scores[] = {0, 50, 100};
        this->radius = radii[size];
        this->speed = speeds[size];
        this->score = scores[size];
    }
};

class Diamond : public GameObject {
public:
    Diamond(int x, int y, IMAGE& img, IMAGE& mask) : GameObject(x, y, SML, img, mask) { setRadiusAndSpeed(); }
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
LinkedList<CBomb> m_bombs;

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
            m_button_signin.simulateMouseMSG(m);
            m_button_login.simulateMouseMSG(m);
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
        m_input_confirm(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI), 
        m_button_ok(0.8 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "OK", std::bind(&CSignin::callbackOk, this)), 
        m_button_cancel(0.04 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, "CANCEL", std::bind(&CSignin::callbackCancel, this)) {}
    void update() override {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            if (confirm) {
                m_input_confirm.simulateMouseMSG(m);
            } else {
                m_input_username.simulateMouseMSG(m);
                m_input_password.simulateMouseMSG(m);
            }
            m_button_ok.simulateMouseMSG(m);
            m_button_cancel.simulateMouseMSG(m);
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
            m_input_username.simulateMouseMSG(m);
            m_input_password.simulateMouseMSG(m);
            m_button_ok.simulateMouseMSG(m);
            m_button_cancel.simulateMouseMSG(m);
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
private:
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
    CBomb m_bomb;
    CButton m_button_quit;
    bool gaming = false;
public:
    CGame(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene), m_clock(), m_score(), m_stage(), m_miner(), m_hook(), m_bomb(),
        m_button_quit(0.65 * WID, (MINER_Y + MINER_H - 0.08 * HEI) / 2, 0.12 * WID, 0.08 * HEI, "Quit", std::bind(&CGame::callbackQuit, this)) {}
    void initGameObjects() {
        m_gameObjects.clear();
        m_stage.init(stage);
        m_clock.init(GAME_TIME);
        m_score.init(1000 + (int)(8 * std::sqrt(stage)) * 100);
        m_miner.init(img_goldminer_1, mask_goldminer_1, img_goldminer_2, mask_goldminer_2);
        m_hook.init(img_hook, mask_hook);
        m_bomb.init(img_bomb, mask_bomb);
        std::unique_ptr<GameObject> obj_gold_big;
        std::unique_ptr<GameObject> obj_gold_mid;
        std::unique_ptr<GameObject> obj_gold_small;
        std::unique_ptr<GameObject> obj_rock_mid;
        std::unique_ptr<GameObject> obj_rock_small;
        std::unique_ptr<GameObject> obj_diamond;
        obj_gold_big = GameObjectFactory::createGameObject(GameObjectType::GOLD, 200, 200, BIG, img_gold_big, mask_gold_big);
        m_gameObjects.push_back(std::move(obj_gold_big));
        obj_gold_mid = GameObjectFactory::createGameObject(GameObjectType::GOLD, 400, 100, MID, img_gold_mid, mask_gold_mid);
        m_gameObjects.push_back(std::move(obj_gold_mid));
        obj_gold_small = GameObjectFactory::createGameObject(GameObjectType::GOLD, 300, 150, SML, img_gold_small, mask_gold_small);
        m_gameObjects.push_back(std::move(obj_gold_small));
        obj_rock_mid = GameObjectFactory::createGameObject(GameObjectType::ROCK, 500, 150, MID, img_rock_mid, mask_rock_mid);
        m_gameObjects.push_back(std::move(obj_rock_mid));
        obj_rock_small = GameObjectFactory::createGameObject(GameObjectType::ROCK, 700, 300, SML, img_rock_small, mask_rock_small);
        m_gameObjects.push_back(std::move(obj_rock_small));
        obj_diamond = GameObjectFactory::createGameObject(GameObjectType::DIAMOND, 400, 200, SML, img_diamond, mask_diamond);
        m_gameObjects.push_back(std::move(obj_diamond));
        for (int i = 0; i < 5; ++i) {
            m_bomb.setXY(0.56 * WID + BOMB_W * i, MINER_Y + MINER_H - BOMB_H);
            m_bombs.push_back(m_bomb);
        }
    }
    void update() override {
        updateWithInput();
        updateWithoutInput();
    }
    void render() override {
        setbkcolor(WHITE);
        cleardevice();
        putimage(0, MINER_Y + MINER_H + 10, &img_game_background);
        putimage(0, MINER_Y + MINER_H, &img_brick);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        m_clock.draw();
        m_score.draw();
        m_stage.draw();
        m_miner.draw();
        m_hook.draw();
        m_button_quit.draw();
        for (auto bomb : m_bombs) {
            bomb.draw();
        }
        for (const auto& obj : m_gameObjects) {
            obj->draw();
        }
        FlushBatchDraw();
    }
    bool gameStarted() const {
        return gaming;
    }
    void start() {
        gaming = true;
    }
    void over() {
        gaming = false;
    }
private:
    void updateWithInput() {
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                m_hook.move();
                m_miner.work();
            } else if (m.uMsg == WM_RBUTTONDOWN && m_hook.isRetract() && m_bombs.size() > 0) {
                m_bombs[m_bombs.size() - 1].blow();
                m_hook.setSpeed(HOOK_SPEED);
                for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
                    if ((*it)->retracted()) {
                        (*it)->bomb();
                    }
                }
            }
            m_button_quit.simulateMouseMSG(m);
        }
    }
    void updateWithoutInput() {
        if (!m_clock.isContinue()) {
            if (m_score.reachGoal()) {
                outputStatus("GOOD!");
                ++stage;
                setGameScene(GameSceneType::WIN);
            } else {
                outputStatus("LOOSE!");
                setGameScene(GameSceneType::LOSE);
            }
        } else if (m_gameObjects.empty()) {
            outputStatus("AMAZING!!!");
            ++stage;
            setGameScene(GameSceneType::WIN);
        } else {
            m_clock.update();
            m_hook.update();
            m_miner.update();
            m_button_quit.draw();
            if (m_hook.isStop()) {
                m_miner.stop();
            }
            if (m_bombs[m_bombs.size() - 1].blowed()) {
                m_bombs.removeAt(m_bombs.size() - 1);
            }
            for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
                if ((*it)->bombed()) {
                    it = m_gameObjects.erase(it);
                    break;
                }
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
    void callbackQuit() {
        setGameScene(GameSceneType::OVER);
        outputStatus("GoodBye!");
    }
};

class CWin : public CScene {
private:
    CButton m_button_continue;
    CButton m_button_quit;
public:
    CWin(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_continue(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI, "Continue", std::bind(&CWin::callbackContinue, this)),
        m_button_quit(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI, "Quit", std::bind(&CWin::callbackQuit, this)) {}
    void update() override {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            m_button_continue.simulateMouseMSG(m);
            m_button_quit.simulateMouseMSG(m);
        }
    }
    void render() override {
        cleardevice();
        putimage(0, 0, &img_game_end);
        setbkmode(TRANSPARENT);
        setfillcolor(RGB(224, 243, 225));
        fillrectangle(0.12 * WID, 0.37 * HEI, 0.88 * WID, 0.8 * HEI);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        m_button_continue.draw();
        m_button_quit.draw();
        FlushBatchDraw();
    }
private:
    void callbackContinue() {
        setGameScene(GameSceneType::GAME);
    }
    void callbackQuit() {
        setGameScene(GameSceneType::OVER);
    }
};

class CLose : public CScene {
private:
    CButton m_button_retry;
    CButton m_button_quit;
public:
    CLose(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_retry(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI, "Retry", std::bind(&CLose::callbackRetry, this)),
        m_button_quit(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI, "Quit", std::bind(&CLose::callbackQuit, this)) {}
    void update() override {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            m_button_retry.simulateMouseMSG(m);
            m_button_quit.simulateMouseMSG(m);
        }
    }
    void render() override {
        cleardevice();
        putimage(0, 0, &img_game_end);
        setbkmode(TRANSPARENT);
        setfillcolor(RGB(224, 243, 225));
        fillrectangle(0.12 * WID, 0.37 * HEI, 0.88 * WID, 0.8 * HEI);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        m_button_retry.draw();
        m_button_quit.draw();
        FlushBatchDraw();
    }
private:
    void callbackRetry() {
        setGameScene(GameSceneType::GAME);
    }
    void callbackQuit() {
        setGameScene(GameSceneType::OVER);
    }
};

class Game {
private:
    GameSceneType m_game_scene;
    CMenu m_menu;
    CSignin m_signin;
    CLogin m_login;
    CGame m_game;
    CWin m_win;
    CLose m_lose;
public:
    Game(): m_game_scene(GameSceneType::MENU),
            m_menu([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_signin([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_login([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_game([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_win([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_lose([this](GameSceneType scene) { this->m_game_scene = scene; }) {
                loadTEXT();
                loadIMAGE();
            }
    void run() {
        if (proofreadIMAGE()) {
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
                        if (!m_game.gameStarted()) {
                            m_game.initGameObjects();
                            m_game.start();
                        }
                        m_game.update();
                        m_game.render();
                        break;
                    case GameSceneType::WIN:
                        m_game.over();
                        m_win.update();
                        m_win.render();
                        break;
                    case GameSceneType::LOSE:
                        m_game.over();
                        m_lose.update();
                        m_lose.render();
                        break;
                    default:
                        m_game.over();
                        EndBatchDraw();
                        writeTEXT();
                        closegraph();
                        return;
                }
                FlushBatchDraw();
                Sleep(SLEEP_TIME);
            }
        } else {
            std::cerr << "There're something wrong with image loading" << std::endl;
        }
    }
private:
    bool loadTEXT() {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << " for checking username." << std::endl;
            return false;
        }
        int tempStage;
        std::string tempUsername, tempPassword;
        if (file.peek() == std::ifstream::traits_type::eof()) {
            file.close();
            return true;
        }
        while (file >> tempUsername >> tempPassword >> tempStage) {
            storedUsername.push_back(tempUsername);
            storedPassword.push_back(tempPassword);
            storedStage.push_back(tempStage);
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
        loadimage(&img_gold_mid, imgPath_gold_mid.c_str(), 80, 80, true);
        loadimage(&mask_gold_mid, maskPath_gold_mid.c_str(), 80, 80, true);
        loadimage(&img_gold_small, imgPath_gold_small.c_str(), 30, 30, true);
        loadimage(&mask_gold_small, maskPath_gold_small.c_str(), 30, 30, true);
        loadimage(&img_rock_mid, imgPath_rock_mid.c_str(), 80, 80, true);
        loadimage(&mask_rock_mid, maskPath_rock_mid.c_str(), 80, 80, true);
        loadimage(&img_rock_small, imgPath_rock_small.c_str(), 30, 30, true);
        loadimage(&mask_rock_small, maskPath_rock_small.c_str(), 30, 30, true);
        loadimage(&img_diamond, imgPath_diamond.c_str(), 30, 30, true);
        loadimage(&mask_diamond, maskPath_diamond.c_str(), 30, 30, true);
        loadimage(&img_hook, imgPath_hook.c_str(), 28, 16, true);
        loadimage(&mask_hook, maskPath_hook.c_str(), 28, 16, true);
        loadimage(&img_bomb, imgPath_bomb.c_str(), BOMB_W, BOMB_H, true);
        loadimage(&mask_bomb, maskPath_bomb.c_str(), BOMB_W, BOMB_H, true);
        loadimage(&img_game_end, imgPath_game_end.c_str(), WID, HEI, true);
    }
    bool proofreadIMAGE() {
        if (img_startup.getwidth() != WID || img_startup.getheight() != HEI) {
            std::cerr << "Failed to load img_startup!" << std::endl;
            return false;
        } else if (img_signin.getwidth() != WID || img_signin.getheight() != HEI) {
            std::cerr << "Failed to load img_signin!" << std::endl;
            return false;
        } else if (img_login.getwidth() != WID || img_login.getheight() != HEI) {
            std::cerr << "Failed to load img_login!" << std::endl;
            return false;
        } else if (img_game_background.getwidth() != WID || img_game_background.getheight() != HEI) {
            std::cerr << "Failed to load img_game_background!" << std::endl;
            return false;
        } else if (img_goldminer_1.getwidth() != MINER_W || img_goldminer_1.getheight() != MINER_H) {
            std::cerr << "Failed to load img_goldminer_1!" << std::endl;
            return false;
        } else if (mask_goldminer_1.getwidth() != MINER_W || mask_goldminer_1.getheight() != MINER_H) {
            std::cerr << "Failed to load mask_goldminer_1!" << std::endl;
            return false;
        } else if (img_goldminer_2.getwidth() != MINER_W || img_goldminer_2.getheight() != MINER_H) {
            std::cerr << "Failed to load img_goldminer_2!" << std::endl;
            return false;
        } else if (mask_goldminer_2.getwidth() != MINER_W || mask_goldminer_2.getheight() != MINER_H) {
            std::cerr << "Failed to load mask_goldminer_2!" << std::endl;
            return false;
        } else if (img_brick.getwidth() != WID || img_brick.getheight() != 10) {
            std::cerr << "Failed to load img_brick!" << std::endl;
            return false;
        } else if (img_gold_big.getwidth() != 120 || img_gold_big.getheight() != 120) {
            std::cerr << "Failed to load img_gold_big!" << std::endl;
            return false;
        } else if (mask_gold_big.getwidth() != 120 || mask_gold_big.getheight() != 120) {
            std::cerr << "Failed to load mask_gold_big!" << std::endl;
            return false;
        } else if (img_gold_mid.getwidth() != 80 || img_gold_mid.getheight() != 80) {
            std::cerr << "Failed to load img_gold_mid!" << std::endl;
            return false;
        } else if (mask_gold_mid.getwidth() != 80 || mask_gold_mid.getheight() != 80) {
            std::cerr << "Failed to load mask_gold_mid!" << std::endl;
            return false;
        } else if (img_gold_small.getwidth() != 30 || img_gold_small.getheight() != 30) {
            std::cerr << "Failed to load img_gold_small!" << std::endl;
            return false;
        } else if (mask_gold_small.getwidth() != 30 || mask_gold_small.getheight() != 30) {
            std::cerr << "Failed to load mask_gold_small!" << std::endl;
            return false;
        } else if (img_rock_mid.getwidth() != 80 || img_rock_mid.getheight() != 80) {
            std::cerr << "Failed to load img_rock_mid!" << std::endl;
            return false;
        } else if (mask_rock_mid.getwidth() != 80 || mask_rock_mid.getheight() != 80) {
            std::cerr << "Failed to load mask_rock_mid!" << std::endl;
            return false;
        } else if (img_rock_small.getwidth() != 30 || img_rock_small.getheight() != 30) {
            std::cerr << "Failed to load img_rock_small!" << std::endl;
            return false;
        } else if (mask_rock_small.getwidth() != 30 || mask_rock_small.getheight() != 30) {
            std::cerr << "Failed to load mask_rock_small!" << std::endl;
            return false;
        } else if (img_diamond.getwidth() != 30 || img_diamond.getheight() != 30) {
            std::cerr << "Failed to load img_diamond!" << std::endl;
            return false;
        } else if (mask_diamond.getwidth() != 30 || mask_diamond.getheight() != 30) {
            std::cerr << "Failed to load mask_diamond!" << std::endl;
            return false;
        } else if (img_hook.getwidth() != 28 || img_hook.getheight() != 16) {
            std::cerr << "Failed to load img_hook!" << std::endl;
            return false;
        } else if (mask_hook.getwidth() != 28 || mask_hook.getheight() != 16) {
            std::cerr << "Failed to load mask_hook!" << std::endl;
            return false;
        } else if (img_bomb.getwidth() != BOMB_W || img_bomb.getheight() != BOMB_H) {
            std::cerr << "Failed to load img_bomb!" << std::endl;
            return false;
        } else if (mask_bomb.getwidth() != BOMB_W || mask_bomb.getheight() != BOMB_H) {
            std::cerr << "Failed to load mask_bomb!" << std::endl;
            return false;
        } else if (img_game_end.getwidth() != WID || img_game_end.getheight() != HEI) {
            std::cerr << "Failed to load img_game_end!" << std::endl;
            return false;
        } else {
            return true;
        }
    }
    void writeTEXT() {
        for (int i = 0; i < storedUsername.size(); ++i) {
            if (username == storedUsername[i]) {
                storedStage[i] = stage;
                break;
            }
            if (i == storedUsername.size() - 1) {
                std::cerr << "Failed to find username: " << username << " when writing into the file." << std::endl;
                return;
            }
        }
        std::ofstream file(filePath, std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << " when writing into the file." << std::endl;
            return;
        }
        auto itUser = storedUsername.begin();
        auto itPass = storedPassword.begin();
        auto itStag = storedStage.begin();
        for (; itUser != storedUsername.end(); ++itUser, ++itPass, ++itStag) {
            file << *itUser << " " << *itPass << " " << *itStag << std::endl;
        }
        file.close();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
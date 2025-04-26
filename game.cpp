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

#pragma comment(lib, "Winmm.lib")

time_t getCurrentTimeInMilliseconds() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return now_ms.time_since_epoch().count();
}

LinkedList<std::string> storedUsername;
LinkedList<std::string> storedPassword;
LinkedList<int> storedStage;
std::string username = "kerry";
std::string password = "kerry";
int stage = 9;

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
std::string imgPath_hook = "res/img_hook.bmp";
std::string maskPath_hook = "res/img_hook_mask.bmp";
std::string imgPath_bomb = "res/img_bomb.jpg";
std::string maskPath_bomb = "res/img_bomb_mask.jpg";
std::string imgPath_game_win = "res/img_game_win.jpg";
std::string imgPath_game_lose = "res/img_game_lose.jpg";
std::string imgPath_game_over = "res/img_game_over.jpeg";

LinkedList<std::string> imgPath_explosive;
LinkedList<std::string> maskPath_explosive;

std::string musicPath_background_normal = "res/music_background_normal.mp3";
std::string musicPath_background_stormy = "res/music_background_stormy.mp3";
std::string musicPath_background_quicksand = "res/music_background_quicksand.mp3";
std::string musicPath_background_magnetic = "res/music_background_magnetic.mp3";

std::string musicPath_bomb_explosive = "res/music_bomb_explosive.mp3";
std::string musicPath_hook_goingOut = "res/music_hook_goingOut.mp3";
std::string musicPath_hook_treasure = "res/music_hook_treasure.mp3";
std::string musicPath_hook_gold = "res/music_hook_gold.mp3";
std::string musicPath_hook_rock = "res/music_hook_rock.mp3";
std::string musicPath_transition = "res/music_transition.mp3";
std::string musicPath_thunder = "res/music_thunder.mp3";
std::string musicPath_countdown = "res/music_countdown.mp3";

IMAGE img_startup;
IMAGE img_signin;
IMAGE img_login;
IMAGE img_game_background;
IMAGE img_goldminer_1;
IMAGE mask_goldminer_1;
IMAGE img_goldminer_2;
IMAGE mask_goldminer_2;
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
IMAGE img_game_win;
IMAGE img_game_lose;
IMAGE img_game_over;

LinkedList<IMAGE> img_explosive;
LinkedList<IMAGE> mask_explosive;

void setImageExplosivePath() {
    for (int i = 0; i < 12; ++i) {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << i + 1;
        std::string twoDigit = oss.str();
    
        std::string imgPath ="res/explosion/explosion_" + twoDigit + ".jpg";
        std::string maskPath = "res/explosion/explosion_" + twoDigit + "_mask.jpg";
        imgPath_explosive.push_back(imgPath);
        maskPath_explosive.push_back(maskPath);
    }
}

const int SLEEP_TIME = 10;
const int LENGTH_INDEX = 400;
const int WID = 3 * LENGTH_INDEX;
const int HEI = 2 * LENGTH_INDEX;
const int HOOK_LENGTH = 30;
const int HOOK_SPEED = SLEEP_TIME * 0.7;
const int MINER_X = (WID - 90) / 2;
const int MINER_Y = 10;
const int MINER_W = 90;
const int MINER_H = 90;
const int HOOK_X = MINER_X + MINER_W * 0.18;
const int HOOK_Y = MINER_Y + MINER_H * 0.6;
const int BOMB_W = 15;
const int BOMB_H = 30;
const int GAME_TIME = 99;
const std::time_t EXPLOSION_TIME = 1000;

struct GoldRadiusType {
    static constexpr int BIG = 75;
    static constexpr int MID = 50;
    static constexpr int SMALL = 25;
};

struct RockRadiusType {
    static constexpr int MID = 50;
    static constexpr int SMALL = 25;
};

struct TreasureRadiusType {
    static constexpr int DIAMOND = 20;
    static constexpr int MONEY = 30;
    static constexpr int MONEYBAG = 25;
};

enum class GameSceneType {
    MENU,
    SIGNIN,
    LOGIN,
    GAME,
    WIN,
    LOSE,
    OVER,
    NULLSCENE
};

enum class GameObjectType {
    GOLD,
    ROCK,
    TREASURE
};

enum class GameStageType {
    NORMAL,
    STORMY,
    QUICKSAND,
    MAGNETIC
};

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)

class Clock {
private:
    int x, y, w, h;
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
        display = "0";
    }

    void draw() {
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
        int textX = 0.91 * WID - textWidth / 2;
        int textY = 0.015 * HEI;
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
        oss << remain;
        display = oss.str();
    }

    bool isContinue() {
        return gameContinue;
    }

    int remainTime() {
        return remain;
    }
};

class Score {
private:
    int score;
    int goal;
    std::string displayScore;
    std::string displayGoal;

public:
    Score () {}

    void init(int goal) {
        score = 0;
        this->goal = goal;
        displayScore = std::to_string(score);
        displayGoal = std::to_string(goal);
    }

    void draw() {
        int textWidth1 = textwidth(displayScore.c_str());
        int textHeight1 = textheight(displayScore.c_str());
        int textWidth2 = textwidth(displayGoal.c_str());
        int textHeight2 = textheight(displayGoal.c_str());
        int textX1 = 0.135 * WID - textWidth1 / 2;
        int textX2 = 0.135 * WID - textWidth2 / 2;
        int textY1 = 0.015 * HEI;
        int textY2 = 0.065 * HEI;
        outtextxy(textX1, textY1, displayScore.c_str());
        outtextxy(textX2, textY2, displayGoal.c_str());
    }

    void get(int newScore) {
        score += newScore;
        displayScore = std::to_string(score);
    }

    bool reachGoal() {
        return score >= goal;
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
        display = std::to_string(stage);
    }

    int getStage() {
        return stage;
    }

    void draw() {
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
        int textX = 0.91 * WID - textWidth / 2;
        int textY = 0.065 * HEI;
        outtextxy(textX, textY, display.c_str());
    }
};

using ButtonCallBack = std::function<void()>;

class CControl {
protected:
    int x, y, w, h;
    bool isFocused = false;
    bool isReleased = false;
    std::string text;

public:
    CControl(int x, int y, int w, int h, const std::string& text) : x(x), y(y), w(w), h(h), text(text) {}

    bool isMouseInButton(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h;
    }

    void draw() {
        if (isFocused) {
            setfillcolor(LIGHTGRAY);
            setlinestyle(PS_NULL);
            fillrectangle(x + 3, y + 3, x + w - 2, y + h - 3);
        }
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        int textWidth = textwidth(_T(text).c_str());
        int textHeight = textheight(_T(text).c_str());
        int textX = x + (w - textWidth) / 2;
        int textY = y + (h - textHeight) / 2;
        outtextxy(textX, textY, _T(text).c_str());
    }
};

class CButton : public CControl {
private:
    int X, Y, W, H;
    ButtonCallBack callback;

public:
    CButton(int x, int y, int w, int h, const std::string& text, ButtonCallBack callback) 
        : CControl(x, y, w, h, text), X(x), Y(y), W(w), H(h), callback(callback) {}

    void simulateMouseMSG(MOUSEMSG m) {
        if (isMouseInButton(m.x, m.y)) {
            if (m.uMsg == WM_LBUTTONDOWN) {
                isFocused = true;
            } else if (m.uMsg == WM_LBUTTONUP) {
                isFocused = false;
                isReleased = true;
            }
        } else {
            isFocused = false;
        }
        if (isFocused) {
            x = X + W * 1 / 20;
            y = Y + H * 1 / 20;
            w = W * 9 / 10;
            h = H * 9 / 10;
        } else if (isReleased) {
            x = X;
            y = Y;
            w = W;
            h = H;
            isReleased = false;
            callback();
        }
    }
};

class CInputBox : public CControl {
public:
    CInputBox(int x, int y, int w, int h) : CControl(x, y, w, h, "") {}

    std::string getInputText() const {
        return text;
    }

    void simulateMouseMSG(MOUSEMSG m) {
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (isMouseInButton(m.x, m.y)) {
                isFocused = true;
            } else {
                isFocused = false;
            }
        }
    }

    void simulateKeyboardMSG() {
        if (isFocused) {
            if (kbhit()) {
                wchar_t ch = _getwch();
                if (ch == L'\r') {
                    isFocused = false;
                } else if (ch == L'\b') {
                    if (!text.empty()) {
                        text.pop_back();
                    }
                } else {
                    text += ch;
                }
            }
        }
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
    double endX, endY;
    int length;
    int speed;
    double angle;
    double angleSpeed;
    bool rotate = true;
    bool isMoving = false;
    bool isRetracting = false;
    IMAGE img;
    IMAGE mask;
    IMAGE img_rotate;
    IMAGE mask_rotate;

public:
    CHook() : x(HOOK_X), y(HOOK_Y), length(HOOK_LENGTH), speed(HOOK_SPEED), angleSpeed(SLEEP_TIME * 0.15), rotate(true) {}

    void init(IMAGE& img, IMAGE& mask) {
        angle = 90;
        this->img = img;
        this->mask = mask;
    }

    void draw() {
        setcolor(BLACK);
        setlinecolor(BLACK);
        setfillcolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        line(x, y, endX, endY);
        if (rotate) {
            rotateimage(&img_rotate, &img, degreesToRadians(90 - angle), WHITE, true);
            rotateimage(&mask_rotate, &mask, degreesToRadians(90 - angle), BLACK, true);
            int imageX = endX - img.getwidth() * std::sin(degreesToRadians(angle)) / 2 - img.getheight() * (1 - std::cos(degreesToRadians(angle))) / 2;
            int imageY = endY - img.getwidth() * std::abs(std::cos(degreesToRadians(angle))) / 2;
            putimgwithmask(img_rotate, mask_rotate, imageX, imageY);
        } else {
            putimgwithmask(img, mask, endX - img.getwidth() / 2, endY);
        }
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
            if (isRetracting) {
                length -= speed;
                if (length <= HOOK_LENGTH) {
                    length = HOOK_LENGTH;
                    setSpeed(HOOK_SPEED);
                    stop();
                }
            } else {
                length += speed;
                if (endX <= 0 || endX >= WID || endY >= HEI) {
                    isRetracting = true;
                }
            }
        }
    }

    bool isGoingOut() {
        return length > HOOK_LENGTH && isMoving && !isRetracting;
    }

    bool isGoingBack() {
        return length > HOOK_LENGTH && isMoving && isRetracting;
    }
    bool isStop() {
        return (!isMoving) && (!isRetracting) && (length <= HOOK_LENGTH);
    }

    void setmageticmode() {
        rotate = false;
    }

    void setSpeed(int speed) {
        this->speed = speed;
    }

    void move() {
        isMoving = true;
    }

    void magnetic(int magnetic_source_x, int magnetic_source_y, double magnetic_strength) {
        int angle_target = std::atan2(magnetic_source_y - y, magnetic_source_x - x) * 180 / M_PI;
        int angle_distance = angle_target - angle;
        int distance_x = magnetic_source_x - endX;
        int distance_y = magnetic_source_y - endY;
        double magnetic_force = magnetic_strength / std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));
        angle += magnetic_force * angle_distance;
    }

    void retract() {
        isRetracting = true;
    }

    void stop() {
        isMoving = false;
        isRetracting = false;
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
};

class CBomb : public CObject {
private:
    int x, y;
    bool blowUp;
    IMAGE imgB;
    IMAGE maskB;

public:
    CBomb() : blowUp(false) {}

    bool operator==(const CBomb& other) const {
        return this->x == other.x && this->y == other.y;
    }

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
};

class GameObject : public CObject {
protected:
    GameObjectType type;
    double x, y;
    int radius;
    int speed;
    int score;
    bool isBombed = false;
    int explosedIndex = -1;
    std::time_t explosedTime;
    IMAGE img;
    IMAGE mask;

public:
    GameObject() {}

    GameObject(GameObjectType type, double x, double y, const int radiusType, IMAGE& img, IMAGE& mask)
        : type(type), x(x), y(y), radius(radiusType), img(img), mask(mask) {}

    GameObject(const GameObject& other)
        : type(other.type), x(other.x), y(other.y), radius(other.radius), speed(other.speed), score(other.score), 
        isBombed(other.isBombed), img(other.img), mask(other.mask) {}

    GameObject& operator=(const GameObject& other) {
        if (this != &other) {
            type = other.type;
            x = other.x;
            y = other.y;
            radius = other.radius;
            speed = other.speed;
            score = other.score;
            isBombed = other.isBombed;
            img = other.img;
            mask = other.mask;
        }
        return *this;
    }

    bool operator==(const GameObject& other) const {
        return this->type == other.type && this->x == other.x && this->y == other.y && this->radius == other.radius;
    }

    bool operator!=(const GameObject& other) const {
        return !operator==(other);
    }

    void draw() {
        if (isBombed && explosedIndex != -1) {
            int explosedX = x + radius - img_explosive[explosedIndex].getwidth() / 2;
            int explosedY = y + radius - img_explosive[explosedIndex].getwidth() / 2;;
            putimgwithmask(img_explosive[explosedIndex], mask_explosive[explosedIndex], explosedX, explosedY);
        } else if (explosedIndex == -1) {
            putimgwithmask(img, mask, x, y);
        }
    }

    void move(int moveangle) {
        x -= speed * cos(degreesToRadians(moveangle));
        y -= speed * sin(degreesToRadians(moveangle));
    }

    void submerge(int distance) {
        y += distance;
    }
        
    void bomb() {
        explosedTime = getCurrentTimeInMilliseconds();
        isBombed = true;
    }

    void explosing() {
        std::time_t currentTime = getCurrentTimeInMilliseconds();
        std::time_t elapsedTime = currentTime - explosedTime;
        if (elapsedTime < EXPLOSION_TIME) {
            if (explosedIndex < img_explosive.size()) {
                explosedIndex = img_explosive.size() * elapsedTime / EXPLOSION_TIME;
            }
        } else {
            isBombed = false;
        }
    }
    
    bool isHooked(int hookX, int hookY) {
        return std::pow((x + radius - hookX), 2) + std::pow((y + radius - hookY), 2) - radius * radius <= 35;
    }

    bool bombed() const {
        return isBombed;
    }

    GameObjectType getType() const {
        return type;
    }
    
    int getScore() const {
        return score;
    }
    
    int getSpeed() const {
        return speed;
    }
    
    int getRadius() const {
        return radius;
    }
    
    int getRx() const {
        return x + radius;
    }
    
    int getRy() const {
        return y + radius;
    }
};

class Gold : public GameObject {
public:
    Gold(int x, int y, int radiusType, IMAGE& img, IMAGE& mask) : GameObject(GameObjectType::GOLD, x, y, radiusType, img, mask) {
        int index = (radiusType == GoldRadiusType::BIG) ? 3 
                  : (radiusType == GoldRadiusType::MID) ? 2 
                  : (radiusType == GoldRadiusType::SMALL) ? 1 
                  : 0;
        static const int speeds[] = {0, 4, 2, 1};
        static const int scores[] = {0, 100, 300, 500};
        this->radius = radius;
        this->speed = speeds[index];
        this->score = scores[index];
    }
};

class Rock : public GameObject {
public:
    Rock(int x, int y, int radiusType, IMAGE& img, IMAGE& mask) : GameObject(GameObjectType::ROCK, x, y, radiusType, img, mask) {
        int index = (radiusType == GoldRadiusType::MID) ? 2 
                  : (radiusType == GoldRadiusType::SMALL) ? 1 
                  : 0;
        static const int speeds[] = {0, 3, 1};
        static const int scores[] = {0, 50, 100};
        this->radius = radius;
        this->speed = speeds[index];
        this->score = scores[index];
    }
};

class Treasure : public GameObject {
public:
    Treasure(int x, int y, int radiusType, IMAGE& img, IMAGE& mask) : GameObject(GameObjectType::TREASURE, x, y, radiusType, img, mask) {
        int index = (radiusType == TreasureRadiusType::DIAMOND) ? 3 
                  : (radiusType == TreasureRadiusType::MONEY) ? 2 
                  : (radiusType == TreasureRadiusType::MONEYBAG) ? 1 
                  : 0;
        static const int scores[] = {0, 600, 800, 1000};
        this->radius = radiusType;
        this->speed = 4;
        this->score = scores[index];
    }
};

class GameObjectFactory {
public:
    static GameObject createGameObject(GameObjectType type, int x, int y, int radiusType, IMAGE& img, IMAGE& mask) {
        switch (type) {
            case GameObjectType::GOLD:
                return Gold(x, y, radiusType, img, mask);
            case GameObjectType::ROCK:
                return Rock(x, y, radiusType, img, mask);
            case GameObjectType::TREASURE:
                return Treasure(x, y, radiusType, img, mask);
            default:
                throw std::invalid_argument("Invalid GameObjectType");
        }
    }
};

typedef struct {
    int x, y;
    int length;
    int speed;
} Raindrop;

class Rain {
private:
    LinkedList<Raindrop> drops;

public:
    Rain() {}

    void init(int count) {
        for (int i = 0; i < count; ++i) {
            Raindrop drop;
            drop.x = rand() % WID;
            drop.y = rand() % HEI;
            drop.length = 10 + rand() % 20;
            drop.speed = 5 + rand() % 5;
            drops.push_back(drop);
        }
    }

    void draw() {
        setlinecolor(0xAAAAAA);
        setfillcolor(0x888888);
        setbkmode(TRANSPARENT);
        setrop2(R2_MERGEPEN);
        setlinestyle(PS_SOLID, 2);
        for (Raindrop& drop : drops) {
            line(drop.x, drop.y, drop.x, drop.y + drop.length);
        }
        setrop2(R2_COPYPEN);
        setcolor(BLACK);
    }

    void update() {
        for (Raindrop& drop : drops) {
            drop.y += drop.speed;
            if (drop.y > HEI) {
                drop.y = -drop.length;
                drop.x = rand() % WID;
            }
        }
    }
};

class Lightning {
private:
    LinkedList<POINT> points;
    bool isActive;
    int duration;

public:
    Lightning() {}

    void init(int duration) {
        this->duration = duration * 1000 / SLEEP_TIME;
        isActive = false;
    }

    void generateLightning() {
        points.clear();
        isActive = true;
        POINT start = { rand() % WID, 0 };
        points.push_back(start);
        for (int i = 0; i < 10; ++i) {
            POINT next = { points.back().x + (rand() % 40 - 20), points.back().y + (rand() % 50 + 20) };
            if (next.y > HEI) {
                break;
            } else if (next.x < 0) {
                next.x = 0;
            } else if (next.x > WID) {
                next.x = WID;
            }
            points.push_back(next);
        }
    }
    
    void draw() {
        if (isActive) {
            setlinestyle(PS_SOLID, 5);
            setlinecolor(WHITE);
            for (size_t i = 1; i < points.size(); ++i) {
                line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
            }
            setlinestyle(PS_SOLID, 2);
        }
    }
    
    void update() {
        if (isActive) {
            --duration;
            if (duration <= 0) {
                isActive = false;
            }
        }
    }
};

LinkedList<GameObject> m_gameObjects;
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
        setbkcolor(WHITE);
        settextstyle(40, 0, _T("黑体"));
        settextcolor(BLACK);
        int textX = 0.5 * WID - (textwidth(_T(text).c_str())) / 2;
        int textY = 0.59 * HEI - (textheight(_T(text).c_str())) / 2;
        fillrectangle(textX, textY, textX + textwidth(_T(text).c_str()), textY + textheight(_T(text).c_str()));
        outtextxy(textX, textY, _T(text).c_str());
        FlushBatchDraw();
        while(true) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                break;
            }
        }
    }

    void playBackgroundMusic(std::string& music) {
        mciSendString("close bkmusic", NULL, 0, NULL);
        mciSendString(("open " + music + " alias bkmusic").c_str(), NULL, 0, NULL);
        mciSendString("play bkmusic repeat", NULL, 0, NULL);
    }

    void endBackgroundMusic() {
        mciSendString("close bkmusic", NULL, 0, NULL);
    }

    void playSpecialEffectMusic(std::string& music) {
        mciSendString(("close " + music).c_str(), NULL, 0, NULL);
        mciSendString(("open " + music + " alias " + music).c_str(), NULL, 0, NULL);
        mciSendString(("play " + music).c_str(), NULL, 0, NULL);
    }
};

class CMenu : public CScene {
private:
    CButton m_button_signin;
    CButton m_button_login;

public:
    CMenu(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_signin(0.654 * WID, 0.5 * HEI, 0.3 * WID, 0.1625 * HEI, "signin", std::bind(&CMenu::callbackSignin, this)), 
        m_button_login(0.025 * WID, 0.5 * HEI, 0.3 * WID, 0.1625 * HEI, "login", std::bind(&CMenu::callbackLogin, this)) {}

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
        m_input_username(0.3575 * WID, 0.2887 * HEI, 0.381 * WID, 0.0825 * HEI), 
        m_input_password(0.3575 * WID, 0.4013 * HEI, 0.381 * WID, 0.0825 * HEI), 
        m_input_confirm(0.3575 * WID, 0.5138 * HEI, 0.381 * WID, 0.0825 * HEI), 
        m_button_ok(0.5225 * WID, 0.655 * HEI, 0.2175 * WID, 0.1125 * HEI, "OK", std::bind(&CSignin::callbackOk, this)), 
        m_button_cancel(0.2808 * WID, 0.655 * HEI, 0.2175 * WID, 0.1125 * HEI, "CANCEL", std::bind(&CSignin::callbackCancel, this)) {}

    void update() override {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            m_input_username.simulateMouseMSG(m);
            m_input_password.simulateMouseMSG(m);
            m_input_confirm.simulateMouseMSG(m);
            m_button_ok.simulateMouseMSG(m);
            m_button_cancel.simulateMouseMSG(m);
        }
        m_input_username.simulateKeyboardMSG();
        m_input_password.simulateKeyboardMSG();
        m_input_confirm.simulateKeyboardMSG();
    }

    void render() override {
        cleardevice();
        putimage(0, 0, &img_signin);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        m_input_username.draw();
        m_input_password.draw();
        m_input_confirm.draw();
    }

private:
    void callbackOk() {
        username = m_input_username.getInputText();
        password = m_input_password.getInputText();
        if (username.empty()) {
            outputStatus("Username cannot be empty");
            return;
        } else if (password.empty()) {
            outputStatus("Password cannot be empty");
            return;
        } else if (m_input_confirm.getInputText().empty()) {
            outputStatus("Confirm password cannot be empty");
            return;
        } else if (password != m_input_confirm.getInputText()) {
            outputStatus("The passwords are different twice");
            return;
        } else {
            for (std::string user : storedUsername) {
                if (username == user) {
                    outputStatus("Username has been used");
                    return;
                }
            }
        }
        stage = 1;
        storedUsername.push_back(username);
        storedPassword.push_back(password);
        storedStage.push_back(stage);
        outputStatus("Welcome in...");
        setGameScene(GameSceneType::GAME);
    }

    void callbackCancel() {
        setGameScene(GameSceneType::MENU);
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
        m_button_ok(0.5108 * WID, 0.6025 * HEI, 0.2175 * WID, 0.1125 * HEI, "OK", std::bind(&CLogin::callbackOk, this)),
        m_button_cancel(0.2692 * WID, 0.6025 * HEI, 0.2175 * WID, 0.1125 * HEI, "CANCEL", std::bind(&CLogin::callbackCancel, this)),
        m_input_username(0.3675 * WID, 0.3675 * HEI, 0.3816 * WID, 0.0825 * HEI),
        m_input_password(0.3675 * WID, 0.48125 * HEI, 0.3816 * WID, 0.0825 * HEI) {}

    void update() override {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            m_input_username.simulateMouseMSG(m);
            m_input_password.simulateMouseMSG(m);
            m_button_ok.simulateMouseMSG(m);
            m_button_cancel.simulateMouseMSG(m);
        }
        m_input_username.simulateKeyboardMSG();
        m_input_password.simulateKeyboardMSG();
    }

    void render() override {
        cleardevice();
        putimage(0, 0, &img_login);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        m_input_username.draw();
        m_input_password.draw();
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

int goal = 0;
IMAGE img_null;
GameObject nullObject(GameObjectType::GOLD, 0, 0, GoldRadiusType::BIG, img_null, img_null);

class CGame : public CScene {
protected:
    Clock m_clock;
    Score m_score;
    Stage m_stage;
    CMiner m_miner;
    CHook m_hook;
    CBomb m_bomb;
    CButton m_button_quit;
    GameObject* m_focusedGameObject = &nullObject;
    GameObject* m_explosedGameObject = &nullObject;
    bool countdown = false;

    CGame(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene), m_clock(), m_score(), m_stage(), m_miner(), m_hook(), m_bomb(),
        m_button_quit(0.638 * WID, 0.01375 * HEI, 0.14 * WID, 0.07 * HEI, "Quit", std::bind(&CGame::callbackQuit, this)) {}
    
public:
    virtual void init() {
        goal = 1000 + ((stage - 1) % 5 + 1) * 500;
        m_gameObjects.clear();
        m_stage.init(stage);
        m_clock.init(GAME_TIME);
        m_score.init(goal);
        m_miner.init(img_goldminer_1, mask_goldminer_1, img_goldminer_2, mask_goldminer_2);
        m_hook.init(img_hook, mask_hook);
        m_bomb.init(img_bomb, mask_bomb);
        init_m_GameObjects();
        init_m_Boombs();
    }

    void update() override {
        updateWithInput();
        updateWithoutInput();
    }

    void render() override {
        cleardevice();
        setbkcolor(WHITE);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        putimage(0, 0, &img_game_background);
        for (CBomb& bomb : m_bombs) {
            bomb.draw();
        }
        for (GameObject& obj : m_gameObjects) {
            obj.draw();
        }
        m_clock.draw();
        m_score.draw();
        m_stage.draw();
        m_miner.draw();
        m_hook.draw();
        if (m_focusedGameObject != &nullObject) {
            m_focusedGameObject->draw();
        }
        if (m_explosedGameObject != &nullObject) {
            m_explosedGameObject->draw();
        }
    }

private:
    void updateWithInput() {
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            m_button_quit.simulateMouseMSG(m);
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (!m_button_quit.isMouseInButton(m.x, m.y)) {
                    m_hook.move();
                    m_miner.work();
                    playSpecialEffectMusic(musicPath_hook_goingOut);
                }
            } else if (m.uMsg == WM_RBUTTONDOWN) {
                if (m_hook.isGoingBack() && m_bombs.size() > 0) {
                    m_hook.setSpeed(HOOK_SPEED);
                    if (m_focusedGameObject != &nullObject) {
                        m_focusedGameObject->bomb();
                        playSpecialEffectMusic(musicPath_bomb_explosive);
                    }
                }
            }
        }
    }

    void updateWithoutInput() {
        if (!m_clock.isContinue()) {
            endBackgroundMusic();
            if (m_score.reachGoal()) {
                outputStatus("GOOD!");
                ++stage;
                setGameScene(GameSceneType::WIN);
            } else {
                outputStatus("LOOSE!");
                setGameScene(GameSceneType::LOSE);
            }
        } else if (m_gameObjects.empty()) {
            endBackgroundMusic();
            outputStatus("AMAZING!!!");
            ++stage;
            setGameScene(GameSceneType::WIN);
        } else {
            m_clock.update();
            m_hook.update();
            m_miner.update();
            if (m_hook.isStop()) {
                m_miner.stop();
            }
            if (m_focusedGameObject == &nullObject) {
                if (m_hook.isGoingOut()) {
                    for (GameObject& obj : m_gameObjects) {
                        if (obj.isHooked(m_hook.getEndX(), m_hook.getEndY())) {
                            m_miner.useEnergy();
                            m_hook.setSpeed(obj.getSpeed());
                            m_hook.retract();
                            m_focusedGameObject = &obj;
                        }
                    }
                }
            } else {
                if (m_focusedGameObject->bombed()) {
                    m_bombs.erase(m_bombs[m_bombs.size() - 1]);
                    m_explosedGameObject = m_focusedGameObject;
                    m_focusedGameObject = &nullObject;
                } else {
                    if (m_hook.isStop()) {
                        m_score.get(m_focusedGameObject->getScore());
                        playMusicForGameObject(*m_focusedGameObject);
                        m_gameObjects.erase(*m_focusedGameObject);
                        m_focusedGameObject = &nullObject;
                        m_miner.stop();
                    }
                    m_focusedGameObject->move(m_hook.getAngle());
                }
            }
        }
        if (m_explosedGameObject != &nullObject) {
            if (m_explosedGameObject->bombed()) {
                m_explosedGameObject->explosing();
            } else {
                m_gameObjects.erase(*m_explosedGameObject);
                m_explosedGameObject = &nullObject;
            }
        }
        if (!countdown && m_clock.remainTime() == 5) {
            playSpecialEffectMusic(musicPath_countdown);
            countdown = true;
        }
    }

    void init_m_GameObjects() {
        m_gameObjects.clear();
        int num_index = tanh(stage % 5 + 1);
        int num_gold = 3 + 8 * num_index + rand() % 3;
        int num_rock = 3 + 3 * num_index + rand() % 2;
        int num_diamond = num_index + rand() % 2;
        while (1000 * num_diamond + 320 * num_gold + 75 * num_rock - goal < 500) {
            int random = rand() % 20;
            if (random == 0) {
                ++ num_diamond;
            } else if (random < 8) {
                ++ num_gold;
            } else {
                ++ num_rock;
            }
        }
        int num_gold_big = num_gold * 0.3;
        int num_gold_mid = num_gold * 0.5;
        int num_gold_sml = num_gold * 0.2;
        int num_rock_mid = num_rock * 0.5;
        int num_rock_sml = num_rock * 0.5;

        initOneTypeOfGameObjects(num_diamond, GameObjectType::TREASURE, TreasureRadiusType::DIAMOND, img_diamond, mask_diamond);
        initOneTypeOfGameObjects(num_gold_big, GameObjectType::GOLD, GoldRadiusType::BIG, img_gold_big, mask_gold_big);
        initOneTypeOfGameObjects(num_gold_mid, GameObjectType::GOLD, GoldRadiusType::MID, img_gold_mid, mask_gold_mid);
        initOneTypeOfGameObjects(num_gold_sml, GameObjectType::GOLD, GoldRadiusType::SMALL, img_gold_small, mask_gold_small);
        initOneTypeOfGameObjects(num_rock_mid, GameObjectType::ROCK, RockRadiusType::MID, img_rock_mid, mask_rock_mid);
        initOneTypeOfGameObjects(num_rock_sml, GameObjectType::ROCK, RockRadiusType::SMALL, img_rock_small, mask_rock_small);
    }

    void initOneTypeOfGameObjects(int num, GameObjectType type, int radius, IMAGE& img, IMAGE& mask) {
        int x, y;
        GameObject obj;
        for (int i = 0; i < num; ++i) {
            do {
                x = rand() % (WID - img.getwidth());
                y = rand() % (HEI - img.getheight());
            } while (outOfBounds(x, y, radius) || isTooClose(x, y, radius));
            obj = GameObjectFactory::createGameObject(type, x, y, radius, img, mask);
            m_gameObjects.push_back(obj);
        }
    }

    void init_m_Boombs() {
        m_bombs.clear();
        for (int i = 0; i < 5; ++i) {
            m_bomb.setXY(0.56 * WID + BOMB_W * i, MINER_Y + MINER_H - BOMB_H);
            m_bombs.push_back(m_bomb);
        }
    }

    bool isTooClose(int x, int y, int radius) {
        if (!m_gameObjects.empty()) {
            for (GameObject& obj : m_gameObjects) {
                if (std::pow((obj.getRx() - (x + radius)), 2) + std::pow((obj.getRy() - (y + radius)), 2) 
                  < std::pow((obj.getRadius() + radius + 0.1 * LENGTH_INDEX), 2)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool outOfBounds(int x, int y, int radius) {
        if (WID - radius - 20 <= 20 || HEI - radius - 20 <= WID / 4) {
            std::cerr << "Error: bounds too small !" << std::endl;
        }
        return x < 20 || x > WID - radius - 20 || y < HEI / 4 || y > HEI - radius - 20;
    }

    void playMusicForGameObject(GameObject& obj) {
        if (obj.getType() == GameObjectType::GOLD) {
            playSpecialEffectMusic(musicPath_hook_gold);
        } else if (obj.getType() == GameObjectType::ROCK) {
            playSpecialEffectMusic(musicPath_hook_rock);
        } else if (obj.getType() == GameObjectType::TREASURE) {
            playSpecialEffectMusic(musicPath_hook_treasure);
        } else {
            std::cerr << std::endl << "Error: GameObject type not recognized!" << std::endl;
        }
    }

    void callbackQuit() {
        setGameScene(GameSceneType::NULLSCENE);
    }
};

class CGameNormal : public CGame {
public:
    CGameNormal(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) {}

    void init() {
        CGame::init();
        outputStatus("This is just the beginning, so only higher and higher goals");
        playBackgroundMusic(musicPath_background_normal);
    }

    void update() {
        CGame::update();
    }

    void render() {
        CGame::render();
    }
};

class CGameStormy : public CGame {
private:
    Rain rain;
    Lightning lightning;
    int startTime = 3;
    int stormyTime = 1;
    int stormyInterval = 6;
    bool dark = true;
    bool thundering = false;

public:
    CGameStormy(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) {void init();}

    void init() {
        CGame::init();
        rain.init(500);
        switch (stage) {
            case 6: // Stormy start
                stormyTime = 2;
                stormyInterval = 6;
                outputStatus("Stormy start, so the game is a little bit harder");
                break;
            case 7: // More game objects
                stormyTime = 2;
                stormyInterval = 6;
                outputStatus("More game objects");
                break;
            case 8: // The days are shorter
                stormyTime = 1;
                stormyInterval = 6;
                outputStatus("The days are shorter");
                break;
            case 9: // The nights are longer
                stormyTime = 1;
                stormyInterval = 7;
                outputStatus("The nights are longer");
                break;
            case 10: // Faster storms with less time to watch
                startTime = 1;
                stormyTime = 1;
                stormyInterval = 7;
                outputStatus("Faster storms with less time to watch");
                break;
            default:
                break;
        }
        lightning.init(stormyTime * 1000 / SLEEP_TIME);
        playBackgroundMusic(musicPath_background_stormy);
    }

    void update() {
        CGame::update();
        rain.update();
        lightning.update();
        if (m_clock.remainTime() + startTime < GAME_TIME && 
            (m_clock.remainTime() + startTime) % (stormyTime + stormyInterval) > stormyTime) {
            thundering = false;
            dark = true;
        } else {
            if (thundering == false) {
                playSpecialEffectMusic(musicPath_thunder);
                thundering = true;
                lightning.generateLightning();
            }
            dark = false;
        }
    }

    void render() override {
        CGame::render();
        if (dark) {
            setfillcolor(BLACK);
            fillrectangle(0, MINER_Y + MINER_H + 10, WID, HEI);
        } else {
            lightning.draw();
        }
        for (CBomb& bomb : m_bombs) {
            bomb.draw();
        }
        m_hook.draw();
        if (m_explosedGameObject != &nullObject) {
            m_explosedGameObject->draw();
        }
        rain.draw();
    }
};

class CGameQuicksand : public CGame {
private:
    int lastRemainTime = GAME_TIME;

public:
    CGameQuicksand(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) {}

    void init() {
        CGame::init();
        switch (stage) {
            case 11: // Quicksand start
                outputStatus("Quicksand start, so the game is a little bit harder");
                break;
            case 12: // Faster settling rate
                outputStatus("Faster settling rate");
                break;
            case 13: // The quicksand becomes soft, so heavier objects will settle first
                outputStatus("The quicksand becomes soft, so heavier objects will settle first");
                break;
            case 14: // The quicksand becomes soft
                outputStatus("The quicksand becomes soft");
                break;
            case 15: // Golds will fall quickly, while lighter stones fall very slowly
                outputStatus("Golds will fall quickly, while lighter stones fall very slowly");
                break;
            default:
                break;
        }
        playBackgroundMusic(musicPath_background_quicksand);
    }

    void update() {
        CGame::update();
        if (lastRemainTime != m_clock.remainTime()) {
            lastRemainTime = m_clock.remainTime();
            for (GameObject& obj : m_gameObjects) {
                if (obj.getRy() + obj.getRadius() < HEI && &obj != m_focusedGameObject) {
                    switch (stage) {
                        case 11: // Quicksand start
                            obj.submerge(1);
                            break;
                        case 12: // Faster settling rate
                            obj.submerge(2);
                            break;
                        case 13: // The quicksand becomes soft, so heavier objects will settle first
                            obj.submerge(obj.getRadius() / 100 + 2);
                            break;
                        case 14: // The quicksand becomes soft
                            obj.submerge(obj.getRadius() / 75 + 2);
                            break;
                        case 15: // Golds will fall quickly, while lighter stones fall very slowly
                            if (obj.getType() == GameObjectType::GOLD) {
                                obj.submerge(obj.getRadius() / 30);
                            } else if (obj.getType() == GameObjectType::ROCK) {
                                obj.submerge(obj.getRadius() / 100 + 1);
                            } else {
                                obj.submerge(1);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void render() {
        CGame::render();
    }
};

class CGameMagnetic : public CGame {
public:
    CGameMagnetic(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) {}

    void init() {
        CGame::init();
        switch (stage) {
            case 16: // Magnetic start
                outputStatus("Magnetic start, so the game is a little bit harder");
                break;
            case 17: // More game objects and stronger magnetic force
                outputStatus("More game objects and stronger magnetic force");
                break;
            case 18: // Stronger magnetic force
                outputStatus("Stronger magnetic force");
                break;
            case 19: // The magnetic force starts to change over time, so collect the side target as soon
                outputStatus("The magnetic force starts to change over time, so collect the side target as soon");
                break;
            case 20: // Stronger magnetic force
                outputStatus("Stronger magnetic force");
                break;
            default:
                break;
        }
        playBackgroundMusic(musicPath_background_normal);
    }

    void update() {
        double magnetic_index = 10 - m_clock.remainTime() / 10;
        CGame::update();
        if (m_hook.isGoingOut()) {
            switch (stage)
            {
            case 16:
                m_hook.magnetic(HOOK_X, HEI, 0.5); // Magnetic start
                break;
            case 17:
                m_hook.magnetic(HOOK_X, HEI, 1); // More game objects and stronger magnetic force
                break;
            case 18:
                m_hook.magnetic(HOOK_X, HEI, magnetic_index / 2); // Stronger magnetic force
                break;
            case 19:
                m_hook.magnetic(HOOK_X, HEI, magnetic_index); // The magnetic force starts to change over time, so collect the side target as soon
                break;
            case 20:
                m_hook.magnetic(HOOK_X, HEI, magnetic_index * 1.5); // Stronger magnetic force
                break;
            default:
                break;
            }
        }
    }

    void render() {
        CGame::render();
    }
};

class CGameFactory {
    public:
        static CGame* createGame(GameStageType type, const std::function<void(GameSceneType)>& setGameScene) {
            switch (type) {
                case GameStageType::NORMAL:
                    return new CGameNormal(setGameScene);
                case GameStageType::STORMY:
                    return new CGameStormy(setGameScene);
                case GameStageType::QUICKSAND:
                    return new CGameQuicksand(setGameScene);
                case GameStageType::MAGNETIC:
                    return new CGameMagnetic(setGameScene);
                default:
                    throw std::invalid_argument("Invalid GameObjectType");
            }
        }
    };

class CWin : public CScene {
private:
    CButton m_button_continue;
    CButton m_button_quit;

public:
    CWin(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_continue(0.665 * WID, 0.51375 * HEI, 0.29 * WID, 0.15 * HEI, "Continue", std::bind(&CWin::callbackContinue, this)),
        m_button_quit(0.665 * WID, 0.70875 * HEI, 0.29 * WID, 0.15 * HEI, "Quit", std::bind(&CWin::callbackQuit, this)) {}

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
        putimage(0, 0, &img_game_win);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
    }

private:
    void callbackContinue() {
        if (stage >= 20) {
            setGameScene(GameSceneType::OVER);
        } else {
            setGameScene(GameSceneType::GAME);
        }
    }
    
    void callbackQuit() {
        setGameScene(GameSceneType::NULLSCENE);
    }
};

class CLose : public CScene {
private:
    CButton m_button_retry;
    CButton m_button_quit;
public:
    CLose(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_retry(0.6725 * WID, 0.12625 * HEI, 0.29 * WID, 0.15 * HEI, "Retry", std::bind(&CLose::callbackRetry, this)),
        m_button_quit(0.6725 * WID, 0.3 * HEI, 0.29 * WID, 0.15 * HEI, "Quit", std::bind(&CLose::callbackQuit, this)) {}

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
        putimage(0, 0, &img_game_lose);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
        // m_button_retry.draw();
        // m_button_quit.draw();
    }

private:
    void callbackRetry() {
        setGameScene(GameSceneType::GAME);
    }

    void callbackQuit() {
        setGameScene(GameSceneType::NULLSCENE);
    }
};

class COver : public CScene {
private:
    int y = 0;

public:
    COver(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene) {}

    void update() override {
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                setGameScene(GameSceneType::NULLSCENE);
            }
        }
        if (y > HEI - 1700) {
            --y;
        }
    }

    void render() override {
        cleardevice();
        putimage(0, y, &img_game_over);
    }    
};

class Game {
private:
    GameSceneType m_game_scene;
    CMenu m_menu;
    CSignin m_signin;
    CLogin m_login;
    CGame* m_game = nullptr;
    CWin m_win;
    CLose m_lose;
    COver m_over;

public:
    Game(): m_game_scene(GameSceneType::GAME),
            m_menu([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_signin([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_login([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_win([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_lose([this](GameSceneType scene) { this->m_game_scene = scene; }),
            m_over([this](GameSceneType scene) { this->m_game_scene = scene; }) {
                setImageExplosivePath();
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
                        if (m_game == nullptr) {
                            if (stage < 6) {
                                m_game = CGameFactory::createGame(GameStageType::NORMAL, [this](GameSceneType scene) { this->m_game_scene = scene; });
                            } else if (stage < 11) {
                                m_game = CGameFactory::createGame(GameStageType::STORMY, [this](GameSceneType scene) { this->m_game_scene = scene; });
                            } else if (stage < 16) {
                                m_game = CGameFactory::createGame(GameStageType::QUICKSAND, [this](GameSceneType scene) { this->m_game_scene = scene; });
                            } else if (stage < 21){
                                m_game = CGameFactory::createGame(GameStageType::MAGNETIC, [this](GameSceneType scene) { this->m_game_scene = scene; });
                            }
                            m_game->init();
                        }
                        m_game->update();
                        m_game->render();
                        break;
                    case GameSceneType::WIN:
                        m_win.update();
                        m_win.render();
                        m_game = nullptr;
                        break;
                    case GameSceneType::LOSE:
                        m_lose.update();
                        m_lose.render();
                        m_game = nullptr;
                        break;
                    case GameSceneType::OVER:
                        m_over.update();
                        m_over.render();
                        m_game = nullptr;
                        break;
                    default:
                        m_game = nullptr;
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
        loadimage(&img_gold_big, imgPath_gold_big.c_str(), 2 * GoldRadiusType::BIG, 2 * GoldRadiusType::BIG, true);
        loadimage(&mask_gold_big, maskPath_gold_big.c_str(), 2 * GoldRadiusType::BIG, 2 * GoldRadiusType::BIG, true);
        loadimage(&img_gold_mid, imgPath_gold_mid.c_str(), 2 * GoldRadiusType::MID, 2 * GoldRadiusType::MID, true);
        loadimage(&mask_gold_mid, maskPath_gold_mid.c_str(), 2 * GoldRadiusType::MID, 2 * GoldRadiusType::MID, true);
        loadimage(&img_gold_small, imgPath_gold_small.c_str(), 2 * GoldRadiusType::SMALL, 2 * GoldRadiusType::SMALL, true);
        loadimage(&mask_gold_small, maskPath_gold_small.c_str(), 2 * GoldRadiusType::SMALL, 2 * GoldRadiusType::SMALL, true);
        loadimage(&img_rock_mid, imgPath_rock_mid.c_str(), 2 * RockRadiusType::MID, 2 * RockRadiusType::MID, true);
        loadimage(&mask_rock_mid, maskPath_rock_mid.c_str(), 2 * RockRadiusType::MID, 2 * RockRadiusType::MID, true);
        loadimage(&img_rock_small, imgPath_rock_small.c_str(), 2 * RockRadiusType::SMALL, 2 * RockRadiusType::SMALL, true);
        loadimage(&mask_rock_small, maskPath_rock_small.c_str(), 2 * RockRadiusType::SMALL, 2 * RockRadiusType::SMALL, true);
        loadimage(&img_diamond, imgPath_diamond.c_str(), 2 * TreasureRadiusType::DIAMOND, 2 * TreasureRadiusType::DIAMOND, true);
        loadimage(&mask_diamond, maskPath_diamond.c_str(), 2 * TreasureRadiusType::DIAMOND, 2 * TreasureRadiusType::DIAMOND, true);
        loadimage(&img_hook, imgPath_hook.c_str(), 36, 20, true);
        loadimage(&mask_hook, maskPath_hook.c_str(), 36, 20, true);
        loadimage(&img_bomb, imgPath_bomb.c_str(), BOMB_W, BOMB_H, true);
        loadimage(&mask_bomb, maskPath_bomb.c_str(), BOMB_W, BOMB_H, true);
        loadimage(&img_game_win, imgPath_game_win.c_str(), WID, HEI, true);
        loadimage(&img_game_lose, imgPath_game_lose.c_str(), WID, HEI, true);
        loadimage(&img_game_over, imgPath_game_over.c_str(), WID, 1684 * WID / 1180, true);
        for (int i = 0; i < 12; ++i) {
            IMAGE img;
            IMAGE mask;
            loadimage(&img, imgPath_explosive[i].c_str());
            loadimage(&mask, maskPath_explosive[i].c_str());
            img_explosive.push_back(img);
            mask_explosive.push_back(mask);
        }
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
        } else if (img_gold_big.getwidth() != 2 * GoldRadiusType::BIG || img_gold_big.getheight() != 2 * GoldRadiusType::BIG) {
            std::cerr << "Failed to load img_gold_big!" << std::endl;
            return false;
        } else if (mask_gold_big.getwidth() != 2 * GoldRadiusType::BIG || mask_gold_big.getheight() != 2 * GoldRadiusType::BIG) {
            std::cerr << "Failed to load mask_gold_big!" << std::endl;
            return false;
        } else if (img_gold_mid.getwidth() != 2 * GoldRadiusType::MID || img_gold_mid.getheight() != 2 * GoldRadiusType::MID) {
            std::cerr << "Failed to load img_gold_mid!" << std::endl;
            return false;
        } else if (mask_gold_mid.getwidth() != 2 * GoldRadiusType::MID || mask_gold_mid.getheight() != 2 * GoldRadiusType::MID) {
            std::cerr << "Failed to load mask_gold_mid!" << std::endl;
            return false;
        } else if (img_gold_small.getwidth() != 2 * GoldRadiusType::SMALL || img_gold_small.getheight() != 2 * GoldRadiusType::SMALL) {
            std::cerr << "Failed to load img_gold_small!" << std::endl;
            return false;
        } else if (mask_gold_small.getwidth() != 2 * GoldRadiusType::SMALL || mask_gold_small.getheight() != 2 * GoldRadiusType::SMALL) {
            std::cerr << "Failed to load mask_gold_small!" << std::endl;
            return false;
        } else if (img_rock_mid.getwidth() != 2 * RockRadiusType::MID || img_rock_mid.getheight() != 2 * RockRadiusType::MID) {
            std::cerr << "Failed to load img_rock_mid!" << std::endl;
            return false;
        } else if (mask_rock_mid.getwidth() != 2 * RockRadiusType::MID || mask_rock_mid.getheight() != 2 * RockRadiusType::MID) {
            std::cerr << "Failed to load mask_rock_mid!" << std::endl;
            return false;
        } else if (img_rock_small.getwidth() != 2 * RockRadiusType::SMALL || img_rock_small.getheight() != 2 * RockRadiusType::SMALL) {
            std::cerr << "Failed to load img_rock_small!" << std::endl;
            return false;
        } else if (mask_rock_small.getwidth() != 2 * RockRadiusType::SMALL || mask_rock_small.getheight() != 2 * RockRadiusType::SMALL) {
            std::cerr << "Failed to load mask_rock_small!" << std::endl;
            return false;
        } else if (img_diamond.getwidth() != 2 * TreasureRadiusType::DIAMOND || img_diamond.getheight() != 2 * TreasureRadiusType::DIAMOND) {
            std::cerr << "Failed to load img_diamond!" << std::endl;
            return false;
        } else if (mask_diamond.getwidth() != 2 * TreasureRadiusType::DIAMOND || mask_diamond.getheight() != 2 * TreasureRadiusType::DIAMOND) {
            std::cerr << "Failed to load mask_diamond!" << std::endl;
            return false;
        } else if (img_hook.getwidth() != 36 || img_hook.getheight() != 20) {
            std::cerr << "Failed to load img_hook!" << std::endl;
            return false;
        } else if (mask_hook.getwidth() != 36 || mask_hook.getheight() != 20) {
            std::cerr << "Failed to load mask_hook!" << std::endl;
            return false;
        } else if (img_bomb.getwidth() != BOMB_W || img_bomb.getheight() != BOMB_H) {
            std::cerr << "Failed to load img_bomb!" << std::endl;
            return false;
        } else if (mask_bomb.getwidth() != BOMB_W || mask_bomb.getheight() != BOMB_H) {
            std::cerr << "Failed to load mask_bomb!" << std::endl;
            return false;
        } else if (img_game_win.getwidth() != WID || img_game_win.getheight() != HEI) {
            std::cerr << "Failed to load img_game_win!" << std::endl;
            return false;
        } else if (img_game_lose.getwidth() != WID || img_game_lose.getheight() != HEI) {
            std::cerr << "Failed to load img_game_lose!" << std::endl;
            return false;
        } else if (img_explosive.size() !=12 || mask_explosive.size() != 12) {
            std::cerr << "Failed to load img_explosive or mask_explosive!" << std::endl;
            return false;
        } else {
            for (int i = 0; i < 12; ++i) {
                if (img_explosive[i].getwidth() != 191 || img_explosive[i].getheight() != 191) {
                    std::cerr << "Failed to load img_explosive!" << std::endl;
                    return false;
                } else if (mask_explosive[i].getwidth() != 191 || mask_explosive[i].getheight() != 191) {
                    std::cerr << "Failed to load mask_explosive!" << std::endl;
                    return false;
                }
            }
        }
        return true;
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
#ifndef ELEMENT_CLASS_H
#define ELEMENT_CLASS_H

#include <graphics.h>
#include <conio.h>
#include <string>
#include <locale>
#include <codecvt>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <memory>
#include <chrono>

// 文件资源路径
std::string filePath = "users.txt";

// 图片资源路径
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

//基本功能型函数
double degreesToRadians(double degrees) {
    return degrees * std::acos(-1) / 180.0;
}

std::string tstring_to_string(const std::basic_string<TCHAR>& tstr) {
    #ifdef _UNICODE
        try {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            return converter.to_bytes(reinterpret_cast<const std::wstring&>(tstr));
        } catch (const std::range_error& e) {
            std::cerr << "转换失败: " << e.what() << std::endl;
            return "";
        }
    #else
        return std::string(tstr.begin(), tstr.end());
    #endif
}

void putimgwithmask(IMAGE& img, IMAGE& mask, int x, int y) {
    putimage(x, y, &mask, NOTSRCERASE);
    putimage(x, y, &img, SRCINVERT);
}

//一些全局数据
#define SLEEP_TIME 10
#define LENGTH_INDEX 300
#define WID (3 * LENGTH_INDEX)
#define HEI (2 * LENGTH_INDEX)

#define HOOK_LENGTH 30
#define HOOK_SPEED (SLEEP_TIME * 6 / 10)

class Miner {
    public:
        int x;
        int y;
        int w;
        int h;
        bool working = false;
        bool usingEnergy = false;
        std::chrono::time_point<std::chrono::system_clock> lastTime = std::chrono::system_clock::now();
        bool showSecondImage = true;
        IMAGE img1;
        IMAGE mask1;
        IMAGE img2;
        IMAGE mask2;
    
        Miner(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    
        void setImage(IMAGE& img1, IMAGE& mask1, IMAGE& img2, IMAGE& mask2) {
            this->img1 = img1;
            this->mask1 = mask1;
            this->img2 = img2;
            this->mask2 = mask2;
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
    
        void draw() {
            if (working && showSecondImage) {
                putimgwithmask(img2, mask2, x, y);
            } else {
                putimgwithmask(img1, mask1, x, y);
            }
        }
    };

class GameObject {
public:
    double x;
    double y;
    int size;
    int radius;
    int speed;
    int score;
    bool isRetracting = false;
    IMAGE img;
    IMAGE mask;

    GameObject() {}
    GameObject(double x, double y, int size, IMAGE img, IMAGE mask)
        : x(x), y(y), size(size), img(img), mask(mask) {}

    virtual void setRadiusAndSpeed() = 0;

    void draw() {
        putimage(x, y, &mask, NOTSRCERASE);
        putimage(x, y, &img, SRCINVERT);
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
};

class Gold : public GameObject {
public:
    Gold() : GameObject() {}
    Gold(int x, int y, int size, IMAGE img, IMAGE mask) 
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
    Rock() : GameObject() {}
    Rock(int x, int y, int size, IMAGE img, IMAGE mask) 
        : GameObject(x, y, size, img, mask) {
        setRadiusAndSpeed();
    }

    void setRadiusAndSpeed() override {
        static const int radii[] = {0, 8, 18, 40};
        static const int speeds[] = {0, 3, 2, 1};
        static const int scores[] = {0, 20, 50, 100};
        this->radius = radii[size];
        this->speed = speeds[size];
        this->score = scores[size];
    }
};

class GameObjectFactory {
public:
    static std::unique_ptr<GameObject> createGameObject(const std::string& type, int x, int y, int size, IMAGE img, IMAGE mask) {
        if (type == "gold") {
            return std::make_unique<Gold>(x, y, size, img, mask);
        } else if (type == "rock") {
            return std::make_unique<Rock>(x, y, size, img, mask);
        }
        return nullptr;
    }
};

class Hook {
public:
    int x;
    int y;
    int endX;
    int endY;
    int length;
    int speed;
    double angle = 90;
    double angleSpeed;
    bool isMoving = false;
    bool isRetracting = false;

    Hook(int x, int y, int length, int speed, double angleSpeed)
    : x(x), y(y), length(length), speed(speed), angleSpeed(angleSpeed) {}

    void draw() {
        setcolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        line(x, y, endX, endY);
        circle(endX, endY, 5);
    }

    void update() {
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
                // 钩子伸展
                length += speed;
                if (endX <= 0 || endX >= WID || endY >= HEI) {
                    isRetracting = true;
                }
            } else {
                // 钩子收回
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
};

class Button {
public:
    int x, y;
    int textcolor;
    int width, height;
    std::string text;

    Button(int x, int y, int width, int height, int textcolor, const std::string& text)
        : x(x), y(y), width(width), height(height), textcolor(textcolor), text(text) {}

    // 绘制按钮基础样式
    void drawbase(COLORREF color) {
        setfillcolor(color);
        fillrectangle(x, y, x + width, y + height);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
    
        int textWidth = textwidth(_T(text).c_str());
        int textHeight = textheight(_T(text).c_str());
    
        int textX = x + (width - textWidth) / 2;
        int textY = y + (height - textHeight) / 2;
    
        outtextxy(textX, textY, _T(text).c_str());
    }

    // 绘制被点击状态的按钮
    void drawkickedbutton() {
        drawbase(RGB(100, 100, 100));
    }

    // 绘制正常状态的按钮
    void drawbutton() {
        drawbase(WHITE);
    }

    // 判断鼠标是否在按钮区域内
    bool isMouseInButton(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }
};

class Clock {
public:
    int start = 0;
    int total;
    int current;
    int remain;
    bool gameContinue = true;
    std::string display = "Time: 0";

    Clock(int total) : total(total) {}

    void draw() {
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
    
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
    
        int textX = (WID - textWidth - WID / 50);
        int textY = (50 - textHeight) / 2;
    
        outtextxy(textX, textY, display.c_str());
    }

    void update() {
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
};

class Score {
private:
    int score = 0;
    int goal = 0;
    std::string displayScore = "Score: 0";
    std::string displayGoal = "Goal: 0";
public:
    Score(int score, int goal) : score(score), goal(goal){
        std::ostringstream oss;
        oss << goal;
        displayGoal = "Goal: " + oss.str();
    }

    void draw() {
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);

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
        updateDisplay();
    }

    void los(int loseScore) {
        score -= loseScore;
        if (score < 0) {
            score = 0;  // 确保分数不会为负数
        }
    }

    bool reachGoal() {
        return score >= goal;
        updateDisplay();
    }

private:
    void updateDisplay() {
        std::ostringstream oss;
        oss << score;
        displayScore = "Score: " + oss.str();
    }
};

class Stage {
private:
    int stage;
    std::string display;

public:
    Stage(int stage) : stage(stage) {
        std::ostringstream oss;
        oss << stage;
        display = "Stage: " + oss.str();
    }

    int getS() {return stage;}

    void draw() {
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
    
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
    
        int textX = (WID - textWidth - WID / 50);
        int textY = (50 + textHeight) / 2;
    
        outtextxy(textX, textY, display.c_str());
    }

    void nextStage() {
        ++stage;
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << stage;
        display = "Stage: " + oss.str();
    }
};

#endif // ELEMENT_CLASS_H
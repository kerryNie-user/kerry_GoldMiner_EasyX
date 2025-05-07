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

#include "linklist.hpp"  // My linked list with almost all of the functions vector has

#pragma comment(lib, "Winmm.lib")  // For PlaySound

/**
 * @brief Get the current time in milliseconds since epoch.
 * @return The current time in milliseconds.
 */
time_t getCurrentTimeInMilliseconds() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return now_ms.time_since_epoch().count();
}

/**
 * @brief Convert degrees to radians.
 * @param angleDegrees The angle in degrees.
 * @return The angle in radians.
 */
inline double degreesToRadians(double angleDegrees) {
    return angleDegrees * M_PI / 180.0;
}

LinkedList<std::string> storedUsername;  // All the usernames in the file
LinkedList<std::string> storedPassword;  // All the passwords in the file
LinkedList<int> storedStage;             // All the stages in the file

std::string username = "kerry";  // Focused user's username
std::string password = "kerry";  // Focused user's password
int stage = 1;                   // Focused user's stage

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

// Explosion effect frame animation
LinkedList<std::string> imgPath_explosive;
LinkedList<std::string> maskPath_explosive;

// Background music paths
std::string musicPath_background_normal = "res/music_background_normal.mp3";
std::string musicPath_background_stormy = "res/music_background_stormy.mp3";
std::string musicPath_background_quicksand = "res/music_background_quicksand.mp3";
std::string musicPath_background_magnetic = "res/music_background_magnetic.mp3";

// Background sound effects
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

// Explosion effect frame animation picture
LinkedList<IMAGE> img_explosive;
LinkedList<IMAGE> mask_explosive;

const int SLEEP_TIME = 10;  // Sleep time in milliseconds every frame
const int LENGTH_INDEX = 400;  // Length index for the game window, defining the width and height of the game window
const int WID = 3 * LENGTH_INDEX;
const int HEI = 2 * LENGTH_INDEX;
const int MINER_X = (WID - 90) / 2;
const int MINER_Y = 10;
const int MINER_W = 90;
const int MINER_H = 90;
const int HOOK_X = MINER_X + MINER_W * 0.18;
const int HOOK_Y = MINER_Y + MINER_H * 0.6;
const int HOOK_LENGTH = 30;  // Length of the line from the miner to the hook
const int HOOK_SPEED = SLEEP_TIME * 0.7;  // Speed of the hook when going out
const int HOOKED_SIZE = 40;  // To detect if the object is hooked
const int BOMB_W = 15;
const int BOMB_H = 30;
const int GAME_TIME = 99;
const std::time_t EXPLOSION_TIME = 1000;  // Burst frame animation duration

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

class Clock {
private:
    int x, y, w, h;  // Coordinates and dimensions of the clock
    int start;  // Timestamp for game start
    int total;  // Total game time
    int remain;  // Remaining time
    bool gameContinue;  // Flag to check if the game is still ongoing
    std::string display;  // Display remaining time

public:
    Clock () {}

    /**
     * @brief Initialize the clock with the total game time.
     * @param total Total game time in seconds. 
     */
    void init(int total) {
        start = clock();
        this->total = total;
        gameContinue = true;
        display = "0";
    }

    /**
     * @brief Draw the clock on the existed clock panel.
     */
    void draw() {
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
        int textX = 0.91 * WID - textWidth / 2;
        int textY = 0.015 * HEI;
        outtextxy(textX, textY, display.c_str());
    }

    /**
     * @brief Update the clock and check if the game is still ongoing.
     */
    void update () {
        int elapsed = (clock() - start) / CLOCKS_PER_SEC;
        remain = total - elapsed;
        if (remain <= 0) {
            remain = 0;
            gameContinue = false;
        }
        std::ostringstream oss;
        oss << remain;
        display = oss.str();
    }

    /**
     * @brief Check if the game is still ongoing.
     * @return True if the game is still ongoing, false otherwise.
     */
    bool isContinue() {
        return gameContinue;
    }

    /**
     * @brief Get the remaining time.
     * @return Remaining time in seconds.
     */
    int remainTime() {
        return remain;
    }
};

class Score {
private:
    int score;  // The score player has earned
    int goal;   // The score player needs to reach to win the game
    std::string displayScore;  // The score displayed
    std::string displayGoal;   // The goal displayed

public:
    Score () {}

    /**
     * @brief Initialize the score with the goal.
     * @param goal The score player needs to reach to win the game.
     */
    void init(int goal) {
        score = 0;
        this->goal = goal;
        displayScore = std::to_string(score);
        displayGoal = std::to_string(goal);
    }

    /**
     * @brief Draw the score and goal on the existed score and goal panel.
     */
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

    /**
     * @brief The player gets some score.
     * @param newScore The score the player gets.
     */
    void get(int newScore) {
        score += newScore;
        displayScore = std::to_string(score);
    }

    /**
     * @brief Check if the player has reached the goal.
     * @return True if the player has reached the goal, false otherwise.
     */
    bool reachGoal() {
        return score >= goal;
    }

    /**
     * @brief Get the current score.
     * @return The current score.
     */
    int getGoal() {
        return goal;
    }
};

class Stage {
private:
    int stage;  // The current stage of the game
    std::string display;  // The stage displayed

public:
    Stage () {}

    /**
     * @brief Initialize the stage with the current stage.
     * @param stage The current stage of the game.
     */
    void init(int stage) {
        this->stage = stage;
        display = std::to_string(stage);
    }

    /**
     * @brief Draw the stage on the existed stage panel.
     */
    void draw() {
        int textWidth = textwidth(display.c_str());
        int textHeight = textheight(display.c_str());
        int textX = 0.91 * WID - textWidth / 2;
        int textY = 0.065 * HEI;
        outtextxy(textX, textY, display.c_str());
    }

    /**
     * @brief Get the current stage.
     * @return The current stage.
     */
    int getStage() {
        return stage;
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
    int X, Y, W, H;  // The button detecting area
    ButtonCallBack callback;  // Callback function for each button(if you want your button have some reaction when clicking it you need to implement it)

public:
    CButton(int x, int y, int w, int h, const std::string& text, ButtonCallBack callback) 
        : CControl(x, y, w, h, text), X(x), Y(y), W(w), H(h), callback(callback) {}

    /**
     * @brief Simulate the mouse message of the button.
     * @param m The mouse message.
     */
    void simulateMouseMSG(MOUSEMSG m) {
        if (isMouseInButton(m.x, m.y)) {
            if (m.uMsg == WM_LBUTTONDOWN) {  // if the mouse is clicked down, then it will be focused(for if you want some special reaction)
                isFocused = true;
            } else if (m.uMsg == WM_LBUTTONUP) {  // if the mouse is released, and it's still on focused button, the button will reform the action
                isFocused = false;
                isReleased = true;
            }
        } else {
            isFocused = false;
        }
        if (isFocused) {  // for special reaction: smaller and blacker when it's focused
            x = X + W * 1 / 20;
            y = Y + H * 1 / 20;
            w = W * 9 / 10;
            h = H * 9 / 10;
        } else if (isReleased) {  // for special reaction: back to normal when it's released
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

    /**
     * @brief Get the text have been input.
     * @return text.
     */
    std::string getInputText() const {
        return text;
    }

    /**
     * @brief Simulate the mouse message of the input box.
     * @param m The mouse message.
     */
    void simulateMouseMSG(MOUSEMSG m) {
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (isMouseInButton(m.x, m.y)) {  // get the focus when the mouse is clicked down
                isFocused = true;
            } else {  // release the focus when the mouse clicking outside the input box
                isFocused = false;
            }
        }
    }

    /**
     * @brief Simulate the keyboard message including "backspace", "return" and the normal input.
     */
    void simulateKeyboardMSG() {
        if (isFocused) {
            if (kbhit()) {
                wchar_t ch = _getwch();
                if (ch == L'\r') {  // when the user press "return", the focus will be released
                    isFocused = false;
                } else if (ch == L'\b') {  // when the user press "backspace", the last character will be deleted if there is any
                    if (!text.empty()) {
                        text.pop_back();
                    }
                } else {  // normal input
                    text += ch;
                }
            }
        }
    }
};

class CObject {
protected:
    virtual void draw() = 0;

    /**
     * @brief Put the image with the mask on the screen.
     * @param img The image to be put.
     * @param mask The mask of the image.
     * @param x The x coordinate of the image.
     * @param y The y coordinate of the image.
     */
    void putimgwithmask(IMAGE& img, IMAGE& mask, int x, int y) const {
        putimage(x, y, &mask, NOTSRCERASE);
        putimage(x, y, &img, SRCINVERT);
    }
};

class CMiner : public CObject {
private:
    int x, y, w, h;  // Coordinates and dimensions of the miner
    bool working;  // Whether the miner's dragging the hook
    bool usingEnergy;  // Whether there is something in the hook
    bool showSecondImage;  // The bool variable for the animation of the miner
    std::chrono::time_point<std::chrono::system_clock> lastTime;  // A timestamp for the last time the miner's animation is updated
    IMAGE img1, mask1, img2, mask2;  // The two images and masks of the miner

public:
    CMiner() : x(MINER_X), y(MINER_Y), w(MINER_W), h(MINER_H) {}

    /**
     * @brief Initialize the miner with the two images and masks.
     * @param img1 The first image of the miner.
     * @param mask1 The first mask of the miner.
     * @param img2 The second image of the miner.
     * @param mask2 The second mask of the miner.
     */
    void init(IMAGE& img1, IMAGE& mask1, IMAGE& img2, IMAGE& mask2) {
        this->working = false;
        this->usingEnergy = false;
        this->showSecondImage = false;
        this->img1 = img1;
        this->mask1 = mask1;
        this->img2 = img2;
        this->mask2 = mask2;
    }

    /**
     * @brief Draw the miner on the screen.
     */
    void draw() {
        if (working && showSecondImage) {
            putimgwithmask(img2, mask2, x, y);
        } else {
            putimgwithmask(img1, mask1, x, y);
        }
    }

    /**
     * @brief Update the miner's animation.
     * If the miner is working and the interval between the last time and the current time is greater than "interval", the miner's animation will be updated.
     * If the miner is using energy, the "interval" will be 0.5 second, otherwise it will be 0.25 second.
     */
    void update() {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - lastTime;
        double interval = usingEnergy ? 0.5 : 0.25;
        if (elapsedTime.count() >= interval) {
            showSecondImage = !showSecondImage;
            lastTime = currentTime;
        }
    }

    /**
     * @brief Let the miner work.
     */
    void work() {
        working = true;
    }

    /**
     * @brief Let the miner using energy, because there is something in the hook.
     */
    void useEnergy() {
        working = true;
        usingEnergy = true;
    }

    /**
     * @brief Let the miner stop, because the hook is stop.
     */
    void stop() {
        working = false;
        usingEnergy = false;
    }
};

class CHook : public CObject {
private:
    int x, y;  // Coordinates of the start point of the line(connected to the miner)
    double endX, endY;  // Coordinates of the end point of the line(connected to the hook)
    int length;  // Length of the line
    int speed;  // Speed of the line
    double angle;  // Angle of the line(0 degree is three o'clock)
    double angleSpeed;  // Angular velocity
    bool isMoving = false;  // Whther the line is moving(including going out and retracting)
    bool isRetracting = false;  // Whether the line is retracting
    IMAGE img, mask;  // The image and mask of the hook
    IMAGE img_rotate, mask_rotate;  // The rotated image and mask of the hook

public:
    CHook() : x(HOOK_X), y(HOOK_Y), length(HOOK_LENGTH), speed(HOOK_SPEED), angleSpeed(SLEEP_TIME * 0.15), rotate(true) {}

    /**
     * @brief Initialize the hook with the image and mask.
     * @param img The image of the hook.
     * @param mask The mask of the hook.
     */
    void init(IMAGE& img, IMAGE& mask) {
        angle = 90;
        this->img = img;
        this->mask = mask;
    }

    /**
     * @brief Draw the hook on the screen.
     * Draw the line
     * Rotate the image and mask
     * Use a function to fit the hook's center to the line's end point.
     * Adjust the position of the image according to my calculations and draw it.
     */
    void draw() {
        setcolor(BLACK);
        setlinecolor(BLACK);
        setfillcolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        line(x, y, endX, endY);
        rotateimage(&img_rotate, &img, degreesToRadians(90 - angle), WHITE, true);
        rotateimage(&mask_rotate, &mask, degreesToRadians(90 - angle), BLACK, true);
        int imageX = endX - img.getwidth() * std::sin(degreesToRadians(angle)) / 2 - img.getheight() * (1 - std::cos(degreesToRadians(angle))) / 2;
        int imageY = endY - img.getwidth() * std::abs(std::cos(degreesToRadians(angle))) / 2;
        putimgwithmask(img_rotate, mask_rotate, imageX, imageY);
    }

    /**
     * @brief Update the hook's status(including it's rotate angel and it's position when it is going out).
     * Update the end point of the line with the current angel.
     * case1: If the hook is swaing, then check the angel(20 - 160 degree) and update it.
     * case2: If the hook is going out, then update the length and check if it's out of the screen.
     * case3: If the hook is retracting, then update the length and check if it's back to the miner(whether the current length is shorter then start).
     */
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

    /**
     * @brief Magnetic function.
     * This is a special function made for the MagneticScene, in this type of scene, the hook will be attracted to the magnetic source.
     * @see CGameMagnetic::update()
     * @param magnetic_source_x The x coordinate of the magnetic source.
     * @param magnetic_source_y The y coordinate of the magnetic source.
     * @param magnetic_strength The strength of the magnetic force.
     */
    void magnetic(int magnetic_source_x, int magnetic_source_y, double magnetic_strength) {
        int angle_target = std::atan2(magnetic_source_y - y, magnetic_source_x - x) * 180 / M_PI;
        int angle_distance = angle_target - angle;
        int distance_x = magnetic_source_x - endX;
        int distance_y = magnetic_source_y - endY;
        double magnetic_force = magnetic_strength / std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));
        angle += magnetic_force * angle_distance;
    }

    /**
     * @brief Check if the hook is going out.
     * @return True if the hook is going out, false otherwise.
     */
    bool isGoingOut() {
        return length > HOOK_LENGTH && isMoving && !isRetracting;
    }

    /**
     * @brief Check if the hook is retracting.
     * @return True if the hook is retracting, false otherwise.
     */
    bool isGoingBack() {
        return length > HOOK_LENGTH && isMoving && isRetracting;
    }

    /**
     * @brief Check if the hook is stop.
     * If the hook is not moving and not retracting and the length is smaller than the start length, then the hook is stop.
     * @return True if the hook is stop, false otherwise.
     */
    bool isStop() {
        return (!isMoving) && (!isRetracting) && (length <= HOOK_LENGTH);
    }

    /**
     * @brief Set the speed of the hook.
     * Usually, when there is somethinng hooked, the speed will be set to the object's speed.
     * And when the hook is back, the speed will be set to the original speed.
     * @param speed The speed of the hook.
     */
    void setSpeed(int speed) {
        this->speed = speed;
    }

    /**
     * @brief Move the hook.
     * Set the isMoving to true.
     */
    void move() {
        isMoving = true;
    }

    /**
     * @brief Retract the hook.
     * Set the isRetracting to true, usually when the hook is going out and the object is hooked, the hook will retract, or when the hook is out of the screen.
     */
    void retract() {
        isRetracting = true;
    }

    /**
     * @brief Stop the hook.
     * Set the isMoving and isRetracting to false.
     */
    void stop() {
        isMoving = false;
        isRetracting = false;
    }
    
    /**
     * @brief Get the end point x of the line.
     * @return The end point x of the line.
     */
    int getEndX() const {
        return endX;
    }

    /**
     * @brief Get the end point y of the line.
     * @return The end point y of the line.
     */
    int getEndY() const {
        return endY;
    }

    /**
     * @brief Get the length of the line.
     * Usually for adjust whether the hook is back.
     * @return The length of the line.
     */
    int getLength() const {
        return length;
    }

    /**
     * @brief Get the angle of the line.
     * @return The angle of the line.
     */
    double getAngle() const {
        return angle;
    }   
};

class CBomb : public CObject {
private:
    int x, y;  // The coordinates of the bomb
    bool blowUp;  // Whether the bomb is blew up
    IMAGE img;  // The image of the bomb
    IMAGE mask;  // The mask of the bomb

public:
    CBomb() : blowUp(false) {}

    bool operator==(const CBomb& other) const {
        return this->x == other.x && this->y == other.y;
    }

    /**
     * @brief Initialize the bomb with the image and mask.
     * @param img The image of the bomb.
     * @param mask The mask of the bomb.
     */
    void init(IMAGE& img, IMAGE& mask) {
        this->img = img;
        this->mask = mask;
    }

    /**
     * @brief Set the coordinates of the bomb.
     * Usually, this function is used for initialize the bombs array.
     * @param x The x coordinate of the bomb.
     * @param y The y coordinate of the bomb.
     */
    void setXY(int x, int y) {
        this->x = x;
        this->y = y;
    }

    /**
     * @brief Draw the bomb on the screen.
     */
    void draw() override {
        putimgwithmask(img, mask, x, y);
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
    int explosedIndex = -1;  // For the animation of the explosive, -1 means the object is not booming
    std::time_t explosedTime;  // A timestamp for the booming of this object
    IMAGE img, mask;

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

    /**
     * @brief Draw the object on the screen.
     * If the object is bombed, then draw the explosive animation.
     * Otherwise, draw the normal image.
     */
    void draw() {
        if (isBombed && explosedIndex != -1) {
            int explosedX = x + radius - img_explosive[explosedIndex].getwidth() / 2;
            int explosedY = y + radius - img_explosive[explosedIndex].getwidth() / 2;;
            putimgwithmask(img_explosive[explosedIndex], mask_explosive[explosedIndex], explosedX, explosedY);
        } else if (explosedIndex == -1) {
            putimgwithmask(img, mask, x, y);
        }
    }

    /**
     * @brief Move the object by it's speed.
     * @param moveangle The angle of the movement.
     */
    void move(int moveangle) {
        x -= speed * cos(degreesToRadians(moveangle));
        y -= speed * sin(degreesToRadians(moveangle));
    }

        /**
     * @brief Update for booming animation's index.
     * If the booming is not finished, then update the index of the animation.
     * Otherwise, set the isBombed to false.
     */
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

    /**
     * @brief Submerge the object by the distance.
     * This is a special function made for the QuickSandScene, in this type of scene, the object will keep submerging.
     * @see CGameQuickSand::update()
     * @param distance The distance of the submerge.
     */
    void submerge(int distance) {
        y += distance;
    }
    
    /**
     * @brief Bomb the object.
     * Set the isBombed to true and record the start timestamp.
     */
    void bomb() {
        explosedTime = getCurrentTimeInMilliseconds();
        isBombed = true;
    }
    
    /**
     * @brief Check if the object is hooked.
     * @param hookX The x coordinate of the hook.
     * @param hookY The y coordinate of the hook.
     * @return True if the object is hooked, false otherwise.
     */
    bool isHooked(int hookX, int hookY) {
        return std::pow((x + radius - hookX), 2) + std::pow((y + radius - hookY), 2) - radius * radius <= HOOKED_SIZE;
    }

    /**
     * @brief Check if the object is bombed.
     * @return True if the object is bombed, false otherwise.
     */
    bool bombed() const {
        return isBombed;
    }

    /**
     * @brief Get the type of the object.
     * @return The type of the object.
     */
    GameObjectType getType() const {
        return type;
    }
    
    /**
     * @brief Get the score if this object is get by miner.
     * @return The score of the object.
     */
    int getScore() const {
        return score;
    }
    
    /**
     * @brief Get the speed of the object.
     * Usually, this speed will be used for hook's speed update.
     * @return The speed of the object.
     */
    int getSpeed() const {
        return speed;
    }
    
    /**
     * @brief Get the radius of the object.
     * @return The radius of the object.
     */
    int getRadius() const {
        return radius;
    }
    
    /**
     * @brief Get the center x coordinate of the object.
     * @return The center x coordinate of the object.
     */
    int getRx() const {
        return x + radius;
    }
    
    /**
     * @brief Get the center y coordinate of the object.
     * @return The center y coordinate of the object.
     */
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

/**
 * @brief A factory class for creating game objects.
 * This class is used to create game objects with different types.
 */
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
    LinkedList<Raindrop> drops;  // A linked list to store every raindrops
    bool lightningActive = true;  // Whether the lightning is active (Used to judge whether it is lignt)

public:
    Rain() {}

    /**
     * @brief Initialize the raindrops.
     * This function will create every raindrops completely at random position and speed.
     * @param count The number of raindrops.
     */
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

    /**
     * @brief Draw the raindrops on the screen.
     * This function will draw every raindrops on the screen.
     * If the lightning is active, then the raindrops will be drawn in gray color. Otherwise, the raindrops will be drawn in black color. That will make the raindrops look more natural.
     */
    void draw() {
        if (lightningActive) {
            setlinecolor(LIGHTGRAY);
        } else {
            setlinecolor(RGB(100, 100, 100));
        }
        setbkmode(TRANSPARENT);
        setlinestyle(PS_SOLID, 2);
        for (Raindrop& drop : drops) {
            line(drop.x, drop.y, drop.x, drop.y + drop.length);
        }
        setcolor(BLACK);
    }

    /**
     * @brief Update the raindrops.
     * This function will update every raindrops.
     * If the raindrop is out of the screen, then it will be reset to the top of the screen.
     */
    void update() {
        for (Raindrop& drop : drops) {
            drop.y += drop.speed;
            if (drop.y > HEI) {
                drop.y = -drop.length;
                drop.x = rand() % WID;
            }
        }
    }

    void setLightningActive(bool active) {
        lightningActive = active;
    }
};

class Lightning {
private:
    LinkedList<POINT> points;  // The path points of the lightning
    bool isActive;  // Whether the lightning is active
    int duration;  // The duration time of the lightning

public:
    Lightning() {}

    /**
     * @brief Initialize the lightning.
     * This function will create the lightning with the duration time at milliseconds.
     * @param duration The duration time of the lightning.
     */
    void init(int duration) {
        this->duration = duration * 1000 / SLEEP_TIME;
        isActive = false;
    }

    /**
     * @brief Generate the lightning.
     * This function will generate the lightning with the path points, unless the lightning is out of the screen.
     * The path points will be generated randomly.
     */
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
    
    /**
     * @brief Draw the lightning on the screen.
     * If the lightning is active, the lines will connect all of the path points and act just like a real lightning.
     */
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
    
    /**
     * @brief Update the lightning.
     * If the lightning is active, then the duration time will be reduced by 1.
     * If the duration time is 0, then the lightning will be deactivated.
     */
    void update() {
        if (isActive) {
            --duration;
            if (duration <= 0) {
                isActive = false;
            }
        }
    }
};

class CScene {
protected:
    int m_scene;
    std::function<void(GameSceneType)> setGameScene;

public:
    CScene(const std::function<void(GameSceneType)>& setGameScene) : setGameScene(setGameScene) {}
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    /**
     * @brief Output the status of the game.
     * This function will output the status of the game and wait for click.
     * @param text The text of the status.
     */
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

    /**
     * @brief Play the background music.
     * This function will shut all the background music and play the new music.
     * @param music The path of the music.
     */
    void playBackgroundMusic(std::string& music) {
        mciSendString("close bkmusic", NULL, 0, NULL);
        mciSendString(("open " + music + " alias bkmusic").c_str(), NULL, 0, NULL);
        mciSendString("play bkmusic repeat", NULL, 0, NULL);
    }

    /**
     * @brief End the background music.
     */
    void endBackgroundMusic() {
        mciSendString("close bkmusic", NULL, 0, NULL);
    }

    /**
     * @brief Play the special effect music.
     * This function will shut the special effect music with the same name.
     * And play the new music with the name input path of the music.
     * @param music The path of the music.
     */
    void playSpecialEffectMusic(std::string& music) {
        mciSendString(("close " + music).c_str(), NULL, 0, NULL);
        mciSendString(("open " + music + " alias " + music).c_str(), NULL, 0, NULL);
        mciSendString(("play " + music).c_str(), NULL, 0, NULL);
    }
};

/**
 * @brief The menu scene.
 * This scene is the first scene of the game.
 */
class CMenu : public CScene {
private:
    CButton m_button_signin;
    CButton m_button_login;

public:
    CMenu(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_signin(0.654 * WID, 0.5 * HEI, 0.3 * WID, 0.1625 * HEI, "signin", std::bind(&CMenu::callbackSignin, this)), 
        m_button_login(0.025 * WID, 0.5 * HEI, 0.3 * WID, 0.1625 * HEI, "login", std::bind(&CMenu::callbackLogin, this)) {}

    /**
     * @brief Update the menu.
     * If the mouse is clicked, then the buttoncallback function will be called.
     * @see CButton::simulateMouseMSG()
     */
    void update() override{
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            m_button_signin.simulateMouseMSG(m);
            m_button_login.simulateMouseMSG(m);
        }
    }

    /**
     * @brief Render the start menu.
     */
    void render() override {
        cleardevice();
        putimage(0, 0, &img_startup);
    }

private:
    /**
     * @brief Callback function for the signin button.
     * This function will set the game scene to signin scene.
     */
    void callbackSignin() {
        setGameScene(GameSceneType::SIGNIN);
    }

    /**
     * @brief Callback function for the login button.
     * This function will set the game scene to login scene.
     */
    void callbackLogin() {
        setGameScene(GameSceneType::LOGIN);
    }
};

/**
 * @brief The login scene.
 * This scene is used to sign up a new account and login this account.
 */
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

    /**
     * @brief Update the signin scene.
     * If the mouse is clicked, then the buttoncallback function of the button and the input box will be called.
     * @see CButton::simulateMouseMSG()
     * @see CInputBox::simulateMouseMSG()
     */ 
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

    /**
     * @brief Render the signin scene.
     * The word have been written in the input box will be shown on the screen in time.
     */
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
    /**
     * @brief Callback function for the ok button.
     * This function will check the input of the user.
     * If the inputs is all valid, then detect whether the username has been used.
     * If not, then the username and password will be stored in the linked list, which will be stored in the file after the game is closed.
     */
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

    /**
     * @brief Callback function for the cancel button.
     * This function will set the game scene to menu scene.
     */
    void callbackCancel() {
        setGameScene(GameSceneType::MENU);
    }
};

/**
 * @brief The login scene.
 * This scene is used to login the account.
 */
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

    /**
     * @brief Update the login scene.
     * If the mouse is clicked, then the buttoncallback function of the button and the input box will be called.
     * @see CButton::simulateMouseMSG()
     * @see CInputBox::simulateMouseMSG()
     */
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

    /**
     * @brief Render the login scene.
     * The word have been written in the input box will be shown on the screen in time.
     */
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
    /**
     * @brief Callback function for the ok button.
     * This function will check the input of the user.
     * If the inputs is all valid, then detect whether the username and password are correct.
     * If correct, then the username and password will extracted from the linked list, and used for the gaming user update.
     */
    void callbackOk() {
        username = m_input_username.getInputText();
        password = m_input_password.getInputText();
        for (int i = 0; i < storedUsername.size(); ++i) {
            if (username == storedUsername[i] && password == storedPassword[i]) {
                stage = storedStage[i];
                outputStatus("Welcome back...");
                if (stage > 20) {
                    stage = 1;
                }
                setGameScene(GameSceneType::GAME);
                return;
            }
        }
        outputStatus("Username or Password incorrect");
    }

    /**
     * @brief Callback function for the cancel button.
     * This function will set the game scene to menu scene.
     */
    void callbackCancel() {
        setGameScene(GameSceneType::MENU);
    }
};

IMAGE img_null;  // A null image for the null object
GameObject nullObject(GameObjectType::GOLD, 0, 0, GoldRadiusType::BIG, img_null, img_null);  // A null object for the 'null' pointer
LinkedList<CBomb> m_bombs;             // A linked list to store every bombs
LinkedList<GameObject> m_gameObjects;  // A linked list to store every game objects

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
    bool countdown = false;  // Whether the countdown effective sound is need to be played

    CGame(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene), m_clock(), m_score(), m_stage(), m_miner(), m_hook(), m_bomb(),
        m_button_quit(0.638 * WID, 0.01375 * HEI, 0.14 * WID, 0.07 * HEI, "Quit", std::bind(&CGame::callbackQuit, this)) {}
    
public:
    /**
     * @brief Initialize the game.
     * This function will initialize all the components and gameObjects in the game.
     */
    virtual void init() {
        m_gameObjects.clear();
        m_stage.init(stage);
        m_clock.init(GAME_TIME);
        m_score.init(1000 + ((stage - 1) % 5 + 1) * 500);
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

    /**
     * @brief Render the game.
     * This function will render all the components and gameObjects in the game.
     */
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
    /**
     * @brief Update the components and gameObjects been operated in the game.
     * I will detect whether the mouse is clicked.
     * If the mouse is clicking the button, then the buttoncallback function of the button will be called.
     * If the left button is clicked, then the hook will move and the miner will work.
     * If the right button is clicked, then the hook will retract and the focused gameObject will be bombed if have.
     * And I will also detect whether the keyboard is pressed.
     * If 'return key' or 'space key' is pressed, then the hook will move and the miner will work.
     * If 'backspace key' is pressed, then the hook will retract and the focused gameObject will be bombed if have.
     * If 'q key' or 'Q key' is pressed, then the game scene will be set to menu scene.
     * If 'p key' or 'P key' is pressed, then the game will be paused.
     * @see CButton::simulateMouseMSG()
     */
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
        if (kbhit()) {
            wchar_t ch = _getwch();
            if (ch == L'\r' || ch == L' ') {
                m_hook.move();
                m_miner.work();
                playSpecialEffectMusic(musicPath_hook_goingOut);
            } else if (ch == L'\b') {  // when the user press "backspace", the last character will be deleted if there is any
                if (m_hook.isGoingBack() && m_bombs.size() > 0) {
                    m_hook.setSpeed(HOOK_SPEED);
                    if (m_focusedGameObject != &nullObject) {
                        m_focusedGameObject->bomb();
                        playSpecialEffectMusic(musicPath_bomb_explosive);
                    }
                }
            } else if (ch == L'q' || ch == L'Q') {
                setGameScene(GameSceneType::MENU);
            } else if (ch == L'p' || ch == L'P') {
                while (true) {
                    MOUSEMSG m = GetMouseMsg();
                    m_button_quit.simulateMouseMSG(m);
                    if (m.uMsg == WM_LBUTTONDOWN) {
                        break;
                    }
                    if (kbhit()) {
                        wchar_t ch = _getwch();
                        if (ch == L'q' || ch == L'Q') {
                            setGameScene(GameSceneType::MENU);
                            return;
                        } else if (ch == L'p' || ch == L'P') {
                            break;
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief Update the components and gameObjects in the game.
     * This function will update all the components and gameObjects in the game.
     * If the clock is continue, then the game will continue.
     * If the clock is not continue, then the game will be over.
     * If the gameObjects is empty, then the game will be won.
     * If the gameObjects is not empty, then the game will be continued.
     */
    void updateWithoutInput() {
        if (!m_clock.isContinue()) {
            endBackgroundMusic();  // If the game is end, then end the backMusic
            if (m_score.reachGoal()) {  // If you reach the goal, then win
                outputStatus("GOOD!");
                ++stage;
                setGameScene(GameSceneType::WIN);
            } else {  // If you have not reach the goal, then loose
                outputStatus("LOOSE!");
                setGameScene(GameSceneType::LOSE);
            }
        } else if (m_gameObjects.empty()) {  // If game object is empty, then win
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
            if (m_focusedGameObject == &nullObject) {  // If there's no focused gameObject, then find which gameObject can be focused
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
            } else {  // If there's a focused gameObject, it means the hook is going back with the focused gameObject
                if (m_focusedGameObject->bombed()) {  // If the focused gameObject is bombed
                    m_bombs.erase(m_bombs[m_bombs.size() - 1]);
                    m_explosedGameObject = m_focusedGameObject;  // give ownership of the gameObject to the explosedGameObject
                    m_focusedGameObject = &nullObject;
                } else {
                    if (m_hook.isStop()) {  // If the hook is stop, then erase the focused gameObject and get the score
                        m_score.get(m_focusedGameObject->getScore());
                        playMusicForGameObject(*m_focusedGameObject);
                        m_gameObjects.erase(*m_focusedGameObject);
                        m_focusedGameObject = &nullObject;
                        m_miner.stop();
                    }
                    m_focusedGameObject->move(m_hook.getAngle());  // If the hook is not stop, then the focused gameObject will move with the hook
                }
            }
        }
        if (m_explosedGameObject != &nullObject) {  // If there is something need to be exploded
            if (m_explosedGameObject->bombed()) {  // If the booming isn't finished, then start the booming
                m_explosedGameObject->explosing();
            } else {  // If the booming is finished, then erase the gameObject from the gameObjects list.
                m_gameObjects.erase(*m_explosedGameObject);
                m_explosedGameObject = &nullObject;
            }
        }
        if (!countdown && m_clock.remainTime() == 5) {  // If there is 5 seconds left, then play the countdown sound
            playSpecialEffectMusic(musicPath_countdown);
            countdown = true;
        }
    }

    /**
     * @brief Init the gameObjects with a special type.
     */
    void init_m_GameObjects() {
        m_gameObjects.clear();
        int num_index = tanh((stage - 1) % 5 + 1);
        int num_gold = 3 + 8 * num_index + rand() % 3;
        int num_rock = 3 + 3 * num_index + rand() % 2;
        int num_diamond = num_index + rand() % 2;
        while (1000 * num_diamond + 320 * num_gold + 75 * num_rock - m_score.getGoal() < 500) {
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

    /**
     * @brief Init the gameObjects with a special type, served for the init_m_GameObjects().
     * This function will init the gameObjects with a special type.
     * It will detect whether the gameObjects is too close or out of bounds.
     * If the gameObjects is too close or out of bounds, then the gameObjects will be reinitialized.
     * @param num The number of this type of gameObjects.
     * @param type The type of the gameObjects.
     * @param radius The radius of the gameObjects.
     * @param img The image of the gameObjects.
     * @param mask The mask of the gameObjects.
     */
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

    /**
     * @brief Init 5 bombs list, with compact arrangement.
     */
    void init_m_Boombs() {
        m_bombs.clear();
        for (int i = 0; i < 5; ++i) {
            m_bomb.setXY(0.56 * WID + BOMB_W * i, MINER_Y + MINER_H - BOMB_H);
            m_bombs.push_back(m_bomb);
        }
    }

    /**
     * @brief Detect whether the gameObjects is too close.
     * This function will iterate over all elements in the gameObjects list.
     * If the distance between the gameObjects and the gameObjects is less than the sum of the radius of the gameObjects, then return true.
     * Otherwise, return false.
     * @param x The x coordinate of the gameObjects.
     * @param y The y coordinate of the gameObjects.
     * @param radius The radius of the gameObjects.
     * @return Whether the gameObjects is too close.
     */
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

    /**
     * @brief Detect whether the gameObjects is out of bounds.
     * This function will detect whether the gameObjects is out of bounds.
     * @param x The x coordinate of the gameObjects.
     * @param y The y coordinate of the gameObjects.
     * @param radius The radius of the gameObjects.
     * @return Whether the gameObjects is out of bounds.
     */
    bool outOfBounds(int x, int y, int radius) {
        if (WID - radius - 20 <= 20 || HEI - radius - 20 <= WID / 4) {
            std::cerr << "Error: bounds too small !" << std::endl;
        }
        return x < 20 || x > WID - radius - 20 || y < HEI / 4 || y > HEI - radius - 20;
    }

    /**
     * A function to manage the music for the gameObjects when it is 'scored'.
     */
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

    /**
     * @brief Callback function for the quit button.
     * This function will set the game scene to null scene, so as will exit the game.
     */
    void callbackQuit() {
        setGameScene(GameSceneType::NULLSCENE);
    }
};

/**
 * @brief The normal game type, with no special.
 */
class CGameNormal : public CGame {
public:
    CGameNormal(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) {}

    void init() {
        CGame::init();
        // outputStatus("This is just the beginning, so only higher and higher goals");
        playBackgroundMusic(musicPath_background_normal);
    }

    void update() {
        CGame::update();
    }

    void render() {
        CGame::render();
    }
};

/**
 * @brief The stormy game type.
 * This game type will continue to rain.
 * The lightning will be generated every epochs.
 * When the lightning is generated, the scene will be lighted.
 * And after the lightning is over, the scene will be dark.
 */
class CGameStormy : public CGame {
private:
    Rain rain;
    Lightning lightning;
    int startTime = 3;  // There will be 'startTime' light scene before the darkness fall.
    int stormyTime = 1;  // The time of lightning to stay.
    int stormyInterval = 6;  // The interval of lightning existing.
    bool dark = true;  // Whether the scene is dark.
    bool thundering = false;  // Whether the lightning is generated.

public:
    CGameStormy(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) { void init(); }

    /**
     * @brief Init the stormy game.
     * The stormyTime and stormyInterval will be set according to the stage.
     */
    void init() {
        CGame::init();
        rain.init(350);
        switch (stage) {
            case 6: // Stormy start
                stormyTime = 2;
                stormyInterval = 6;
                // outputStatus("Stormy start, so the game is a little bit harder");
                break;
            case 7: // More game objects
                stormyTime = 2;
                stormyInterval = 6;
                // outputStatus("More game objects");
                break;
            case 8: // The days are shorter
                stormyTime = 1;
                stormyInterval = 6;
                // outputStatus("The days are shorter");
                break;
            case 9: // The nights are longer
                stormyTime = 1;
                stormyInterval = 7;
                // outputStatus("The nights are longer");
                break;
            case 10: // Faster storms with less time to watch
                startTime = 1;
                stormyTime = 1;
                stormyInterval = 7;
                // outputStatus("Faster storms with less time to watch");
                break;
            default:
                break;
        }
        lightning.init(stormyTime * 1000 / SLEEP_TIME);
        playBackgroundMusic(musicPath_background_stormy);
    }

    /**
     * @brief Update the stormy game.
     */
    void update() {
        CGame::update();
        rain.update();
        lightning.update();
        if (m_clock.remainTime() + startTime < GAME_TIME && 
            (m_clock.remainTime() + startTime) % (stormyTime + stormyInterval) > stormyTime) {  // If the darkness has not come, then stay light
            //  ------**  The time is just like this, '-' means the darkness, '*' means the light. And loop through this process.
            thundering = false;
            dark = true;
        } else {
            if (thundering == false) {  // Generate the lightning
                playSpecialEffectMusic(musicPath_thunder);
                thundering = true;
                lightning.generateLightning();
            }
            dark = false;
        }
        rain.setLightningActive(!dark);  // Pass in the background darkness to the rain, so as to make the rain more visible.
    }

    /**
     * @brief Render the stormy game.
     * If the scene is dark, then fill the screen with black, only the hook and explosion animation will be visible.
     * If the scene is light, then render normal.
     */
    void render() override {
        CGame::render();
        if (dark) {
            setfillcolor(BLACK);
            fillrectangle(0, 0, WID, HEI);
        } else {
            lightning.draw();
        }
        m_hook.draw();
        if (m_explosedGameObject != &nullObject) {
            m_explosedGameObject->draw();
        }
        rain.draw();
    }
};

/**
 * @brief The quicksand game type.
 * This game type will make the gameObjects submerge.
 * The gameObjects will submerge faster when the stage is bigger.
 */
class CGameQuicksand : public CGame {
private:
    int lastRemainTime = GAME_TIME;

public:
    CGameQuicksand(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) {}

    /**
     * @brief This function will play the background music for the quicksand game.
     */
    void init() {
        CGame::init();
        std::string outputText = "sorry, there're something wrong";
        switch (stage) {
            case 11:
                outputText = "Quicksand start, so the game is a little bit harder";
                break;
            case 12:
                outputText = "Faster settling rate";
                break;
            case 13:
                outputText = "The quicksand becomes soft, so heavier objects will settle first";
                break;
            case 14:
                outputText = "The quicksand becomes soft";
                break;
            case 15:
                outputText = "Golds will fall quickly, while lighter stones fall very slowly";
                break;
            default:
                break;
        }
        // outputStatus(outputText);
        playBackgroundMusic(musicPath_background_quicksand);
    }

    /**
     * @brief Update the quicksand game.
     * This function will update the gameObjects.
     * The gameObjects will submerge faster when the stage is bigger.
     * And the gameObjects will submerge faster if the stage is bigger.
     */
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

/**
 * @brief The magnetic game type.
 * This game type will make a magnetic resource on the bottom of the screen.
 * The hook will be attracted to the magnetic resource.
 * The magnetic force will be stronger when the stage is bigger.
 * The magnetic force will after 19.
 */
class CGameMagnetic : public CGame {
public:
    CGameMagnetic(const std::function<void(GameSceneType)>& setGameScene) : CGame(setGameScene) {}

    /**
     * @brief This function will play the background music for the magnetic game.
     */
    void init() {
        CGame::init();
        std::string outputText = "sorry, there're something wrong";
        switch (stage) {
            case 16:
                outputText = "Magnetic start, so the game is a little bit harder";
                break;
            case 17:
                outputText = "More game objects and stronger magnetic force";
                break;
            case 18:
                outputText = "Stronger magnetic force";
                break;
            case 19:
                outputText = "The magnetic force starts to change over time, so collect the side target as soon";
                break;
            case 20:
                outputText = "Stronger magnetic force";
                break;
            default:
                break;
        }
        // outputStatus(outputText);
        playBackgroundMusic(musicPath_background_normal);
    }

    /**
     * @brief Update the magnetic game.
     * This function will update the hook.
     * The hook will be attracted to the magnetic resource.
     * The magnetic force will be stronger when the stage is bigger.
     * The magnetic force will after 19.
     */
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

/**
 * @brief The game factory class.
 * This class will create the game scene according to the stage.
 */
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

/**
 * @brief The win scene class.
 * This class will render scene if you win.
 */
class CWin : public CScene {
private:
    CButton m_button_continue;
    CButton m_button_quit;

public:
    CWin(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_continue(0.665 * WID, 0.51375 * HEI, 0.29 * WID, 0.15 * HEI, "Continue", std::bind(&CWin::callbackContinue, this)),
        m_button_quit(0.665 * WID, 0.70875 * HEI, 0.29 * WID, 0.15 * HEI, "Quit", std::bind(&CWin::callbackQuit, this)) {}

    /**
     * @brief Update the win scene.
     * This function will update the buttons.
     */
    void update() override {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            m_button_continue.simulateMouseMSG(m);
            m_button_quit.simulateMouseMSG(m);
        }
    }

    /**
     * @brief Render the win scene.
     */
    void render() override {
        cleardevice();
        putimage(0, 0, &img_game_win);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
    }

private:
    /**
     * @brief Callback function for the continue button.
     * This function will set the game scene to game scene if the game is not over.
     * Otherwise, set the game scene to over scene.
     */
    void callbackContinue() {
        if (stage >= 20) {
            stage = 21;
            setGameScene(GameSceneType::OVER);
        } else {
            setGameScene(GameSceneType::GAME);
        }
    }
    
    /**
     * @brief Callback function for the quit button.
     * This function will set the game scene to null scene, so as will exit the game.
     */
    void callbackQuit() {
        setGameScene(GameSceneType::NULLSCENE);
    }
};

/**
 * @brief The lose scene class.
 * This class will render scene if you lose.
 */
class CLose : public CScene {
private:
    CButton m_button_retry;
    CButton m_button_quit;
public:
    CLose(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene),
        m_button_retry(0.6725 * WID, 0.12625 * HEI, 0.29 * WID, 0.15 * HEI, "Retry", std::bind(&CLose::callbackRetry, this)),
        m_button_quit(0.6725 * WID, 0.3 * HEI, 0.29 * WID, 0.15 * HEI, "Quit", std::bind(&CLose::callbackQuit, this)) {}

    /**
     * @brief Update the lose scene.
     * This function will update the buttons.
     */
    void update() override {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            m_button_retry.simulateMouseMSG(m);
            m_button_quit.simulateMouseMSG(m);
        }
    }

    /**
     * @brief Render the lose scene.
     */
    void render() override {
        cleardevice();
        putimage(0, 0, &img_game_lose);
        setbkmode(TRANSPARENT);
        settextstyle(40, 0, _T("宋体"));
        settextcolor(BLACK);
    }

private:
    /**
     * @brief Callback function for the retry button.
     * This function will set the game scene to game scene, you will retry this stage.
     */
    void callbackRetry() {
        setGameScene(GameSceneType::GAME);
    }

    /**
     * @brief Callback function for the quit button.
     * This function will set the game scene to null scene, so as will exit the game.
     */
    void callbackQuit() {
        setGameScene(GameSceneType::NULLSCENE);
    }
};

class COver : public CScene {
private:
    int y = 0;  // The y coordinate of the game over image

public:
    COver(const std::function<void(GameSceneType)>& setGameScene) : CScene(setGameScene) {}

    /**
     * @brief Update the over scene.
     * This function will update the y coordinate of the game over image.
     * And if the mouse is clicked, then set the game scene to null scene, so as will exit the game.
     */
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

    /**
     * @brief Scroll through the end screen.
     */
    void render() override {
        cleardevice();
        putimage(0, y, &img_game_over);
    }    
};

/**
 * @brief The game class.
 * This class will manage all the game scene.
 */
class Game {
private:
    GameSceneType m_game_scene;  // The current game scene
    CMenu m_menu;                // The menu scene
    CSignin m_signin;            // The signin scene
    CLogin m_login;              // The login scene
    CGame* m_game = nullptr;     // The game scene
    CWin m_win;                  // The win scene
    CLose m_lose;                // The lose scene
    COver m_over;                // The over scene

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

    /**
     * @brief Run the game.
     * This function will run the game.
     */
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
    /**
     * @brief Load the image and mask path.
     * This function will load the image and mask path.
     */
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

    /**
     * @brief Set the image and mask path for the explosion.
     * This function will set the image and mask path for the explosion.
     */
    void setImageExplosivePath() {
        for (int i = 0; i < 9; ++i) {
            std::string imgPath ="res/explosion/explosion_0" + std::to_string(i + 1) + ".jpg";
            std::string maskPath = "res/explosion/explosion_0" + std::to_string(i + 1) + "_mask.jpg";
            imgPath_explosive.push_back(imgPath);
            maskPath_explosive.push_back(maskPath);
        }
    }

    /**
     * @brief Load the image and mask.
     * This function will load the image and mask.
     */
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
        for (int i = 0; i < 9; ++i) {
            IMAGE img;
            IMAGE mask;
            loadimage(&img, imgPath_explosive[i].c_str(), 200, 200, true);
            loadimage(&mask, maskPath_explosive[i].c_str(), 200, 200, true);
            img_explosive.push_back(img);
            mask_explosive.push_back(mask);
        }
    }

    /**
     * @brief Proofread the image and mask.
     * This function will proofread the image and mask by it's size.
     * If the image and mask are not loaded successfully, then return false.
     */
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
        } else if (img_explosive.size() != 9 || mask_explosive.size() != 9) {
            std::cerr << "Failed to load img_explosive or mask_explosive!" << std::endl;
            return false;
        } else {
            for (int i = 0; i < 9; ++i) {
                if (img_explosive[i].getwidth() != 200 || img_explosive[i].getheight() != 200) {
                    std::cerr << "Failed to load img_explosive!" << std::endl;
                    return false;
                } else if (mask_explosive[i].getwidth() != 200 || mask_explosive[i].getheight() != 200) {
                    std::cerr << "Failed to load mask_explosive!" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * @brief Write the information of all the users into the file.
     */
    void writeTEXT() {
        for (int i = 0; i < storedUsername.size(); ++i) {  // First add the current user's information into the linked list
            if (username == storedUsername[i]) {
                storedStage[i] = stage;
                break;
            }
            if (i == storedUsername.size() - 1) {  // If the current user is not in the linked list, then there must be a mistake in the code
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
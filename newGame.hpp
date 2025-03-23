#include <graphics.h>
#include <conio.h>
#include <string>
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
#include "linklist.hpp"

#define SLEEP_TIME 10
#define LENGTH_INDEX 300
#define WID (3 * LENGTH_INDEX)
#define HEI (2 * LENGTH_INDEX)
#define HOOK_LENGTH 30
#define HOOK_SPEED (SLEEP_TIME * 6 / 10)

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

// 定义游戏场景宏
#define game_scene_menu 1
#define game_scene_signin 2
#define game_scene_login 4
#define game_scene_game 5

LinkedList<std::string> storedUsername;
LinkedList<std::string> storedPassword;
LinkedList<int> storedStage;
int userIndex;

IMAGE img_startup;
IMAGE img_signin;
IMAGE img_login;

using ButtonCallBack = std::function<void()>;

class CScene {
protected:
    int m_scene;
    std::function<void(int)> setGameScene;
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
public:
    CScene(std::function<void(int)> setGameScene) : setGameScene(setGameScene) {}
    virtual void update() = 0;
    virtual void render() = 0;
};

class CControl {
public:
    virtual void draw() = 0;
    virtual ~CControl() {}
};

class CButton : public CControl {
private:
    int x, y;
    int width, height;
    std::string buttonText;
    ButtonCallBack callback;
public:
    CButton(int x, int y, int width, int height, const std::string& buttonText, ButtonCallBack callback)
        : x(x), y(y), width(width), height(height), buttonText(buttonText), callback(callback) {}

    void simulateMouseClick(int mouseX, int mouseY) {
        if (isMouseInButton(mouseX, mouseY)) {
            // 添加调试信息，用于确认按钮是否被点击
            std::cout << "Button clicked!" << std::endl; 
            if (callback) {
                callback();
            }
        }
    }

    void draw() override {
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
    bool isMouseInButton(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }
};

class CInputBox : public CControl {
private:
    int x, y;
    int width, height;
    std::string inputText;
    bool isFocused;
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

    void draw() override {
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

class CMenu : public CScene {
private:
    CButton m_button_signin;
    CButton m_button_login;
public:
    // 构造函数传入设置场景的回调函数，并初始化按钮和回调
    CMenu(std::function<void(int)> setGameScene) : CScene(setGameScene),
    m_button_signin(0.1 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, "signin", std::bind(&CMenu::callbackSignin, this)), 
    m_button_login(0.6 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, "login", std::bind(&CMenu::callbackLogin, this)) {}

    void update() override {
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
    void callbackSignin () {
        setGameScene(game_scene_signin);
    }

    void callbackLogin () {
        setGameScene(game_scene_login);
    }
};

class CSignin : public CScene {
protected:
    CInputBox m_input_username;
    CInputBox m_input_password;
    CInputBox m_input_confirm;
private:
    CButton m_button_ok;
    CButton m_button_cancel;
    bool confirm;
public:
    // 构造函数传入设置场景的回调函数，并初始化输入框和按钮及回调
    CSignin(std::function<void(int)> setGameScene) : CScene(setGameScene), confirm(false), 
        m_input_username(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI), 
        m_input_password(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI), 
        m_input_confirm(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI), 
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
    void callbackOk () {
        if (confirm) {
            std::string passwordOld = m_input_password.getInputText();
            std::string passwordNew = m_input_confirm.getInputText();
            if (passwordOld == passwordNew) {
                storedUsername.push_back(m_input_username.getInputText());
                storedPassword.push_back(m_input_password.getInputText());
                storedStage.push_back(1);
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

    void callbackCancel () {
        if (confirm) {
            confirm = false;
        } else {
            setGameScene(game_scene_menu);
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
    // 构造函数传入设置场景的回调函数，并初始化输入框和按钮及回调
    CLogin(std::function<void(int)> setGameScene) : CScene(setGameScene),
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
private:
    void callbackOk () {
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

    void callbackCancel () {
        setGameScene(game_scene_menu);
    }
};

class Game {
private:
    int m_game_scene;
    CMenu m_menu;
    CSignin m_signin;
    CLogin m_login;
public:
    Game() : m_game_scene(game_scene_menu),
             m_menu([this](int scene) { this->m_game_scene = scene; }),
             m_signin([this](int scene) { this->m_game_scene = scene; }),
             m_login([this](int scene) { this->m_game_scene = scene; }) {}
    void run() {
        initgraph(WID, HEI);
        loadIMAGE();
        loadTEXT();
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
                    EndBatchDraw();
                    writeTEXT();
                    closegraph();
                    return;
                    break;
                default:
                    break;
            }
            FlushBatchDraw();
            Sleep(SLEEP_TIME);
        }
        EndBatchDraw();
        closegraph();
        writeTEXT();
    }
private:
    bool loadTEXT () {
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
        return storedUsername.size() == storedPassword.size() && storedUsername.size() == storedStage.size();
    }
    void loadIMAGE () {
        loadimage(&img_startup, imgPath_startup.c_str(), WID, HEI, true);
        loadimage(&img_signin, imgPath_signin.c_str(), WID, HEI, true);
        loadimage(&img_login, imgPath_login.c_str(), WID, HEI, true);
    }
    bool writeTEXT () {
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
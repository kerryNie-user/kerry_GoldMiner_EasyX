#ifndef START_H
#define START_H

#include "linklist.hpp"
#include "energy.hpp"

#include <string>
#include <fstream>
#include <list>
#include <graphics.h>
#include <iostream>
#include <sstream>

class Start {
private:
    // 输入框和按钮相关定义
    int box_x;
    int box_y;
    int box_w;
    int box_h;

    // 按钮对象
    Button button_signin;
    Button button_login;
    Button null_button;
    Button login_username;
    Button login_password;
    Button login_reenterp;
    Button back_button;
    Button next_button;

    // 用户数据存储
    std::string filePath;
    LinkedList<std::string> storedusername;
    LinkedList<std::string> storedpassword;

    // 图片对象
    IMAGE img_startup;
    IMAGE img_signin;
    IMAGE img_login;

    // 私有方法
    bool readingtext();
    void drawLoginSigninInterface(Button& passer);
    void outputStatusForStart(std::basic_string<TCHAR> tempText);
    bool reenterPassword();
    bool handleInputInterface(Button& passer, bool isSignin);
    bool turnToSigninInterface();
    bool turnToLoginInterface();
    void dealWithInput(Button& btn);
    bool checkUserName();
    bool signin();
    bool login();

public:
    Start(const std::string& filePath);
    void startup();
};

// Start声明函数//
Start::Start(const std::string& filePath) :
    box_x(0.12 * WID),
    box_y(0.37 * HEI),
    box_w(0.76 * WID),
    box_h(0.43 * HEI),

    button_signin(0.1 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, 0, ""),
    button_login(0.6 * WID, 0.7 * HEI, 0.3 * WID, 0.08 * HEI, 0, ""),
    null_button(0, 0, 0, 0, 0, _T("")),
    login_username(0.34 * WID, 0.44 * HEI, 0.48 * WID, 0.12 * HEI, 0, ""),
    login_password(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI, 0, ""),
    login_reenterp(0.34 * WID, 0.61 * HEI, 0.48 * WID, 0.12 * HEI, 0, ""),
    next_button(0.8 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, 0, "->"),
    back_button(0.04 * WID, 0.8 * HEI, 0.16 * WID, 0.15 * HEI, 0, "<-")
{
    this->filePath = filePath;
    loadimage(&this->img_startup, imgPath_startup.c_str(), WID, HEI, true);
    loadimage(&this->img_signin, imgPath_signin.c_str(), WID, HEI, true);
    loadimage(&this->img_login, imgPath_login.c_str(), WID, HEI, true);
}

// 读取用户数据文件//
bool Start::readingtext() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << " for checking username." << std::endl;
        return false;
    }
    std::string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        storedusername.push_back(storedUsername);
        storedpassword.push_back(storedPassword);
    }
    file.close();
    return storedusername.size() == storedpassword.size();
}

// 绘制登录/注册界面//
void Start::drawLoginSigninInterface(Button& passer) {
    setbkmode(TRANSPARENT);
    setfillcolor(RGB(224, 243, 225));
    fillrectangle(box_x, box_y, box_x + box_w, box_y + box_h);
    settextstyle(40, 0, _T("宋体"));
    settextcolor(BLACK);
    login_username.drawbutton();
    passer.drawbutton();
    back_button.drawbutton();
    next_button.drawbutton();
}

// 输出启动状态信息//
void Start::outputStatusForStart(std::basic_string<TCHAR> tempText) {
    fillrectangle(box_x, box_y, box_x + box_w, box_y + box_h);
    int textX = box_x + (box_w - textwidth(tempText.c_str())) / 2;
    int textY = box_y + (box_h - textheight(tempText.c_str())) / 2;
    outtextxy(textX, textY, tempText.c_str());
    Sleep(1000);
}

// 重新输入密码逻辑//
bool Start::reenterPassword() {
    outputStatusForStart(_T("Please reenter password"));
    BeginBatchDraw();
    while (true) {
        putimage(0, 0, &img_signin);
        drawLoginSigninInterface(login_reenterp);
        FlushBatchDraw();
        Sleep(10);

        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (login_reenterp.isMouseInButton(m.x, m.y)) {
                    dealWithInput(login_reenterp);
                } else if (next_button.isMouseInButton(m.x, m.y)) {
                    if (login_reenterp.text == login_password.text) {
                        if (signin()) {
                            outputStatusForStart(_T("Welcom in..."));
                            return true;
                        } else {
                            outputStatusForStart(_T("Failed to open file"));
                        }
                    } else {
                        outputStatusForStart(_T("Password error"));
                    }
                } else if (back_button.isMouseInButton(m.x, m.y)) {
                    return false;
                }
            }
        }
    }
    EndBatchDraw();
    return false;
}

// 处理输入界面逻辑//
bool Start::handleInputInterface(Button& passer, bool isSignin) {
    cleardevice();
    BeginBatchDraw();
    while (true) {
        if (isSignin) {
            putimage(0, 0, &img_signin);
        } else {
            putimage(0, 0, &img_login);
        }
        drawLoginSigninInterface(passer);
        FlushBatchDraw();
        Sleep(10);

        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (login_username.isMouseInButton(m.x, m.y)) {
                    dealWithInput(login_username);
                } else if (passer.isMouseInButton(m.x, m.y)) {
                    dealWithInput(passer);
                } else if (next_button.isMouseInButton(m.x, m.y)) {
                    if (isSignin) {
                        if (checkUserName()) {
                            if (reenterPassword()) {
                                return true;
                            }
                        } else {
                            outputStatusForStart(_T("Username has been used"));
                        }
                    } else {
                        if (login()) {
                            outputStatusForStart(_T("Welcom in..."));
                            return true;
                        } else {
                            outputStatusForStart(_T("Username and Password incorrect"));
                        }
                    }
                } else if (back_button.isMouseInButton(m.x, m.y)) {
                    return false;
                }
            }
        }
    }
    EndBatchDraw();
    return false;
}

// 进入注册界面//
bool Start::turnToSigninInterface() {
    return handleInputInterface(login_password, true);
}

// 进入登录界面//
bool Start::turnToLoginInterface() {
    return handleInputInterface(login_password, false);
}

// 处理输入框输入逻辑//
void Start::dealWithInput(Button& btn) {
    BeginBatchDraw();
    btn.drawkickedbutton();
    FlushBatchDraw();
    while (true) {
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (!btn.isMouseInButton(m.x, m.y)) {
                    btn.drawbutton();
                    break;
                }
            }
        }
        if (kbhit()) {
            wchar_t ch = _getwch();
            if (ch == L'\r') {
                break;
            } else if (ch == L'\b') {
                if (!btn.text.empty()) {
                    btn.text.pop_back();
                }
            } else {
                btn.text += ch;
            }
            btn.drawkickedbutton();
            FlushBatchDraw();
        }
    }
    Sleep(10);
    EndBatchDraw();
}

// 检查用户名是否已存在//
bool Start::checkUserName() {
    std::string username = tstring_to_string(login_username.text);
    for (const std::string& user : storedusername) {
        if (username == user) {
            return false;
        }
    }
    return true;
}

// 用户注册逻辑/
bool Start::signin() {
    std::string username = tstring_to_string(login_username.text);
    std::string password = tstring_to_string(login_password.text);
    std::ofstream file(filePath, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << " for signing in." << std::endl;
        return false;
    }
    file << username << " " << password << std::endl;
    file.close();
    storedusername.push_back(username);
    storedpassword.push_back(password);
    return true;
}

// 用户登录逻辑//
bool Start::login() {
    std::string username = tstring_to_string(login_username.text);
    std::string password = tstring_to_string(login_password.text);
    auto itUser = storedusername.begin();
    auto itPass = storedpassword.begin();
    for (; itUser != storedusername.end() && itPass != storedpassword.end(); ++itUser, ++itPass) {
        if (username == *itUser && password == *itPass) {
            return true;
        }
    }
    return false;
}

// 启动登录注册界面
void Start::startup() {
    if (!readingtext()) {
        outputStatusForStart(_T("Failed to read user data."));
        return;
    }
    while (true) {
        cleardevice();
        putimage(0, 0, &img_startup);
        button_signin.drawbutton();
        button_login.drawbutton();
        FlushBatchDraw();
        Sleep(10);
        MOUSEMSG m;
        if (MouseHit()) {
            m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (button_login.isMouseInButton(m.x, m.y)) {
                    if (turnToLoginInterface()) {
                        break;
                    }
                } else if (button_signin.isMouseInButton(m.x, m.y)) {
                    if (turnToSigninInterface()) {
                        break;
                    }
                }
            }
        }
    }
}    

#endif //START_H    
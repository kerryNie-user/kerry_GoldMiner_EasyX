#include <string>
#include <sstream>
#include <ctime>
#include <graphics.h>

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
  
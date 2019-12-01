#ifndef menu_h
#define menu_h

#include "HighScore.h"
#include "Start.h"
#include "Settings.h"

struct pos {
  int col, lin;
  pos(int _col, int _lin) : col(_col), lin(_lin) {}
};

class Menu
{
  private:
    MenuOption * options[3];
    bool loadedItem;
    bool stateChanged;
    const pos arrow_position[3] = {pos(0,0), pos(7,0), pos(0,1)};
    int current_position;
    void menuDisplay(LiquidCrystal & lcd);
  public:
    Menu(Start * s, Settings * se, HighScore * hs);
    void displayMenu(LiquidCrystal & lcd);
    bool isLoaded() const { return loadedItem; }
    bool Load() { loadedItem = true; stateChanged = true; }
    int getArrowPos() const { return current_position; }
    void setArrowPos(int newPos) { current_position = (newPos + 3) % 3; stateChanged = true; }
    bool getState() const { return stateChanged; }
    void waitingEvent();
};

#endif

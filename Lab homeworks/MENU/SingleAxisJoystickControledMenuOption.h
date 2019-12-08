#ifndef single_axis_joystick_controled_menuoption_h
#define single_axis_joystick_controled_menuoption_h

#include "MenuOption.h"

class SingleAxisJoystickControledMenuOption : virtual public MenuOption
{
private:
    const int maxThreshold = 600;
    const int minThreshold = 400;
    bool joyMoved;
    int axisPin;

protected:
    template <typename Func1, typename Func2>
    void takeActionsOnJoystickMoved(Func1 positiveMoved, Func2 negativeMoved);

public:
    SingleAxisJoystickControledMenuOption(int axisPin)
        : joyMoved(false), axisPin(axisPin) {}
    virtual ~SingleAxisJoystickControledMenuOption() = default;
};

template <typename Func1, typename Func2>
void SingleAxisJoystickControledMenuOption::takeActionsOnJoystickMoved(Func1 positiveMoved, Func2 negativeMoved)
{
    int valueOnAxis;
    valueOnAxis = analogRead(axisPin);
    if (valueOnAxis < minThreshold && joyMoved == false)
    {
        negativeMoved();
        joyMoved = true;
    }
    if (valueOnAxis > maxThreshold && joyMoved == false)
    {
        positiveMoved();
        joyMoved = true;
    }
    if (valueOnAxis >= minThreshold && valueOnAxis <= maxThreshold)
        joyMoved = false;
}

#endif
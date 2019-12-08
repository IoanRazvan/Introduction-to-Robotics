#ifndef button_controled_menuoption_h
#define button_controled_menuoption_h

#include "MenuOption.h"

//ButtonControledMenuOption also represents an Interface
//it's derived from MenuOption and it represents a
//specialized button-comanded menu option.

//It differs from MenuOption by adding int variables
//describing the buttonPin and the current and previous
//state of the button.

//takeActionOnBurronPressed is a template function which
//takes as argument any callable entity such as a function pointer,
//a functor or a lambda expression indicating the code to be executed
//if the asociated button was pressed.

class ButtonControledMenuOption : virtual public MenuOption
{
private:
    int swState;
    int lastSwState;
    int buttonPin;

protected:
    template <typename Func>
    void takeActionOnButtonPressed(Func f);

public:
    ButtonControledMenuOption(int buttonPin)
        : buttonPin(buttonPin), swState(0), lastSwState(0) {}
    virtual ~ButtonControledMenuOption() = default;
};

template <typename Func>
void ButtonControledMenuOption::takeActionOnButtonPressed(Func f)
{
    swState = digitalRead(buttonPin);
    if (swState != lastSwState)
    {
        if (swState == LOW)
            f();
    }
    lastSwState = swState;
}

#endif
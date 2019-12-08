# **The Snake Game** 🐍
## Description
>Snake is the name of a video game concept in which the player has to navigate a "snake" (an array of contiguous dots) towards "apples" (randomly placed dots) in order to increase it's size.
The game becomes more difficult as the snake consumes more apples since the increase in size also leads to an increase in the likelyhood of collision with ones tail. 
The end goal of the game is to increase the size of the snake to be equal to the number of display units of the screen.

## Controls
>The player will move through the menu using a joystick, and use it's button to select options. Once the `Start Game` option is pressed a timer will begin, indicating the number of seconds until the snake starts moving, in this time the player can quit back to the menu by clicking the button again. If the timer reaches the 0 mark, the game begins and the snake starts moving, in this state the button can be used to pause/play the game. Once the game starts the player controls the snake by moving the joystick up, down, left or right.

## Meeting the requirements
>- The score will be evaluated as being the number of apples eaten times the current level plus a bonus of half of the current score each time the snake passes a length of `1/2^n` of the matrix.
For example when the length of the snake reaches half of the number of leds on the matrix,the player will be awarded half of it's current score, and so on. 
>- After every 3 apples eaten the speed of the snake will be increased with a constant proportional to the level.
>- The player will have the option of choosing different starting level with each higher level having the snake reach higher and higher speeds.
>- The best score will automaticaly be updated and saved to permanent storage.

    

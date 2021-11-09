# ROCK PAPER SCISSORS    
 * @author  Chang Tu (ctu28)   Caleb Wenborn (cwe55)   
 * Team number : 422
 *

Welcome to the ROCK PAPER SCISSORS README.

## Prerequisites

To play ROCK PAPER SCISSORS you will need the following:

1. UCFK4 (UC Fun Kit 4)
2. Type B Mini USB cable
3. ROCK PAPER SCISSORS source code
4. Custom screen divider (optional)


## How to launch ROCK PAPER SCISSORS

1. Open terminal.
2. Navigate to the path of the ROCK PAPER SCISSORS source code.
2. Run command `make program`.

## Code explainations

The display.c function displays the rock-paper-scissors on UCFK, game.c is the main function of this project, show_display function show figures for each operation placed for paper, scissors and rock when words is 0, draw paper when the bitmap shape is 0,  draw scissors when the bitmap shape is 1 and draw rock when the bitmap shape is 2. Since the game played by two parties (both students have UCFK), send_choice and recieve_choice are the sender and the reciever, the fun-kit displays RECIEVING if the message has been received.  

the navigation switch has four directions changing choices, and you can also push the switch for confirm your submission. calculate_winner calculates the game outcome and returns the text message to be displayed. display_winner displays whether you win or lose or it's a draw, the beeper will have different sound for win and lose.






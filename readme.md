# Lights Out Solver
Lights Out is a game consisting of a grid of lights(usually 5x5). When the game starts, a random number or a stored pattern of these lights is switched on. Pressing any of the lights will toggle it and the adjacent lights. The goal of the puzzle is to switch all the lights off, preferably with as few button presses as possible.

This program in C helps you to figure the lights you need to toggle to switch all of them off, in the least number of turns.

You have to input the the lights' ON or OFF state as 1 or 0 respectively. Then the algorithm each cell toggle's state as a variable (which can be 1 or 0) and then solves multiple equations tp get the final toggle states. 

Note that if a cell is pressed twice it results to the same state as not pressed a single time(as there is no state 2, only 1 and 0), so this effectively gives you the minimum no of toggles required to get the end result.

Credits for the algorithm and for futher reading: https://www.keithschwarz.com/interesting/code/?dir=lights-out
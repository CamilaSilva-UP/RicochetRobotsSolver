# Ricochet Robots

Ricochet Robots is a board game by Alex Randolph. The goal of the game is to place one of the robots in its corresponding target (of the same color), in the fewest steps possible. The trick is that once a robot starts moving, it won't stop until it hits a wall or another robot. The player(s) have to find the sequence of moves, using the multiple robots, to reach the goal in the fewest steps possible. This is a digital recreation of the game, in which you will be facing a bot always capable of finding the most optimal solution! 

<img width="1201" height="1006" alt="image" src="https://github.com/user-attachments/assets/b4c18bad-55ca-4f33-ba86-a11fef75f2ec" />

## Installation

Clone this repository, and then use the provided Makefile to build the project:

```
git clone https://github.com/CamilaSilva-UP/RicochetRobotsSolver.git RicochetRobots
cd RicochetRobots
make
```

Then run the executable:

```
./Ricochet
```

## How to play

You can access the How to Play screen from the main menu of the game! But here are the general rules:
- At the start of the round, the game will tell which colored robot to get to its target
- You choose which robot to control from the menu on the right
- You can move the robot using the arrow keys. Be careful, as each move you do gets added to the move counter!
- When you reach the goal, it's the bot's turn. It will find and display the most optimal solution. If you were able to find the same solution, or one with the same amount of steps, you won the round!
- You can press the purple button on the menu to reset and reshuffle the board
- If you are stuck, or simply wish to see the optimal solution, you can press the "AI SOLVER" button:
  - If you didn't do any moves, it will display the optimal solution
  - If you already did some moves, it will display the optimal solution **from the current position**, and then display the most optimal solution from the beginning

![ricochet](https://github.com/user-attachments/assets/29c1957f-ef83-46a9-8b48-c702c61d5395)

Have fun!

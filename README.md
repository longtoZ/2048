<h1 align="center" style="font-size: 50px">2048 in C++</h1>

*This is a simple implementation of the popular game 2048 using C++, as my project in **Programming Techniques** subject. The game is played on a square grid, where the player combines tiles with the same number to create new tiles with higher numbers.*


## 1. Getting Started

To compile and run the game, follow these steps:

1. Clone the repository (or download the source code).
    ```shell
    git clone https://github.com/longtoZ/2048.git
    ```
2. Open a terminal or command prompt and navigate to the project directory.
3. Compile the code using a C++ compiler. For example, you can use the following command with `g++`:

    ```shell
    g++ -I ./core/headers/ ./core/*.cpp main.cpp -o 2048
    ```

4. Run the executable:

    ```shell
    2048.exe
    ```

## 2. How to Play

- Use the arrow keys (**up, down, left, right**) to move the tiles in the corresponding direction. More keys can be included in each menu.
- Tiles with the same number will merge into one tile with the sum of their values.
- After each move, a new tile with a value of 2 or 4 will appear on the board.
- The game ends when there are no more valid moves.

## 3. Features

- Expandable board size (4x4, 5x5,...).
- Infinite undo, redo while playing.
- Save game and continue playing at anytime.
- View your achievement on every game.
- Create account and join the global leaderboard.

## 4. Contributing

Contributions are welcome! If you have any ideas for improvements or bug fixes, feel free to submit a pull request.

## 5. Demo

Here are some screenshots of the game.

![](./img/1.png)
![](./img/2.png)
![](./img/3.png)
![](./img/4.png)
![](./img/5.png)
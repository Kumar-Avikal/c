#include <iostream>
#include <set>
#include <random>
#include <vector>
#include <conio.h>
#include <chrono>

using namespace std;

class Board
{
private:
    vector<vector<char>> grid;
    int score;
    int snakeLength;
    pair<int, int> headPosition;
    vector<pair<int, int>> path;
    char direction;
    int time = 90000000;

public:
    Board() : grid(20, vector<char>(20, ' ')), direction('d')
    {
        headPosition.first = 10;
        headPosition.second = 10;
        path.push_back(headPosition);
    };

    int randomNumber()
    {
        static set<int> generatedNumbers;

        if (generatedNumbers.size() == 19)
        {
            generatedNumbers.clear();
        }

        int randomNumber;
        do
        {
            randomNumber = rand() % 19 + 1;
        } while (generatedNumbers.count(randomNumber) > 0);

        generatedNumbers.insert(randomNumber);
        return randomNumber;
    }

    void generateFood()
    {
        int x = randomNumber();
        int y = randomNumber();
        grid[x][y] = '0';
    }

    void showBoard()
    {
        system("cls");
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                bool isSnake = false;
                for (auto &e : path)
                {
                    if (e.first == i && e.second == j)
                    {
                        isSnake = true;
                        break;
                    }
                }
                if (isSnake)
                {
                    cout << 'O';
                }
                else if (grid[i][j] == '0')
                {
                    cout << '0';
                }
                else
                {
                    cout << '.';
                }
            }
            cout << endl;
        }
    }

    void delay()
    {
        for (volatile int i = 0; i < time; ++i)
        {
        }
    }

    void updateSnake()
    {
        pair<int, int> newHead;
        switch (direction)
        {
        case 'u':
            newHead = {headPosition.first - 1, headPosition.second};
            break;
        case 'd':
            newHead = {headPosition.first + 1, headPosition.second};
            break;
        case 'l':
            newHead = {headPosition.first, headPosition.second - 1};
            break;
        case 'r':
            newHead = {headPosition.first, headPosition.second + 1};
            break;
        }

        // Check for collisions (including self-collision)
        if (newHead.first < 0 || newHead.first >= 20 || newHead.second < 0 || newHead.second >= 20)
        {
            gameOver();
        }

        for (size_t i = 1; i < path.size(); ++i)
        { // Check for self-collision
            if (newHead == path[i])
            {
                gameOver();
            }
        }

        headPosition = newHead;
        path.push_back(headPosition);

        if (grid[headPosition.first][headPosition.second] == '0')
        {
            score++;
            generateFood();
            time -= 1000000;
        }
        else
        {
            path.erase(path.begin());
        }
        grid[headPosition.first][headPosition.second] = '.';
    }

    void gameLoop()
    {
        while (true)
        {
            if (_kbhit())
            {
                char input = _getch();
                switch (input)
                {
                case 'w':
                    if (direction != 'd')
                    {
                        direction = 'u';
                    }
                    break;
                case 'a':
                    if (direction != 'r')
                    {
                        direction = 'l';
                    }
                    break;
                case 's':
                    if (direction != 'u')
                    {
                        direction = 'd';
                    }
                    break;
                case 'd':
                    if (direction != 'l')
                    {
                        direction = 'r';
                    }
                    break;
                }
            }
            updateSnake();
            showBoard();
            delay();
        }
    }

    void gameOver()
    {
        system("cls");
        cout << "Game Over!" << endl;
        cout << "Your Score: " << score << endl;
        exit(0);
    }
};

int main()
{
    Board board;
    board.generateFood();
    board.gameLoop();
    return 0;
}
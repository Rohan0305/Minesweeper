#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "Func.h"

using namespace std;

vector<vector<int> > Board(int w, int h, int mines)
{
    vector<vector<int> > board(h, vector<int>(w, 0));


    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> place(1, (w*h));

    vector<int> vecMines;

    vecMines.push_back(place(rng));
    int i = 0;

    vector<int>::iterator iter;

    int attempts = 0;
    const int maxAttempts = 1000; // Prevent infinite loop
    
    while (vecMines.size() < mines && attempts < maxAttempts)
    {
        int x = place(rng);
        if (find(vecMines.begin(), vecMines.end(), x) == vecMines.end())
        {
            vecMines.push_back(x);
        }
        attempts++;
    }
    
    // Ensure we have the correct number of mines
    if (vecMines.size() != mines)
    {
        // If we couldn't place enough mines randomly, fill the remaining spots
        for (int i = 1; i <= (w*h) && vecMines.size() < mines; i++)
        {
            if (find(vecMines.begin(), vecMines.end(), i) == vecMines.end())
            {
                vecMines.push_back(i);
            }
        }
    }


    int y;
    int x;

    for (int a = 0; a < vecMines.size(); ++a)
    {
        if (vecMines[a] % w == 0)
        {
            y = (vecMines[a] / w) - 1;
        }
        else
        {
            y = (vecMines[a] / w);
        }

        if (vecMines[a] % w == 0)
        {
            x = w - 1;
        }
        else
        {
            x = (vecMines[a] % w) - 1;
        }

        board[y][x] = 9;

    }

    return board;

}
vector<vector<int>> cornerBoard(int w, int h, vector<vector<int>>& board)
{
    // Top left corner
    int count = 0;
    if (board[0][0] == 0)
    {
        if (board[0][1] == 9)
        {
            count += 1;
        }

        if (board[1][0] == 9)
        {
            count += 1;
        }

        if (board[1][1] == 9)
        {
            count += 1;
        }

        board[0][0] = count;
    }

    // Top right corner
    count = 0;
    if (board[0][w-1] == 0)
    {
        if (board[0][w - 2] == 9)
        {
            count += 1;
        }

        if (board[1][w - 1] == 9)
        {
            count += 1;
        }

        if (board[1][w - 2] == 9)
        {
            count += 1;
        }

        board[0][w - 1] = count;
    }

    // Bottom left corner
    count = 0;
    if (board[h - 1][0] == 0)
    {
        if (board[h - 1][1] == 9)
        {
            count += 1;
        }

        if (board[h - 2][0] == 9)
        {
            count += 1;
        }

        if (board[h - 2][1] == 9)
        {
            count += 1;
        }

        board[h - 1][0] = count;
    }

    // Bottom right corner
    count = 0;
    if (board[h - 1][w - 1] == 0)
    {
        if (board[h - 1][w - 2] == 9)
        {
            count += 1;
        }

        if (board[h - 2][w - 1] == 9)
        {
            count += 1;
        }

        if (board[h - 2][w - 2] == 9)
        {
            count += 1;
        }

        board[h - 1][w - 1] = count;
    }
    return board;
}

vector<vector<int>> edgesBoard(int w, int h, vector<vector<int>>& board)
{
    // Top edge
    for (int i = 1; i < w - 1; ++i)
    {
        int count = 0;
        if (board[0][i] == 0)
        {
            if (board[0][i - 1] == 9)
            {
                count += 1;
            }

            if (board[0][i + 1] == 9)
            {
                count += 1;
            }

            if (board[1][i] == 9)
            {
                count += 1;
            }

            if (board[1][i - 1] == 9)
            {
                count += 1;
            }

            if (board[1][i + 1] == 9)
            {
                count += 1;
            }

            board[0][i] = count;
        }
    }

    // Bottom edge
    for (int i = 1; i < w - 1; ++i)
    {
        int count = 0;
        if (board[h - 1][i] == 0)
        {
            if (board[h - 1][i - 1] == 9)
            {
                count += 1;
            }

            if (board[h - 1][i + 1] == 9)
            {
                count += 1;
            }

            if (board[h - 2][i] == 9)
            {
                count += 1;
            }

            if (board[h - 2][i - 1] == 9)
            {
                count += 1;
            }

            if (board[h - 2][i + 1] == 9)
            {
                count += 1;
            }

            board[h - 1][i] = count;
        }
    }

    // Left edge
    for (int i = 1; i < h - 1; ++i)
    {
        int count = 0;
        if (board[i][0] == 0)
        {
            if (board[i - 1][0] == 9)
            {
                count += 1;
            }

            if (board[i + 1][0] == 9)
            {
                count += 1;
            }

            if (board[i][1] == 9)
            {
                count += 1;
            }

            if (board[i - 1][1] == 9)
            {
                count += 1;
            }

            if (board[i + 1][1] == 9)
            {
                count += 1;
            }

            board[i][0] = count;
        }
    }

    // Right edge
    for (int i = 1; i < h - 1; ++i)
    {
        int count = 0;
        if (board[i][w - 1] == 0)
        {
            if (board[i - 1][w - 1] == 9)
            {
                count += 1;
            }

            if (board[i + 1][w - 1] == 9)
            {
                count += 1;
            }

            if (board[i][w - 2] == 9)
            {
                count += 1;
            }

            if (board[i - 1][w - 2] == 9)
            {
                count += 1;
            }

            if (board[i + 1][w - 2] == 9)
            {
                count += 1;
            }

            board[i][w - 1] = count;
        }

    }
    return board;
}

vector<vector<int>> fullBoard(int w, int h, vector<vector<int>>& board)
{
    for (int i = 1; i < h - 1; ++i)
    {
        for (int j = 1; j < w - 1; ++j)
        {
            int count = 0;
            if (board[i][j] == 0)
            {
                if (board[i][j + 1] == 9)
                {
                    count += 1;
                }

                if (board[i][j - 1] == 9)
                {
                    count += 1;
                }

                if (board[i - 1][j] == 9)
                {
                    count += 1;
                }

                if (board[i + 1][j] == 9)
                {
                    count += 1;
                }

                if (board[i - 1][j - 1] == 9)
                {
                    count += 1;
                }

                if (board[i - 1][j + 1] == 9)
                {
                    count += 1;
                }

                if (board[i + 1][j - 1] == 9)
                {
                    count += 1;
                }

                if (board[i + 1][j + 1] == 9)
                {
                    count += 1;
                }

                board[i][j] = count;
            }
        }
    }

    return board;
}

int numIndex(vector<vector<int>>& board, int y, int x)
{
    if (board[y][x] == 1)
    {
        return 0;
    }
    else if (board[y][x] == 2)
    {
        return 1;
    }
    else if (board[y][x] == 3)
    {
        return 2;
    }
    else if (board[y][x] == 4)
    {
        return 3;
    }
    else if (board[y][x] == 5)
    {
        return 4;
    }
    else if (board[y][x] == 6)
    {
        return 5;
    }
    else if (board[y][x] == 7)
    {
        return 6;
    }
    else if (board[y][x] == 8)
    {
        return 7;
    }
}

bool checkNumBoard(vector<vector<int>>& board, int y, int x)
{
    if (board[y][x] > 0 && board[y][x] < 9)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void revealBlanks(vector<vector<int>>& dummyBoard, int y, int x)
{
    if (dummyBoard[y][x] == 0)
    {
        dummyBoard[y][x] = -1;
        for (int r = y - 1; r <= y + 1; r++)
        {
            for (int c = x - 1; c <= x + 1; c++)
            {
                if (r >= 0 && r < dummyBoard.size() && c >= 0 && c < dummyBoard[0].size() && dummyBoard[r][c] >= 0)
                {
                    revealBlanks(dummyBoard, r, c);
                }
            }
        }
    }
    else
    {
        dummyBoard[y][x] = -2;
    }
}

bool checkWin(vector<vector<int>>& flagBoard, int& flagTracker)
{
    // Check if all mines are correctly flagged and all non-mine tiles are revealed
    for (int a = 0; a < flagBoard.size(); ++a)
    {
        for (int b = 0; b < flagBoard[a].size(); ++b)
        {
            // If there's a mine (value 9) that isn't flagged (-1), player hasn't won yet
            if (flagBoard[a][b] == 9)
            {
                return false;
            }
            // If there's a non-mine tile (value > 0) that hasn't been revealed (-2), player hasn't won yet
            if (flagBoard[a][b] > 0 && flagBoard[a][b] != 9)
            {
                return false;
            }
        }
    }
    
    // All mines are flagged and all non-mine tiles are revealed, player wins!
    return true;
}

int getLeft(int flagTracker)
{
    int l = flagTracker / 10;
    return l;
}

int getRight(int flagTracker)
{
    int r = flagTracker % 10;
    return r;
}

int getLeft3(int flagTracker)
{
    int l = flagTracker % 10;
    l = flagTracker - l;
    int x = l % 100;
    l = x / 10;
    return l;
}

int getRight3(int flagTracker)
{
    int r = flagTracker % 10;
    return r;
}

int getL1(int flagTracker)
{
    int l1 = flagTracker / 100;
    return l1;
}
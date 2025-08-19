#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Func.h"
#include <sstream>

#include <random>

using namespace std;

int main()
{
    string filename = "config.cfg";
    ifstream configFile(filename);

    if (!configFile)
    {
        cerr << "Failed to open file " << filename << endl;
        return 1;
    }

    int widthMultiplier, heightMultiplier, mineCount;
    configFile >> widthMultiplier >> heightMultiplier >> mineCount;

    int actualWidth = widthMultiplier * 32;
    int actualHeight = heightMultiplier * 32 + 100;

    int tileCount = widthMultiplier * heightMultiplier;

    vector<vector<int>> board;
    board = Board(widthMultiplier, heightMultiplier, mineCount);
    board = cornerBoard(widthMultiplier, heightMultiplier, board);
    board = edgesBoard(widthMultiplier, heightMultiplier, board);
    board = fullBoard(widthMultiplier, heightMultiplier, board);
    vector<vector<int>> flagBoard = board;

    configFile.close();

    for (int i = 0; i < heightMultiplier; ++i)
    {
        for (int j = 0; j < widthMultiplier; ++j)
        {
            cout << board[i][j];
        }
        cout << endl;
    }

    // Verify the correct number of mines were placed
    int actualMineCount = 0;
    for (int i = 0; i < heightMultiplier; ++i)
    {
        for (int j = 0; j < widthMultiplier; ++j)
        {
            if (board[i][j] == 9)
            {
                actualMineCount++;
            }
        }
    }
    cout << "Mines placed: " << actualMineCount << " (requested: " << mineCount << ")" << endl;

    sf::RenderWindow window(sf::VideoMode(actualWidth, actualHeight), "Minesweeper");

    sf::Texture tile_hidden;
    if (!tile_hidden.loadFromFile("images/tile_hidden.png"))
    {
        cout << "Failed to open tile_hidden.png" << endl;
    }

    sf::Texture tile_revealed;
    if (!tile_revealed.loadFromFile("images/tile_revealed.png"))
    {
        cout << "Failed to open tile_revealed.png" << endl;
    }

    sf::Texture mineText;
    if (!mineText.loadFromFile("images/mine.png"))
    {
        cout << "Failed to open mine.png" << endl;
    }

    sf::Sprite tile_Rev;
    tile_Rev.setTexture(tile_revealed);

    sf::Sprite mine;
    mine.setTexture(mineText);

    sf::Sprite tile_Hid;
    tile_Hid.setTexture(tile_hidden);

    sf::RenderTexture rendText;
    rendText.create(tile_hidden.getSize().x, tile_hidden.getSize().y);
    rendText.draw(tile_Hid);
    rendText.draw(mine);
    rendText.display();
    sf::Texture comb(rendText.getTexture());

    sf::Texture tile1;
    if (!tile1.loadFromFile("images/number_1.png"))
    {
        cout << "Failed to open number_1.png" << endl;
    }

    sf::Texture tile2;
    if (!tile2.loadFromFile("images/number_2.png"))
    {
        cout << "Failed to open number_2.png" << endl;
    }

    sf::Texture tile3;
    if (!tile3.loadFromFile("images/number_3.png"))
    {
        cout << "Failed to open number_3.png" << endl;
    }

    sf::Texture tile4;
    if (!tile4.loadFromFile("images/number_4.png"))
    {
        cout << "Failed to open number_4.png" << endl;
    }

    sf::Texture tile5;
    if (!tile5.loadFromFile("images/number_5.png"))
    {
        cout << "Failed to open number_5.png" << endl;
    }

    sf::Texture tile6;
    if (!tile6.loadFromFile("images/number_6.png"))
    {
        cout << "Failed to open number_6.png" << endl;
    }

    sf::Texture tile7;
    if (!tile7.loadFromFile("images/number_7.png"))
    {
        cout << "Failed to open number_7.png" << endl;
    }

    sf::Texture tile8;
    if (!tile8.loadFromFile("images/number_8.png"))
    {
        cout << "Failed to open number_8.png" << endl;
    }

    sf::Texture flagText;
    if (!flagText.loadFromFile("images/flag.png"))
    {
        cout << "Failed to open flag.png" << endl;
    }

    sf::Texture digitsText;
    if (!digitsText.loadFromFile("images/digits.png"))
    {
        cout << "Failed to open digits.png" << endl;
    }


    vector<sf::Texture> numbers;
    numbers.push_back(tile1);
    numbers.push_back(tile2);
    numbers.push_back(tile3);
    numbers.push_back(tile4);
    numbers.push_back(tile5);
    numbers.push_back(tile6);
    numbers.push_back(tile7);
    numbers.push_back(tile8);

    vector<vector<sf::Sprite>> tiles;
    tiles.resize(heightMultiplier);

    for (int i = 0; i < heightMultiplier; i++)
    {
        tiles[i].resize(widthMultiplier);
        for (int j = 0; j < widthMultiplier; j++)
        {
            tiles[i][j].setTexture(tile_hidden);
            tiles[i][j].setPosition(j * 32, i * 32);
        }
    }

    vector<vector<sf::Sprite>> dummytiles = tiles;


    int x;
    int y;

    bool lose = false;
    bool win = false;

    sf::Sprite number;

    bool hidden = false;

   int flagTracker = mineCount;

   int debugClicks = 1;
   bool debug_ = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && lose == false && win == false)
                {
                    x = (event.mouseButton.x) / 32;
                    y = (event.mouseButton.y) / 32;
                    if (event.mouseButton.y < actualHeight - 100 && tiles[y][x].getTexture() != &flagText)
                    {
                        flagBoard[y][x] = -2;
                        win = checkWin(flagBoard, flagTracker);

                        cout << y << " " << x << endl;
                        if (x >= 0 && x < widthMultiplier && y >= 0 && y < heightMultiplier)
                        {
                            tiles[y][x].setTexture(tile_revealed);
                        }

                        if (board[y][x] != 0 && board[y][x] != 9)
                        {
                            int index = numIndex(board, y, x);
                            tiles[y][x].setTexture(numbers[index]);
                        }

                        if (board[y][x] == 9)
                        {
                            lose = true;
                            tiles[y][x].setTexture(mineText);
                        }

                        //code to make multiple blank tiles disappear
                        if (board[y][x] == 0)
                        {
                            vector<vector<int>> dummyBoard = board;
                            revealBlanks(dummyBoard, y, x);

                            for (int i = 0; i < dummyBoard.size(); ++i)
                            {
                                for (int j = 0; j < dummyBoard[i].size(); ++j)
                                {
                                    if (dummyBoard[i][j] == -1 && tiles[i][j].getTexture() != &flagText)
                                    {
                                        tiles[i][j].setTexture(tile_revealed);
                                        tiles[i][j].setPosition(j * 32, i * 32);
                                    }
                                    else if (dummyBoard[i][j] == -2 && tiles[i][j].getTexture() != &flagText)
                                    {
                                        int indexNumTexture = numIndex(board, i, j);
                                        tiles[i][j].setTexture(numbers[indexNumTexture]);
                                        tiles[i][j].setPosition(j * 32, i * 32);
                                    }
                                }
                            }
                        }
                    }

                    if ((event.mouseButton.x >= ((actualWidth / 2) + 96) && event.mouseButton.x <= ((actualWidth / 2) + 160)))
                    {
                        if ((event.mouseButton.y >= actualHeight - 100) && (event.mouseButton.y <= actualHeight - 36) && lose == false && win == false)
                        {
                            if (debugClicks % 2 == 1)
                            {
                                debug_ = true;
                            }
                            else
                            {
                                debug_ = false;
                            }

                            for (int a = 0; a < board.size(); ++a)
                            {
                                for (int b = 0; b < board[a].size(); ++b)
                                {
                                    if (board[a][b] == 9)
                                    {
                                        dummytiles[a][b].setTexture(mineText);
                                        dummytiles[a][b].setPosition(b * 32, a * 32);
                                    }
                                }
                            }
                            ++debugClicks;
                        }
                    }


                }



                if (event.mouseButton.button == sf::Mouse::Right && lose == false && win == false)
                {
                    cout << "Right" << endl;
                    if (event.mouseButton.y < actualHeight - 100)
                    {
                        x = (event.mouseButton.x) / 32;
                        y = (event.mouseButton.y) / 32;

                        if (tiles[y][x].getTexture() == &tile_hidden)
                        {
                            tiles[y][x].setTexture(flagText);
                            tiles[y][x].setPosition(x * 32, y * 32);
                            --flagTracker;

                            if (board[y][x] == 9)
                            {
                                flagBoard[y][x] = -1;
                            }

                            for (int a = 0; a < flagBoard.size(); ++a)
                            {
                                for (int b = 0; b < flagBoard[a].size(); ++b)
                                {
                                    for (int c = 0; c < 8; ++ c)
                                    {
                                        if (tiles[a][b].getTexture() == &tile_revealed || tiles[a][b].getTexture() == &numbers[c])
                                        {
                                            flagBoard[a][b] = -2;
                                        }
                                    }
                                }
                            }
                            for (int a = 0; a < flagBoard.size(); ++a)
                            {
                                for (int b = 0; b < flagBoard[a].size(); ++b)
                                {
                                    cout << flagBoard[a][b] << " ";
                                }
                                cout << endl;
                            }

                            win = checkWin(flagBoard, flagTracker);



                        }
                        else if (tiles[y][x].getTexture() == &flagText)
                        {
                            tiles[y][x].setTexture(tile_hidden);
                            tiles[y][x].setPosition(x * 32, y * 32);
                            ++flagTracker;
                            
                            // Reset the flagBoard value for this tile back to its original value
                            flagBoard[y][x] = board[y][x];
                        }
                        
                        // Update flagBoard for all revealed tiles
                        for (int a = 0; a < flagBoard.size(); ++a)
                        {
                            for (int b = 0; b < flagBoard[a].size(); ++b)
                            {
                                for (int c = 0; c < 8; ++ c)
                                {
                                    if (tiles[a][b].getTexture() == &tile_revealed || tiles[a][b].getTexture() == &numbers[c])
                                    {
                                        flagBoard[a][b] = -2;
                                    }
                                }
                            }
                        }

                        win = checkWin(flagBoard, flagTracker);


                    }
                }

                if ((event.mouseButton.x >= ((actualWidth / 2) - 32) && event.mouseButton.x <= ((actualWidth / 2) + 32)))
                {
                    if ((event.mouseButton.y >= actualHeight - 100) && (event.mouseButton.y <= actualHeight - 36))
                    {
                        board = Board(widthMultiplier, heightMultiplier, mineCount);
                        board = cornerBoard(widthMultiplier, heightMultiplier, board);
                        board = edgesBoard(widthMultiplier, heightMultiplier, board);
                        board = fullBoard(widthMultiplier, heightMultiplier, board);
                        flagBoard = board;
                        for (int i = 0; i < heightMultiplier; ++i)
                        {
                            for (int j = 0; j < widthMultiplier; ++j)
                            {
                                cout << board[i][j];
                                tiles[i][j].setTexture(tile_hidden);
                                tiles[i][j].setPosition(j * 32, i * 32);
                            }
                            cout << endl;
                        }
                        vector<vector<sf::Sprite>> dummytiles = tiles;
                        lose = false;
                        win = false;
                        flagTracker = mineCount;
                        bool hidden = false;
                    }
                }
               // cout << event.mouseButton.x << ", " << event.mouseButton.y << endl;
                if ((event.mouseButton.x >= ((actualWidth / 2) - 32) && event.mouseButton.x <= ((actualWidth / 2) + 32)))
                {
                    if ((event.mouseButton.y >= actualHeight - 100) && (event.mouseButton.y <= actualHeight - 36))
                    {
                        board = Board(widthMultiplier, heightMultiplier, mineCount);
                        board = cornerBoard(widthMultiplier, heightMultiplier, board);
                        board = edgesBoard(widthMultiplier, heightMultiplier, board);
                        board = fullBoard(widthMultiplier, heightMultiplier, board);
                        flagBoard = board;
                        for (int i = 0; i < heightMultiplier; ++i)
                        {
                            for (int j = 0; j < widthMultiplier; ++j)
                            {
                                cout << board[i][j];
                                tiles[i][j].setTexture(tile_hidden);
                                tiles[i][j].setPosition(j * 32, i * 32);
                            }
                            cout << endl;
                        }
                        vector<vector<sf::Sprite>> dummytiles = tiles;
                        lose = false;
                        win = false;
                        flagTracker = mineCount;
                        bool hidden = false;
                    }
                }
            }
        }

        window.clear();
        for (int i = 0; i < heightMultiplier; i++)
        {
            for (int j = 0; j < widthMultiplier; j++)
            {
                bool tileWithNum = checkNumBoard(board, i, j);
                for (int a = 0; a < 8; ++a)
                {
                    if (tiles[i][j].getTexture() == &numbers[a] && tileWithNum == true)
                    {
                        tile_Rev.setPosition(j * 32, i * 32);
                        window.draw(tile_Rev);
                    }
                }
                if (board[i][j] == 9 && tiles[i][j].getTexture() == &mineText)
                {
                    for (int ycor = 0; ycor < heightMultiplier; ++ycor)
                    {
                        for (int xcor = 0; xcor < widthMultiplier; ++xcor)
                        {
                            if (board[ycor][xcor] == 9)
                            {
                                tiles[ycor][xcor].setTexture(mineText);
                                tiles[ycor][xcor].setPosition(xcor * 32, ycor * 32);
                                tile_Rev.setPosition(xcor * 32, ycor * 32);
                                window.draw(tile_Rev);
                                window.draw(tiles[ycor][xcor]);

                            }
                        }
                    }

                }
                if (tiles[i][j].getTexture() == &flagText)
                {
                    tile_Hid.setPosition(j * 32, i * 32);
                    window.draw(tile_Hid);
                }

                if (debug_)
                {
                    for (int z = 0; z < heightMultiplier; z++)
                    {
                        for (int x = 0; x < widthMultiplier; x++)
                        {
                            if (board[z][x] == 9)
                            {
                                tiles[z][x].setTexture(comb);
                                tiles[z][x].setPosition(x * 32, z * 32);
                            }
                        }
                    }
                }
                window.draw(tiles[i][j]);
            }
        }



        //Draw black rectangle to fill bottom of window
        sf::RectangleShape bottomRect(sf::Vector2f(actualWidth, 100));
        bottomRect.setPosition(0, actualHeight - 100);
        bottomRect.setFillColor(sf::Color::White);
        window.draw(bottomRect);

        if (debug_)
        {
            for (int a = 0; a < board.size(); ++a)
            {
                for (int b = 0; b < board[a].size(); ++b)
                {
                    if (board[a][b] == 9)
                        window.draw(dummytiles[a][b]);
                }
            }
        }
        else
        {
            for (int a = 0; a < board.size(); ++a)
            {
                for (int b = 0; b < board[a].size(); ++b)
                {
                    if (board[a][b] == 9)
                    {
                        dummytiles[a][b].setTexture(tile_hidden);
                        dummytiles[a][b].setPosition(b * 32, a * 32);
                        window.draw(dummytiles[a][b]);
                    }

                    if (tiles[a][b].getTexture() == &flagText)
                    {
                        tiles[a][b].setPosition(b * 32, a * 32);
                        window.draw(tiles[a][b]);
                    }

                    if (tiles[a][b].getTexture() == &mineText)
                    {
                        tiles[a][b].setPosition(b * 32, a * 32);
                        window.draw(tiles[a][b]);
                    }

                }
            }
        }

        if(lose == false)
        {
            sf::Texture faceT;
            if (!faceT.loadFromFile("images/face_happy.png"))
            {
                cout << "Failed to open images/face_happy.png" << endl;
            }

            sf::Sprite face_;
            face_.setTexture(faceT);
            face_.setPosition((actualWidth / 2) - 32, (actualHeight - 100));
            window.draw(face_);
        }

        if (win == true && lose == false)
        {
            sf::Texture faceT;
            if (!faceT.loadFromFile("images/face_win.png"))
            {
                cout << "Failed to open images/face_win.png" << endl;
            }

            sf::Sprite face_;
            face_.setTexture(faceT);
            face_.setPosition((actualWidth / 2) - 32, (actualHeight - 100));
            window.draw(face_);
        }

        if (lose == true)
        {
            sf::Texture faceT;
            if (!faceT.loadFromFile("images/face_lose.png"))
            {
                cout << "Failed to open images/face_lose.png" << endl;
            }

            sf::Sprite face_;
            face_.setTexture(faceT);
            face_.setPosition((actualWidth / 2) - 32, (actualHeight - 100));
            window.draw(face_);
        }

        sf::Texture debugText;
        if (!debugText.loadFromFile("images/debug.png"))
        {
            cout << "Failed to open images/debug.png" << endl;
        }

        sf::Sprite debug;
        debug.setTexture(debugText);
        debug.setPosition((actualWidth / 2)  + 96, (actualHeight - 100));
        window.draw(debug);

        if (flagTracker >= 0)
        {
            if (flagTracker >= 0 && flagTracker < 100)
            {
                sf::Texture lnText;
                if (!lnText.loadFromFile("images/digits.png"))
                {
                    cout << "Failed to open digits.png" << endl;
                }

                int l = getLeft(flagTracker);

                sf::Sprite leftNum(lnText, sf::IntRect(0 + (l * 21), 0, 20, 30));
                leftNum.setPosition(32, actualHeight - 100);

                window.draw(leftNum);

                sf::Texture rnText;
                if (!rnText.loadFromFile("images/digits.png"))
                {
                    cout << "Failed to open digits.png" << endl;
                }

                int r = getRight(flagTracker);

                sf::Sprite rightNum(lnText, sf::IntRect(0 + (r * 21), 0, 20, 30));
                rightNum.setPosition(50, actualHeight - 100);

                window.draw(rightNum);

                sf::Texture l1Text;
                if (!l1Text.loadFromFile("images/digits.png"))
                {
                    cout << "Failed to open digits.png" << endl;
                }

                int l1_ = getL1(flagTracker);

                sf::Sprite l1(l1Text, sf::IntRect(0 + (l1_ * 21), 0, 25, 30));
                l1.setPosition(10, actualHeight - 100);

                window.draw(l1);
            }
            if (flagTracker >= 100)
            {
                sf::Texture lnText;
                if (!lnText.loadFromFile("images/digits.png"))
                {
                    cout << "Failed to open digits.png" << endl;
                }

                int l = getLeft3(flagTracker);

                sf::Sprite leftNum(lnText, sf::IntRect(0 + (l * 21), 0, 20, 30));
                leftNum.setPosition(32, actualHeight - 100);

                window.draw(leftNum);

                sf::Texture rnText;
                if (!rnText.loadFromFile("images/digits.png"))
                {
                    cout << "Failed to open digits.png" << endl;
                }

                int r = getRight3(flagTracker);

                sf::Sprite rightNum(lnText, sf::IntRect(0 + (r * 21), 0, 20, 30));
                rightNum.setPosition(50, actualHeight - 100);

                window.draw(rightNum);

                sf::Texture l1Text;
                if (!l1Text.loadFromFile("images/digits.png"))
                {
                    cout << "Failed to open digits.png" << endl;
                }

                int l1_ = getL1(flagTracker);

                sf::Sprite l1(l1Text, sf::IntRect(0 + (l1_ * 21), 0, 25, 30));
                l1.setPosition(10, actualHeight - 100);

                window.draw(l1);
            }
        }

        if (flagTracker < 0)
        {
            sf::Texture negText;
            if (!negText.loadFromFile("images/digits.png"))
            {
                cout << "Failed to open digits.png" << endl;
            }
            sf::Sprite negSign(negText, sf::IntRect(210, 0, 20, 30));
            negSign.setPosition(13, actualHeight - 100);

            window.draw(negSign);

            sf::Texture lnText;
            if (!lnText.loadFromFile("images/digits.png"))
            {
                cout << "Failed to open digits.png" << endl;
            }

            int l = getLeft(-1 * flagTracker);

            sf::Sprite leftNum(lnText, sf::IntRect(0 + (l * 21), 0, 20, 30));
            leftNum.setPosition(32, actualHeight - 100);

            window.draw(leftNum);

            sf::Texture rnText;
            if (!rnText.loadFromFile("images/digits.png"))
            {
                cout << "Failed to open digits.png" << endl;
            }

            int r = getRight(-1 * flagTracker);

            sf::Sprite rightNum(lnText, sf::IntRect(0 + (r * 21), 0, 20, 30));
            rightNum.setPosition(50, actualHeight - 100);

            window.draw(rightNum);
        }



        window.display();
    }

    return 0;
}




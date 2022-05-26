#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>

void showArrayInt(std::vector<std::vector<int>> &vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = 0; j < vector[i].size(); j++)
        {
            if (vector[i][j] == 0)
                std::cout << " ";
            else if (vector[i][j] == 1)
                std::cout << "X";
            else if (vector[i][j] == 2)
                std::cout << "O";
            else if (vector[i][j] == 3)
                std::cout << "*";
            if (j % 3 == 0)
                std::cout << "|";
            else if (j % 3 == 1)
                std::cout << "|";
        }
        std::cout << "\n";
    }
}

void ClearScreen() //Some magic Microsoft function to clear console
{
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR)' ',
            cellCount,
            homeCoords,
            &count))
        return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count))
        return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

int winLoseGame(int currentCharInt, std::vector<std::vector<int>> &vector) //Checking the board for any winner and returning who won
{
    std::vector<int> tempTab;

    //Any row is the same
    for (int i = 0; i < 3; i++)
    {
        tempTab = {0, 0, 0};
        for (int j = 0; j < 3; j++)
        {
            tempTab[j] = vector[i][j];
        }
        if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 1)
            return 1;
        else if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 2)
            return 2;
    }

    //Any column is the same
    for (int i = 0; i < 3; i++)
    {
        tempTab = {0, 0, 0};
        for (int j = 0; j < 3; j++)
        {
            tempTab[j] = vector[j][i];
        }
        if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 1)
            return 1;
        else if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 2)
            return 2;
    }

    //First diagonal is same
    for (int i = 0; i < 2; i++)
    {
        tempTab = {0, 0, 0};
        for (int j = 0; j < 3; j++)
        {
            tempTab[j] = vector[j][j];
        }
        if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 1)
            return 1;
        else if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 2)
            return 2;
    }

    int X = 0, Y = 2;
    //Second diagonal is same
    tempTab = {0, 0, 0};
    while (X <= 2 && Y >= 0)
    {
        tempTab[X] = vector[X][Y];
        X++;
        Y--;
    }
    if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 1)
        return 1;
    else if (std::count(std::begin(tempTab), std::end(tempTab), tempTab.front()) == tempTab.size() && tempTab[0] == 2)
        return 2;

    //No one won, we continue
    return 0;
}

int main() //Main function
{
    std::vector<std::vector<int>> logicPosArray = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};

    int logicPosX = 1,
        logicPosY = 1,
        currentCharInt = 0,
        currentVisualPos = 7,
        prevPosX = 1,
        prevPosY = 1,
        movesAmount = 9;

    bool movPossible = true,
         noQuit = true;
    
    ClearScreen();
    std::cout << "Press Q to quit\n";

    logicPosArray[logicPosX][logicPosY] = 3;

    showArrayInt(logicPosArray);

    currentCharInt = 1;

    do
    {
        /*
           Field
            |*| 
            | | 
            | | 
        */

        if (GetAsyncKeyState(0x51) & 1) //Read key Q - in this usage, we read key toggle down
        {
            noQuit = false;
            ClearScreen();
        }

        if (GetAsyncKeyState(0x41) & 1) //Read key A - in this usage, we read key toggle down
        {
            if (logicPosY != 0)
            {
                
                prevPosY = logicPosY;
                logicPosY -= 1;
                if (logicPosArray[logicPosX][prevPosY] != 1 && logicPosArray[logicPosX][prevPosY] != 2)
                    logicPosArray[logicPosX][prevPosY] = 0;
                if (logicPosArray[logicPosX][logicPosY] != 1 && logicPosArray[logicPosX][logicPosY] != 2)
                    logicPosArray[logicPosX][logicPosY] = 3;
                ClearScreen();
                if(currentCharInt == 1)
                    std::cout << "Current player: X\n";
                else if(currentCharInt == 2)
                    std::cout << "Current player: O\n";
                showArrayInt(logicPosArray);
            }
        }

        if (GetAsyncKeyState(0x57) & 1) //Read key W - in this usage, we read key toggle down
        {
            if (logicPosX != 0)
            {
                prevPosX = logicPosX;
                logicPosX -= 1;
                if (logicPosArray[prevPosX][logicPosY] != 1 && logicPosArray[prevPosX][logicPosY] != 2)
                    logicPosArray[prevPosX][logicPosY] = 0;
                if (logicPosArray[logicPosX][logicPosY] != 1 && logicPosArray[logicPosX][logicPosY] != 2)
                    logicPosArray[logicPosX][logicPosY] = 3;
                ClearScreen();
                if(currentCharInt == 1)
                    std::cout << "Current player: X\n";
                else if(currentCharInt == 2)
                    std::cout << "Current player: O\n";
                showArrayInt(logicPosArray);
            }
        }

        if (GetAsyncKeyState(0x53) & 1) //Read key S - in this usage, we read key toggle down
        {
            if (logicPosX != 2)
            {
                prevPosX = logicPosX;
                logicPosX += 1;
                if (logicPosArray[prevPosX][logicPosY] != 1 && logicPosArray[prevPosX][logicPosY] != 2)
                    logicPosArray[prevPosX][logicPosY] = 0;
                if (logicPosArray[logicPosX][logicPosY] != 1 && logicPosArray[logicPosX][logicPosY] != 2)
                    logicPosArray[logicPosX][logicPosY] = 3;
                ClearScreen();
                if(currentCharInt == 1)
                    std::cout << "Current player: X\n";
                else if(currentCharInt == 2)
                    std::cout << "Current player: O\n";
                showArrayInt(logicPosArray);
            }
        }

        if (GetAsyncKeyState(0x44) & 1) //Read key D - in this usage, we read key toggle down
        {
            if (logicPosY != 2)
            {
                prevPosY = logicPosY;
                logicPosY += 1;
                if (logicPosArray[logicPosX][prevPosY] != 1 && logicPosArray[logicPosX][prevPosY] != 2)
                    logicPosArray[logicPosX][prevPosY] = 0;
                if (logicPosArray[logicPosX][logicPosY] != 1 && logicPosArray[logicPosX][logicPosY] != 2)
                    logicPosArray[logicPosX][logicPosY] = 3;
                ClearScreen();
                if(currentCharInt == 1)
                    std::cout << "Current player: X\n";
                else if(currentCharInt == 2)
                    std::cout << "Current player: O\n";
                showArrayInt(logicPosArray);
            }
        }

        if (GetAsyncKeyState(0x46) & 1) //Read key F - in this usage, we read key toggle down
        {
            ClearScreen();
            if (movesAmount > 0)
            {
                //Checking what character we are using and if the field is occupied
                if (currentCharInt == 1 && logicPosArray[logicPosX][logicPosY] != 1 && logicPosArray[logicPosX][logicPosY] != 2)
                {
                    std::cout << "Current player: X\n";
                    logicPosArray[logicPosX][logicPosY] = currentCharInt; //Setting the character on the empty field
                    if (winLoseGame(currentCharInt, logicPosArray) == 1) //Checking for win condition at this stage
                    {
                        ClearScreen(); //Using to clear console
                        std::cout << "X has won!\n";
                        showArrayInt(logicPosArray);
                        noQuit = false; //If there is a winner, the program exits the do while loop, thus ending the program
                    }
                    else //If not we decrease number of moves and change the character from 'X' to 'O'
                    {
                        ClearScreen();
                        std::cout << "Current player: O\n";
                        movesAmount--;
                        currentCharInt = 2;

                        showArrayInt(logicPosArray);
                    }
                }

                //Checking what character we are using and if the field is occupied
                else if (currentCharInt == 2 && logicPosArray[logicPosX][logicPosY] != 1 && logicPosArray[logicPosX][logicPosY] != 2) 
                {
                    std::cout << "Current player: O\n";
                    logicPosArray[logicPosX][logicPosY] = currentCharInt; //Setting the character on the empty field
                    if (winLoseGame(currentCharInt, logicPosArray) == 2) //Checking for win condition at this stage
                    {
                        ClearScreen(); //Using to clear console
                        std::cout << "O has won!\n";
                        showArrayInt(logicPosArray);
                        noQuit = false; //If there is a winner, the program exits the do while loop, thus ending the program
                    }
                    else //If not we decrease number of moves and change the character from 'O' to 'X'
                    {
                        ClearScreen();
                        std::cout << "Current player: X\n";
                        movesAmount--;
                        currentCharInt = 1;
                        showArrayInt(logicPosArray);
                    }
                }
                else
                {
                    std::cout << "Field already occupied!\n";
                    showArrayInt(logicPosArray);
                }
            }
            else //We have no more moves to make, that would make for a Tie
            {
                std::cout << "End of moves! No player has won.\n";
                showArrayInt(logicPosArray);
                noQuit = false;
            }
        }
    } while (noQuit);
}
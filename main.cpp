#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
using namespace std;

// Global variables for Pac-Man and ghost positions
int pacmanX = 13;
int pacmanY = 23;
int ghostX = 12;
int ghostY = 13;
char input = 'd';

string yellow = "\033[33m";
string blue = "\033[34m";
string reset = "\033[0m";

struct xy {
    int x, y;
};


void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}


// Map definition
char mapp[31][29] = {
        {'3','2','2','2','2','2','2','2','2','2','2','2','2','4','3','2','2','2','2','2','2','2','2','2','2','2','2','4'}, //0
        {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'}, //1
        {'1',' ','3','2','2','4',' ','3','2','2','2','4',' ','1','1',' ','3','2','2','2','4',' ','3','2','2','4',' ','1'}, //2
        {'1',' ','1','0','0','1',' ','1','0','0','0','1',' ','1','1',' ','1','0','0','0','1',' ','1','0','0','1',' ','1'}, //3
        {'1',' ','5','2','2','6',' ','5','2','2','2','6',' ','5','6',' ','5','2','2','2','6',' ','5','2','2','6',' ','1'}, //4
        {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'}, //5
        {'1',' ','3','2','2','4',' ','3','4',' ','3','2','2','2','2','2','2','4',' ','3','4',' ','3','2','2','4',' ','1'}, //6
        {'1',' ','5','2','2','6',' ','1','1',' ','5','2','2','4','3','2','2','6',' ','1','1',' ','5','2','2','6',' ','1'}, //7
        {'1',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ','1'}, //8
        {'5','2','2','2','2','4',' ','1','5','2','2','4','0','5','6','0','3','2','2','6','1',' ','3','2','2','2','2','6'}, //9
        {' ',' ',' ',' ',' ','1',' ','1','3','2','2','6','0','0','0','0','5','2','2','4','1',' ','1',' ',' ',' ',' ',' '}, //10
        {' ',' ',' ',' ',' ','1',' ','1','1','0','0','0','0','0','0','0','0','0','0','1','1',' ','1',' ',' ',' ',' ',' '}, //11
        {' ',' ',' ',' ',' ','1',' ','1','1','0','3','2','2','0','0','2','2','4','0','1','1',' ','1',' ',' ',' ',' ',' '}, //12
        {'2','2','2','2','2','6',' ','5','6','0','1','0','0','0','0','0','0','1','0','5','6',' ','5','2','2','2','2','2'}, //13
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','0','1','0','0','0','0','0','0','1','0',' ',' ',' ',' ',' ',' ',' ',' ',' '}, //14
        {'2','2','2','2','2','4',' ','3','4','0','1','0','0','0','0','0','0','1','0','3','4',' ','3','2','2','2','2','2'}, //15
        {' ',' ',' ',' ',' ','1',' ','1','1','0','5','2','2','2','2','2','2','6','0','1','1',' ','1',' ',' ',' ',' ',' '}, //16
        {' ',' ',' ',' ',' ','1',' ','1','1','0','0','0','0','0','0','0','0','0','0','1','1',' ','1',' ',' ',' ',' ',' '}, //17
        {' ',' ',' ',' ',' ','1',' ','1','1','0','3','2','2','2','2','2','2','4','0','1','1',' ','1',' ',' ',' ',' ',' '}, //18
        {'3','2','2','2','2','6',' ','5','6','0','5','2','2','4','3','2','2','6','0','5','6',' ','5','2','2','2','2','4'}, //19
        {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'}, //20
        {'1',' ','3','2','2','4',' ','3','2','2','2','4',' ','1','1',' ','3','2','2','2','4',' ','3','2','2','4',' ','1'}, //21
        {'1',' ','5','2','4','1',' ','5','2','2','2','6',' ','5','6',' ','5','2','2','2','6',' ','1','3','2','6',' ','1'}, //22
        {'1',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ','1'}, //23
        {'5','2','4',' ','1','1',' ','3','4',' ','3','2','2','2','2','2','2','4',' ','3','4',' ','1','1',' ','3','2','6'}, //24
        {'3','2','6',' ','5','6',' ','1','1',' ','5','2','2','4','3','2','2','6',' ','1','1',' ','5','6',' ','5','2','4'}, //25
        {'1',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ','1'}, //26
        {'1',' ','3','2','2','2','2','6','5','2','2','4',' ','1','1',' ','3','2','2','6','5','2','2','2','2','4',' ','1'}, //27
        {'1',' ','5','2','2','2','2','2','2','2','2','6',' ','5','6',' ','5','2','2','2','2','2','2','2','2','6',' ','1'}, //28
        {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'}, //29
        {'5','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','6'} //30
    };

void printMap(int pacmanX, int pacmanY, int ghostX, int ghostY) {
    for (int i = 0; i < 31; ++i) {
        for (int j = 0; j < 29; ++j) {
            if (i == pacmanY && j == pacmanX) {
                cout << 'P'; // Display Pac-Man
            } else if (i == ghostY && j == ghostX) {
                cout << 'W'; // Display the ghost
            } else if (mapp[i][j] == '1')
                cout << (char)186;
            else if (mapp[i][j] == '2')
                cout << (char)205;
            else if (mapp[i][j] == '3')
                cout << (char)201;
            else if (mapp[i][j] == '4')
                cout << (char)187;
            else if (mapp[i][j] == '5')
                cout << (char)200;
            else if (mapp[i][j] == '6')
                cout << (char)188;
            else if (mapp[i][j] == ' ')
                cout << ".";
            else if (mapp[i][j] == '0')
                cout << " ";
        }
        cout << endl;
    }
}

void move_pacman() {

    if(kbhit())
    input = _getch();

    switch (input ) {
        case 'w':
        case 'W':
            if (pacmanY > 0 && mapp[pacmanY - 1][pacmanX] == ' ') {
                pacmanY--;
            }
            break;
        case 's':
        case 'S':
            if (pacmanY < 30 && mapp[pacmanY + 1][pacmanX] == ' ') {
                pacmanY++;
            }
            break;
        case 'a':
        case 'A':
            if (pacmanX > 0 && mapp[pacmanY][pacmanX - 1] == ' ') {
                pacmanX--;
            }
            break;
        case 'd':
        case 'D':
            if (pacmanX < 28 && mapp[pacmanY][pacmanX + 1] == ' ') {
                pacmanX++;
            }
            break;
        case 'q':
        case 'Q':
            exit(0); // Quit the game
    }

}

void move_ghost() {
    int lastDirection = -1; // Variable to store the last direction moved
    int direction = rand() % 4; // Randomly choose a direction

    // Check for valid moves and avoid repeating the last move
    for (int i = 0; i < 4; ++i) {
        direction = (direction + 1) % 4; // Cycle through directions
        switch (direction) {
            case 0: // Move up
                if (ghostY > 0 && mapp[ghostY - 1][ghostX] == ' ') {
                    ghostY--;
                    lastDirection = 0;
                    return; // Exit after moving
                }
                break;
            case 1: // Move down
                if (ghostY < 30 && mapp[ghostY + 1][ghostX] == ' ') {
                    ghostY++;
                    lastDirection = 1;
                    return; // Exit after moving
                }
                break;
            case 2: // Move left
                if (ghostX > 0 && mapp[ghostY][ghostX - 1] == ' ') {
                    ghostX--;
                    lastDirection = 2;
                    return; // Exit after moving
                }
                break;
            case 3: // Move right
                if (ghostX < 28 && mapp[ghostY][ghostX + 1] == ' ') {
                    ghostX++;
                    lastDirection = 3;
                    return; // Exit after moving
                }
                break;
        }
    }
}

int menu() {
    xy men[4];
    men[1] = {50, 10};
    men[2] = {50, 12};
    men[3] = {50, 14};

    int cursor = 1;
    bool end = false;

    while (!end) {
        system("cls");
        const int FRAME_HEIGHT = 30;
        const int FRAME_WIDTH = 120;

        char v = 186; // vertical
        char h = 205; // horizontal
        char ka = 201; // kiri atas
        char kb = 200; // kiri bawah
        char bk = 188; // bawah kanan
        char ak = 187; // atas kanan

        // border batasan
        for (int i = 0; i < FRAME_HEIGHT; i++) {
            for (int j = 0; j < FRAME_WIDTH; j++) {
                if (i == 0 && j == 0)
                    cout << ka;
                else if (i == 0 && j == FRAME_WIDTH - 1)
                    cout << ak;
                else if (i == FRAME_HEIGHT - 1 && j == 0)
                    cout << kb;
                else if (i == FRAME_HEIGHT - 1 && j == FRAME_WIDTH - 1)
                    cout << bk;
                else if (i == 0 || i == FRAME_HEIGHT - 1)
                    cout << h;
                else if (j == 0 || j == FRAME_WIDTH - 1)
                    cout << v;
                else
                    cout << " ";
            }
            cout << endl;
        }

        // Welcome sign
        gotoxy(48, 4);
        cout << ka << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << ak;
        gotoxy(48, 5);
        cout << v << " WELCOME TO PACMAN " << v;
        gotoxy(48, 6);
        cout << kb << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << bk;

        // Menu
        for (int i = 1; i <= 3; i++) {
            if (cursor == i) {
                gotoxy(men[i].x, men[i].y);
                cout << "> " << (i == 1 ? "PLAY GAME" : i == 2 ? "LEADERBOARD" : "EXIT");
            } else {
                gotoxy(men[i].x-2 , men[i].y);
                cout << "  " << (i == 1 ? "PLAY GAME" : i == 2 ? "LEADERBOARD" : "EXIT");
            }
        }

        // input
        char in = _getch();

        if (in == 'W' || in == 'w') {
            if (cursor > 1) cursor--;
        } else if (in == 'S' || in == 's') {
            if (cursor < 3) cursor++;
        } else if (in == '\r') { // Enter
            switch (cursor) {
                case 1:
                    system("cls");
                    return 1;
                    end = true;
                case 2:
                    system("cls");
                    return 2;
                    end = true;
                case 3:
                    system("cls");
                    return 3;
                    end = true;
            }
        }
    }
}


void play(int &score)
{
    //cout << "PACMAN" << endl;
    //cout << "Score : " << score << endl;
    while(true)
    {
        system("cls"); // Clear the console
        printMap(pacmanX, pacmanY, ghostX, ghostY); // Draw the map with Pac-Man and the ghost
        move_pacman(); // Handle Pac-Man's movement
        move_ghost(); // Handle ghost's movement
        Sleep(100); // Pause for a short duration to control the speed of movement

    }
    //system("pause");
}


int main(){
    srand((time(0))); // Seed for random number generation
    int pil;
    do{
            int score=0;
            pil = menu();
            switch(pil)
            {
            //play
            case 1 :
                play(score);
                break;

            //leaderboard
            case 2:
                break;
            }

    }while(pil!=3);

    system("cls");
    cout << "Thank You For Playing" ; Sleep(100);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    cout << endl << endl;
    return 0;
}

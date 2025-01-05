#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct xy {
    int x, y;
};


void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}


char map [28][25]={
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#',' ','#','#','#','#',' ','#'},
    {'#',' ','#',' ',' ','#',' ','#',' ',' ',' ','#',' ','#','#',' ','#',' ',' ',' ','#',' ','#',' ',' ','#',' ','#'},
    {'#',' ','#','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#',' ','#','#','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#'},
    {'#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ','#',' ','#','#','#','#','#',' ',' ',' ',' ','#','#','#','#','#',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ',' '},
    {'#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ',' ',' ',' ','#'},
    {' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#',' ','#','#','#','#',' ','#'},
    {'#',' ','#','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#',' ','#','#','#','#',' ','#'},
    {'#',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ','#'},
    {'#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#'},
    {'#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#'},
    {'#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
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


int main{

}
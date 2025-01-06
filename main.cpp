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


char maps [31][29]={
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
};

void printMap() {

    char mapp [31][29]={
    {'3','2','2','2','2','2','2','2','2','2','2','2','2','4','3','2','2','2','2','2','2','2','2','2','2','2','2','4'},
    {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
    {'1',' ','3','2','2','4',' ','3','2','2','2','4',' ','1','1',' ','3','2','2','2','4',' ','3','2','2','4',' ','1'},
    {'1',' ','1','0','0','1',' ','1','0','0','0','1',' ','1','1',' ','1','0','0','0','1',' ','1','0','0','1',' ','1'},
    {'1',' ','5','2','2','6',' ','5','2','2','2','6',' ','5','6',' ','5','2','2','2','6',' ','5','2','2','6',' ','1'},
    {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
    {'1',' ','3','2','2','4',' ','3','4',' ','3','2','2','2','2','2','2','4',' ','3','4',' ','3','2','2','4',' ','1'},
    {'1',' ','5','2','2','6',' ','1','1',' ','5','2','2','4','3','2','2','6',' ','1','1',' ','5','2','2','6',' ','1'},
    {'1',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ','1'},
    {'5','2','2','2','2','4',' ','1','5','2','2','4',' ','5','6',' ','3','2','2','6','1',' ','3','2','2','2','2','6'},
    {'0','0','0','0','0','1',' ','1','3','2','2','6',' ',' ',' ',' ','5','2','2','4','1',' ','1','0','0','0','0','0'},
    {'0','0','0','0','0','1',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ','1','0','0','0','0','0'},
    {'0','0','0','0','0','1',' ','1','1',' ','3','2','2','2','2','2','2','4',' ','1','1',' ','1','0','0','0','0','0'},
    {'2','2','2','2','2','6',' ','5','6',' ','1',' ',' ',' ',' ',' ',' ','1',' ','5','6',' ','5','2','2','2','2','2'},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',' ',' ',' ',' ',' ',' ','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'2','2','2','2','2','4',' ','3','4',' ','1',' ',' ',' ',' ',' ',' ','1',' ','3','4',' ','3','2','2','2','2','2'},
    {'0','0','0','0','0','1',' ','1','1',' ','5','2','2','2','2','2','2','6',' ','1','1',' ','1','0','0','0','0','0'},
    {'0','0','0','0','0','1',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ','1','0','0','0','0','0'},
    {'0','0','0','0','0','1',' ','1','1',' ','3','2','2','2','2','2','2','4',' ','1','1',' ','1','0','0','0','0','0'},
    {'3','2','2','2','2','6',' ','5','6',' ','5','2','2','4','3','2','2','6',' ','5','6',' ','5','2','2','2','2','4'},
    {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
    {'1',' ','3','2','2','4',' ','3','2','2','2','4',' ','1','1',' ','3','2','2','2','4',' ','3','2','2','4',' ','1'},
    {'1',' ','5','2','4','1',' ','5','2','2','2','6',' ','5','6',' ','5','2','2','2','6',' ','1','3','2','6',' ','1'},
    {'1',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ','1'},
    {'5','2','4',' ','1','1',' ','3','4',' ','3','2','2','2','2','2','2','4',' ','3','4',' ','1','1',' ','3','2','6'},
    {'3','2','6',' ','5','6',' ','1','1',' ','5','2','2','4','3','2','2','6',' ','1','1',' ','5','6',' ','5','2','4'},
    {'1',' ',' ',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ','1','1',' ',' ',' ',' ',' ',' ','1'},
    {'1',' ','3','2','2','2','2','6','5','2','2','4',' ','1','1',' ','3','2','2','6','5','2','2','2','2','4',' ','1'},
    {'1',' ','5','2','2','2','2','2','2','2','2','6',' ','5','6',' ','5','2','2','2','2','2','2','2','2','6',' ','1'},
    {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
    {'5','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','6'}
};
    cout << blue;
    gotoxy(40,0);
    for (int i = 0; i < 31; ++i) {
        for (int j = 0; j < 29; ++j) {
            if(mapp[i][j] == '1')
                cout << (char)186;
            else if(mapp[i][j] == '2')
                cout << (char)205;
            else if(mapp[i][j] == '3')
                cout << (char)201;
            else if(mapp[i][j] == '4')
                cout << (char)187;
            else if(mapp[i][j] == '5')
                cout << (char)200;
            else if(mapp[i][j] == '6')
                cout << (char)188;
            else if(mapp[i][j] == '0')
                cout << ' ';
            else
                cout << mapp[i][j];
               }
            gotoxy(40,i+1);
    }
    cout << reset;
    cout << endl;
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
    cout << "PACMAN" << endl;
    cout << "Score : " << score << endl;
    printMap();
    system("pause");
}

int main(){
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

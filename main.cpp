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


string yellow = "\033[33m";
string blue = "\033[34m";
string reset = "\033[0m";

struct xy {
    int x, y;
};

struct player {
    int x, y;
    char shape;
};


void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

char mapp[32][29];
 Map initialize
char mapp_ori[32][29] = {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
       {'3','2','2','2','2','2','2','2','2','2','2','2','2','4','3','2','2','2','2','2','2','2','2','2','2','2','2','4'}, //0
        {'1','p','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','p','1'}, //1
        {'1','0','3','2','2','4','0','3','2','2','2','4','0','1','1','0','3','2','2','2','4','0','3','2','2','4','0','1'}, //2
        {'1','0','1',' ',' ','1','0','1',' ',' ',' ','1','0','1','1','0','1',' ',' ',' ','1','0','1',' ',' ','1','0','1'}, //3
        {'1','0','5','2','2','6','0','5','2','2','2','6','0','5','6','0','5','2','2','2','6','0','5','2','2','6','0','1'}, //4
        {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'}, //5
        {'1','0','3','2','2','4','0','3','4','0','3','2','2','2','2','2','2','4','0','3','4','0','3','2','2','4','0','1'}, //6
        {'1','0','5','2','2','6','0','1','1','0','5','2','2','4','3','2','2','6','0','1','1','0','5','2','2','6','0','1'}, //7
        {'1','0','0','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','0','0','1'}, //8
        {'5','2','2','2','2','4','0','1','5','2','2','4','0','5','6','0','3','2','2','6','1','0','3','2','2','2','2','6'}, //9
        {' ',' ',' ',' ',' ','1','0','1','3','2','2','6','0','0','0','0','5','2','2','4','1','0','1',' ',' ',' ',' ',' '}, //10
        {' ',' ',' ',' ',' ','1','0','1','1','0','0','0','0','0','0','0','0','0','0','1','1','0','1',' ',' ',' ',' ',' '}, //11
        {' ',' ',' ',' ',' ','1','0','1','1','0','3','2','2','9','9','2','2','4','0','1','1','0','1',' ',' ',' ',' ',' '}, //12
        {'2','2','2','2','2','6','0','5','6','0','1',' ',' ',' ',' ',' ',' ','1','0','5','6','0','5','2','2','2','2','2'}, //13
        {'8','8','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ','1','0','0','0','0','0','0','0','0','0','8'}, //14
        {'2','2','2','2','2','4','0','3','4','0','1',' ',' ',' ',' ',' ',' ','1','0','3','4','0','3','2','2','2','2','2'}, //15
        {' ',' ',' ',' ',' ','1','0','1','1','0','5','2','2','2','2','2','2','6','0','1','1','0','1',' ',' ',' ',' ',' '}, //16
        {' ',' ',' ',' ',' ','1','0','1','1','0','0','0','0','0','0','0','0','0','0','1','1','0','1',' ',' ',' ',' ',' '}, //17
        {' ',' ',' ',' ',' ','1','0','1','1','0','3','2','2','2','2','2','2','4','0','1','1','0','1',' ',' ',' ',' ',' '}, //18
        {'3','2','2','2','2','6','0','5','6','0','5','2','2','4','3','2','2','6','0','5','6','0','5','2','2','2','2','4'}, //19
        {'1','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'}, //20
        {'1','0','3','2','2','4','0','3','2','2','2','4','0','1','1','0','3','2','2','2','4','0','3','2','2','4','0','1'}, //21
        {'1','0','5','2','4','1','0','5','2','2','2','6','0','5','6','0','5','2','2','2','6','0','1','3','2','6','0','1'}, //22
        {'1','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','1'}, //23
        {'5','2','4','0','1','1','0','3','4','0','3','2','2','2','2','2','2','4','0','3','4','0','1','1','0','3','2','6'}, //24
        {'3','2','6','0','5','6','0','1','1','0','5','2','2','4','3','2','2','6','0','1','1','0','5','6','0','5','2','4'}, //25
        {'1','0','0','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','0','0','1'}, //26
        {'1','0','3','2','2','2','2','6','5','2','2','4','0','1','1','0','3','2','2','6','5','2','2','2','2','4','0','1'}, //27
        {'1','0','5','2','2','2','2','2','2','2','2','6','0','5','6','0','5','2','2','2','2','2','2','2','2','6','0','1'}, //28
        {'1','p','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','p','1'}, //29
        {'5','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','6'} //30
    };

void reset_map()
{
    for (int i = 0; i < 32; ++i)
        for (int j = 0; j < 29; ++j)
            mapp[i][j] = mapp_ori[i][j];
}



void printMap() {

    cout << blue;

    for (int i = 0; i < 31; ++i) {
        for (int j = 0; j < 29; ++j) {
            if (mapp[i][j] == '1')
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
            else if (mapp[i][j] == '9')
                cout << (char)196;
            else if (mapp[i][j] == '8') // path gaada coin
                cout << ' ';
            else if (mapp[i][j] == '0') //coin
                cout << yellow << '.' << blue;
            else if (mapp[i][j] == 'p') //power pelet
                cout << yellow << 'o' << blue;
            else
                cout << mapp[i][j];
        }
        cout << endl;
    }
        cout << reset;
}

void move_pacman(player &pacman, char &input) {
    kalo ada ganti arah
    if (_kbhit())
        input = _getch();

    hapus posisi sblumnya
    gotoxy(pacman.x, pacman.y-2);
    cout << ' ';

    if(pacman.y == 15 && pacman.x > 26)
        pacman.x = 1;
    else if(pacman.y == 15 && pacman.x < 1)
            pacman.x = 27;

    jalan
    switch (input) {
        case 'w':
        case 'W':
            if (pacman.y >= 0 &&( mapp[pacman.y - 1][pacman.x] == '0' || mapp[pacman.y - 1][pacman.x] == '8' || mapp[pacman.y - 1][pacman.x] == 'p' )) {
                pacman.y--;
                pacman.shape = 'v';
            }
            break;
        case 's':
        case 'S':
            if (pacman.y < 30 && (mapp[pacman.y + 1][pacman.x] == '0' ) || mapp[pacman.y + 1][pacman.x]  == '8'  ||mapp[pacman.y + 1][pacman.x] == 'p') {
                pacman.y++;
                pacman.shape = '^';
            }
            break;
        case 'a':
        case 'A':
            if (pacman.x > 0 && (mapp[pacman.y][pacman.x - 1] == '0'||mapp[pacman.y][pacman.x - 1] == '8'   || mapp[pacman.y][pacman.x - 1] == 'p') ) {
                pacman.x--;
                pacman.shape = '>';
            }            break;

            break;
        case 'd':
        case 'D':
            if (pacman.x < 28 && (mapp[pacman.y][pacman.x + 1] == '0' || mapp[pacman.y][pacman.x + 1] == '8'  || mapp[pacman.y][pacman.x + 1] == 'p' ) ) {
                pacman.x++;
                pacman.shape = '<';
            }
    }

     cetak pacman
    gotoxy(pacman.x, pacman.y-2);
    cout << yellow << pacman.shape << reset;
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

         border batasan
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

         Welcome sign
        gotoxy(48, 4);
        cout << ka << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << ak;
        gotoxy(48, 5);
        cout << v << " WELCOME TO PACMAN " << v;
        gotoxy(48, 6);
        cout << kb << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << bk;

         Menu
        for (int i = 1; i <= 3; i++) {
            if (cursor == i) {
                gotoxy(men[i].x, men[i].y);
                cout << "> " << (i == 1 ? "PLAY GAME" : i == 2 ? "LEADERBOARD" : "EXIT");
            } else {
                gotoxy(men[i].x-2 , men[i].y);
                cout << "  " << (i == 1 ? "PLAY GAME" : i == 2 ? "LEADERBOARD" : "EXIT");
            }
        }

         input
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

void cek_pacman(player pacman, int &score, bool &power)
{
    if(mapp[pacman.y][pacman.x] == '0')
    {
        score+=100; //1 pelet 100 point
        mapp[pacman.y][pacman.x] = '8';
    }
    if(mapp[pacman.y][pacman.x] == 'p')
    {
        power = true; //enter hunting mode
        mapp[pacman.y][pacman.x] = '8';
    }
     return;
}


bool isCollide(player &pacman, player ghost[3])
{
    if(pacman.x == ghost[0].x && pacman.y == ghost[0].y)
        return true;
    else if(pacman.x == ghost[1].x && pacman.y == ghost[1].y)
        return true;
    else if(pacman.x == ghost[2].x && pacman.y == ghost[2].y)
        return true;
    else
        return false;
}

void play(int &score)
{
    reset_map();

    pacman initialize
    player pacman;
    pacman.x = 13;
    pacman.y = 18;
    pacman.shape = '<';
    char input ='D';

    ghost initialize
    player ghost[3];

    ghost[0].x = 18;
    ghost[0].y = 18;
    initialize cetak2
    gotoxy(0,0);
        printMap(); // cetak map
    gotoxy(pacman.x,pacman.y-2);
        cout << yellow << pacman.shape << reset;
        kalo makan power pelet
        bool power = false;
    do{
        move_pacman(pacman,input);
        cek_pacman(pacman, score, power); // <- per-pelet peletan
        Sleep(200);
        gotoxy(50, 6);
            cout << "Score : " << score;
        gotoxy(50, 9);
            cout << "Use W/A/S/D To Move";

    }while(!isCollide(pacman, ghost) || power == false);
    system("pause");
}


int main(){
    srand((time(0))); // Seed for random number generation
    int pil;
    do{
            int score=0;
            pil = menu();
            switch(pil)
            {
            play
            case 1 :
                play(score);
                break;

            leaderboard
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


string yellow = "\033[33m";
string blue = "\033[34m";
string reset = "\033[0m";

struct xy {
    int x, y;
};

struct player {
    int x, y;
    char shape;
};


void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

char mapp[32][29];
// Map initialize
char mapp_ori[32][29] = {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
       {'3','2','2','2','2','2','2','2','2','2','2','2','2','4','3','2','2','2','2','2','2','2','2','2','2','2','2','4'}, //0
        {'1','p','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','p','1'}, //1
        {'1','0','3','2','2','4','0','3','2','2','2','4','0','1','1','0','3','2','2','2','4','0','3','2','2','4','0','1'}, //2
        {'1','0','1',' ',' ','1','0','1',' ',' ',' ','1','0','1','1','0','1',' ',' ',' ','1','0','1',' ',' ','1','0','1'}, //3
        {'1','0','5','2','2','6','0','5','2','2','2','6','0','5','6','0','5','2','2','2','6','0','5','2','2','6','0','1'}, //4
        {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'}, //5
        {'1','0','3','2','2','4','0','3','4','0','3','2','2','2','2','2','2','4','0','3','4','0','3','2','2','4','0','1'}, //6
        {'1','0','5','2','2','6','0','1','1','0','5','2','2','4','3','2','2','6','0','1','1','0','5','2','2','6','0','1'}, //7
        {'1','0','0','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','0','0','1'}, //8
        {'5','2','2','2','2','4','0','1','5','2','2','4','0','5','6','0','3','2','2','6','1','0','3','2','2','2','2','6'}, //9
        {' ',' ',' ',' ',' ','1','0','1','3','2','2','6','0','0','0','0','5','2','2','4','1','0','1',' ',' ',' ',' ',' '}, //10
        {' ',' ',' ',' ',' ','1','0','1','1','0','0','0','0','0','0','0','0','0','0','1','1','0','1',' ',' ',' ',' ',' '}, //11
        {' ',' ',' ',' ',' ','1','0','1','1','0','3','2','2','9','9','2','2','4','0','1','1','0','1',' ',' ',' ',' ',' '}, //12
        {'2','2','2','2','2','6','0','5','6','0','1',' ',' ',' ',' ',' ',' ','1','0','5','6','0','5','2','2','2','2','2'}, //13
        {'8','8','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ','1','0','0','0','0','0','0','0','0','0','8'}, //14
        {'2','2','2','2','2','4','0','3','4','0','1',' ',' ',' ',' ',' ',' ','1','0','3','4','0','3','2','2','2','2','2'}, //15
        {' ',' ',' ',' ',' ','1','0','1','1','0','5','2','2','2','2','2','2','6','0','1','1','0','1',' ',' ',' ',' ',' '}, //16
        {' ',' ',' ',' ',' ','1','0','1','1','0','0','0','0','0','0','0','0','0','0','1','1','0','1',' ',' ',' ',' ',' '}, //17
        {' ',' ',' ',' ',' ','1','0','1','1','0','3','2','2','2','2','2','2','4','0','1','1','0','1',' ',' ',' ',' ',' '}, //18
        {'3','2','2','2','2','6','0','5','6','0','5','2','2','4','3','2','2','6','0','5','6','0','5','2','2','2','2','4'}, //19
        {'1','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'}, //20
        {'1','0','3','2','2','4','0','3','2','2','2','4','0','1','1','0','3','2','2','2','4','0','3','2','2','4','0','1'}, //21
        {'1','0','5','2','4','1','0','5','2','2','2','6','0','5','6','0','5','2','2','2','6','0','1','3','2','6','0','1'}, //22
        {'1','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','1'}, //23
        {'5','2','4','0','1','1','0','3','4','0','3','2','2','2','2','2','2','4','0','3','4','0','1','1','0','3','2','6'}, //24
        {'3','2','6','0','5','6','0','1','1','0','5','2','2','4','3','2','2','6','0','1','1','0','5','6','0','5','2','4'}, //25
        {'1','0','0','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','0','0','1'}, //26
        {'1','0','3','2','2','2','2','6','5','2','2','4','0','1','1','0','3','2','2','6','5','2','2','2','2','4','0','1'}, //27
        {'1','0','5','2','2','2','2','2','2','2','2','6','0','5','6','0','5','2','2','2','2','2','2','2','2','6','0','1'}, //28
        {'1','p','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','p','1'}, //29
        {'5','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','6'} //30
    };

void reset_map()
{
    for (int i = 0; i < 32; ++i)
        for (int j = 0; j < 29; ++j)
            mapp[i][j] = mapp_ori[i][j];
}



void printMap() {

    cout << blue;

    for (int i = 0; i < 31; ++i) {
        for (int j = 0; j < 29; ++j) {
            if (mapp[i][j] == '1')
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
            else if (mapp[i][j] == '9')
                cout << (char)196;
            else if (mapp[i][j] == '8') // path gaada coin
                cout << ' ';
            else if (mapp[i][j] == '0') //coin
                cout << yellow << '.' << blue;
            else if (mapp[i][j] == 'p') //power pelet
                cout << yellow << 'o' << blue;
            else
                cout << mapp[i][j];
        }
        cout << endl;
    }
        cout << reset;
}

void move_pacman(player &pacman, char &input) {
    //kalo ada ganti arah
    if (_kbhit())
        input = _getch();

    //hapus posisi sblumnya
    gotoxy(pacman.x, pacman.y-2);
    cout << ' ';

    if(pacman.y == 15 && pacman.x > 26)
        pacman.x = 1;
    else if(pacman.y == 15 && pacman.x < 1)
            pacman.x = 27;

    //jalan
    switch (input) {
        case 'w':
        case 'W':
            if (pacman.y >= 0 &&( mapp[pacman.y - 1][pacman.x] == '0' || mapp[pacman.y - 1][pacman.x] == '8' || mapp[pacman.y - 1][pacman.x] == 'p' )) {
                pacman.y--;
                pacman.shape = 'v';
            }
            break;
        case 's':
        case 'S':
            if (pacman.y < 30 && (mapp[pacman.y + 1][pacman.x] == '0' ) || mapp[pacman.y + 1][pacman.x]  == '8'  ||mapp[pacman.y + 1][pacman.x] == 'p') {
                pacman.y++;
                pacman.shape = '^';
            }
            break;
        case 'a':
        case 'A':
            if (pacman.x > 0 && (mapp[pacman.y][pacman.x - 1] == '0'||mapp[pacman.y][pacman.x - 1] == '8'   || mapp[pacman.y][pacman.x - 1] == 'p') ) {
                pacman.x--;
                pacman.shape = '>';
            }            break;

            break;
        case 'd':
        case 'D':
            if (pacman.x < 28 && (mapp[pacman.y][pacman.x + 1] == '0' || mapp[pacman.y][pacman.x + 1] == '8'  || mapp[pacman.y][pacman.x + 1] == 'p' ) ) {
                pacman.x++;
                pacman.shape = '<';
            }
    }

    // cetak pacman
    gotoxy(pacman.x, pacman.y-2);
    cout << yellow << pacman.shape << reset;
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

void cek_pacman(player pacman, int &score, bool &power)
{
    if(mapp[pacman.y][pacman.x] == '0')
    {
        score+=100; //1 pelet 100 point
        mapp[pacman.y][pacman.x] = '8';
    }
    if(mapp[pacman.y][pacman.x] == 'p')
    {
        power = true; //enter hunting mode
        mapp[pacman.y][pacman.x] = '8';
    }
     return;
}


bool isCollide(player &pacman, player ghost[3])
{
    if(pacman.x == ghost[0].x && pacman.y == ghost[0].y)
        return true;
    else if(pacman.x == ghost[1].x && pacman.y == ghost[1].y)
        return true;
    else if(pacman.x == ghost[2].x && pacman.y == ghost[2].y)
        return true;
    else
        return false;
}

void play(int &score)
{
    reset_map();

    //pacman initialize
    player pacman;
    pacman.x = 13;
    pacman.y = 18;
    pacman.shape = '<';
    char input ='D';

    //ghost initialize
    player ghost[3];

//    ghost[0].x = 18;
//    ghost[0].y = 18;
    //initialize cetak2
    gotoxy(0,0);
        printMap(); // cetak map
    gotoxy(pacman.x,pacman.y-2);
        cout << yellow << pacman.shape << reset;
        //kalo makan power pelet
        bool power = false;
    do{
        move_pacman(pacman,input);
        cek_pacman(pacman, score, power); // <- per-pelet peletan
        Sleep(200);
        gotoxy(50, 6);
            cout << "Score : " << score;
        gotoxy(50, 9);
            cout << "Use W/A/S/D To Move";

    }while(!isCollide(pacman, ghost) || power == false);
    system("pause");
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


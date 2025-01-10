
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

struct player {
    int x, y, score,dir;
    char shape;
    string color,name;
};


void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void cek_file_leaderboard()
{
    fstream myFile;
    myFile.open("leaderboard.txt", ios::out | ios::app);
    myFile.close();
}
void upload_score(string name, int score){
    fstream myFile;
    myFile.open("leaderboard.txt", ios::app);
    if(myFile.is_open())
    {
        myFile << name << endl;
        myFile << score << endl;
    }
    myFile.close();
}

void view_leaderboard(){
    vector<player> players;

    fstream myFile;
    myFile.open("leaderboard.txt", ios::in);
    if (myFile.is_open()) {
        player p;
        while (myFile >> p.name >> p.score) {
            players.push_back(p);
        }
        myFile.close();
    }

    sort(players.begin(), players.end(), [](player a, player b) {
        return a.score > b.score;
    });

    // Display
    system("cls");
    cout << "========== LEADERBOARD ==========" << endl;
    cout << "RANK   NAME               SCORE" << endl;
    for (size_t i = 0; i < players.size() && i < 5; i++) { // Display top 10
        cout << left << i + 1 << setw(6) << "." << setw(19) << players[i].name << players[i].score << endl;
    }
    cout << endl << endl << endl << endl;
    system("pause");
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

bool isWin()
{
    for (int i = 0; i < 32; ++i){
        for (int j = 0; j < 29; ++j){
          if(mapp[i][j]=='0' || mapp[i][j]=='p')
            return false;
        }}
        return true;
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
    char before = input;

    if (_kbhit())
        input = _getch();

    //BIAR GA STOP KALO PENCET KEY RANDOM
    if(input != 'W' && input != 'w' && input != 'A' && input != 'a' && input != 'S' && input != 's' && input != 'D' && input != 'd')
         input = before;

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
                break;
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
        Beep(1500, 100);
    }
    else if(mapp[pacman.y][pacman.x] == 'p')
    {
        power = true; //enter hunting mode
        mapp[pacman.y][pacman.x] = '8';
        Beep(550, 350);
        Sleep(500);
    }
    else
        Sleep(100);

     return;
}


bool isCollide(player &pacman, player ghost[4], bool power) {
    if (power) return false;
    for (int i = 0; i < 4; i++) {
        if (pacman.x == ghost[i].x && pacman.y == ghost[i].y) {
            return true;
        }
    }
    return false;
}
void makan_ghost(player &pacman, player ghost[], bool power, int &score)
{
        if(pacman.x == ghost[0].x && pacman.y == ghost[0].y)
        {
            // Erase ghost's current position
            gotoxy(ghost[0].x, ghost[0].y - 2);
                cout << yellow << pacman.shape << reset;

            score+=1000;//makan ghost dapet 1000
            ghost[0].x = 14;
            ghost[0].y = 11;
            Beep(3000, 100);

             // Draw the ghost in its new position
            gotoxy(ghost[0].x, ghost[0].y - 2);
            if(power==false)
                cout << ghost[0].color << ghost[0].shape << reset;
            else
                cout << "\033[44m" << ghost[0].shape << reset;
        }
        else if(pacman.x == ghost[1].x && pacman.y == ghost[1].y)
        {
            // Erase ghost's current position
            gotoxy(ghost[1].x, ghost[1].y - 2);
                cout << yellow << pacman.shape << reset;

            score+=1000;//makan ghost dapet 1000
            ghost[1].x = 14;
            ghost[1].y = 11;
            Beep(3000, 100);

             // Draw the ghost in its new position
            gotoxy(ghost[1].x, ghost[1].y - 2);
            if(power==false)
                cout << ghost[1].color << ghost[1].shape << reset;
            else
                cout << "\033[44m" << ghost[1].shape << reset;
        }
        else if(pacman.x == ghost[2].x && pacman.y == ghost[2].y)
         {
           // Erase ghost's current position
            gotoxy(ghost[2].x, ghost[2].y - 2);
              cout << yellow << pacman.shape << reset;

            score+=1000;//makan ghost dapet 1000
            ghost[2].x = 14;
            ghost[2].y = 11;
            Beep(3000, 100);

             // Draw the ghost in its new position
            gotoxy(ghost[2].x, ghost[2].y - 2);
            if(power==false)
                cout << ghost[2].color << ghost[2].shape << reset;
            else
                cout << "\033[44m" << ghost[2].shape << reset;
        }
        else if(pacman.x == ghost[3].x && pacman.y == ghost[3].y)
         {
            // Erase ghost's current position
            gotoxy(ghost[3].x, ghost[3].y - 2);
            cout << yellow << pacman.shape << reset;

            score+=1000;//makan ghost dapet 1000
            ghost[3].x = 14;
            ghost[3].y = 11;
            Beep(3000, 100);

             // Draw the ghost in its new position
            gotoxy(ghost[3].x, ghost[3].y - 2);
            if(power==false)
                cout << ghost[3].color << ghost[3].shape << reset;
            else
                cout << "\033[44m" << ghost[3].shape << reset;
        }

}

void move_ghost(player &ghost, int &current_dir, player &pacman, bool power) {
    const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;

    gotoxy(ghost.x, ghost.y - 2);
    if (mapp[ghost.y][ghost.x] == '8')
        cout << ' ';
    else if (mapp[ghost.y][ghost.x] == '0')
        cout << yellow << '.' << reset;
    else if (mapp[ghost.y][ghost.x] == 'p')
        cout << yellow << 'o' << reset;

    if (ghost.y == 15 && ghost.x > 26)
        ghost.x = 1;
    else if (ghost.y == 15 && ghost.x < 1)
        ghost.x = 27;

    if (power) {
        if (ghost.x < pacman.x) {
            if (ghost.x > 0 && (mapp[ghost.y][ghost.x - 1] == '0' || mapp[ghost.y][ghost.x - 1] == '8' || mapp[ghost.y][ghost.x - 1] == 'p')) {
                ghost.x--;
            }
        } else if (ghost.x > pacman.x) {
            if (ghost.x < 28 && (mapp[ghost.y][ghost.x + 1] == '0' || mapp[ghost.y][ghost.x + 1] == '8' || mapp[ghost.y][ghost.x + 1] == 'p')) {
                ghost.x++;
            }
        }

        if (ghost.y < pacman.y) {
            if (ghost.y > 0 && (mapp[ghost.y - 1][ghost.x] == '0' || mapp[ghost.y - 1][ghost.x] == '8' || mapp[ghost.y - 1][ghost.x] == 'p')) {
                ghost.y--;
            }
        } else if (ghost.y > pacman.y) {
            if (ghost.y < 30 && (mapp[ghost.y + 1][ghost.x] == '0' || mapp[ghost.y + 1][ghost.x] == '8' || mapp[ghost.y + 1][ghost.x] == 'p')) {
                ghost.y++;
            }
        }
    } else {
        vector<pair<int, int>> directions = {
            {0, -1}, // UP
            {0, 1},  // DOWN
            {-1, 0}, // LEFT
            {1, 0}   // RIGHT
        };

        int reverse_dir = -1;
        if (current_dir == UP) reverse_dir = DOWN;
        if (current_dir == DOWN) reverse_dir = UP;
        if (current_dir == LEFT) reverse_dir = RIGHT;
        if (current_dir == RIGHT) reverse_dir = LEFT;

        vector<int> valid_moves;
        for (int i = 0; i < 4; ++i) {
            if (i == reverse_dir) continue;
            int new_x = ghost.x + directions[i].first;
            int new_y = ghost.y + directions[i].second;
            char map_cell = mapp[new_y][new_x];
            if (map_cell == '0' || map_cell == '8' || map_cell == 'p') {
                valid_moves.push_back(i);
            }
        }

        if (!valid_moves.empty()) {
            srand(time(NULL) ^ ghost.x ^ ghost.y);
            current_dir = valid_moves[rand() % valid_moves.size()];
            ghost.x += directions[current_dir].first;
            ghost.y += directions[current_dir].second;
        }
    }

    gotoxy(ghost.x, ghost.y - 2);
    cout << ghost.color << ghost.shape << reset;
}

void move_ghost_hard(player &ghost, player &pacman, bool power) {
    // Erase ghost's current position
    gotoxy(ghost.x, ghost.y - 2);
    if (mapp[ghost.y][ghost.x] == '8') // Path without coin
        cout << ' ';
    else if (mapp[ghost.y][ghost.x] == '0') // Coin
        cout << yellow << '.' << reset;
    else if (mapp[ghost.y][ghost.x] == 'p') // Power pellet
        cout << yellow << 'o' << reset;

    // Store previous position
    int oldX = ghost.x;
    int oldY = ghost.y;

        if (power) {
        // Move away from Pac-Man
            if (ghost.x < pacman.x && ghost.x > 0 &&
                (mapp[ghost.y][ghost.x - 1] == '0' || mapp[ghost.y][ghost.x - 1] == '8' || mapp[ghost.y][ghost.x - 1] == 'p')) {
                ghost.x--;
            } else if (ghost.x > pacman.x && ghost.x < 28 &&
                       (mapp[ghost.y][ghost.x + 1] == '0' || mapp[ghost.y][ghost.x + 1] == '8' || mapp[ghost.y][ghost.x + 1] == 'p')) {
                ghost.x++;
            } else if (ghost.y < pacman.y && ghost.y > 0 &&
                       (mapp[ghost.y - 1][ghost.x] == '0' || mapp[ghost.y - 1][ghost.x] == '8' || mapp[ghost.y - 1][ghost.x] == 'p')) {
                ghost.y--;
            } else if (ghost.y > pacman.y && ghost.y < 30 &&
                       (mapp[ghost.y + 1][ghost.x] == '0' || mapp[ghost.y + 1][ghost.x] == '8' || mapp[ghost.y + 1][ghost.x] == 'p')) {
                ghost.y++;
            }
        }
        else {
            // Chase Pac-Man
            if (ghost.x > pacman.x && ghost.x > 0 &&
                (mapp[ghost.y][ghost.x - 1] == '0' || mapp[ghost.y][ghost.x - 1] == '8' || mapp[ghost.y][ghost.x - 1] == 'p')) {
                ghost.x--; //kenanan
            } else if (ghost.x < pacman.x && ghost.x < 28 &&
                       (mapp[ghost.y][ghost.x + 1] == '0' || mapp[ghost.y][ghost.x + 1] == '8' || mapp[ghost.y][ghost.x + 1] == 'p')) {
                ghost.x++; //kekiri
            } else if (ghost.y > pacman.y && ghost.y > 0 &&
                       (mapp[ghost.y - 1][ghost.x] == '0' || mapp[ghost.y - 1][ghost.x] == '8' || mapp[ghost.y - 1][ghost.x] == 'p')) {
                ghost.y--; //keatas
            } else if (ghost.y < pacman.y && ghost.y < 30 &&
                       (mapp[ghost.y + 1][ghost.x] == '0' || mapp[ghost.y + 1][ghost.x] == '8' || mapp[ghost.y + 1][ghost.x] == 'p')) {
                ghost.y++; //kebawah
            }
        }

    // Render ghost's new position
    gotoxy(ghost.x, ghost.y - 2);
    cout << ghost.color << ghost.shape << reset;
}

void play(int &score, string &name)
{
    reset_map();

    //pacman initialize
    player pacman;
    pacman.x = 13;
    pacman.y = 18;
    pacman.shape = '<';
    char input ='D';

    //ghost initialize
    player ghost[4];
    //dir = direction || UP = 0,  DOWN = 1,  LEFT = 2,  RIGHT = 3.
    //setan kiri atas
    ghost[0].x = 1;
    ghost[0].y = 2;
    ghost[0].shape= '"';
    ghost[0].color= "\033[41m";
    ghost[0].dir = 3;
    //setan kanan atas
    ghost[1].x = 26;
    ghost[1].y = 3;
    ghost[1].shape= '"';
    ghost[1].color= "\033[46m";

    ghost[1].dir = 2;
    //setan kiri bawah
    ghost[2].x = 1;
    ghost[2].y = 30;
    ghost[2].shape= '"';
    ghost[2].color= "\033[42m";
    ghost[2].dir = 0;
    //setan kanan bawah
    ghost[3].x = 26;
    ghost[3].y = 30;
    ghost[3].shape= '"';
    ghost[3].color= "\033[43m";
    ghost[3].dir = 0;

    //initialize cetak2
    gotoxy(0,0);
    printMap(); // cetak map
    gotoxy(pacman.x,pacman.y-2);
        cout << yellow << pacman.shape << reset;
        //kalo makan power pelet
        bool power = false;
    do{
        move_pacman(pacman,input);
        move_ghost(ghost[0], ghost[0].dir, pacman, power);
        move_ghost(ghost[1], ghost[1].dir, pacman, power);
        move_ghost(ghost[2], ghost[2].dir, pacman, power);
        move_ghost(ghost[3], ghost[3].dir, pacman, power);
        cek_pacman(pacman, score, power); // <- per-pelet peletan
        Sleep(100);
        gotoxy(40, 6);
            cout << "SCORE : " << score;
        gotoxy(40, 9);
            cout << "USE W/A/S/D TO MOVE";
        if(isWin())
        {
            gotoxy(40, 12);
                cout << "CONGRATS"; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << ".";
            gotoxy(40, 13);
                cout << "WELCOME"; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." ; cout << "TO THE HELLISH STAGE" ;
            gotoxy(40, 14);
                gotoxy(40, 16);
        cout << "T"; Sleep(100);cout << "R"; Sleep(100);cout << "A"; Sleep(100);cout << "N"; Sleep(100);cout << "S"; Sleep(100);cout << "P"; Sleep(100);cout << "O"; Sleep(100);cout << "R"; Sleep(100);cout << "T"; Sleep(100);cout << "I"; Sleep(100);cout << "N"; Sleep(100);cout << "G"; Sleep(100);
        cout << "."; Sleep(500);cout << "."; Sleep(500);cout << "."; Sleep(500);
        }

    }while(!isCollide(pacman, ghost,power) && isWin()==false);
    //HELL MODE
    if(isWin())
    {
        system("cls");
        reset_map();

        //pacman initialize
        pacman.x = 13;
        pacman.y = 18;
        pacman.shape = '<';
        char input ='D';

        //ghost initialize
        //dir = direction || UP = 0,  DOWN = 1,  LEFT = 2,  RIGHT = 3.
        //setan kiri atas
        ghost[0].x = 1;
        ghost[0].y = 2;
        ghost[0].shape= '"';
        ghost[0].color= "\033[41m";
        ghost[0].dir = 3;
        //setan kanan atas
        ghost[1].x = 26;
        ghost[1].y = 3;
        ghost[1].shape= '"';
        ghost[1].color= "\033[46m";
        ghost[1].dir = 2;
        //setan kiri bawah
        ghost[2].x = 1;
        ghost[2].y = 30;
        ghost[2].shape= '"';
        ghost[2].color= "\033[42m";
        ghost[2].dir = 0;
        //setan kanan bawah
        ghost[3].x = 26;
        ghost[3].y = 30;
        ghost[3].shape= '"';
        ghost[3].color= "\033[43m";
        ghost[3].dir = 0;

        //initialize cetak2
        gotoxy(0,0);
            printMap(); // cetak map
        gotoxy(pacman.x,pacman.y-2);
            cout << yellow << pacman.shape << reset;
            //kalo makan power pelet
            bool power = false;
        do{
            move_pacman(pacman,input);
            move_ghost_hard(ghost[0], pacman, power);
            move_ghost_hard(ghost[1], pacman, power);
            move_ghost_hard(ghost[2], pacman, power);
            move_ghost_hard(ghost[3], pacman, power);
            cek_pacman(pacman, score, power); // <- per-pelet peletan
            Sleep(100);
            gotoxy(40, 6);
                cout << "SCORE : " << score;
            gotoxy(40, 9);
                cout << "USE W/A/S/D TO MOVE";

        }while(!isCollide(pacman, ghost,power) && isWin()==false);
    }
    Beep(5000, 1000);
    gotoxy(40, 12);
        cout << "GAME OVER"; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl;
    gotoxy(40, 13);
        cout <<"PLEASE INSERT YOUR NAME : "; cin >> name; Sleep(500);
    gotoxy(40, 16);
        cout << "G"; Sleep(100);cout << "O"; Sleep(100);cout << "I"; Sleep(100);cout << "N"; Sleep(100);cout << "G "; Sleep(100);cout << "B"; Sleep(100);cout << "A"; Sleep(100);cout << "C"; Sleep(100);cout << "K "; Sleep(100);cout << "T"; Sleep(100);cout << "O "; Sleep(100);cout << "M"; Sleep(100);cout << "A"; Sleep(100);cout << "I"; Sleep(100);cout << "N "; Sleep(100);cout << "M"; Sleep(100);cout << "E"; Sleep(100);cout << "N"; Sleep(100);cout << "U"; Sleep(100);
        cout << "."; Sleep(500);cout << "."; Sleep(500);cout << "."; Sleep(500);
}

int main(){
    cek_file_leaderboard();
    srand((time(0))); // Seed for random number generation
    int pil;
    do{
            int score=0;
            string name = "";
            pil = menu();
            switch(pil)
            {
            //play
            case 1 :
                play(score, name);
                upload_score(name,score);
                break;

            //leaderboard
            case 2:
                view_leaderboard();
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

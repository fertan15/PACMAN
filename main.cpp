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

// --- Kode Warna ANSI ---
string yellow = "\033[33m";
string blue = "\033[34m";
string reset = "\033[0m";

// --- struct ---

// Posisi X,Y 
struct xy {
    int x, y;
};

// struct buat player sama skalian ghost
struct player {
    int x, y;         
    int score;        
    int dir;         
    char shape;       
    string color;     
    string name;      
};

// --- ini gotoxy buat pointer print di console ---

// Atur posisi kursor
void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

// --- Leaderboard ---

// Pastiin file leaderboard.txt ada
void cek_file_leaderboard() {
    fstream myFile;
    myFile.open("leaderboard.txt", ios::out | ios::app); 
    myFile.close();
}

// Simpan skor ke file
void upload_score(string name, int score) {
    fstream myFile;
    myFile.open("leaderboard.txt", ios::app);
    if (myFile.is_open()) {
        myFile << name << endl;
        myFile << score << endl;
    }
    myFile.close();
}

// load leaderboard (Top 5)
void view_leaderboard() {
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

    // Urutin skor tertinggi
    sort(players.begin(), players.end(), [](player a, player b) {
        return a.score > b.score;
    });

    // print
    system("cls");
    cout << "========== LEADERBOARD ==========" << endl;
    cout << "RANK    NAME                 SCORE" << endl;
    for (size_t i = 0; i < players.size() && i < 5; i++) { 
        cout << left << i + 1 << setw(6) << "." << setw(19) << players[i].name << players[i].score << endl;
    }
    cout << endl << endl << endl << endl;
    system("pause");
}

// --- Map ---

char mapp[32][29]; // map aktif yang dipake pas game

// map yang bakal di duplikat kalo misal new game lagi 
char mapp_ori[32][29] = {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'3','2','2','2','2','2','2','2','2','2','2','2','2','4','3','2','2','2','2','2','2','2','2','2','2','2','2','4'}, 
        {'1','p','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','p','1'}, 
        {'1','0','3','2','2','4','0','3','2','2','2','4','0','1','1','0','3','2','2','2','4','0','3','2','2','4','0','1'}, 
        {'1','0','1',' ',' ','1','0','1',' ',' ',' ','1','0','1','1','0','1',' ',' ',' ','1','0','1',' ',' ','1','0','1'}, 
        {'1','0','5','2','2','6','0','5','2','2','2','6','0','5','6','0','5','2','2','2','6','0','5','2','2','6','0','1'}, 
        {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'}, 
        {'1','0','3','2','2','4','0','3','4','0','3','2','2','2','2','2','2','4','0','3','4','0','3','2','2','4','0','1'}, 
        {'1','0','5','2','2','6','0','1','1','0','5','2','2','4','3','2','2','6','0','1','1','0','5','2','2','6','0','1'}, 
        {'1','0','0','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','0','0','1'}, 
        {'5','2','2','2','2','4','0','1','5','2','2','4','0','5','6','0','3','2','2','6','1','0','3','2','2','2','2','6'}, 
        {' ',' ',' ',' ',' ','1','0','1','3','2','2','6','0','0','0','0','5','2','2','4','1','0','1',' ',' ',' ',' ',' '}, 
        {' ',' ',' ',' ',' ','1','0','1','1','0','0','0','0','0','0','0','0','0','0','1','1','0','1',' ',' ',' ',' ',' '}, 
        {' ',' ',' ',' ',' ','1','0','1','1','0','3','2','2','9','9','2','2','4','0','1','1','0','1',' ',' ',' ',' ',' '}, 
        {'2','2','2','2','2','6','0','5','6','0','1',' ',' ',' ',' ',' ',' ','1','0','5','6','0','5','2','2','2','2','2'}, 
        {'8','8','0','0','0','0','0','0','0','0','1',' ',' ',' ',' ',' ',' ','1','0','0','0','0','0','0','0','0','0','8'}, 
        {'2','2','2','2','2','4','0','3','4','0','1',' ',' ',' ',' ',' ',' ','1','0','3','4','0','3','2','2','2','2','2'}, 
        {' ',' ',' ',' ',' ','1','0','1','1','0','5','2','2','2','2','2','2','6','0','1','1','0','1',' ',' ',' ',' ',' '}, 
        {' ',' ',' ',' ',' ','1','0','1','1','0','0','0','0','0','0','0','0','0','0','1','1','0','1',' ',' ',' ',' ',' '}, 
        {' ',' ',' ',' ',' ','1','0','1','1','0','3','2','2','2','2','2','2','4','0','1','1','0','1',' ',' ',' ',' ',' '}, 
        {'3','2','2','2','2','6','0','5','6','0','5','2','2','4','3','2','2','6','0','5','6','0','5','2','2','2','2','4'}, 
        {'1','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1'}, 
        {'1','0','3','2','2','4','0','3','2','2','2','4','0','1','1','0','3','2','2','2','4','0','3','2','2','4','0','1'}, 
        {'1','0','5','2','4','1','0','5','2','2','2','6','0','5','6','0','5','2','2','2','6','0','1','3','2','6','0','1'}, 
        {'1','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','1'}, 
        {'5','2','4','0','1','1','0','3','4','0','3','2','2','2','2','2','2','4','0','3','4','0','1','1','0','3','2','6'}, 
        {'3','2','6','0','5','6','0','1','1','0','5','2','2','4','3','2','2','6','0','1','1','0','5','6','0','5','2','4'}, 
        {'1','0','0','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','1','1','0','0','0','0','0','0','1'}, 
        {'1','0','3','2','2','2','2','6','5','2','2','4','0','1','1','0','3','2','2','6','5','2','2','2','2','4','0','1'}, 
        {'1','0','5','2','2','2','2','2','2','2','2','6','0','5','6','0','5','2','2','2','2','2','2','2','2','2','6','0','1'}, 
        {'1','p','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','p','1'}, 
        {'5','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','6'}
    };

// Copy map
void reset_map() {
    for (int i = 0; i < 32; ++i)
        for (int j = 0; j < 29; ++j)
            mapp[i][j] = mapp_ori[i][j];
}

// cek masih ada pelet ga
bool isWin() {
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 29; ++j) {
            if (mapp[i][j] == '0' || mapp[i][j] == 'p')
                return false;
        }
    }
    return true;
}

// print map
void printMap() {
    cout << blue; 

    for (int i = 0; i < 31; ++i) { 
        for (int j = 0; j < 29; ++j) {
            char cell = mapp[i][j];
            // Karakter tembok
            if (cell == '1')
                cout << (char)186; 
            else if (cell == '2')
                cout << (char)205; 
            else if (cell == '3')
                cout << (char)201; 
            else if (cell == '4')
                cout << (char)187; 
            else if (cell == '5')
                cout << (char)200; 
            else if (cell == '6')
                cout << (char)188; 
            else if (cell == '9')
                cout << (char)196; 
            else if (cell == '8') // Jalur kosong
                cout << ' ';
            else if (cell == '0') // Pellet biasa
                cout << yellow << '.' << blue;
            else if (cell == 'p') // Power pellet
                cout << yellow << 'o' << blue;
            else
                cout << cell; 
        }
        cout << endl;
    }
    cout << reset; 
}

// --- game logic ---

// Gerakin Pac-Man
void move_pacman(player &pacman, char &input) {
    char before = input; 

    if (_kbhit())
        input = _getch();

    if (input != 'W' && input != 'w' && input != 'A' && input != 'a' && input != 'S' && input != 's' && input != 'D' && input != 'd')
        input = before;

    // Hapus di posisi lama
    gotoxy(pacman.x, pacman.y - 2);
    cout << ' ';

    // kalo nembus terowongan
    if (pacman.y == 15) {
        if (pacman.x > 26) 
            pacman.x = 1;
        else if (pacman.x < 1) 
            pacman.x = 27;
    }

    int next_x = pacman.x;
    int next_y = pacman.y;
    char next_shape = pacman.shape;

    // next position
    switch (input) {
        case 'w': case 'W': next_y--; next_shape = 'v'; break;
        case 's': case 'S': next_y++; next_shape = '^'; break;
        case 'a': case 'A': next_x--; next_shape = '>'; break;
        case 'd': case 'D': next_x++; next_shape = '<'; break;
    }

    // collision
    if (next_y >= 0 && next_y < 31 && next_x >= 0 && next_x < 28) {
        char target_cell = mapp[next_y][next_x];
        if (target_cell == '0' || target_cell == '8' || target_cell == 'p') {
            pacman.x = next_x;
            pacman.y = next_y;
            pacman.shape = next_shape;
        }
    }

    // new position
    gotoxy(pacman.x, pacman.y - 2);
    cout << yellow << pacman.shape << reset;
}

// Cek collision sama pellet
void cek_pacman(player pacman, int &score, bool &power, int &timer) {
    if (mapp[pacman.y][pacman.x] == '0') {
        score += 100; 
        mapp[pacman.y][pacman.x] = '8'; // Jadi kosong
        Beep(1500, 50); 
    } else if (mapp[pacman.y][pacman.x] == 'p') {
        power = true; // Mode power ON
        mapp[pacman.y][pacman.x] = '8'; 
        Beep(550, 200); 
        Sleep(100);
        timer = 0; 
    } else {
        Sleep(100); 
    }
}

// Cek tabrakan
bool isCollide(player &pacman, player ghost[4], bool power) {
    if (power) return false;
    for (int i = 0; i < 4; i++) {
        if (pacman.x == ghost[i].x && pacman.y == ghost[i].y) {
            return true;
        }
    }
    return false;
}

// Makan hantu (mode power)
void makan_ghost(player &pacman, player ghost[], bool power, int &score) {
    if (!power) return; 

    for (int i = 0; i < 4; i++) {
        if (pacman.x == ghost[i].x && pacman.y == ghost[i].y) {
            score += 1000; 
            // Kirim hantu ke rumahnya
            ghost[i].x = 14;
            ghost[i].y = 11;
            Beep(3000, 200); 
        }
    }
}

// --- ghost movement ---

// Easy move: Random & nggak balik arah
void move_ghost(player &ghost, int &current_dir, bool power) {
    const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;

    gotoxy(ghost.x, ghost.y - 2);
    if (mapp[ghost.y][ghost.x] == '8') 
        cout << ' ';
    else if (mapp[ghost.y][ghost.x] == '0') 
        cout << yellow << '.' << reset;
    else if (mapp[ghost.y][ghost.x] == 'p') 
        cout << yellow << 'o' << reset;

    // Warp terowongan
    if (ghost.y == 15) {
        if (ghost.x > 26)
            ghost.x = 1;
        else if (ghost.x < 1)
            ghost.x = 27;
    }

    vector<pair<int, int>> directions = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };

    int reverse_dir = -1;
    if (current_dir == UP) reverse_dir = DOWN;
    else if (current_dir == DOWN) reverse_dir = UP;
    else if (current_dir == LEFT) reverse_dir = RIGHT;
    else if (current_dir == RIGHT) reverse_dir = LEFT;

    // cek valid move
    vector<int> valid_moves;
    for (int i = 0; i < 4; ++i) {
        if (i == reverse_dir) continue; 
        int new_x = ghost.x + directions[i].first;
        int new_y = ghost.y + directions[i].second;
        char map_cell = mapp[new_y][new_x];
        if (map_cell == '0' || map_cell == '8' || map_cell == 'p' || map_cell == '9') {
            valid_moves.push_back(i);
        }
    }

    // Pilih random dari list valid move
    if (!valid_moves.empty()) {
        current_dir = valid_moves[rand() % valid_moves.size()];
        ghost.x += directions[current_dir].first;
        ghost.y += directions[current_dir].second;
    }

    
    gotoxy(ghost.x, ghost.y - 2);
    //ini if cuman buat bedain warna
    if (power == false)
        cout << ghost.color << ghost.shape << reset; 
    else
        cout << "\033[44m" << ghost.shape << reset; 
}

// Hard mode: ada kejar & kabur
void move_ghost_hard(player &ghost, player &pacman, bool power) {
    gotoxy(ghost.x, ghost.y - 2);
    if (mapp[ghost.y][ghost.x] == '8')
        cout << ' ';
    else if (mapp[ghost.y][ghost.x] == '0')
        cout << yellow << '.' << reset;
    else if (mapp[ghost.y][ghost.x] == 'p')
        cout << yellow << 'o' << reset;

    int next_x = ghost.x;
    int next_y = ghost.y;

    // gerakan valid
    auto is_valid_move = [&](int x, int y) {
        if (y < 0 || y >= 31 || x < 0 || x >= 28) return false;
        char cell = mapp[y][x];
        return (cell == '0' || cell == '8' || cell == 'p' || cell == '9');
    };

    if (power) {
        // Mode Kabur: Jauhi Pac-Man
        if (ghost.x < pacman.x && is_valid_move(ghost.x - 1, ghost.y)) { next_x--; } 
        else if (ghost.x > pacman.x && is_valid_move(ghost.x + 1, ghost.y)) { next_x++; } 
        else if (ghost.y < pacman.y && is_valid_move(ghost.x, ghost.y - 1)) { next_y--; } 
        else if (ghost.y > pacman.y && is_valid_move(ghost.x, ghost.y + 1)) { next_y++; }
    } else {
        // Mode Kejar: Dekati Pac-Man
        if (ghost.x > pacman.x && is_valid_move(ghost.x - 1, ghost.y)) { next_x--; } 
        else if (ghost.x < pacman.x && is_valid_move(ghost.x + 1, ghost.y)) { next_x++; } 
        else if (ghost.y > pacman.y && is_valid_move(ghost.x, ghost.y - 1)) { next_y--; } 
        else if (ghost.y < pacman.y && is_valid_move(ghost.x, ghost.y + 1)) { next_y++; }
    }

    // Update posisi
    if (next_x != ghost.x || next_y != ghost.y) {
        ghost.x = next_x;
        ghost.y = next_y;
    }

    // new position
    gotoxy(ghost.x, ghost.y - 2);
    if (power == false)
        cout << ghost.color << ghost.shape << reset;
    else
        cout << "\033[44m" << ghost.shape << reset;
}

// --- main program ---

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
        char v = 186; char h = 205; char ka = 201; char kb = 200; char bk = 188; char ak = 187; 

        for (int i = 0; i < FRAME_HEIGHT; i++) {
            for (int j = 0; j < FRAME_WIDTH; j++) {
                if (i == 0 && j == 0) cout << ka; else if (i == 0 && j == FRAME_WIDTH - 1) cout << ak;
                else if (i == FRAME_HEIGHT - 1 && j == 0) cout << kb;
                else if (i == FRAME_HEIGHT - 1 && j == FRAME_WIDTH - 1) cout << bk;
                else if (i == 0 || i == FRAME_HEIGHT - 1) cout << h;
                else if (j == 0 || j == FRAME_WIDTH - 1) cout << v;
                else cout << " ";
            }
            cout << endl;
        }

        gotoxy(48, 4);
        cout << ka << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << ak;
        gotoxy(48, 5);
        cout << v << " WELCOME TO PACMAN " << v;
        gotoxy(48, 6);
        cout << kb << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << h << bk;

        for (int i = 1; i <= 3; i++) {
            gotoxy(men[i].x - 2, men[i].y);
            string option_text = (i == 1 ? "PLAY GAME" : i == 2 ? "LEADERBOARD" : "EXIT");
            if (cursor == i) {
                cout << "> " << option_text;
            } else {
                cout << "  " << option_text;
            }
        }

        
        char in = _getch();

        if (in == 'W' || in == 'w') {
            if (cursor > 1) cursor--;
        } else if (in == 'S' || in == 's') {
            if (cursor < 3) cursor++;
        } else if (in == '\r') { // Tombol Enter
            end = true;
            return cursor;
        }
    }
    return 0;
}

// game loop
void play(int &score, string &name) {
    system("cls");
    reset_map(); 

    // --- Pac-Man ---
    player pacman;
    pacman.x = 13; pacman.y = 18; pacman.shape = '<';
    char input = 'D'; 

    // --- ghost ---
    player ghost[4];

    // Hantu 0 (Merah) - Kiri Atas
    ghost[0].x = 1; ghost[0].y = 2; ghost[0].shape = (char)234; 
    ghost[0].color = "\033[41m"; ghost[0].dir = 3; 

    // Hantu 1 (Cyan) - Kanan Atas
    ghost[1].x = 26; ghost[1].y = 3; ghost[1].shape = (char)234;
    ghost[1].color = "\033[46m"; ghost[1].dir = 2; 

    // Hantu 2 (Hijau) - Kiri Bawah
    ghost[2].x = 1; ghost[2].y = 30; ghost[2].shape = (char)234;
    ghost[2].color = "\033[42m"; ghost[2].dir = 0; 

    // Hantu 3 (Magenta) - Kanan Bawah
    ghost[3].x = 26; ghost[3].y = 30; ghost[3].shape = (char)234;
    ghost[3].color = "\033[43m"; ghost[3].dir = 0; 

    gotoxy(0, 0);
    printMap(); 
    gotoxy(pacman.x, pacman.y - 2);
    cout << yellow << pacman.shape << reset;

    bool power = false; 
    int timer = 100;   
    int stage = 1;     
    bool game_running = true; 

    // --- STAGE 1 (Mode easy) ---
    gotoxy(40, 4);
    cout << "STAGE: 1 (EASY GHOSTS)";

    while (game_running && !isWin()) {
        if (timer == 50) {
            power = false; 
        }

        timer++;

        int pacman_old_x = pacman.x;
        int pacman_old_y = pacman.y;
        xy ghost_old_pos[4];
        for (int i = 0; i < 4; ++i) {
            ghost_old_pos[i] = {ghost[i].x, ghost[i].y};
        }

        // 1. Gerakan
        move_pacman(pacman, input);
        move_ghost(ghost[0], ghost[0].dir, power);
        move_ghost(ghost[1], ghost[1].dir, power);
        move_ghost(ghost[2], ghost[2].dir, power);
        move_ghost(ghost[3], ghost[3].dir, power);

        // 2. Makan pellet
        cek_pacman(pacman, score, power, timer);

        // 3. Cek tabrakan
        if (power == false) {
            for (int i = 0; i < 4; i++) {
                // Tabrakan langsung
                if (pacman.x == ghost[i].x && pacman.y == ghost[i].y) {
                    game_running = false;
                    break;
                }
                // Tabrakan langkah
                if (pacman.x == ghost_old_pos[i].x && pacman.y == ghost_old_pos[i].y &&
                    pacman_old_x == ghost[i].x && pacman_old_y == ghost[i].y) {
                    game_running = false;
                    break;
                }
            }
        }

        // 4. Makan hantu
        if (game_running && power == true) { 
            makan_ghost(pacman, ghost, power, score);
        }


            // Update skor & info
            gotoxy(40, 6);
            cout << "SCORE : " << score;
            gotoxy(40, 9);
            cout << "USE W/A/S/D TO MOVE        ";

        Sleep(100);

    }

    // --- STAGE 2 (Mode hard) ---
    // Kalau menang Stage 1, lanjut Stage 2
    if (isWin()) {
        score += 5000; 
        stage = 2;
        game_running = true; 
        system("cls");
        reset_map();

        // Reset Posisi Pac-Man
        pacman.x = 13; pacman.y = 18; pacman.shape = '<';
        input = 'D';

        // Reset Posisi Hantu (dikerumunin)
        for (int i = 0; i < 4; i++) {
            ghost[i].x = 14; 
            ghost[i].y = 14;
        }

        // print ulang
        gotoxy(0, 0);
        printMap();
        gotoxy(pacman.x, pacman.y - 2);
        cout << yellow << pacman.shape << reset;

        power = false;
        timer = 100;

        gotoxy(40, 4);
        cout << "STAGE: 2 (HELL GHOSTS)     ";
        gotoxy(40, 12);
        cout << "CONGRATS!!! TRANSPORTING TO HELLISH STAGE"; Sleep(1000);

        while (game_running && !isWin()) {
            if (timer == 50) {
                power = false;
            }

            timer++;

            // Simpan posisi lama buat cek tabrakan
            int pacman_old_x = pacman.x;
            int pacman_old_y = pacman.y;
            xy ghost_old_pos[4];
            for (int i = 0; i < 4; ++i) {
                ghost_old_pos[i] = {ghost[i].x, ghost[i].y};
            }

            // 1. Gerakan
            move_pacman(pacman, input);
            move_ghost_hard(ghost[0], pacman, power);
            move_ghost_hard(ghost[1], pacman, power);
            move_ghost_hard(ghost[2], pacman, power);
            move_ghost_hard(ghost[3], pacman, power);

            // 2. Makan pellet
            cek_pacman(pacman, score, power, timer);

            // 3. Cek tabrakan
            if (power == false) {
                for (int i = 0; i < 4; i++) {
                    // Tabrakan langsung
                    if (pacman.x == ghost[i].x && pacman.y == ghost[i].y) {
                        game_running = false;
                        break;
                    }
                    // Tabrakan langkah
                    if (pacman.x == ghost_old_pos[i].x && pacman.y == ghost_old_pos[i].y &&
                        pacman_old_x == ghost[i].x && pacman_old_y == ghost[i].y) {
                        game_running = false;
                        break;
                    }
                }
            }

            // 4. Makan hantu
            if (game_running && power == true) { 
                makan_ghost(pacman, ghost, power, score);
            }

            // Update skor
            gotoxy(40, 6);
            cout << "SCORE : " << score;

            Sleep(100);

        }
    }

    // --- yes kalo menang/ kalah ---
    Beep( stage == 2 && isWin() ? 7000 : 5000, 1000); 

    gotoxy(40, 12);
    if (isWin()) {
        cout << "ULTIMATE VICTORY! FINAL SCORE: " << score << "!!!                      ";
    } else {
        cout << "GAME OVER"; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl;
    }

    gotoxy(40, 14);
    cout << "PLEASE INSERT YOUR NAME: ";
    cin >> name; 
    upload_score(name, score);

    gotoxy(40, 16);
    cout << "GOING BACK TO MAIN MENU";
    Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << ".";
}

int main() {
    cek_file_leaderboard();
    srand(time(0));
    
    int pil;
    do {
        int score = 0;
        string name = "";
        pil = menu(); 
        switch (pil) {
        case 1: // Main
            play(score, name);
            break;

        case 2: // Leaderboard
            view_leaderboard();
            break;
        }

    } while (pil != 3); 
    system("cls");
    cout << "Thank You For Playing"; Sleep(100);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    cout << endl << endl;

    return 0;
}

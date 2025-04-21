#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>  // For _getch() on Windows

using namespace std;

// new dimensions
const int ROWS = 10;   // number of rows
const int COLS = 30;   // number of columns

// ANSI escape sequences for coloring
#define ANSI_CLEAR_SCREEN   "\033[2J\033[H"
#define ANSI_COLOR_GREEN    "\033[32;1m"
#define ANSI_COLOR_RESET    "\033[0m"

//--------------------- Base Entity Class -------------------------
class Entity {
protected:
    int x, y;
public:
    Entity(int x, int y) : x(x), y(y) {}
    virtual ~Entity() {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
};

//--------------------- Player Class -------------------------
class Player : public Entity {
public:
    int score;
    int moves;
    bool hasKey;
    Player(int x, int y) : Entity(x, y), score(0), moves(0), hasKey(false) {}
};

//--------------------- Guard Class -------------------------
class Guard : public Entity {
public:
    bool keyGiven;
    Guard(int x, int y) : Entity(x, y), keyGiven(false) {}

    // Ask a cyber/C++ related question. Returns true if answered correctly.
    bool askQuestion() {
        const int numQuestions = 2;
        string questions[numQuestions] = {
            "In C++, which operator is used to access members of a pointer? ",
            "What does 'OOP' stand for in programming? "
        };
        string answers[numQuestions] = {
            "->",
            "Object Oriented Programming"
        };

        int index = rand() % numQuestions;
        cout << ANSI_COLOR_GREEN
             << "\nGuard: Answer the following question to earn the key!\n"
             << "Question: " << questions[index] << "\nYour answer: "
             << ANSI_COLOR_RESET;

        string userAnswer;
        getline(cin, userAnswer);
        if(userAnswer == answers[index]) {
            cout << ANSI_COLOR_GREEN
                 << "Guard: Correct! Here is your key.\n"
                 << ANSI_COLOR_RESET;
            return true;
        } else {
            cout << ANSI_COLOR_GREEN
                 << "Guard: Incorrect answer. Come back later when you are ready.\n"
                 << ANSI_COLOR_RESET;
            return false;
        }
    }
};

//--------------------- Enemy Class -------------------------
class Enemy : public Entity {
public:
    Enemy(int x, int y) : Entity(x, y) {}
    void move(const vector<vector<char>> &maze) {
        int direction = rand() % 4;
        int newX = x, newY = y;
        switch(direction) {
            case 0: newX--; break;
            case 1: newX++; break;
            case 2: newY--; break;
            case 3: newY++; break;
        }
        if(newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS && maze[newX][newY] != '#')
            setPosition(newX, newY);
    }
};

//--------------------- Door Class -------------------------
class Door : public Entity {
public:
    bool isExit;
    Door(int x, int y, bool isExit) : Entity(x, y), isExit(isExit) {}
};

//--------------------- Collectible Class -------------------------
class Collectible : public Entity {
public:
    bool collected;
    Collectible(int x, int y) : Entity(x, y), collected(false) {}
};

//--------------------- MazeGame Class -------------------------
class MazeGame {
private:
    vector<vector<char>> maze;
    Player* player;
    Guard* guard;
    vector<Enemy*> enemies;
    vector<Door*> doors;
    vector<Collectible*> collectibles;
    int level;
    bool gameOver;
    bool levelCompleted;

    // Initialize maze layout based on floor (level)
    void initLevelLayout(int lvl) {
    maze.clear();
    vector<string> layout;

    // --- Complex 30×10 maze ---
    layout.push_back("##############################");
    layout.push_back("#P   ###     #     ###     D#");
    layout.push_back("#  # ###   # ###   # ###   # #");
    layout.push_back("###    #   #####   #####   ###");
    layout.push_back("#    ### ###   ### ###   ### #");
    layout.push_back("#  *  X   *   X   *   X  *   #");
    layout.push_back("#   ### ##### X ###### ##### #");
    layout.push_back("#    G   #       #       #   #");
    layout.push_back("#   D   ###   *   ###    X   #");
    layout.push_back("##############################");

    // copy into maze grid
    for (int i = 0; i < ROWS; i++) {
        vector<char> row;
        for (int j = 0; j < COLS; j++) {
            row.push_back(layout[i][j]);
        }
        maze.push_back(row);
    }
}


    // Initialize entities from the maze layout.
    void initEntities() {
        if(player) { delete player; player = nullptr; }
        if(guard)  { delete guard;  guard  = nullptr; }
        for(auto e : enemies)       delete e;
        for(auto d : doors)         delete d;
        for(auto c : collectibles)  delete c;
        enemies.clear();
        doors.clear();
        collectibles.clear();

        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                char ch = maze[i][j];
                if(ch == 'P') {
                    player = new Player(i, j);
                    maze[i][j] = ' ';
                }
                else if(ch == 'G') {
                    guard = new Guard(i, j);
                    maze[i][j] = ' ';
                }
                else if(ch == 'X') {
                    enemies.push_back(new Enemy(i, j));
                    maze[i][j] = ' ';
                }
                else if(ch == 'D') {
                    // designate exit door on the second‑to‑last row
                    bool isExit = (i == ROWS - 2);
                    doors.push_back(new Door(i, j, isExit));
                }
                else if(ch == '*') {
                    collectibles.push_back(new Collectible(i, j));
                }
            }
        }
    }

public:
    MazeGame(int lvl)
      : player(nullptr), guard(nullptr), level(lvl),
        gameOver(false), levelCompleted(false)
    {
        srand(static_cast<unsigned int>(time(0)));
        initLevelLayout(level);
        initEntities();
    }

    ~MazeGame() {
        delete player;
        delete guard;
        for(auto e : enemies)      delete e;
        for(auto d : doors)        delete d;
        for(auto c : collectibles) delete c;
    }

    void saveMazeToFile(const string &filename) {
        ofstream outFile(filename);
        if(!outFile.is_open()) {
            cout << ANSI_COLOR_GREEN
                 << "Error: Unable to open file for saving maze."
                 << ANSI_COLOR_RESET << "\n";
            return;
        }
        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                outFile << maze[i][j];
            }
            outFile << "\n";
        }
        cout << ANSI_COLOR_GREEN
             << "Maze layout saved to " << filename
             << ANSI_COLOR_RESET << "\n";
        outFile.close();
    }

    void loadMazeFromFile(const string &filename) {
        ifstream inFile(filename);
        if(!inFile.is_open()) {
            cout << ANSI_COLOR_GREEN
                 << "Error: Unable to open file for loading maze."
                 << ANSI_COLOR_RESET << "\n";
            return;
        }
        maze.clear();
        string line;
        while(getline(inFile, line)) {
            vector<char> row;
            for(char c : line) row.push_back(c);
            maze.push_back(row);
        }
        inFile.close();
        initEntities();
        cout << ANSI_COLOR_GREEN
             << "Maze layout loaded from " << filename
             << ANSI_COLOR_RESET << "\n";
    }

    void displayMaze() {
        cout << ANSI_CLEAR_SCREEN << ANSI_COLOR_GREEN;
        // make a copy so we can overlay items
        auto display = maze;
        for(auto c : collectibles) if(!c->collected)
            display[c->getX()][c->getY()] = '*';
        if(guard) display[guard->getX()][guard->getY()] = 'G';
        for(auto e : enemies) display[e->getX()][e->getY()] = 'X';
        if(player) display[player->getX()][player->getY()] = 'P';

        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                cout << display[i][j];
            }
            cout << "\n";
        }
        cout << ANSI_COLOR_RESET;
    }

    void displayStatus() {
        cout << ANSI_COLOR_GREEN
             << "Score: " << player->score
             << " | Moves: " << player->moves
             << " | Key: "   << (player->hasKey ? "Yes" : "No")
             << ANSI_COLOR_RESET << "\n";
    }

    bool isWalkable(int x, int y) {
        return x >= 0 && x < ROWS
            && y >= 0 && y < COLS
            && maze[x][y] != '#';
    }

    bool movePlayer(char direction) {
        int newX = player->getX(), newY = player->getY();
        if(direction == 'W' || direction == 'w') newX--;
        else if(direction == 'S' || direction == 's') newX++;
        else if(direction == 'A' || direction == 'a') newY--;
        else if(direction == 'D' || direction == 'd') newY++;
        else return false;

        if(!isWalkable(newX, newY)) {
            cout << ANSI_COLOR_GREEN
                 << "You cannot move into a wall!"
                 << ANSI_COLOR_RESET << "\n";
            return false;
        }
        // block door if no key
        if(maze[newX][newY] == 'D' && !player->hasKey) {
            cout << ANSI_COLOR_GREEN
                 << "You need a key to open the door!"
                 << ANSI_COLOR_RESET << "\n";
            return false;
        }
        player->setPosition(newX, newY);
        player->moves++;
        return true;
    }

    void moveEnemies() {
        for(auto e : enemies) e->move(maze);
    }

    bool checkCollisions() {
        // enemy collision
        for(auto e : enemies) {
            if(e->getX() == player->getX() && e->getY() == player->getY()) {
                cout << ANSI_COLOR_GREEN
                     << "\nYou were caught by an enemy! Game Over."
                     << ANSI_COLOR_RESET << "\n";
                gameOver = true;
                return true;
            }
        }
        // collectible
        for(auto c : collectibles) {
            if(!c->collected
               && c->getX() == player->getX()
               && c->getY() == player->getY())
            {
                c->collected = true;
                player->score += 10;
                cout << ANSI_COLOR_GREEN
                     << "You collected an item! +10 points."
                     << ANSI_COLOR_RESET << "\n";
                maze[c->getX()][c->getY()] = ' ';
            }
        }
        // guard
        if(guard
           && player->getX() == guard->getX()
           && player->getY() == guard->getY())
        {
            if(!guard->keyGiven && guard->askQuestion()) {
                player->hasKey = true;
                guard->keyGiven = true;
            }
        }
        // door / exit
        for(auto d : doors) {
            if(d->getX() == player->getX()
               && d->getY() == player->getY())
            {
                if(d->isExit && player->hasKey) {
                    levelCompleted = true;
                    return true;
                } else {
                    cout << ANSI_COLOR_GREEN
                         << "\nThis door is a decoy. Try another door."
                         << ANSI_COLOR_RESET << "\n";
                }
            }
        }
        return false;
    }

    void gameLoop() {
        while(!gameOver && !levelCompleted) {
            displayMaze();
            displayStatus();
            cout << ANSI_COLOR_GREEN << "Move (W/A/S/D): " << ANSI_COLOR_RESET;
            char input = _getch();
            cout << input << "\n";
            if(movePlayer(input)) {
                if(checkCollisions()) break;
                moveEnemies();
                if(checkCollisions()) break;
            }
        }
    }

    bool isLevelCompleted() const { return levelCompleted; }
    bool isGameOver()        const { return gameOver; }
};

//--------------------- Menu Functions -------------------------
void showHowToPlay() {
    cout << ANSI_COLOR_GREEN << "\n=== How to Play ===\n";
    cout << "1. Navigate with W, A, S, D (no Enter needed).\n";
    cout << "2. Collect items (*) to increase score.\n";
    cout << "3. Answer the guard's question (G) to earn a key.\n";
    cout << "4. Doors (D) require a key. One door is the exit.\n";
    cout << "5. Avoid enemies (X).\n\n";
    cout << ANSI_COLOR_RESET;
}

void showInstructions() {
    cout << ANSI_COLOR_GREEN << "\n=== Instructions ===\n";
    cout << "Escape the maze by finding the correct door on each floor.\n";
    cout << "After floor 1, you'll be asked if you wish to proceed to floor 2.\n\n";
    cout << ANSI_COLOR_RESET;
}

void startGame() {
    string playerName;
    cout << ANSI_COLOR_GREEN << "\nEnter your name: " << ANSI_COLOR_RESET;
    getline(cin, playerName);

    ofstream outFile("players.txt", ios::app);
    if(outFile.is_open()) {
        outFile << playerName << "\n";
        outFile.close();
        cout << ANSI_COLOR_GREEN
             << "Welcome, " << playerName << "!"
             << ANSI_COLOR_RESET << "\n";
    } else {
        cout << ANSI_COLOR_GREEN
             << "Error: Unable to save your name."
             << ANSI_COLOR_RESET << "\n";
        return;
    }

    // Floor 1
    MazeGame game1(1);
    game1.saveMazeToFile("maze_floor1.txt");
    game1.gameLoop();
    if(game1.isGameOver()) {
        cout << ANSI_COLOR_GREEN
             << "Game Over, better luck next time, " << playerName << "."
             << ANSI_COLOR_RESET << "\n";
        return;
    }
    if(game1.isLevelCompleted()) {
        char choice;
        cout << ANSI_COLOR_GREEN
             << "\nFloor 1 complete! Move to floor 2? (y/n): "
             << ANSI_COLOR_RESET;
        cin >> choice;
        cin.ignore();
        if(choice!='y' && choice!='Y') {
            cout << ANSI_COLOR_GREEN
                 << "Exiting game. Goodbye!"
                 << ANSI_COLOR_RESET << "\n";
            return;
        }
    }

    // Floor 2
    MazeGame game2(2);
    game2.saveMazeToFile("maze_floor2.txt");
    game2.gameLoop();
    if(game2.isGameOver())
        cout << ANSI_COLOR_GREEN
             << "Game Over, better luck next time, " << playerName << "."
             << ANSI_COLOR_RESET << "\n";
    else if(game2.isLevelCompleted())
        cout << ANSI_COLOR_GREEN
             << "\nCongratulations, " << playerName << "! You have escaped!"
             << ANSI_COLOR_RESET << "\n";
}

int main() {
    int choice = 0;
    do {
        cout << ANSI_COLOR_GREEN << "\n=== Maze Game Menu ===\n";
        cout << "1. Start Game\n";
        cout << "2. How to Play\n";
        cout << "3. Instructions\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cout << ANSI_COLOR_RESET;
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: startGame();     break;
            case 2: showHowToPlay(); break;
            case 3: showInstructions(); break;
            case 4:
                cout << ANSI_COLOR_GREEN
                     << "Exiting game. Goodbye!"
                     << ANSI_COLOR_RESET << "\n";
                break;
            default:
                cout << ANSI_COLOR_GREEN
                     << "Invalid choice. Please select 1-4."
                     << ANSI_COLOR_RESET << "\n";
        }
    } while(choice != 4);
    return 0;
}

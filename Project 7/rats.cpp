// rats.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;            // max number of rows in the arena
const int MAXCOLS = 20;            // max number of columns in the arena
const int MAXRATS = 100;           // max number of rats allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Rat declaration.

class Rat
{
public:
    // Constructor
    Rat(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   hasEaten;
    bool   waitTurn;
    bool   deadRat;
    // FINISHED: You'll probably find that a rat object needs additional
    // data members to support your implementation of the behavior affected
    // by poison pellets.
};

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string dropPoisonPellet();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     ratCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRatsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRat(int r, int c);
    bool addPlayer(int r, int c);
    void moveRats();
    
private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rat*    m_rats[MAXRATS];
    int     m_nRats;
    int     m_turns;
    
    // Helper functions
    void checkPos(int r, int c) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int min, int max);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Rat implementation
///////////////////////////////////////////////////////////////////////////

Rat::Rat(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rat must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Rat created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    hasEaten = false;
    waitTurn = true;
    deadRat = false;
}

int Rat::row() const
{
    return m_row;
}

int Rat::col() const
{
    // FINISHED: TRIVIAL:  Return what column the Rat is at
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

bool Rat::isDead() const
{
    // FINISHED: Return whether the Rat is dead
    // Delete the following line and replace it with the correct code.
    
    return deadRat;
    // This implementation compiles, but is incorrect.
}

void Rat::move()
{
    // FINISHED:
    //   Return without moving if the rat has eaten one poison pellet (so
    //   is supposed to move only every other turn) and this is a turn it
    //   does not move.
    
    //   Otherwise, attempt to move in a random direction; if it can't
    //   move, don't move.  If it lands on a poison pellet, eat the pellet,
    //   so it is no longer on that grid point.
    
    int ran = randInt(0,NUMDIRS-1);
    
    if (hasEaten && waitTurn)
    {
        waitTurn = false;
        return;
    }
    attemptMove(*m_arena, ran, m_row, m_col);
    
    if ((hasEaten && !waitTurn))
    {
        waitTurn = true;
        if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row, m_col, EMPTY);
            deadRat = true;
        }
    }
    if (!hasEaten)
    {
        if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row, m_col, EMPTY);
            hasEaten = true;
        }
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    // FINISHED: TRIVIAL:  Return what row the Player is at
    // Delete the following line and replace it with the correct code.
    return m_row;  // This implementation compiles, but is incorrect.
}

int Player::col() const
{
    // FINISHED: TRIVIAL:  Return what column the Player is at
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

string Player::dropPoisonPellet()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poison pellet at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poison pellet has been dropped.";
}

string Player::move(int dir)
{
    //        FINISHED:  Attempt to move the player one step in the indicated
    //        direction.  If this fails,
    //        return "Player couldn't move; player stands."
    //        A player who moves onto a rat dies, and this
    //        returns "Player walked into a rat and died."
    //        Otherwise, return one of "Player moved north.",
    //        "Player moved east.", "Player moved south.", or
    //        "Player moved west."
    
    bool truth = attemptMove(*m_arena, dir, m_row, m_col);
    
    if (m_arena->numberOfRatsAt(m_row,m_col) > 0)
    {
        setDead();
        return "Player walked into a rat and died.";
    }
    
    
    if (truth)
    {
        switch(dir)
        {
            case 0: return "Player moved north.";
            case 1: return "Player moved east.";
            case 2: return "Player moved south.";
            case 3: return "Player moved west.";
        }
    }
    return "Player couldn't move; player stands.";
    
    // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    // Finished: Return whether the Player is dead
    // Delete the following line and replace it with the correct code.
    //This implementation compiles, but is incorrect.
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRats = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    // FINISHED:  Deallocate the player and all remaining dynamically allocated rats
    for (int i = 0; i < m_nRats; i++)
        delete m_rats[i];
    delete m_player;
}

int Arena::rows() const
{
    // FINISHED: TRIVIAL:  Return the number of rows in the arena
    // Delete the following line and replace it with the correct code.
    return m_rows;  // This implementation compiles, but is incorrect.
}

int Arena::cols() const
{
    // FINISHED: TRIVIAL:  Return the number of columns in the arena
    // Delete the following line and replace it with the correct code.
    return m_cols;  // This implementation compiles, but is incorrect.
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::ratCount() const
{
    // FINISHED: TRIVIAL:  Return the number of rats in the arena
    // Delete the following line and replace it with the correct code.
    return m_nRats;  // This implementation compiles, but is incorrect.
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

int Arena::numberOfRatsAt(int r, int c) const
{
    // FINISHED:  Return the number of rats at row r, column c
    // Delete the following line and replace it with the correct code.
    
    int counter = 0;
    for (int i = 0; i < m_nRats; i++)
    {
        if (m_rats[i]->row() == r && m_rats[i]->col() == c)
            counter++;
    }
    return counter;  // This implementation compiles, but is incorrect.
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill displayGrid with dots (empty) and stars (poison pellets)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');
    
    // Indicate each rat's position
    // FINISHED:  If one rat is at some grid point, set the displayGrid char
    //        to 'R'.  If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    
    for (int i = 1; i <= rows(); i++)
    {
        for (int j = 1; j <= cols(); j++)
        {
            if (numberOfRatsAt(i,j) > 9)
                displayGrid[i-1][j-1] = '9';
            else if (numberOfRatsAt(i,j) > 1 && numberOfRatsAt(i,j) < 9)
                displayGrid[i-1][j-1] = numberOfRatsAt(i,j) + 48;
            else if (numberOfRatsAt(i,j) == 1)
                displayGrid[i-1][j-1] = 'R';
        }
    }
    
    
    // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');
    
    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
    // Write message, rat, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << ratCount() << " rats remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Arena::addRat(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;
    
    // Don't add a rat on a spot with a poison pellet
    if (getCellStatus(r, c) != EMPTY)
        return false;
    
    // Don't add a rat on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
    // If there are MAXRATS existing rats, return false.  Otherwise,
    // dynamically allocate a new rat at coordinates (r,c).  Save the
    // pointer to the newly allocated rat and return true.
    
    // FINISHED:  Implement this.
    if (m_nRats == MAXRATS)
        return false;
    
    m_rats[m_nRats] = new Rat(this, r, c);
    m_nRats++;
    return true;  // This implementation compiles, but is incorrect.
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;
    
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Don't add a player on a spot with a rat
    if (numberOfRatsAt(r, c) > 0)
        return false;
    
    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRats()
{
    // Move all rats
    // FINISHED:  Move each rat.  Mark the player as dead if necessary.
    //        Deallocate any dead dynamically allocated rat.
    for (int i = 0; i < m_nRats; i++)
        m_rats[i]->move();
    
    int r = m_player->row();
    int c = m_player->col();
    if (numberOfRatsAt(r,c) > 0)
        m_player->setDead();
    
    for (int i = 0; i < m_nRats; i++)
    {
        if (m_rats[i]->isDead())
        {
            delete m_rats[i];
            
            for (int j = i; j < m_nRats-1; j++)
            {
                m_rats[j] = m_rats[j+1];
            }
            m_nRats--;
            i--;
        }
    }
    // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  ||  c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
        << c << ")" << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRats)
{
    if (nRats < 0)
    {
        cout << "***** Cannot create Game with negative number of rats!" << endl;
        exit(1);
    }
    if (nRats > MAXRATS)
    {
        cout << "***** Trying to create Game with " << nRats
        << " rats; only " << MAXRATS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nRats > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the rats!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with rats
    while (nRats > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRat(r, c);
        nRats--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);
        
        Player* player = m_arena->player();
        int dir;
        
        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonPellet();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->dropPoisonPellet();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    while ( ! m_arena->player()->isDead()  &&  m_arena->ratCount() > 0)
    {
        string msg = takePlayerTurn();
        Player* player = m_arena->player();
        if (player->isDead())
        {
            cout << msg << endl;
            break;
        }
        m_arena->moveRats();
        m_arena->display(msg);
    }
    if (m_arena->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

// Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
        default:  return false;
        case 'n': dir = NORTH; break;
        case 'e': dir = EAST;  break;
        case 's': dir = SOUTH; break;
        case 'w': dir = WEST;  break;
    }
    return true;
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would run off the edge of the arena.
// Otherwise, update r and c to the position resulting from the move and
// return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    // FINISHED:  Implement this function
    // Delete the following line and replace it with the correct code.
    
    if (dir == 0 && r == 1)                             //North
        return false;
    else if (dir == 0)
        r--;
    
    if (dir == 1 && c == a.cols())                      //East
        return false;
    else if (dir == 1)
        c++;
    
    if (dir == 2 && r == a.rows())                      //South
        return false;
    else if (dir == 2)
        r++;
    
    if (dir == 3 && c == 1)                             //West
        return false;
    else if (dir == 3)
        c--;
    return true;  // This implementation compiles, but is incorrect.
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poison pellet and not
// move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // FINISHED:  Implement this function
    // Delete the following line and replace it with your code.
    
    
    int badN = a.numberOfRatsAt (r-1,c-1) + a.numberOfRatsAt (r-2,c) + a.numberOfRatsAt (r-1,c+1);
    int badE = a.numberOfRatsAt (r-1,c+1) + a.numberOfRatsAt (r,c+2) + a.numberOfRatsAt (r+1,c+1);
    int badS = a.numberOfRatsAt (r+1,c-1) + a.numberOfRatsAt (r+2,c) + a.numberOfRatsAt (r+1,c+1);
    int badW = a.numberOfRatsAt (r-1,c-1) + a.numberOfRatsAt (r,c-2) + a.numberOfRatsAt (r+1,c-1);
    
    bool atN = (a.numberOfRatsAt (r-1,c) > 0);
    bool atE = (a.numberOfRatsAt (r,c+1) > 0);
    bool atS = (a.numberOfRatsAt (r+1,c) > 0);
    bool atW = (a.numberOfRatsAt (r,c-1) > 0);
    
    bool wallN = (r == 1);
    bool wallE = (c == a.cols());
    bool wallS = (r == a.rows());
    bool wallW = (c == 1);
    
    if (atN && atE && atS && atW)       //Case with Four
        return false;
    
    else if (atN && atE && atS)              //Case with Three
    {
        if (wallW)
            return false;
        bestDir = WEST;
        return true;
    }
    else if (atN && atE && atW)
    {
        if (wallS)
            return false;
        bestDir = SOUTH;
        return true;
    }
    else if (atN && atS && atW)
    {
        if (wallE)
            return false;
        bestDir = EAST;
        return true;
    }
    else if (atS && atE && atW)
    {
        if (wallN)
            return false;
        bestDir = NORTH;
        return true;
    }
    
    else if (atN && atE)                     //Case with Two
    {
        if (wallW && wallS)
            return false;
        else if (wallW)
            bestDir = SOUTH;
        else if (wallS)
            bestDir = WEST;
        else if (badS > badW)
            bestDir = WEST;
        else
            bestDir = SOUTH;
        return true;
    }
    else if (atN && atS)
    {
        if (wallW && wallE)
            return false;
        else if (wallW)
            bestDir = EAST;
        else if (wallE)
            bestDir = WEST;
        else if (badW > badE)
            bestDir = EAST;
        else
            bestDir = WEST;
        return true;
    }
    else if (atN && atW)
    {
        if (wallS && wallE)
            return false;
        else if (wallS)
            bestDir = EAST;
        else if (wallE)
            bestDir = SOUTH;
        else if (badS > badE)
            bestDir = EAST;
        else
            bestDir = SOUTH;
        return true;
    }
    else if (atS && atW)
    {
        if (wallN && wallE)
            return false;
        else if (wallN)
            bestDir = EAST;
        else if (wallE)
            bestDir = NORTH;
        else if (badN > badE)
            bestDir = EAST;
        else
            bestDir = NORTH;
        return true;
    }
    else if (atS && atE)
    {
        if (wallN && wallW)
            return false;
        else if (wallN)
            bestDir = WEST;
        else if (wallW)
            bestDir = NORTH;
        else if (badN > badW)
            bestDir = WEST;
        else
            bestDir = NORTH;
        return true;
    }
    else if (atW && atE)
    {
        if (wallN && wallS)
            return false;
        else if (wallN)
            bestDir = SOUTH;
        else if (wallS)
            bestDir = NORTH;
        else if (badN > badS)
            bestDir = SOUTH;
        else
            bestDir = NORTH;
        return true;
    }
    
    else if (atN)                            //Case with One
    {
        if (wallW && wallS)
            bestDir = EAST;
        else if (wallE && wallS)
            bestDir = WEST;
        else if (wallW)
            bestDir = (badE > badS) ? SOUTH : EAST;
        else if (wallE)
            bestDir = (badW > badS) ? SOUTH : WEST;
        else if (wallS)
            bestDir = (badW > badE) ? EAST : WEST;
        else if (badS <= badW && badS <= badE)
            bestDir = SOUTH;
        else if (badE <= badS && badE <= badW)
            bestDir = EAST;
        else
            bestDir = WEST;
        return true;
    }
    else if (atE)
    {
        if (wallW && wallN)
            bestDir = SOUTH;
        else if (wallW && wallS)
            bestDir = NORTH;
        else if (wallW)
            bestDir = (badN > badS) ? SOUTH : NORTH;
        else if (wallS)
            bestDir = (badN > badS) ? SOUTH : NORTH;
        else if (wallN)
            bestDir = (badW > badS) ? SOUTH : WEST;
        else if (badN <= badS && badN <= badW)
            bestDir = NORTH;
        else if (badS <= badN && badS <= badW)
            bestDir = SOUTH;
        else
            bestDir = WEST;
        return true;
    }
    else if (atS)
    {
        if (wallW && wallN)
            bestDir = EAST;
        else if (wallE && wallN)
            bestDir = WEST;
        else if (wallN)
            bestDir = (badE > badW) ? WEST : EAST;
        else if (wallW)
            bestDir = (badN > badE) ? EAST : NORTH;
        else if (wallE)
            bestDir = (badN > badW) ? WEST : NORTH;
        else if (badE <= badN && badE <= badW)
            bestDir = EAST;
        else if (badN <= badE && badN <= badW)
            bestDir = NORTH;
        else
            bestDir = WEST;
        return true;
    }
    else if (atW)
    {
        if (wallS && wallE)
            bestDir = NORTH;
        else if (wallN && wallE)
            bestDir = SOUTH;
        else if (wallN)
            bestDir = (badS > badE) ? EAST : SOUTH;
        else if (wallE)
            bestDir = (badN > badS) ? SOUTH : NORTH;
        else if (wallS)
            bestDir = (badN > badE) ? EAST : NORTH;
        else if (badN <= badS && badN <= badE)
            bestDir = NORTH;
        else if (badE <= badN && badE <= badS)
            bestDir = EAST;
        else
            bestDir = SOUTH;
        return true;
    }
    
    else
    {
        if (badN == 0 && badS == 0 && badE == 0 && badW == 0)
        {
            if (a.getCellStatus (r,c) == HAS_POISON)
            {
                int i = randInt (0, NUMDIRS-1);
                switch (i)
                {
                    case 0:
                    {
                        if (wallN)
                            i = SOUTH;
                        break;
                    }
                    case 1:
                    {
                        if (wallE)
                            i = WEST;
                        break;
                    }
                    case 2:
                    {
                        if (wallS)
                            i = NORTH;
                        break;
                    }
                    case 3:
                    {
                        if (wallW)
                            i = EAST;
                        break;
                    }
                }
                bestDir = i;
            }
            else
                return false;
        }
        else if ((badN > 0 && badS > 0) || (badE > 0 && badW > 0))
        {
            return false;
        }
        else if (badN > 0 && badS == 0)
        {
            if (!wallS)
                bestDir = SOUTH;
            else
            {
                if (badW > 0 && badE > 0)
                    return false;
                else if (badW >= badE)
                    bestDir = (!wallE) ? EAST : WEST;
            }
        }
        else if (badS > 0 && badN == 0)
        {
            if (!wallN)
                bestDir = NORTH;
            else
            {
                if (badW > 0 && badE > 0)
                    return false;
                else if (badW >= badE)
                    bestDir = (!wallE) ? EAST : WEST;
            }
        }
        else if (badW > 0 && badE == 0)
        {
            if (!wallE)
                bestDir = EAST;
            else
            {
                if (badN > 0 && badS > 0)
                    return false;
                else if (badN >= badS)
                    bestDir = (!wallS) ? SOUTH : NORTH;
            }
        }
        else if (badE > 0 && badW == 0)
        {
            if (!wallW)
                bestDir = WEST;
            else
                if (badN > 0 && badS >0)
                    return false;
                else if (badN >= badS)
                    bestDir = (!wallS) ? SOUTH : NORTH;
        }
        else
        {
            if (a.getCellStatus (r,c) != HAS_POISON)
                return false;
            else
                bestDir = randInt(0,NUMDIRS-1);
        }
        return true;
        
    }
    // This implementation compiles, but is incorrect.
    
    // Your replacement implementation should do something intelligent.
    // You don't have to be any smarter than the following, although
    // you can if you want to be:  If staying put runs the risk of a
    // rat possibly moving onto the player's location when the rats
    // move, yet moving in a particular direction puts the player in a
    // position that is safe when the rats move, then the chosen
    // action is to move to a safer location.  Similarly, if staying put
    // is safe, but moving in certain directions puts the player in danger,
    // then the chosen action should not be to move in one of the
    // dangerous directions; instead, the player should stay put or move to
    // another safe position.  In general, a position that may be moved to
    // by many rats is more dangerous than one that may be moved to by
    // few.
    //
    // Unless you want to, you do not have to take into account that a
    // rat might be poisoned and thus sometimes less dangerous than one
    // that is not.  That requires a more sophisticated analysis that
    // we're not asking you to do.
}


///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{

    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10,12,20);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

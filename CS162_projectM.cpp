#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int GetNumPlayers();
void PlayGame(int numPlayers);
void InitializeScores(int* scores, int numPlayers);
int PlayerTurn(int playerNumber);
int GetMoneyBallRack();
int GetShootingCapability();
int ShootRack(int rack, int moneyRack, int shootingCap);
int ShootBall(int shootingCap, int points);
void DeclareWinner(int* scores, int numPlayers);
int ShootStarryBall(int shootingCap);
bool AskPlayAgain();

/*
 * Main function block comment:
 * Main entry point of the program. It initializes the random number generator and prompts
 * the user for the number of players before starting the game.
 */
int main() {
    srand(time(nullptr)); // Seed random number generator

    int numPlayers;
    bool playAgain = true;

    while (playAgain) {
        numPlayers = GetNumPlayers(); // Get number of players

        if (numPlayers < 2) {
            cout << "You need at least 2 players to play!" << endl;
            return 1;
        }
        
        PlayGame(numPlayers); // Start the game with N players

        playAgain = AskPlayAgain(); // Ask if players want to play again
    }

    cout << "Thanks for playing! Goodbye!" << endl;
    return 0;
}

/*
 * Function: getNumPlayers
 * Prompts the user for the number of players and returns it.
 */
int GetNumPlayers() {
    int numPlayers;
    cout << "Welcome to the basketball shooting contest!" << endl;
    cout << "Enter the number of players: ";
    cin >> numPlayers;
    return numPlayers;
}

/*
 * Function: playGame
 * Main game loop. Allocates dynamic memory for player scores and loops through each player's turn.
 */
void PlayGame(int numPlayers) {
    int* scores = new int[numPlayers]; // Dynamic array for scores
    InitializeScores(scores, numPlayers); // Initialize scores

    for (int i = 0; i < numPlayers; i++) {
        scores[i] = PlayerTurn(i + 1); // Get player's score after their turn
    }

    DeclareWinner(scores, numPlayers); // Declare winner
    delete[] scores; // Free memory
}

/*
 * Function: initializeScores
 * Initializes the scores array by setting all scores to zero.
 */
void InitializeScores(int* scores, int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        scores[i] = 0;
    }
}

/*
 * Function: playerTurn
 * Handles a player's turn, including choosing the money-ball rack, shooting, and scoring.
 */
int PlayerTurn(int playerNumber) {
    int moneyRack = GetMoneyBallRack(); // Get money-ball rack position
    int shootingCap = GetShootingCapability(); // Get shooting capability

    int totalScore = 0;
    for (int rack = 1; rack <= 5; rack++) {
        totalScore += ShootRack(rack, moneyRack, shootingCap); // Simulate shots

        if (rack == 2 || rack == 4) {
            totalScore += ShootStarryBall(shootingCap); // Starry ball shots between racks
        }
    }

    cout << "Total: " << totalScore << " pts" << endl << endl;
    return totalScore;
}

/*
 * Function: getMoneyBallRack
 * Prompts the player to choose a money-ball rack (1-5) and returns the valid input.
 */
int GetMoneyBallRack() {
    int moneyRack;
    do {
        cout << "Where do you want to put your money-ball rack? Enter 1-5: ";
        cin >> moneyRack;

        if (moneyRack < 1 || moneyRack > 5){
            cout << "Invalid input. Enter a number between 1 and 5 inclusive." << endl;
        }
    } while (moneyRack < 1 || moneyRack > 5);
    return moneyRack;
}

/*
 * Function: getShootingCapability
 * Prompts the player for their shooting capability (1-99) and returns it.
 */
int GetShootingCapability() {
    int shootingCap;
    do {
        cout << "Enter your shooting capability, from 1 to 99: ";
        cin >> shootingCap;

        if (shootingCap < 1 || shootingCap > 99){
            cout << "Invalid input. Enter a number between 1 and 99 inclusive." << endl;
        }
    } while (shootingCap < 1 || shootingCap > 99);
    return shootingCap;
}

/*
 * Function: shootRack
 * Simulates shooting for a single rack, displaying the results and returning the score.
 * If the current rack is the money-ball rack, all balls in that rack are worth 2 points.
 * Otherwise, the rack only has regular shots worth 1 point.
 */
int ShootRack(int rack, int moneyRack, int shootingCap) {
    int rackScore = 0;
    cout << "Rack " << rack << ": ";

    if (rack == moneyRack) { // Money ball rack: all balls are worth 2 points
        for (int j = 0; j < 5; j++) {
            rackScore += ShootBall(shootingCap, 2); // All shots in this rack are worth 2 points
        }
    } else { // Regular rack with only regular shots (no money balls)
        for (int j = 0; j < 5; j++) {
            rackScore += ShootBall(shootingCap, 1); // Regular shots worth 1 point
        }
    }

    cout << "| " << rackScore << " pts" << endl;
    return rackScore;
}

/*
 * Function: shootBall
 * Simulates the shooting of a ball. Returns the points earned (0 for miss, X points for made shot).
 */
int ShootBall(int shootingCap, int points) {
    if (rand() % 100 < shootingCap) {
        cout << (points == 2 ? "M " : "X "); // Made shot (M for money ball)
        return points;
    } else {
        cout << "_ "; // Missed shot
        return 0;
    }
}

/*
 * Function: shootStarryBall
 * Simulates shooting the Starry ball between racks. Returns the score for the Starry ball shot.
 * Prints "S" if the Starry ball is made, and "_" if missed.
 */
int ShootStarryBall(int shootingCap) {
    cout << "Starry: ";
    if (rand() % 100 < shootingCap) {
        cout << "S | 3 pts" << endl;
        return 3; // Starry ball worth 3 points
    } else {
        cout << "_ | 0 pts" << endl;
        return 0; // Missed Starry ball
    }
}

/*
 * Function: declareWinner
 * Determines and declares the winner based on the scores array.
 */
void DeclareWinner(int* scores, int numPlayers) {
    int winnerIndex = 0;
    for (int i = 1; i < numPlayers; i++) {
        if (scores[i] > scores[winnerIndex]) {
            winnerIndex = i;
        }
    }
    cout << "Player " << winnerIndex + 1 << " is the winner!" << endl;
}

/*
 * Function: askPlayAgain
 * Prompts the players whether they want to play again. Returns true for "yes", false for "no".
 */
bool AskPlayAgain() {
    int playAgain;
    do {
        cout << "Do you want to play again? (1 for Yes, 0 for No): ";
        cin >> playAgain;
    } while (playAgain != 1 && playAgain != 0);

    return playAgain == 1;
}

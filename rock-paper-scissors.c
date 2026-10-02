#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Standard Move Representation
typedef enum {
    MOVE_NONE = 0,
    MOVE_ROCK = 1,
    MOVE_PAPER = 2,
    MOVE_SCISSORS = 3,
    MOVE_QUIT = 4
} Move;

typedef enum {
    RESULT_DRAW,
    RESULT_PLAYER_WIN,
    RESULT_COMPUTER_WIN
} GameResult;

// Function prototypes
void clear_input_buffer(void);
Move get_player_move(void);
Move get_computer_move(void);
GameResult determine_winner(Move player, Move computer);
const char* move_to_string(Move move);
void print_scoreboard(int player_wins, int computer_wins, int draws);

int main(void) {
    // Seed the pseudo-random number generator
    srand((unsigned int)time(NULL));

    int player_wins = 0;
    int computer_wins = 0;
    int draws = 0;

    printf("========================================");
    printf("\n    Welcome to Rock, Paper, Scissors!\n");
    printf("========================================\n\n");

    while (1) {
        Move player = get_player_move();
        
        if (player == MOVE_QUIT) {
            printf("\nThanks for playing!\n");
            break;
        }

        Move computer = get_computer_move();

        printf("\nYou chose:       %s\n", move_to_string(player));
        printf("Computer chose:  %s\n", move_to_string(computer));

        GameResult result = determine_winner(player, computer);

        switch (result) {
            case RESULT_DRAW:
                printf("Outcome:         It's a draw!\n");
                draws++;
                break;
            case RESULT_PLAYER_WIN:
                printf("Outcome:         You win this round!\n");
                player_wins++;
                break;
            case RESULT_COMPUTER_WIN:
                printf("Outcome:         Computer wins this round!\n");
                computer_wins++;
                break;
        }

        print_scoreboard(player_wins, computer_wins, draws);
    }

    return 0;
}

/**
 * Clears remaining input characters from stdin to prevent infinite loops on invalid input.
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard characters
    }
}

/**
 * Prompts the user for a valid move and handles invalid inputs gracefully.
 */
Move get_player_move(void) {
    int choice;
    
    while (1) {
        printf("\nSelect your move:\n");
        printf("  [1] Rock\n");
        printf("  [2] Paper\n");
        printf("  [3] Scissors\n");
        printf("  [4] Quit Game\n");
        printf("Enter choice (1-4): ");

        if (scanf("%d", &choice) == 1) {
            if (choice >= 1 && choice <= 4) {
                clear_input_buffer();
                return (Move)choice;
            }
        }
        
        // Handle invalid input or non-integer characters
        printf("\n[Error] Invalid choice. Please enter a number between 1 and 4.\n");
        clear_input_buffer();
    }
}

/**
 * Generates a random move for the computer.
 */
Move get_computer_move(void) {
    return (Move)((rand() % 3) + 1);
}

/**
 * Compares moves and returns the round result.
 */
GameResult determine_winner(Move player, Move computer) {
    if (player == computer) {
        return RESULT_DRAW;
    }

    // Mathematical rule check: (player - computer + 3) % 3
    // 1 (Win), 2 (Loss)
    if ((player == MOVE_ROCK && computer == MOVE_SCISSORS) ||
        (player == MOVE_PAPER && computer == MOVE_ROCK) ||
        (player == MOVE_SCISSORS && computer == MOVE_PAPER)) {
        return RESULT_PLAYER_WIN;
    }

    return RESULT_COMPUTER_WIN;
}

/**
 * Helper to get printable representation of a move.
 */
const char* move_to_string(Move move) {
    switch (move) {
        case MOVE_ROCK:     return "Rock";
        case MOVE_PAPER:    return "Paper";
        case MOVE_SCISSORS: return "Scissors";
        default:            return "Unknown";
    }
}

/**
 * Prints current match tally.
 */
void print_scoreboard(int player_wins, int computer_wins, int draws) {
    printf("----------------------------------------\n");
    printf("Score -> You: %d | Computer: %d | Draws: %d\n", player_wins, computer_wins, draws);
    printf("----------------------------------------\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FONT_SIZE 128

// Global variables
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
SDL_Color text_color = {255, 0, 0, 255}; // Red text color
int seconds_remaining = 60; // Countdown starts at 60 seconds

// Function declarations
bool initialize();
void close_game();
void display_time_remaining(int seconds_remaining);
void display_game_over();

int main() {
    int choice;
    
    // Initialize SDL and TTF
    if (!initialize()) {
        printf("Error initializing SDL and TTF.\n");
        return EXIT_FAILURE;
    }
    
    // Main game loop
    while (true) {
        // Display the menu and get user choice
        printf("1. Cut the green wire\n");
        printf("2. Cut the red wire\n");
        printf("3. Cut the blue wire\n");
        printf("4. Yank them all out\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        printf("\n");

        // Process the user choice
        switch (choice) {
            case 1:
                // Cut the green wire - reduce time remaining to 45 seconds
                seconds_remaining = 45;
                break;
            case 2:
                // Cut the red wire - game over
                printf("KABOOM! You cut the red wire. Game over.\n");
                display_game_over();
                close_game();
                return EXIT_SUCCESS;
            case 3:
                // Cut the blue wire - reset time remaining to 60 seconds
                seconds_remaining = 60;
                break;
            case 4:
                // Yank them all out - game over
                printf("You yanked all the wires out. Game over.\n");
                display_game_over();
                close_game();
                return EXIT_SUCCESS;
            default:
                // Invalid choice - game over
                printf("Invalid choice. Game over.\n");
                display_game_over();
                close_game();
                return EXIT_SUCCESS;
        }
        
        // Countdown loop
        while (seconds_remaining > 0) {
            display_time_remaining(seconds_remaining);

            // Delay for one second
            SDL_Delay(1000);

            seconds_remaining--;
        }

        // Time's up - game over
        printf("Time's up. Game over.\n");
        display_game_over();
        close_game();
        return EXIT_SUCCESS;
    }

    return 0;
}

bool initialize() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not be initialized: %s\n", SDL_GetError());
        return false;
    }

    // Initialize TTF
    if (TTF_Init() < 0) {
        fprintf(stderr, "SDL_ttf could not be initialized: %s\n", TTF_GetError());
        return false;
    }

    // Create the window
    window = SDL_CreateWindow("Countdown Timer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return false;
    }

    // Create the renderer
    renderer = SDL
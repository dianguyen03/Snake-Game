#include "game.h"
#include <SDL.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_SIZE = 20;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void setup(struct Game_struct* game){
    // initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // initialize game variables
    game->snake.x = SCREEN_WIDTH/2;
    game->snake.y = SCREEN_HEIGHT/2;
    game->fruit.x = rand() % (SCREEN_WIDTH/GRID_SIZE) * GRID_SIZE;
    game->fruit.y = rand() % (SCREEN_HEIGHT/GRID_SIZE) * GRID_SIZE;
    game->score = 0;
    game->dir = STOP;

    // initialize snake's body
    game->bodyLength = 1;
    game->body = (struct Size_struct*)malloc(game->bodyLength * sizeof(struct Size_struct));
    game->body[0].x = game->snake.x;
    game->body[0].y = game->snake.y;

    // create SDL window & renderer
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // print the starting statement
    game->round = 1;
    printf("Game started! Round %d\n", game->round);
}

void draw(struct Game_struct* game){
    // clear the terminal
    system("clear");

    // colors the screen black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw snake's body
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < game->bodyLength; i++) {
        SDL_Rect segmentRect = { game->body[i].x, game->body[i].y, GRID_SIZE, GRID_SIZE };
        SDL_RenderFillRect(renderer, &segmentRect);
    }

    // draw snake's head
    SDL_Rect headRect = { game->snake.x, game->snake.y, GRID_SIZE, GRID_SIZE };
    SDL_RenderFillRect(renderer, &headRect);

    // draw fruit
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect fruitRect = {game->fruit.x, game->fruit.y, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(renderer, &fruitRect);

    SDL_RenderPresent(renderer);
}

void handleInput(SDL_Event event, struct Game_struct* game)
{
    // processes user's arrow inputs
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:
                if (game->dir != RIGHT)
                    game->dir = LEFT;
                break;
            case SDLK_RIGHT:
                if (game->dir != LEFT)
                    game->dir = RIGHT;
                break;
            case SDLK_UP:
                if (game->dir != DOWN)
                    game->dir = UP;
                break;
            case SDLK_DOWN:
                if (game->dir != UP)
                    game->dir = DOWN;
                break;
        }
    }
}

void updateGame(struct Game_struct* game)
{
    // update the position of the snake's body
    for (int i = game->bodyLength - 1; i > 0; i--) {
        game->body[i].x = game->body[i - 1].x;
        game->body[i].y = game->body[i - 1].y;
    }
    game->body[0].x = game->snake.x;
    game->body[0].y = game->snake.y;

    // update the position of the snake's head based on the direction
    switch (game->dir) {
        case LEFT:
            game->snake.x -= GRID_SIZE;
            break;
        case RIGHT:
            game->snake.x += GRID_SIZE;
            break;
        case UP:
            game->snake.y -= GRID_SIZE;
            break;
        case DOWN:
            game->snake.y += GRID_SIZE;
            break;
        default:
            break;
    }

    // check for collision with the snake's body
    for (int i = 1; i < game->bodyLength; i++) {
        if (game->snake.x == game->body[i].x && game->snake.y == game->body[i].y) {
            resetGame(game);
            break;
        }
    }

    // check if the snake goes out of bounds
    if (game->snake.x < 0 || game->snake.x >= SCREEN_WIDTH || game->snake.y < 0 || game->snake.y >= SCREEN_HEIGHT) {
        resetGame(game);
    }

    // when it eats the fruit
    if (game->snake.x == game->fruit.x && game->snake.y == game->fruit.y) {
        // increase the score
        game->score++;

        // spawn a new fruit at a random position
        game->fruit.x = rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE;
        game->fruit.y = rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE;

        // increase the size of the snake's body
        game->bodyLength++;
        game->body = (struct Size_struct*)realloc(game->body, game->bodyLength * sizeof(struct Size_struct));
        game->body[game->bodyLength - 1].x = game->snake.x;
        game->body[game->bodyLength - 1].y = game->snake.y;
    }
}

void resetGame(struct Game_struct* game)
{

    // game over
    printf("Game over! Final score: %d\n", game->score);

    // reset the game state
    game->snake.x = SCREEN_WIDTH / 2;
    game->snake.y = SCREEN_HEIGHT / 2;
    game->fruit.x = rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE;
    game->fruit.y = rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE;
    game->score = 0;
    game->dir = STOP;
    game->bodyLength = 1;
    free(game->body);
    game->body = (struct Size_struct*)malloc(game->bodyLength * sizeof(struct Size_struct));
    game->body[0].x = game->snake.x;
    game->body[0].y = game->snake.y;

    // print the updated round
    game->round++;
    printf("Round %d\n", game->round);
}

void cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
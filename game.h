#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <stdbool.h>
#include <SDL.h>
#include <stdio.h>

struct Size_struct{
    int x;
    int y;
} Size;

struct Snake_struct {
    int x;
    int y;
} Snake;

struct Fruit_struct {
    int x;
    int y;
} Fruit;

struct Game_struct {
    struct Snake_struct snake;
    struct Fruit_struct fruit;
    struct Size_struct* body;
    int score;
    int bodyLength;
    int round;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN} dir;
};

void setup(struct Game_struct* game);
void draw(struct Game_struct* game);
void handleInput(SDL_Event event, struct Game_struct* game);
void updateGame(struct Game_struct* game);
void resetGame(struct Game_struct* game);
void cleanup();

#endif //SNAKE_GAME_H

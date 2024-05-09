#include <SDL.h>
#include "game.h"

int main()
{
    struct Game_struct game;
    setup(&game);


    SDL_Event event;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            // when the user closes the window
            if (event.type == SDL_QUIT)
                quit = true;
            // when a key is pressed
            else if (event.type == SDL_KEYDOWN)
                handleInput(event, &game);
        }

        // updates & renders accordingly
        updateGame(&game);
        draw(&game);

        // delays the speed of the snake
        SDL_Delay(100);
    }

    cleanup();

    return 0;
}
#define SDL_MAIN_HANDLED

#include <dependencies.h>

int main(int argc, char *argv[]){
    init();
    clrscr();

    Sprite mario;
    Sprite *marioptr = &mario;
    initSprite(marioptr, "src/images/mario.png");

    draw(marioptr); 
    update();
    MakeWindowTransparent(window, RGB(1, 1, 1));
    SDL_Delay(1000);
    printf("Looks like an error occured : %s \n", SDL_GetError());

    SDL_Event windowEvent;
    bool running = true;   
    while(running){
        if(SDL_PollEvent(&windowEvent)){
            if(SDL_QUIT == windowEvent.type)break;
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_ESCAPE])running = false;

        update();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
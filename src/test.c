#include <SDL2/SDL.h>
#include <windows.h>
#include <SDL2/SDL_syswm.h>
#include <stdbool.h>
#include <SDL2/SDL_scancode.h>


bool MakeWindowTransparent(SDL_Window* window, COLORREF colorKey) {
    // Get window handle (https://stackoverflow.com/a/24118145/3357935)
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    // Change window type to layered (https://stackoverflow.com/a/3970218/3357935)
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Set transparency color
    return SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}

int main(int argc, char** argv) {
    // Get resolution of primary monitor
    int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
    int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

    SDL_Window* window = SDL_CreateWindow("SDL Transparent Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        desktopWidth/2, desktopHeight/2, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set background color to magenta and clear screen    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);

    // Draw a greyish square the size of the screen first
    SDL_Rect rect0 = {0, 0, desktopWidth/2, desktopHeight/2};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect0);

    // Draw blue square in top-left corner
    SDL_Rect rect1 = {0, 0, 100, 100};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect1);

    // Draw red square in center of the screen
    SDL_Rect rect2 = {(desktopWidth/2-100)/2, (desktopHeight/2-100)/2, 100, 100};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect2);

    // Add window transparency (grey will be see-through)
    // can't make black a transparent color
    MakeWindowTransparent(window, RGB(50, 50, 50));

    // Render the square to the screen
    SDL_RenderPresent(renderer);

    // Loop until user quits
    bool quit = false;
    SDL_Event event;
    while (!quit) {
       while (SDL_PollEvent(&event) != 0) {
           if (event.type == SDL_QUIT) {
               quit = true;
           }
       }

       const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_ESCAPE])quit = false;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
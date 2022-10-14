#ifndef dependencies

    #include <consts.h>
    #include <libs.h>
    #include <sprite.h>

    SDL_HitTestResult MyCallback(SDL_Window* win, const SDL_Point* area, void* data){return SDL_HITTEST_DRAGGABLE;}

    int init(){
        SDL_Init(SDL_INIT_EVERYTHING);

        // initialize the window
        window = SDL_CreateWindow(
                                "Hello SDL World",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WIDTH,
                                HEIGHT,
                                SDL_WINDOW_RESIZABLE|SDL_WINDOW_BORDERLESS);

        // quit if cant initialize window
        if(NULL == window){
            printf("Could not create window!\n");
            printf("ERROR : %s \n", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        // Set draggable without borders
        SDL_SetWindowHitTest(window, MyCallback, 0);

        // initialize the renderer
        renderer = SDL_CreateRenderer(window, -1, renderer_flags);
        // quit if can't initialize renderer
        if(!renderer){
            printf("An Error occured while creating the renderer : -\n ");
            printf("%s \n", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 250, SDL_ALPHA_OPAQUE);
        // SDL_SetWindowOpacity(window, 0.5);


        return 0;
    }

    void clrscr(){
        // Set the base-screen-color to RGB(1, 1, 1) so that transparency works
        SDL_SetRenderDrawColor(renderer, 1, 1, 1, 255);
        SDL_RenderClear(renderer);
    }

    void update(){SDL_RenderPresent(renderer);}

    // Makes a window transparent by setting a transparency color.
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

#endif
#ifndef sprite
    #include <string.h>
    #include <libs.h>

    typedef struct  Sprite{
        char path[100];
        SDL_Texture *spriteTexture;
    } Sprite;

    int initSprite(Sprite *spriteInstance, char pathToImage[]){
        strcpy(spriteInstance->path, pathToImage);
        SDL_Surface *spriteImage = IMG_Load(spriteInstance->path);
        spriteInstance->spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteImage);
        if (!spriteInstance->spriteTexture){
            printf("An Error occured while creating the texture : -\n ");
            printf("%s \n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
        SDL_FreeSurface(spriteImage);
        return 0;
    }

    int removeSprite(Sprite *s){
        SDL_DestroyTexture(s->spriteTexture);
        return 0;
    }

    void draw(Sprite *spriteptr){SDL_RenderCopy(renderer, spriteptr->spriteTexture, NULL, NULL);}
    
#endif
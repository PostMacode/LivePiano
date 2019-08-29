#include "LTexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <string>


//basic texture constructor
LTexture::LTexture() {
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    //Deallocate
    free();
}

//loading texture from file
bool LTexture::loadFromFile( std::string path, SDL_Renderer *gRend ) {
    //free past texture
    free();
    
    //new texture
    SDL_Texture* newTexture = NULL;
    
    //load specific image
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Image load error at %s SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        
        //create texture from surface
        newTexture = SDL_CreateTextureFromSurface(gRend, loadedSurface);
        if( newTexture == NULL ) {
            printf( "Texture creation error at %s SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else {
            //get dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //free loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    //return
    mTexture = newTexture;
    return mTexture != NULL;
}


void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL ) {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int width, int height, SDL_Renderer *gRend) {
    SDL_Rect renderRect;
    renderRect.x = 0;
    renderRect.y = 0;
    renderRect.w = width;
    renderRect.h = height;
    SDL_RenderSetViewport( gRend, &renderRect );
    SDL_RenderCopy(gRend, mTexture, NULL, &renderRect);
}


int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

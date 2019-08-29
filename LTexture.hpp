#ifndef LTexture_hpp
#define LTexture_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>

//Textures
class LTexture {
public:
    
    //initialization
    LTexture();
    
    //deallocate
    ~LTexture();
    
    //loading image from path
    bool loadFromFile( std::string path, SDL_Renderer *gRend );
    
    //free texture
    void free();
    
    //Renders texture
    void render(int width, int height, SDL_Renderer *gRend);
    
    //Get dimensions of current image
    int getWidth();
    int getHeight();
    
    
    
private:
    
    //texture of image
    SDL_Texture* mTexture;
    
    //dimensions
    int mWidth;
    int mHeight;
    
};


#endif /* LTexture_hpp */

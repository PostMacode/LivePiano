//importing main SDL, SDL_image, and SDL_mixer
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "LTexture.hpp"

//our window
SDL_Window* gWindow = NULL;

//renderer for window
SDL_Renderer* gRenderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 1446;
const int SCREEN_HEIGHT = 918;

//Create window for textures
bool init();

//load all media
bool loadMedia();

//shut window and free media
void close();


//scene textures, including textures for all key presses
LTexture synthTexture;
LTexture grandTexture;
LTexture sq;
LTexture gq;
LTexture sw;
LTexture gw;
LTexture se;
LTexture ge;
LTexture sr;
LTexture gr;
LTexture st;
LTexture gt;
LTexture sy;
LTexture gy;
LTexture su;
LTexture gu;
LTexture si;
LTexture gi;
LTexture so;
LTexture go;
LTexture sp;
LTexture gp;
LTexture sa;
LTexture ga;
LTexture ss;
LTexture gs;
LTexture sd;
LTexture gd;
LTexture sf;
LTexture gf;
LTexture sg;
LTexture gg;
LTexture sh;
LTexture gh;
LTexture sj;
LTexture gj;
LTexture skt;
LTexture gkt;
LTexture sl;
LTexture gl;
LTexture sz;
LTexture gz;
LTexture sx;
LTexture gx;
LTexture sc;
LTexture gc;
LTexture sv;
LTexture gv;
LTexture sb;
LTexture gb;
LTexture sn;
LTexture gn;



//Sounds used for piano keys
Mix_Chunk *gqkey = NULL;
Mix_Chunk *gwkey = NULL;
Mix_Chunk *gekey = NULL;
Mix_Chunk *grkey = NULL;
Mix_Chunk *gtkey = NULL;
Mix_Chunk *gykey = NULL;
Mix_Chunk *gukey = NULL;
Mix_Chunk *gikey = NULL;
Mix_Chunk *gokey = NULL;
Mix_Chunk *gpkey = NULL;
Mix_Chunk *gakey = NULL;
Mix_Chunk *gskey = NULL;
Mix_Chunk *gdkey = NULL;
Mix_Chunk *gfkey = NULL;
Mix_Chunk *ggkey = NULL;
Mix_Chunk *ghkey = NULL;
Mix_Chunk *gjkey = NULL;
Mix_Chunk *gkkey = NULL;
Mix_Chunk *glkey = NULL;
Mix_Chunk *gzkey = NULL;
Mix_Chunk *gxkey = NULL;
Mix_Chunk *gckey = NULL;
Mix_Chunk *gvkey = NULL;
Mix_Chunk *gbkey = NULL;
Mix_Chunk *gnkey = NULL;
Mix_Chunk *qk = NULL;
Mix_Chunk *wk = NULL;
Mix_Chunk *ek = NULL;
Mix_Chunk *rk = NULL;
Mix_Chunk *tk = NULL;
Mix_Chunk *yk = NULL;
Mix_Chunk *uk = NULL;
Mix_Chunk *ik = NULL;
Mix_Chunk *ok = NULL;
Mix_Chunk *pk = NULL;
Mix_Chunk *ak = NULL;
Mix_Chunk *sk = NULL;
Mix_Chunk *dk = NULL;
Mix_Chunk *fk = NULL;
Mix_Chunk *gk = NULL;
Mix_Chunk *hk = NULL;
Mix_Chunk *jk = NULL;
Mix_Chunk *kk = NULL;
Mix_Chunk *lk = NULL;
Mix_Chunk *zk = NULL;
Mix_Chunk *xk = NULL;
Mix_Chunk *ck = NULL;
Mix_Chunk *vk = NULL;
Mix_Chunk *bk = NULL;
Mix_Chunk *nk = NULL;



bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
        printf( "SDL initialization error. SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            printf( "Texture filtering error.\n" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "C++ Live Piano", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window creation error. SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Create renderer, using gwindow from earlier and regular vertical sync'd screen
            // (adds visual latency, but visual latency isnt as important as audio latecny
            // for this program
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL ) {
                printf( "Renderer creation error. SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else {
                
                //Initialize renderer with default color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initializing loading with SDL image
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image initialization error. SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                
                //Initialize mixer audio
                //44100 hz
                //2 channels (stereo)
                //2048 byte output (less can make sound cut out, lesser quality, more causes latency)
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
                    printf( "SDL_mixer initialization error. SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                
                //default is 8 different concurrent streams of audio, we switch to 64
                //because our key note sounds are about 3 seconds each, so if you pressed
                //10 keys in 3 seconds while trying to play a song your last two keys wouldn't
                //be registered with default behavior, so we increase to allow 64 separate streams at once
                Mix_AllocateChannels(64);
                
            }
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    
    //load default synth piano image
    if( !synthTexture.loadFromFile( "synthpiano.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    //load default grand piano image
    if( !grandTexture.loadFromFile( "grandpiano.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    //load key press images
    if( !sq.loadFromFile( "synthpianoq.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gq.loadFromFile( "grandpianoq.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sw.loadFromFile( "synthpianow.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gw.loadFromFile( "grandpianow.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !se.loadFromFile( "synthpianoe.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !ge.loadFromFile( "grandpianoe.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sr.loadFromFile( "synthpianor.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gr.loadFromFile( "grandpianor.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !st.loadFromFile( "synthpianot.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gt.loadFromFile( "grandpianot.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sy.loadFromFile( "synthpianoy.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gy.loadFromFile( "grandpianoy.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !su.loadFromFile( "synthpianou.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gu.loadFromFile( "grandpianou.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !si.loadFromFile( "synthpianoi.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gi.loadFromFile( "grandpianoi.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !so.loadFromFile( "synthpianoo.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !go.loadFromFile( "grandpianoo.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sp.loadFromFile( "synthpianop.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gp.loadFromFile( "grandpianop.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sa.loadFromFile( "synthpianoa.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !ga.loadFromFile( "grandpianoa.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !ss.loadFromFile( "synthpianos.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gs.loadFromFile( "grandpianos.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sd.loadFromFile( "synthpianod.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gd.loadFromFile( "grandpianod.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sf.loadFromFile( "synthpianof.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gf.loadFromFile( "grandpianof.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sg.loadFromFile( "synthpianog.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gg.loadFromFile( "grandpianog.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sh.loadFromFile( "synthpianoh.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gh.loadFromFile( "grandpianoh.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sj.loadFromFile( "synthpianoj.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gj.loadFromFile( "grandpianoj.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !skt.loadFromFile( "synthpianok.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gkt.loadFromFile( "grandpianok.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sl.loadFromFile( "synthpianol.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gl.loadFromFile( "grandpianol.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sz.loadFromFile( "synthpianoz.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gz.loadFromFile( "grandpianoz.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sx.loadFromFile( "synthpianox.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gx.loadFromFile( "grandpianox.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sc.loadFromFile( "synthpianoc.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gc.loadFromFile( "grandpianoc.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sv.loadFromFile( "synthpianov.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gv.loadFromFile( "grandpianov.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sb.loadFromFile( "synthpianob.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gb.loadFromFile( "grandpianob.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    if( !sn.loadFromFile( "synthpianon.png", gRenderer ) )
    {
        printf( "failure loading synth texture\n" );
        success = false;
    }
    
    if( !gn.loadFromFile( "grandpianon.png", gRenderer ) )
    {
        printf( "failure loading grand piano texture\n" );
        success = false;
    }
    
    //Load key sounds
    
    gqkey = Mix_LoadWAV( "Q.mp3" );
    if( gqkey == NULL )
    {
        printf( "Failed to load q key SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gwkey = Mix_LoadWAV( "W.mp3" );
    if( gwkey == NULL )
    {
        printf( "Failed to load wkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gekey = Mix_LoadWAV( "E.mp3" );
    if( gekey == NULL )
    {
        printf( "Failed to load e key SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    grkey = Mix_LoadWAV( "R.mp3" );
    if( grkey == NULL )
    {
        printf( "Failed to load rkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gtkey = Mix_LoadWAV( "T.mp3" );
    if( gtkey == NULL )
    {
        printf( "Failed to load tkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gykey = Mix_LoadWAV( "Y.mp3" );
    if( gykey == NULL )
    {
        printf( "Failed to load ykey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gukey = Mix_LoadWAV( "U.mp3" );
    if( gukey == NULL )
    {
        printf( "Failed to load ukey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gikey = Mix_LoadWAV( "I.mp3" );
    if( gikey == NULL )
    {
        printf( "Failed to load ikey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gokey = Mix_LoadWAV( "O.mp3" );
    if( gokey == NULL )
    {
        printf( "Failed to load okey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gpkey = Mix_LoadWAV( "P.mp3" );
    if( gpkey == NULL )
    {
        printf( "Failed to load pkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gakey = Mix_LoadWAV( "A.mp3" );
    if( gakey == NULL )
    {
        printf( "Failed to load a key SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gskey = Mix_LoadWAV( "S.mp3" );
    if( gskey == NULL )
    {
        printf( "Failed to load skey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gdkey = Mix_LoadWAV( "D.mp3" );
    if( gdkey == NULL )
    {
        printf( "Failed to load d key SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gfkey = Mix_LoadWAV( "F.mp3" );
    if( gfkey == NULL )
    {
        printf( "Failed to load fkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    ggkey = Mix_LoadWAV( "G.mp3" );
    if( ggkey == NULL )
    {
        printf( "Failed to load gkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    ghkey = Mix_LoadWAV( "H.mp3" );
    if( ghkey == NULL )
    {
        printf( "Failed to load hkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gjkey = Mix_LoadWAV( "J.mp3" );
    if( gjkey == NULL )
    {
        printf( "Failed to load jkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gkkey = Mix_LoadWAV( "K.mp3" );
    if( gkkey == NULL )
    {
        printf( "Failed to load kkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    glkey = Mix_LoadWAV( "L.mp3" );
    if( glkey == NULL )
    {
        printf( "Failed to load lkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gzkey = Mix_LoadWAV( "Z.mp3" );
    if( gzkey == NULL )
    {
        printf( "Failed to load z key SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gxkey = Mix_LoadWAV( "X.mp3" );
    if( gxkey == NULL )
    {
        printf( "Failed to load xkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gckey = Mix_LoadWAV( "C.mp3" );
    if( gckey == NULL )
    {
        printf( "Failed to load ckey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gvkey = Mix_LoadWAV( "V.mp3" );
    if( gvkey == NULL )
    {
        printf( "Failed to load vkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gbkey = Mix_LoadWAV( "B.mp3" );
    if( gbkey == NULL )
    {
        printf( "Failed to load bkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gnkey = Mix_LoadWAV( "N.mp3" );
    if( gnkey == NULL )
    {
        printf( "Failed to load nkey SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    qk = Mix_LoadWAV( "C3.mp3" );
    if (qk == NULL)
    {
        printf("failure loading grand piano qkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    wk = Mix_LoadWAV( "D3.mp3" );
    if (wk == NULL)
    {
        printf("failure loading grand piano wkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    ek = Mix_LoadWAV( "E3.mp3" );
    if (ek == NULL)
    {
        printf("failure loading grand piano ekey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    rk = Mix_LoadWAV( "F3.mp3" );
    if (rk == NULL)
    {
        printf("failure loading grand piano rkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    tk = Mix_LoadWAV( "G3.mp3" );
    if (tk == NULL)
    {
        printf("failure loading grand piano tkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    yk = Mix_LoadWAV( "A3.mp3" );
    if (yk == NULL)
    {
        printf("failure loading grand piano ykey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    uk = Mix_LoadWAV( "B3.mp3" );
    if (uk == NULL)
    {
        printf("failure loading grand piano ukey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    ik = Mix_LoadWAV( "C4.mp3" );
    if (ik == NULL)
    {
        printf("failure loading grand piano ikey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    ok = Mix_LoadWAV( "D4.mp3" );
    if (ok == NULL)
    {
        printf("failure loading grand piano okey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    pk = Mix_LoadWAV( "E4.mp3" );
    if (pk == NULL)
    {
        printf("failure loading grand piano pkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    ak = Mix_LoadWAV( "F4.mp3" );
    if (ak == NULL)
    {
        printf("failure loading grand piano akey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    sk = Mix_LoadWAV( "G4.mp3" );
    if (sk == NULL)
    {
        printf("failure loading grand piano skey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    dk = Mix_LoadWAV( "A4.mp3" );
    if (dk == NULL)
    {
        printf("failure loading grand piano dkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    fk = Mix_LoadWAV( "B4.mp3" );
    if (fk == NULL)
    {
        printf("failure loading grand piano fkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gk = Mix_LoadWAV( "C5.mp3" );
    if (gk == NULL)
    {
        printf("failure loading grand piano gkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    hk = Mix_LoadWAV( "black1.mp3" );
    if (hk == NULL)
    {
        printf("failure loading grand piano hkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    jk = Mix_LoadWAV( "black2.mp3" );
    if (jk == NULL)
    {
        printf("failure loading grand piano jkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    kk = Mix_LoadWAV( "black3.mp3" );
    if (kk == NULL)
    {
        printf("failure loading grand piano kkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    lk = Mix_LoadWAV( "black4.mp3" );
    if (lk == NULL)
    {
        printf("failure loading grand piano lkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    zk = Mix_LoadWAV( "black5.mp3" );
    if (zk == NULL)
    {
        printf("failure loading grand piano zkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    xk = Mix_LoadWAV( "black6.mp3" );
    if (xk == NULL)
    {
        printf("failure loading grand piano xkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    ck = Mix_LoadWAV( "black7.mp3" );
    if (ck == NULL)
    {
        printf("failure loading grand piano ckey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    vk = Mix_LoadWAV( "black8.mp3" );
    if (vk == NULL)
    {
        printf("failure loading grand piano vkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    bk = Mix_LoadWAV( "black9.mp3" );
    if (bk == NULL)
    {
        printf("failure loading grand piano bkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    nk = Mix_LoadWAV( "black10.mp3" );
    if (nk == NULL)
    {
        printf("failure loading grand piano nkey SDL Mixer error: %s\n", Mix_GetError() );
        success = false;
    }
    
    return success;
    
}

void close()
{
    //Free all loaded images
    
    synthTexture.free();
    grandTexture.free();
    sq.free();
    gq.free();
    sw.free();
    gw.free();
    se.free();
    ge.free();
    sr.free();
    gr.free();
    st.free();
    gt.free();
    sy.free();
    gy.free();
    su.free();
    gu.free();
    si.free();
    gi.free();
    so.free();
    go.free();
    sp.free();
    gp.free();
    sa.free();
    ga.free();
    ss.free();
    gs.free();
    sd.free();
    gd.free();
    sf.free();
    gf.free();
    sg.free();
    gg.free();
    sh.free();
    gh.free();
    sj.free();
    gj.free();
    skt.free();
    gkt.free();
    sl.free();
    gl.free();
    sz.free();
    gz.free();
    sx.free();
    gx.free();
    sc.free();
    gc.free();
    sv.free();
    gv.free();
    sb.free();
    gb.free();
    sn.free();
    gn.free();
    
    //Free the piano note sounds
    Mix_FreeChunk( gqkey );
    Mix_FreeChunk( gwkey );
    Mix_FreeChunk( gekey );
    Mix_FreeChunk( grkey );
    Mix_FreeChunk( gtkey );
    Mix_FreeChunk( gykey );
    Mix_FreeChunk( gukey );
    Mix_FreeChunk( gikey );
    Mix_FreeChunk( gokey );
    Mix_FreeChunk( gpkey );
    Mix_FreeChunk( gakey );
    Mix_FreeChunk( gskey );
    Mix_FreeChunk( gdkey );
    Mix_FreeChunk( gfkey );
    Mix_FreeChunk( ggkey );
    Mix_FreeChunk( ghkey );
    Mix_FreeChunk( gjkey );
    Mix_FreeChunk( gkkey );
    Mix_FreeChunk( glkey );
    Mix_FreeChunk( gzkey );
    Mix_FreeChunk( gxkey );
    Mix_FreeChunk( gckey );
    Mix_FreeChunk( gvkey );
    Mix_FreeChunk( gbkey );
    Mix_FreeChunk( gnkey );
    Mix_FreeChunk( qk );
    Mix_FreeChunk( wk );
    Mix_FreeChunk( ek );
    Mix_FreeChunk( rk );
    Mix_FreeChunk( tk );
    Mix_FreeChunk( yk );
    Mix_FreeChunk( uk );
    Mix_FreeChunk( ik );
    Mix_FreeChunk( ok );
    Mix_FreeChunk( pk );
    Mix_FreeChunk( ak );
    Mix_FreeChunk( sk );
    Mix_FreeChunk( dk );
    Mix_FreeChunk( fk );
    Mix_FreeChunk( gk );
    Mix_FreeChunk( hk );
    Mix_FreeChunk( jk );
    Mix_FreeChunk( kk );
    Mix_FreeChunk( lk );
    Mix_FreeChunk( zk );
    Mix_FreeChunk( xk );
    Mix_FreeChunk( ck );
    Mix_FreeChunk( vk );
    Mix_FreeChunk( bk );
    Mix_FreeChunk( nk );
    gqkey = NULL;
    gwkey = NULL;
    gekey = NULL;
    grkey = NULL;
    gtkey = NULL;
    gykey = NULL;
    gukey = NULL;
    gikey = NULL;
    gokey = NULL;
    gpkey = NULL;
    gakey = NULL;
    gskey = NULL;
    gdkey = NULL;
    gfkey = NULL;
    ggkey = NULL;
    ghkey = NULL;
    gjkey = NULL;
    gkkey = NULL;
    glkey = NULL;
    gzkey = NULL;
    gxkey = NULL;
    gckey = NULL;
    gvkey = NULL;
    gbkey = NULL;
    gnkey = NULL;
    qk = NULL;
    wk = NULL;
    ek = NULL;
    rk = NULL;
    tk = NULL;
    yk = NULL;
    uk = NULL;
    ik = NULL;
    ok = NULL;
    pk = NULL;
    ak = NULL;
    sk = NULL;
    dk = NULL;
    fk = NULL;
    gk = NULL;
    hk = NULL;
    jk = NULL;
    kk = NULL;
    lk = NULL;
    zk = NULL;
    xk = NULL;
    ck = NULL;
    vk = NULL;
    bk = NULL;
    nk = NULL;
    
    
    //destroys renderer and window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //quit all of SDL
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    
    //start SDL
    if( !init() )
    {
        printf( "Init failure \n" );
    }
    else
    {
        //Loads media
        if( !loadMedia() )
        {
            printf( "Media load failure \n" );
        }
        else
        {
            //main loop flag
            bool quit = false;
            
            //synth piano/grand piano flag
            bool sFlag = true;
            
            //SDL event handler
            SDL_Event e;
            
            //while running (not quit)
            while( !quit )
            {
                //Handle events
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User quits
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //Handle key presses
                    else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            //the 1 key is used to change the flag which differentiates
                            //between synth piano and grand piano
                            case SDLK_1:
                                sFlag = !sFlag;
                                
                                break;
                                
                            case SDLK_q:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gqkey, 0 );
                                    sq.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, qk, 0 );
                                    gq.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_w:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gwkey, 0 );
                                    sw.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, wk, 0 );
                                    gw.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                
                                break;
                                
                                
                            case SDLK_e:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gekey, 0 );
                                    se.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, ek, 0 );
                                    ge.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_r:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, grkey, 0 );
                                    sr.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, rk, 0 );
                                    gr.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_t:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gtkey, 0 );
                                    st.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, tk, 0 );
                                    gt.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_y:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gykey, 0 );
                                    sy.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, yk, 0 );
                                    gy.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_u:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gukey, 0 );
                                    su.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, uk, 0 );
                                    gu.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_i:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gikey, 0 );
                                    si.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, ik, 0 );
                                    gi.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_o:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gokey, 0 );
                                    so.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, ok, 0 );
                                    go.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_p:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gpkey, 0 );
                                    sp.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, pk, 0 );
                                    gp.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_a:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gakey, 0 );
                                    sa.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, ak, 0 );
                                    ga.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_s:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gskey, 0 );
                                    ss.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, sk, 0 );
                                    gs.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_d:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gdkey, 0 );
                                    sd.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, dk, 0 );
                                    gd.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_f:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gfkey, 0 );
                                    sf.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, fk, 0 );
                                    gf.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_g:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, ggkey, 0 );
                                    sg.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, gk, 0 );
                                    gg.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_h:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, ghkey, 0 );
                                    sh.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, hk, 0 );
                                    gh.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_j:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gjkey, 0 );
                                    sj.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, jk, 0 );
                                    gj.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_k:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gkkey, 0 );
                                    skt.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, kk, 0 );
                                    gkt.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                            case SDLK_l:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, glkey, 0 );
                                    sl.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, lk, 0 );
                                    gl.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_z:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gzkey, 0 );
                                    sz.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, zk, 0 );
                                    gz.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_x:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gxkey, 0 );
                                    sx.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, xk, 0 );
                                    gx.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_c:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gckey, 0 );
                                    sc.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, ck, 0 );
                                    gc.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_v:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gvkey, 0 );
                                    sv.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, vk, 0 );
                                    gv.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_b:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gbkey, 0 );
                                    sb.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, bk, 0 );
                                    gb.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                            case SDLK_n:
                                if (sFlag) {
                                    Mix_PlayChannel( -1, gnkey, 0 );
                                    sn.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                else {
                                    Mix_PlayChannel( -1, nk, 0 );
                                    gn.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                                    SDL_RenderPresent( gRenderer );
                                }
                                break;
                                
                                
                        }
                    }
                }
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //render synth texture or grand piano texture, depending on which one is selected
                if (sFlag) {
                    synthTexture.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                }
                else {
                    grandTexture.render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                }
                
                //Update screen
                SDL_UpdateWindowSurface(gWindow);
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    
    //Free resources and close SDL
    close();
    
    return 1;
}


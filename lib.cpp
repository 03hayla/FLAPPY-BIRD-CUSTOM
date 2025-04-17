#include  "lib.h"
#include<iostream>
using namespace std;
bool LTexture::quit = false;
bool LTexture::die = true;
short int LTexture::score = 0;
SDL_Window* LTexture::gWindow = NULL;
SDL_Renderer* LTexture::gRenderer = NULL;
SDL_Event LTexture::event;
LTexture::LTexture()
{
	Texture = NULL;
}

short int LTexture::getWidth()
{
	return tWidth;
}

short int LTexture::getHeight()
{
	return tHeight;
}

void LTexture::free()
{
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		tWidth = 0;
		tHeight = 0;
	}
}

void LTexture::Render(short int x, short int y, short int angle, SDL_Rect* clip, SDL_RendererFlip flip)
{
	SDL_Rect Rec_Render = { x, y, tWidth, tHeight };

    if( clip != NULL )
	{
		Rec_Render.w = clip->w ;
		Rec_Render.h = clip->h ;
	}

    SDL_RenderCopyEx( gRenderer, Texture, clip, &Rec_Render, angle, NULL, flip );
}
bool LTexture::Load(string path, double scale)
{
    free();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));
    Texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (Texture == NULL)
    {
        cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }
    tWidth = static_cast<short int>(loadedSurface->w * scale);
    tHeight = static_cast<short int>(loadedSurface->h * scale);
    SDL_FreeSurface(loadedSurface);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}
bool LTexture::isNULL()
{
    if (Texture == NULL) return true;
    return false;
}

void position::getPos(const short int x, const short int y)
{
    this->x = x;
    this->y = y;
}




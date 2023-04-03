#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "map.h"
using namespace std;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
 
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void renderTextureA(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
        SDL_Rect *clip = nullptr)
{
        SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
        SDL_Rect *clip = nullptr)
{
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        if (clip != nullptr){
                dst.w = clip->w;
                dst.h = clip->h;
        }
        else {
                SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
        }
        renderTextureA(tex, ren, dst, clip);
}




SDL_Texture* LoadImage(string file){
   SDL_Surface *loadedImage = nullptr;
   SDL_Texture *texture = nullptr;
    loadedImage = SDL_LoadBMP(file.c_str());
   if (loadedImage != nullptr){
       texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
       SDL_FreeSurface(loadedImage);
   }
   else
       std::cout << SDL_GetError() << std::endl;
   return texture;
}


void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend){
   SDL_Rect pos;
   pos.x = x;
   pos.y = y;
      pos.w = 500;
   pos.h = 500;
   SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
   SDL_RenderCopy(rend, tex, NULL, &pos);
}

int main(int argc, char * argv[])
{
	
int iW = 85, iH = 150;
int x = SCREEN_WIDTH / 2 - iW / 2;
int y = SCREEN_HEIGHT / 2 - iH / 2;

//÷àñòè 
SDL_Rect clips[6];
for (int i = 0; i < 6; ++i){
    // if (i / 10 == 0){
    //     clips[i].x = 15;
    //     clips[i].y = 170;
    //     clips[i].w = iW;
    //     clips[i].h = iH;
    // }

    // else if( i==10){
    //     clips[i].x = 15;
    //     clips[i].y = 330;
    //     clips[i].w = iW;//ТУТ НЕ РБАТОЕТЕТ!!!!!!!!!!1111
    //     clips[i].h = iH;
    clips[i].x = 15;
    clips[i].y = 170;
    clips[i].w = iW;
    clips[i].h = iH;
}
class Bullet {
public:
    int direction;
    int x = SCREEN_WIDTH/2;
    int y = SCREEN_HEIGHT/2;
    float speed = 0.8;
    Bullet(SDL_Texture *wizard, float X, float Y){
        x = X;
        y = Y;
        float speed = 0.8;
    }
    void update(Uint32 time, int x, int y){
        x += speed*time;
    }
};
int useClip = 0;
if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
       std::cout << SDL_GetError() << std::endl;
       return 1;
   }
   window = SDL_CreateWindow("Lesson 2",0,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if (window == nullptr){
       std::cout << SDL_GetError() << std::endl;
       return 2;
   }
   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
       | SDL_RENDERER_PRESENTVSYNC);
   if (renderer == nullptr){
       std::cout << SDL_GetError() << std::endl;
       return 3;
   }
    SDL_Texture *background = nullptr, *image = nullptr,*hero=nullptr;
   background = LoadImage("map2bg.bmp");
   image = LoadImage("background.bmp");
   hero=LoadImage("wizard.bmp");
   if (background == nullptr || image == nullptr)
       return 4;
     
 
   int bW=64, bH=64;

   

   SDL_Event e;
Uint32 time = SDL_GetTicks();
bool quit = false;
while (!quit)
{
    time -= SDL_GetTicks();
	vector <Bullet>puli;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
		{
			quit = true;
		}
		if (e.type == SDL_KEYDOWN)
		{
			 switch (e.key.keysym.sym){
                        case SDLK_d:
                            std::cout <<"pressed D(left)";
							useClip=1;
							if (x+10<=SCREEN_WIDTH) x+=10;
							break;
						case SDLK_a:
                            std::cout <<"pressed A(right)";
							useClip=1;
                            if (x>=10) x-=10;
							break;
						case SDLK_w:
                            std::cout <<"pressed W(top)";
							useClip=1;
							if (y>=10) y-=10;
							break;
                        case SDLK_s:
                            std::cout <<"pressed S(bot)";
							useClip=1;
							if (y+10<=SCREEN_HEIGHT) y+=10;
							break;
                        case SDLK_SPACE:
                            useClip = 1;
                            puli.push_back(Bullet(hero, x, y));
                            break;
                        default:
                                break;
                }
		}
	}
	SDL_RenderClear(renderer);
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == ' ')  SDL_QueryTexture(background, NULL, NULL, &bW, &bH); //если встретили символ пробел, то рисуем 1й квадратик
                ApplySurface(j *64, i*64, background, renderer);
                }
    // SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
   
    // ApplySurface(x, y, image, renderer);
    //vector <Bullet> :: iterator it = puli.begin();
    
    for (Bullet i : puli){
        //advance(it, i);
        useClip = 1;
        *i.update(time, x, y);
        renderTexture(hero, renderer, x, y, &clips[useClip]);
    }    
    renderTexture(hero, renderer, x, y, &clips[useClip]);
	SDL_Delay(80);
	SDL_RenderPresent(renderer);
}

    
  
     SDL_DestroyTexture(background);
   SDL_DestroyTexture(image);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
	return 0;
}
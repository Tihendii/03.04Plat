
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <list>
#include "map.h"
using namespace std;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
 
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
class Objects{
    public:
        float x,y,w,h,speed;int dir;
        bool life,isMove,isSelect,onGround;
        enum {left,right,up,down,jump,stay} state;
        Objects(SDL_Texture *image, float X, float Y, int W, int H) {
			x = X; y = Y; w = W; h = H;
			life = true; isMove = false;
		}


};
class Player :public Objects {
public:
	bool isShoot;
	enum { left, right, up, down, stay } state;

	Player(SDL_Texture image, float X, float Y, int W, int H) :Objects(image, X, Y, W, H) {

	void control() {
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left; speed = speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right; speed = speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				state = up; speed = speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down; speed = speed;
			}
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ô öèÿ ïðîâåðêè ñòîëêíîâåíèé ñ êàðòîé
	{
		/**for ()//ïðîõîäèìñÿ ïî ýëåìåíòàì êàðòû
			for ()
			{
				if (Map[i][j] == '1')
				{
					if (Dy > 0) {}//ïî Y âíèç=>èäåì â ïîë(ñòîèì íà ìåñòå).
					if (Dy < 0) {}//ñòîëêíîâåíèå ñ âåðõíèìè êðàÿìè êàðòû
					if (Dx > 0) {}//ñ ïðàâûì êðàåì êàðòû
					if (Dx < 0) {}// ñ ëåâûì êðàåì êàðòû
				}
			}
	*/
	};
	void update(float time)
	{
		control();//ôóíêöèÿ óïðàâëåíèÿ ïåðñîíàæåì
		switch (state)//òóò äåëàþòñÿ ðàçëè÷íûå äåéñòâèÿ â çàâèñèìîñòè îò ñîñòîÿíèÿ
		{
		case right:dx = speed; break;//ñîñòîÿíèå èäòè âïðàâî
		case left:dx = -speed; break;//ñîñòîÿíèå èäòè âëåâî
		case up: dy = speed; break;
		case down: dy = -speed; break;
		case stay: break;		
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Õ
		y += dy * time;
		checkCollisionWithMap(0, dy);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Y
		sprite.setPosition(x + w / 2, y + h / 2); //çàäàåì ïîçèöèþ ñïðàéòà â ìåñòî åãî öåíòðà
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		//if (life) { setPlayerCoordinateForView(x, y); } ìîæíî äîáàâèòü, ÷òîá êàìåðà íå âñåãäà áûëà íàä ïåðñîíàæåì
	}
};
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
void falling(){
    for 


}

int main(int argc, char * argv[])
{
// list<allObj[]
int iW = 85, iH = 150;

int x = SCREEN_WIDTH / 2 - iW / 2;
int y = SCREEN_HEIGHT / 2 - iH / 2;
Player player(x,y);
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

bool quit = false;
while (!quit)
{
	
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
		{
			quit = true;
		}
        // falling();
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
							if (y+10<=SCREEN_HEIGHT) y-=10;
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

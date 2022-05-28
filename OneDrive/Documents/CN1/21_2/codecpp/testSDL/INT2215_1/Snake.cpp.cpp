#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <SDL_image.h>
#include <SDL_mixer.h>


using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//Che do choi
string sel;
int xx;

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;


Mix_Chunk* music = NULL;
Mix_Chunk* sound = NULL;
Mix_Chunk* gameoverSound = NULL;
Mix_Chunk* xi = NULL;
Mix_Chunk* boom = NULL;



void Startup(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };
	SDL_Color Green = {0, 255, 0};
	SDL_Color Orange = {250, 150, 100};
	// Lay phong chu hien thi van ban
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 20);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* start = TTF_RenderText_Solid(font, "Snake game", Green);
	SDL_Surface* play = TTF_RenderText_Solid(font, "Press E/M/H to select mode", White);

	SDL_Texture* startMessage = SDL_CreateTextureFromSurface(renderer, start);
	SDL_Texture* playMessage = SDL_CreateTextureFromSurface(renderer, play);

	SDL_Rect startRect;
	SDL_Rect playRect;

	startRect.w = 350;
	startRect.h = 250;
	startRect.x = ((24*24) / 2) - (startRect.w / 2);
	startRect.y = ((24*24) / 2) - (startRect.h / 2) - 100;
	playRect.w = 300;
	playRect.h = 50;
	playRect.x = ((24*24) / 2) - ((playRect.w / 2));
	playRect.y = (((24*24) / 2) - ((playRect.h / 2)) + 50);

	SDL_RenderCopy(renderer, startMessage, NULL, &startRect);
	SDL_RenderCopy(renderer, playMessage, NULL, &playRect);

    SDL_Surface* op1 = TTF_RenderText_Solid(font, "Easy (E)", Orange);
	SDL_Surface* op2 = TTF_RenderText_Solid(font, "Medium (M)", Orange);
	SDL_Surface* op3 = TTF_RenderText_Solid(font, "Hard (H)", Orange);
	SDL_Texture* op1Message = SDL_CreateTextureFromSurface(renderer, op1);
	SDL_Texture* op2Message = SDL_CreateTextureFromSurface(renderer, op2);
	SDL_Texture* op3Message = SDL_CreateTextureFromSurface(renderer, op3);
	SDL_Rect op1Rect;
	SDL_Rect op2Rect;
	SDL_Rect op3Rect;
	op1Rect.w = 100;
	op1Rect.h = 50;
	op1Rect.x = 50;
	op1Rect.y = 400;
	op2Rect.w = 150;
	op2Rect.h = 50;
	op2Rect.x = 220;
	op2Rect.y = 400;
	op3Rect.w = 100;
	op3Rect.h = 50;
	op3Rect.x = 450;
	op3Rect.y = 400;
	SDL_RenderCopy(renderer, op1Message, NULL, &op1Rect);
	SDL_RenderCopy(renderer, op2Message, NULL, &op2Rect);
	SDL_RenderCopy(renderer, op3Message, NULL, &op3Rect);

	TTF_CloseFont(font);
		// Show game over screen while space has not been pressed
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_H) {
                sel = "H";
                return;
			} else if (event.key.keysym.scancode == SDL_SCANCODE_M) {
                sel = "M";
                return;
			} else if (event.key.keysym.scancode == SDL_SCANCODE_E) {
                sel = "E";
                return;
			}
		}

	}

}


void renderPlayer(SDL_Renderer* renderer, SDL_Rect player, int x, int y, int scale, vector<int> tailX, vector<int> tailY, int tailLength) {
	SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
	player.w = 15;
	player.h = 15;

	//  Lay x, y cua tat ca cac khoi duoi va hien thi chung
	for (int i = 0; i < tailLength; i++) {
		player.x = tailX[i];
		player.y = tailY[i];
		SDL_RenderFillRect(renderer, &player);
	}

	player.x = x;
	player.y = y;

	SDL_RenderFillRect(renderer, &player);
}

void renderFood(SDL_Renderer* renderer, SDL_Rect food) {
	SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
	SDL_RenderFillRect(renderer, &food);
}

void renderScore(SDL_Renderer* renderer, int tailLength, int scale, int wScale) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	// Lay phong chu duoc su dung de hien thi van ban

    TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
   if (font == NULL) {
        cout << "Font loading error" << endl;
        return;
	}


	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * xx)).c_str(), Red);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect scoreRect;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((576) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);
}

bool checkCollision(int foodx, int foody, int playerx, int playery) {

	if (playerx == foodx && playery == foody){
		return true;
	}

	return false;
}

    SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

// Get a valid spawn for the food which is not on top of a tail or player block
pair<int, int> getFoodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int scale, int wScale, int tailLength) {
	bool valid = false;
	int x = 0;
	int y = 0;
	srand(time(0));
	x = scale * (rand() % wScale);
	y = scale * (rand() % wScale);
	valid = true;

	// Kiem tra tat ca khoi duoi va khoi trinh phat
	for (int i = 0; i < tailLength; i++) {

		if ((x == tailX[i] && y == tailY[i]) || (x == playerX && y == playerY)) {
			valid = false;
		}

	}

	if (!valid) {
		pair<int, int> foodLoc;
		foodLoc = make_pair(-100, -100);
		return foodLoc;
	}

	pair<int, int> foodLoc;
	foodLoc = make_pair(x, y);

	return foodLoc;
}

void gameOver(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
    SDL_Color Orange = {240, 70, 50};
	// Lay phong chu su dung van ban
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over!", Orange);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * xx)).c_str(), Red);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 450;
	gameoverRect.h = 200;
	gameoverRect.x = ((576) / 2)-(gameoverRect.w/2);
	gameoverRect.y = ((576) / 2)-(gameoverRect.h/2)-50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((576) / 2) - ((retryRect.w / 2));
	retryRect.y = (((576) / 2) - ((retryRect.h / 2))+150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((576) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, Message, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Show game over screen while space has not been pressed
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}

void youWin(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };

	// Lay phong chu hien thi van ban
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "You won!", Yellow);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to play again", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * xx)).c_str(), Red);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = ((576) / 2) - (gameoverRect.w / 2);
	gameoverRect.y = ((576) / 2) - (gameoverRect.h / 2) - 50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((576) / 2) - ((retryRect.w / 2));
	retryRect.y = (((576) / 2) - ((retryRect.h / 2)) + 150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((576) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Hien thi man hinh chien thang khi chua nhan phim
	while (true) {
		SDL_RenderPresent(renderer);
		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}

int main(int argc, char* argv[]) {

	// Init everything so we have everything
	SDL_Init(SDL_INIT_EVERYTHING);

	// Init TTF and check for any errors
    //Initialize SDL_mixer

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {

        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }

    sound = Mix_LoadWAV("hl.mp3");
    gameoverSound = Mix_LoadWAV("gameover.mp3");
    boom = Mix_LoadWAV("boom.mp3");



    // Check load
    if( !music || !sound || !gameoverSound ) {
        cout << "Failed to load music or sound: " << Mix_GetError() << endl;
    }

    SDL_Window* window;
	SDL_Renderer* renderer;

    SDL_UpdateWindowSurface(window);
	if (TTF_Init() < 0) {
		cout << "Error: " << TTF_GetError() << endl;
	}
	SDL_Event event;

	// tailLength is incremented every time the snake eats food
	int tailLength = 0;
	// Size of tiles
	int scale = 16;
	int wScale = 16;


	// This is the player rectangle, set all values to 0
	SDL_Rect player;
	player.x = 0;
	player.y = 0;
	player.h = 0;
	player.w = 0;



	// Vectors for storage of tail block positions
	vector<int> tailX;
	vector<int> tailY;



	// Player position variables
	int x = 0;
	int y = 0;
	int prevX = 0;
	int prevY = 0;

	// Movement controls
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	bool inputThisFrame = false;
	bool redo = false;

	// Food rectangle

	SDL_Rect food;
	food.w = 16;
	food.h = 16;
	food.x = 0;
	food.y = 0;

	pair<int, int> foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
	food.x = foodLoc.first;
	food.y = foodLoc.second;

	// Show the window with these settings and apply a renderer to it
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 577, 577, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	float time = SDL_GetTicks() / 100;

	// Vong lap tro choi chinh, luon lien tuc va cap nhat

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);



	//Khoi dong
    Startup(renderer, event, scale, wScale, tailLength);

	while (true) {
        int channel = Mix_PlayChannel( -1, music, 0 );
        channel = Mix_PlayChannel( -1, sound, 0 );
		float newTime = SDL_GetTicks() / 120; //This value (120) is the speed at which the blocks are updated
		if (sel == "H") {
            xx = 30;
            newTime = SDL_GetTicks() / 70;
		}
		else if (sel == "M"){
            newTime = SDL_GetTicks() / 110;
            xx = 25;
		}
		else if (sel == "E") {
            newTime = SDL_GetTicks() / 150;
            xx = 20;
		}
		float delta = newTime - time;
		time = newTime;

		inputThisFrame = false;

		// Kiem tra dieu kien thang, lay duoi lap day cac o
		if (tailLength >= 575) {
			youWin(renderer, event, scale, wScale, tailLength);
			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			food.x = foodLoc.first;
			food.y = foodLoc.second;

            //Reset lai man hinh
            renderFood(renderer, food);
            renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
            renderScore(renderer, tailLength, scale, wScale);

            SDL_RenderDrawLine(renderer, 0, 0, 0, 24 * 24);
            SDL_RenderDrawLine(renderer, 0, 24*24, 24 * 24, 24 * 24);
            SDL_RenderDrawLine(renderer, 24*24, 24 * 24, 24*24, 0);
            SDL_RenderDrawLine(renderer, 24*24, 0, 0, 0);

            // Put everything on screen
            // Nothing is actually put on screen until this is called
            SDL_RenderPresent(renderer);
            // Choose a color and fill the entire window with it, this resets everything before the next frame
            // This also give us the background color
            SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);

            SDL_RenderClear(renderer);
            Startup(renderer, event, scale, wScale, tailLength);

		}

		// Controls
		if (SDL_PollEvent(&event)) {

			// Simply exit the program when told to
			if (event.type == SDL_QUIT) {
				exit(0);
			}

			// Neu nhan 1 phim bat ky
			if (event.type == SDL_KEYDOWN && inputThisFrame == false) {

				// Sau do kiem tra lai phim va thay doi huong cho phu hop
				if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					up = true;
					left = false;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					up = false;
					left = true;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					up = false;
					left = false;
					right = false;
					down = true;
					inputThisFrame = true;
				}
				else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					up = false;
					left = false;
					right = true;
					down = false;
					inputThisFrame = true;
				}

			}

		}

		// Vi tri truoc do cua khoi trinh phat
		prevX = x;
		prevY = y;

		if (up) {
			y -= delta * scale;
		}
		else if (left) {
			x -= delta * scale;
		}
		else if (right) {
			x += delta * scale;
		}
		else if (down) {
			y += delta * scale;
		}

		if (redo == true) {

			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

		}

		// Kiem tra da va cham voi do an chua?
		if (checkCollision(food.x, food.y, x, y)) {

			// Sinh ra thuc an moi sau khi an xong
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}
            xi = Mix_LoadWAV("xi.mp3");
            Mix_HaltChannel(1);
            channel = Mix_PlayChannel(-1, xi, 0);
			tailLength++;
		}

		// Chi chay trong khung ma khoi trinh phat da di chuyen
		if (delta * scale == 16) {

			// Cap nhat kich thuoc va vi tri duoi
			if (tailX.size() != tailLength) {
				tailX.push_back(prevX);
				tailY.push_back(prevY);
			}

			//Loop through every tail block, move all blocks to the nearest block in front
			//This updates the blocks from end (farthest from player block) to the start (nearest to player block)
			for (int i = 0; i < tailLength; i++) {

				if (i > 0) {
					tailX[i - 1] = tailX[i];
					tailY[i - 1] = tailY[i];
				}

			}

			if (tailLength > 0) {
				tailX[tailLength - 1] = prevX;
				tailY[tailLength - 1] = prevY;
			}

		}

		// /neu bi va cham voi khoi duoi, tro choi ket thuc
		for (int i = 0; i < tailLength; i++) {

			if (x == tailX[i] && y == tailY[i]) {
				 Mix_HaltChannel(channel);
                channel = Mix_PlayChannel(-1, boom, 0);
                channel = Mix_PlayChannel( -1, gameoverSound, 0 );
                gameOver(renderer, event, scale, wScale, tailLength);

				x = 0;
				y = 0;
				up = false;
				left = false;
				right = false;
				down = false;
				tailX.clear();
				tailY.clear();
				tailLength = 0;
				redo = false;

				foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
				if (food.x == -100 && food.y == -100) {
					redo = true;
				}

				food.x = foodLoc.first;
				food.y = foodLoc.second;

                //Reset lai man hinh
                renderFood(renderer, food);
                renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
                renderScore(renderer, tailLength, scale, wScale);

                SDL_RenderDrawLine(renderer, 0, 0, 0, 24 * 24);
                SDL_RenderDrawLine(renderer, 0, 24*24, 24 * 24, 24 * 24);
                SDL_RenderDrawLine(renderer, 24*24, 24 * 24, 24*24, 0);
                SDL_RenderDrawLine(renderer, 24*24, 0, 0, 0);

                // Put everything on screen
                // Nothing is actually put on screen until this is called
                SDL_RenderPresent(renderer);
                // Choose a color and fill the entire window with it, this resets everything before the next frame
                // This also give us the background color
                SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);

                SDL_RenderClear(renderer);
                Startup(renderer, event, scale, wScale, tailLength);
			}

		}

		// Neu vuot qua khung tro choi (dam vao tuong), tro choi ket thuc
		if (x < 0 || y < 0 || x > 575 || y > 575) {
            Mix_HaltChannel(channel);
            channel = Mix_PlayChannel(-1, boom, 0);
            channel = Mix_PlayChannel( -1, gameoverSound, 0 );
			gameOver(renderer, event, scale, wScale, tailLength);

			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			//Reset lai man hinh
            renderFood(renderer, food);
            renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
            renderScore(renderer, tailLength, scale, wScale);

            SDL_RenderDrawLine(renderer, 0, 0, 0, 24 * 24);
            SDL_RenderDrawLine(renderer, 0, 24*24, 24 * 24, 24 * 24);
            SDL_RenderDrawLine(renderer, 24*24, 24 * 24, 24*24, 0);
            SDL_RenderDrawLine(renderer, 24*24, 0, 0, 0);

            // Put everything on screen
            // Nothing is actually put on screen until this is called
            SDL_RenderPresent(renderer);
            // Choose a color and fill the entire window with it, this resets everything before the next frame
            // This also give us the background color
            SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);

            SDL_RenderClear(renderer);
            Mix_HaltChannel(channel);


            Startup(renderer, event, scale, wScale, tailLength);
            channel = Mix_PlayChannel( -1, music, 0 );
            channel = Mix_PlayChannel( -1, sound, 0 );

		}

    	// Render everything

		renderFood(renderer, food);
		renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
		renderScore(renderer, tailLength, scale, wScale);

		SDL_RenderDrawLine(renderer, 0, 0, 0, 24 * 24);
		SDL_RenderDrawLine(renderer, 0, 24*24, 24 * 24, 24 * 24);
		SDL_RenderDrawLine(renderer, 24*24, 24 * 24, 24*24, 0);
		SDL_RenderDrawLine(renderer, 24*24, 0, 0, 0);

		// Put everything on screen
		// Nothing is actually put on screen until this is called
		SDL_RenderPresent(renderer);
		// Choose a color and fill the entire window with it, this resets everything before the next frame
		// This also give us the background color
		SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);

		SDL_RenderClear(renderer);
        channel = Mix_PlayChannel( -1, music, 0 );
        channel = Mix_PlayChannel( -1, sound, 0 );

	}

	SDL_DestroyWindow(window);

	TTF_Quit();

	Mix_FreeChunk( sound );
    Mix_FreeChunk( music );

    Mix_Quit();

	SDL_Quit();

	return 0;
}

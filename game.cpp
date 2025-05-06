#include "game.h"
#include "lib.h"
#include <iostream>
void game::checkPowerUpCollision()
{
    if (!die)
    {
        if (powerUp.checkCollision(duck.getX(), duck.getY(), duck.getWidth(), duck.getHeight()))
        {
            // Phát âm thanh khi ăn power-up
            sound.playPowerUp(); // Sử dụng âm thanh hiện có
        }
    }
}

// Hiển thị thời gian hiệu ứng còn lại
void game::renderEffectTimers()
{
    if (powerUp.isSpeedUpActive() || powerUp.isGhostActive())
    {
        // Hiển thị biểu tượng nhỏ cho biết hiệu ứng đang hoạt động
        LTexture image;

        if (powerUp.isSpeedUpActive())
        {
            image.Load("anh_amthanh/speedrun.png", 0.5);
            if (image.isNULL()) // Nếu không tìm thấy biểu tượng, sử dụng màu đen
            {
                image.Load("anh_amthanh/speedrun.png", 0.3); // Dùng tạm con vịt đen
            }
            image.Render(50, 50);

            // Hiển thị thời gian còn lại
            string timeLeft = to_string(powerUp.speedUpEffectTimer / 60 + 1);
            LTexture timeText;
            timeText.Load("anh_amthanh/" + timeLeft + ".png", 0.5);
            timeText.Render(80, 50);
            timeText.free();
        }

        if (powerUp.isGhostActive())
        {
            image.Load("anh_amthanh/ghostbaby.png", 0.5);
            if (image.isNULL()) // Nếu không tìm thấy biểu tượng, sử dụng màu đỏ
            {
                image.Load("anh_amthanh/duck-01.png", 0.3); // Dùng tạm con vịt
            }
            image.Render(50, 90);

            // Hiển thị thời gian còn lại
            string timeLeft = to_string(powerUp.ghostEffectTimer / 60 + 1);
            LTexture timeText;
            timeText.Load("anh_amthanh/" + timeLeft + ".png", 0.5);
            timeText.Render(80, 90);
            timeText.free();
        }

        image.free();
    }
}

void game::takeInput()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            userInput.Type = input::QUIT;
            quit = true;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN &&
		(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0) )
        {
            userInput.Type = input::PLAY;
        }
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0)
		{
			userInput.Type = input::PAUSE;
		}
    }
}

game::game()
{
    initGraphic();
    pipe.init();
    land.init();
    sound.init();
     powerUp.init();
}

game::~game()
{
    duck.Free();
    pipe.Free();
    land.Free();
    sound.Free();
     powerUp.Free();
    backgroundDayTexture.free();
    backgroundNightTexture.free();

    free();
    releaseGraphic();
}

void game::releaseGraphic()
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool game::initGraphic()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Flappy Duck", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				else {

                        if( !backgroundDayTexture.Load("anh_amthanh/bg.png", 1) )
                        {
                            printf( "Failed to load day background texture!\n" );
                            success = false;
                        }


                        if( !backgroundNightTexture.Load("anh_amthanh/background-night.png", 1) )
                        {
                             printf( "Failed to load night background texture!\n" );
                             success = false;
                        }
				}

			}
		}
	}

	return success;
}

void game::display()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

void game::renderScoreSmall()
{
	string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len - 1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("anh_amthanh/11.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("anh_amthanh/22.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("anh_amthanh/33.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("anh_amthanh/44.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("anh_amthanh/55.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("anh_amthanh/66.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("anh_amthanh/77.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("anh_amthanh/88.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("anh_amthanh/99.png", scaleNumberS);
		}
		else
		{
			image.Load("anh_amthanh/number.png", scaleNumberS);
		}
		 image.Render(SCREEN_WIDTH/2 + 70 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 268);
	}
	image.free();
}

void game::renderScoreLarge()
{
    string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = 0; i < len; i++)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("anh_amthanh/1.png", 1);
		}
		else if (number == 2)
		{
			image.Load("anh_amthanh/2.png", 1);
		}
		else if (number == 3)
		{
			image.Load("anh_amthanh/3.png", 1);
		}
		else if (number == 4)
		{
			image.Load("anh_amthanh/4.png", 1);
		}
		else if (number == 5)
		{
			image.Load("anh_amthanh/5.png", 1);
		}
		else if (number == 6)
		{
			image.Load("anh_amthanh/6.png", 1);
		}
		else if (number == 7)
		{
			image.Load("anh_amthanh/7.png", 1);
		}
		else if (number == 8)
		{
			image.Load("anh_amthanh/8.png", 1);
		}
		else if (number == 9)
		{
			image.Load("anh_amthanh/9.png", 1);
		}
		else
		{
			image.Load("anh_amthanh/0.png", 1);
		}
		image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + i * (image.getWidth() + 5), 100);
	}
	image.free();
}

void game::renderBestScore()
{
	ifstream fileIn("anh_amthanh/bestScore.txt");
	fileIn >> bestScore;
	ofstream fileOut("anh_amthanh/bestScore.txt", ios::trunc);

	if (score > bestScore)
	{
		bestScore = score;
	}
	string s = to_string(bestScore);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len-1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("anh_amthanh/11.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("anh_amthanh/22.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("anh_amthanh/33.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("anh_amthanh/44.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("anh_amthanh/55.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("anh_amthanh/66.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("anh_amthanh/77.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("anh_amthanh/88.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("anh_amthanh/99.png", scaleNumberS);
		}
		else
		{
			image.Load("anh_amthanh/number.png", scaleNumberS);
		}
		 image.Render(SCREEN_WIDTH/2 + 70 - image.getWidth()*(len-i-1)*0.75 - 5*(len - i - 1), 315);
	}
	image.free();

	fileOut << bestScore;
	fileIn.close();
	fileOut.close();
}

void game::renderMessage()
{
	LTexture image;
	image.Load("anh_amthanh/duck-ready.png", 1);
	 image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.free();
}



void game::renderBackground()
{

    SDL_Rect screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_RenderCopy(gRenderer, backgroundDayTexture.Texture, NULL, &screenRect);
}



void game::renderBackgroundNight()
{

    SDL_Rect screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_RenderCopy(gRenderer, backgroundNightTexture.Texture, NULL, &screenRect);
}

void game::renderLand()
{
	LTexture image;
	image.Load("anh_amthanh/land.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT- image.getHeight());
	image.free();
}

void game::resume()
{
	LTexture image;
	image.Load("anh_amthanh/resume.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::pause()
{
	LTexture image;
	image.Load("anh_amthanh/pause.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::renderPauseTab()
{
	LTexture image;
	image.Load("anh_amthanh/pauseTab.png", 1);
	 image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230);
	image.free();
}

void game::lightTheme()
{
	LTexture image;
	image.Load("anh_amthanh/duck-01.png", 0.8);
	image.Render(330, 310);
	image.free();
}

void game::darkTheme()
{
	LTexture image;
	image.Load("anh_amthanh/Duck-02.png", 0.8);
	image.Render(325, 315);
	image.free();
}
void game::nextButton()
{
	LTexture image;
	image.Load("anh_amthanh/nextRight.png", 1);
	image.Render(370, 322);
	image.Load("anh_amthanh/nextLeft.png", 1);
	image.Render(310, 322);
	image.free();
}

bool game::changeTheme()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (((x > 370 && x < 370+13)  || (x > 310 && x < 310 + 13)) && (y > 322 && y < 322 + 16))
	{
		return true;
	}
	return false;
}

void game::renderGameOver()
{
	LTexture image;
	image.Load("anh_amthanh/gameOver.png", 1);
	 image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
	image.free();
}

void game::renderMedal()
{
	LTexture image;

	if (score > 20 && score <= 50)
	{
		image.Load("anh_amthanh/silver-medal-demo.png", scaleNumberS);
	}
	else if (score > 50)
	{
		image.Load("anh_amthanh/gold-medal-demo.png", scaleNumberS);
	}
	else
	{
		image.Load("anh_amthanh/bronze-medal-demo.png", scaleNumberS);
	}
	image.Render((SCREEN_WIDTH/2 - 100)-14, 265);

	image.free();
}

void game::replay()
{
	LTexture image;
	image.Load("anh_amthanh/replay.png", 1);
	 image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
	image.free();
}

bool game::checkReplay()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60)
	{
		return true;
	}
	return false;
}

void game::Restart()
{
    die = false;
    score = 0;
    duck.resetTime();
     powerUp.reset();


}

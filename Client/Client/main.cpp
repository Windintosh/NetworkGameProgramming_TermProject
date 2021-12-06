#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include "global.h"
#include "client.h"
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9152
#define BUFSIZE    512

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;			//The surface contained by the window

bool init()
{
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Create window
	gWindow = SDL_CreateWindow("TANK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Get window surface
		gScreenSurface = SDL_GetWindowSurface(gWindow);
	}

	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}


int main(int argc, char* args[])
{
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	printf("connect success \n");

	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE + 1];
	int len;

	int key = 0;
	//Start up SDL and create window
	if (!init()) cout << "Failed to load media!\n";
	else
	{
		bool quit = false;			//Main loop flag
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			key = 0;
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						printf("player up \n");
						key = 1;
						break;

					case SDLK_DOWN:
						printf("player down \n");
						key = 2;
						break;

					case SDLK_RIGHT:
						printf("player right \n");
						key = 3;
						break;

					case SDLK_LEFT:
						printf("player left \n");
						key = 4;
						break;
					case SDLK_SPACE:
						printf("player shoot \n");
						key = 5;
						break;
					case SDLK_ESCAPE:
						printf("player quit \n");
						key = 6;
						break;
					}
				}
				buf[0] = key;
				key = 0;
				retval = send(sock, buf, strlen(buf), 0);
				// before
				key = 0;

				retval = recvn(sock, buf, retval, 0);
				key = buf[0];
				if (key == 1) {
					printf("player up success \n");
					//handle move here
					continue; //to the start of the loop
				}
				else if (key == 2) {
					printf("player down success \n");
					continue;
				}
				else if (key == 3) {
					printf("player right success \n");
					continue;
				}
				else if (key == 4) {
					printf("player left success \n");
					continue;
				}
				else if (key == 5) {
					printf("player shoot success \n");
					continue;
				} 
				else if (key == 6) {
					printf("player quit \n");
					exit(0);
					break;
				}//after here
				break;
			}
			
			////Apply the image
			//SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
			
			////Update the surface
			//SDL_UpdateWindowSurface(gWindow);
		}
	}


	closesocket(sock);
	WSACleanup();
	close();
	return 0;
}
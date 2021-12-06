#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include "global.h"
//#include "server.h"
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#define SERVERPORT 9152
#define BUFSIZE    512

DWORD WINAPI WorkerThread(LPVOID arg);

using namespace std;

void init() {

}

void exit() {

}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}



// 클라이언트와 데이터 통신
DWORD WINAPI CommunicateThread(LPVOID arg) {
    SOCKET client_sock = (SOCKET) arg;
    int retval;
    SOCKADDR_IN clientaddr;
    int addrlen;
    char buf[BUFSIZE + 1];
    char ch[BUFSIZE + 1];

    // 클라이언트 정보 얻기
    addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

    printf("communicate thread create success \n");

    int key = 0;

    while (1) {
        key = 0;
        retval = recv(client_sock, buf, BUFSIZE, 0);
        buf[retval] = '\0';
        key = buf[0];
        if (key == 1) {
            printf("player up \n");
            //handle move here
            buf[0] = key;
            retval = send(client_sock, buf, retval, 0);
            continue;
        }
        else if (key == 2) {
            printf("player down \n");
            buf[0] = key;
            retval = send(client_sock, buf, retval, 0);
            continue;
        }
        else if (key == 3){
            printf("player right \n");
            buf[0] = key;
            retval = send(client_sock, buf, retval, 0);
            continue;
        }
        else if (key == 4) {
            printf("player left \n");
            buf[0] = key;
            retval = send(client_sock, buf, retval, 0);
            continue;
        }
        else if (key == 5) {
            printf("player shoot \n");
            buf[0] = key;
            retval = send(client_sock, buf, retval, 0);
            continue;
        }
        else if (key == 6) {
            printf("player quit \n");
            buf[0] = key;
            retval = send(client_sock, buf, retval, 0);
            continue;
        }
        break;
    }

    //HANDLE wThread;
    //wThread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL); //creates worker thread, gives null for now
    
    //send data to worker thread

    //wait()

    //send data to client

    //closesocket()
    closesocket(client_sock);
    printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
        inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
    return 0;
}



//game logic
DWORD WINAPI WorkerThread(LPVOID arg)
{
    printf("worker thread create success");
    //recv data from communicate thread

    //handle logic


    //send data to communicate thread
    
    
    //signal

    return 1;
}


int main(int argc, char* argv[]) {
    int retval;

    // 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // socket()
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    //if (listen_sock == INVALID_SOCKET) err_quit("socket()");

    // bind()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    //if (retval == SOCKET_ERROR) err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    //if (retval == SOCKET_ERROR) err_quit("listen()");

    // 데이터 통신에 사용할 변수
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;
    HANDLE hThread;

    while (1) {
        // accept()
        addrlen = sizeof(clientaddr);
        client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            //err_display("accept()");
            break;
        }

        // 접속한 클라이언트 정보 출력
        printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
            inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        // 스레드 생성
        hThread = CreateThread(NULL, 0, CommunicateThread, (LPVOID)client_sock, 0, NULL);
        if (hThread == NULL) { closesocket(client_sock); }
        else { CloseHandle(hThread); }
    }

    // closesocket()
    closesocket(listen_sock);

    // 윈속 종료
    WSACleanup();
    return 0;

}
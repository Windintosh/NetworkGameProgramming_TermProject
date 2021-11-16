#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_
#endif // !_SERVER_H_

class Server
{
private:

public:
	Server();
	void listen();
	void recvkey(int keypress); //키 수신
	void recvPlayerAccess(int ID); //접속 수신
	void sendGameData(TANK p, BULLET b);
	void sendGameResult(Player p); //이긴 플레이어

};
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
	void recvkey(int keypress); //Ű ����
	void recvPlayerAccess(int ID); //���� ����
	void sendGameData(TANK p, BULLET b);
	void sendGameResult(Player p); //�̱� �÷��̾�

};
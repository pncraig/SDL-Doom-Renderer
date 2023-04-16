#ifndef PLAYER_H
#define PLAYER_H

#include "DataTypes.h"

class Player
{
private:
	int m_PlayerID{};
	int m_PlayerX{};
	int m_PlayerY{};
	int m_PlayerA{};

public:
	Player(int ID);
	~Player();

	void setPlayerX(int x);
	void setPlayerY(int y);
	void setPlayerA(int a);

	int getPlayerID();
	int getPlayerX();
	int getPlayerY();
	int getPlayerA();
};

#endif


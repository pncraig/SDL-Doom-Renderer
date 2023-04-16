#include "Player.h"

Player::Player(int ID)
	:m_PlayerID{ ID }
{

}

Player::~Player(){}

void Player::setPlayerX(int x)
{
	m_PlayerX = x;
}

void Player::setPlayerY(int y)
{
	m_PlayerY = y;
}

void Player::setPlayerA(int a)
{
	m_PlayerA = a;
}

int Player::getPlayerID() { return m_PlayerID; }
int Player::getPlayerX() { return m_PlayerX; }
int Player::getPlayerY() { return m_PlayerY; }
int Player::getPlayerA() { return m_PlayerA; }
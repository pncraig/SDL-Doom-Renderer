#include "Map.h"

Map::Map(SDL_Renderer* renderer, std::string name, Player* player)
	:m_pRenderer{ renderer }, m_MapName { name }, m_MapPlayer{ player }, m_XMax{ INT_MIN }, m_XMin{ INT_MAX }, m_YMax{ INT_MIN }, m_YMin{ INT_MAX }, m_ScaleFactor{ 15 }
{
	
}

std::string Map::getMapName()
{
	return m_MapName;
}

bool Map::initPlayer()
{
	for (int i{ 0 }; i < m_MapThings.size(); i++)
	{
		if (m_MapThings[i].type == m_MapPlayer->getPlayerID())
		{
			m_MapPlayer->setPlayerX(m_MapThings[i].x);
			m_MapPlayer->setPlayerY(m_MapThings[i].y);
			m_MapPlayer->setPlayerA(m_MapThings[i].a);
			break;
		}
	}

	return true;
}

void Map::addVertex(const Vertex& v)
{
	m_MapVertices.push_back(v);

	// Find the most extreme vertex values to use for drawing the automap
	if (v.x > m_XMax)
		m_XMax = v.x;
	else if (v.x < m_XMin)
		m_XMin = v.x;

	if (v.y > m_YMax)
		m_YMax = v.y;
	else if (v.y < m_YMin)
		m_YMin = v.y;
}

void Map::addLinedef(const Linedef& l)
{
	m_MapLinedefs.push_back(l);
}

void Map::addThing(const Thing& t)
{
	m_MapThings.push_back(t);
}

void Map::addNode(const Node& n)
{
	m_MapNodes.push_back(n);
}

int Map::remapX(int rawX)
{
	return (-m_XMin + rawX) / m_ScaleFactor;
}

int Map::remapY(int rawY)
{
	int w, h;
	SDL_RenderGetLogicalSize(m_pRenderer, &w, &h);

	return (h - 1) - (-m_YMin + rawY) / m_ScaleFactor;
}

bool Map::isPlayerLeftOfSplitter(Node& splitter)
{
	// Vector pointing from the origin of the partition line to the player
	int dx{ m_MapPlayer->getPlayerX() - splitter.startX };
	int dy{ m_MapPlayer->getPlayerY() - splitter.startY };

	// If the cross product of the above vector and the partitioning line vector is positive, the player is left of the partitioning line
	return (splitter.changeX * dy - dx * splitter.changeY) >= 0;
}

void Map::walkThroughBSP(int nodeNum)
{
	if (nodeNum < 0)
		return;

	renderAutomapNode(nodeNum);
	SDL_RenderPresent(m_pRenderer);
	SDL_Delay(1000);

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
	renderAutomapWalls();
	renderAutomapPlayer();

	Node& n{ m_MapNodes[nodeNum] };

	if (isPlayerLeftOfSplitter(n))
		walkThroughBSP(n.leftChild);
	else
		walkThroughBSP(n.rightChild);

}

void Map::renderAutomapWalls()
{
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	for (Linedef& l : m_MapLinedefs)
	{
		Vertex start{ m_MapVertices[l.startVertex] };
		Vertex end{ m_MapVertices[l.endVertex] };

		start.x = remapX(start.x);
		start.y = remapY(start.y);

		end.x = remapX(end.x);
		end.y = remapY(end.y);

		SDL_RenderDrawLine(m_pRenderer, start.x, start.y, end.x, end.y);
	}
}

void Map::renderAutomapPlayer()
{
	int pX{ remapX(m_MapPlayer->getPlayerX()) };
	int pY{ remapY(m_MapPlayer->getPlayerY()) };

	SDL_Rect playerRect{ pX - 1, pY - 1, 2, 2 };
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
	SDL_RenderFillRect(m_pRenderer, &playerRect);
}

void Map::renderAutomapNode(int nodeNum)
{
	Node n{ m_MapNodes[nodeNum] };

	SDL_Rect rightBox{ remapX(n.rightBox[2]), remapY(n.rightBox[0]), remapX(n.rightBox[3]) - remapX(n.rightBox[2]) + 1, remapY(n.rightBox[1]) - remapY(n.rightBox[0]) + 1 };
	SDL_Rect leftBox{ remapX(n.leftBox[2]), remapY(n.leftBox[0]), remapX(n.leftBox[3]) - remapX(n.leftBox[2]) + 1, remapY(n.leftBox[1]) - remapY(n.leftBox[0]) + 1 };

	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(m_pRenderer, &rightBox);

	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(m_pRenderer, &leftBox);

	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 255);
	SDL_RenderDrawLine(m_pRenderer, remapX(n.startX - n.changeX * 100), remapY(n.startY - n.changeY * 100), remapX(n.startX + n.changeX * 100), remapY(n.startY + n.changeY * 100));

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(m_pRenderer, remapX(n.startX), remapY(n.startY), remapX(n.startX + n.changeX), remapY(n.startY + n.changeY));
}

void Map::renderAutomap()
{
	
	renderAutomapWalls();
	renderAutomapPlayer();
	
	walkThroughBSP(m_MapNodes.size() - 1);
}
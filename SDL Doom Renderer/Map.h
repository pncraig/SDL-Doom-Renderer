#ifndef MAP_H
#define MAP_H

#include <vector>
#include "DataTypes.h"
#include <iostream>
#include "SDL.h"
#include "Player.h"

// Class that contains map data

class Map
{
private:
	std::string m_MapName{};
	std::vector<Vertex> m_MapVertices{};
	std::vector<Linedef> m_MapLinedefs{};
	std::vector<Thing> m_MapThings{};
	std::vector<Node> m_MapNodes{};

	Player* m_MapPlayer{};
	SDL_Renderer* m_pRenderer{};

	// Used for drawing the automap
	int m_XMax{};
	int m_XMin{};
	int m_YMax{};
	int m_YMin{};
	int m_ScaleFactor{};

public:
	Map(SDL_Renderer* renderer, std::string name, Player* player);

	std::string getMapName();

	bool initPlayer();			// Initialize the player class with the values from the map thing that represents the player

	void addVertex(const Vertex& v);		// Add a vertex
	void addLinedef(const Linedef& l);		// Add a linedef
	void addThing(const Thing& t);			// Add a thing
	void addNode(const Node& n);			// Add a node

	// Draw the automap
	int remapX(int rawX);
	int remapY(int rawY);

	bool isPlayerLeftOfSplitter(Node& splitter);
	void walkThroughBSP(int nodeNum);

	void renderAutomapWalls();
	void renderAutomapPlayer();
	void renderAutomapNode(int nodeNum);
	void renderAutomap();
};

#endif


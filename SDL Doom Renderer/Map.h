#ifndef MAP_H
#define MAP_H

#include <vector>
#include "DataTypes.h"
#include <iostream>
#include "SDL.h"

// Class that contains map data

class Map
{
private:
	std::string m_MapName{};
	std::vector<Vertex> m_MapVertices{};
	std::vector<Linedef> m_MapLinedefs{};
	std::vector<Thing> m_MapThings{};

	// Used for drawing the automap
	int m_XMax{};
	int m_XMin{};
	int m_YMax{};
	int m_YMin{};
	int m_ScaleFactor{};

public:
	Map(std::string name);

	std::string getMapName();
	void addVertex(const Vertex& v);
	void addLinedef(const Linedef& l);
	void addThing(const Thing& t);
	void renderAutomap(SDL_Renderer* renderer);
};

#endif


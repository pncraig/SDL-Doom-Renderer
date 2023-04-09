#include "Map.h"

Map::Map(std::string name)
	:m_MapName{ name }, m_XMax{ INT_MIN }, m_XMin{ INT_MAX }, m_YMax{ INT_MIN }, m_YMin{ INT_MAX }, m_ScaleFactor{ 15 }
{

}

std::string Map::getMapName()
{
	return m_MapName;
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

void Map::renderAutomap(SDL_Renderer* renderer)
{
	int xShift{ -m_XMin };
	int yShift{ -m_YMin };

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	int renderWidth{};
	int renderHeight{};

	SDL_RenderGetLogicalSize(renderer, &renderWidth, &renderHeight);

	renderWidth--;
	renderHeight--;

	for (Linedef& l : m_MapLinedefs)
	{
		Vertex start{ m_MapVertices[l.StartVertex] };
		Vertex end{ m_MapVertices[l.EndVertex] };

		start.x = (start.x + xShift) / m_ScaleFactor;
		start.y = renderHeight - (start.y + yShift) / m_ScaleFactor;

		end.x = (end.x + xShift) / m_ScaleFactor;
		end.y = renderHeight - (end.y + yShift) / m_ScaleFactor;

		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}
}
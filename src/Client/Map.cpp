#include "Map.h"



Map::Map()
{
	grid = sf::VertexArray(sf::Quads, MWIDTH*MHEIGHT * 4);
	for (unsigned i = 0; i < MWIDTH; ++i) {
		for (unsigned j = 0; j < MHEIGHT; ++j) {
			unsigned pos = (j*MWIDTH+i) * 4;
			for (unsigned k = 0; k < 4; ++k)  grid[pos+k].color = ((i + j) % 2)?sf::Color::Black:sf::Color(90,90,90);
			float x = (float)i*MSIZE;
			float y = (float)j*MSIZE;
			grid[pos].position = { x,y };
			grid[pos+1].position = { x+MSIZE,y };
			grid[pos+2].position = { x+MSIZE,y+MSIZE };
			grid[pos+3].position = { x,y+MSIZE };
		}
	}
}


Map::~Map()
{
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(grid);
}

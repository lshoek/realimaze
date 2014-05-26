#include <string>
#include <sstream>
#include "Glyph.h"

using namespace std;

char id;
int x, y, width, height, xoffset, yoffset, xadvance;

Glyph::Glyph()
{
}

Glyph::~Glyph()
{
}

string Glyph::repstring()
{
	stringstream ss;
	ss << "id=" << id << " x=" << x << " y=" << y << " width=" << width << " height=" << height << " yoffset=" << yoffset << " xadvance=" << xadvance;
	return ss.str();
}

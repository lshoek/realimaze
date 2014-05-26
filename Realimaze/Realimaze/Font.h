#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include "Font.h"
#include "Glyph.h"

using namespace std;

class Font
{
private:
	void printFontData();
public:
	Font(const string fname);
	Font::Font();
	~Font();

	map<char, Glyph> charmap;
	typedef map<char, Glyph>::iterator cgmap;
};

std::string replace(string str, string toReplace, string replacement);
vector<string> split(string str, string sep);


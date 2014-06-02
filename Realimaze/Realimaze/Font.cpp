#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include "Font.h"
#include "Glyph.h"

using namespace std;

Font::Font(const string fname)
{
	ifstream input;
	input.open(fname);
	while (!input.eof())
	{
		string line;
		getline(input, line);

		line = replace(line, "\t", " "); //tabs become spaces
		line = replace(line, "=", " "); //equals become spaces
		while (line.find("  ") != string::npos)
			line = replace(line, "  ", " "); //double spaces become singles

		if (line == "")
			continue;
		if (line[0] == ' ')
			line = line.substr(1);
		if (line == "")
			continue;
		if (line[line.length() - 1] == ' ')
			line = line.substr(0, line.length() - 1);
		if (line == "")
			continue;

		vector<string> params = split(line, " ");
		Glyph g{};
		g.id = 0;
		int index = 0;
		for (int i = 0; i < params.size(); i++)
		{
			if (params[i] == "id")
				g.id = stoi(params.at(i + 1));
			else if (params[i] == "x")
				g.x = stoi(params[i + 1]);
			else if (params[i] == "y")
				g.y = stoi(params[i + 1]);
			else if (params[i] == "width")
				g.width = stoi(params[i + 1]);
			else if (params[i] == "height")
				g.height = stoi(params[i + 1]);
			else if (params[i] == "yoffset")
				g.yoffset = stoi(params[i + 1]);
			else if (params[i] == "xadvance")
				g.xadvance = stoi(params[i + 1]);
		}
		cgmap it = charmap.begin();
		if (g.id != 0)
			charmap.insert(it, std::pair<char, Glyph>(g.id, g));
	}
	cout << "> " << fname << " loaded" << endl;
	//printFontData();
}

Font::Font()
{
}

Font::~Font()
{
}

void Font::printFontData()
{
	for (cgmap iterator = charmap.begin(); iterator != charmap.end(); iterator++)
		cout << "KEY:" << iterator->first << " VALUE: " << iterator->second.repstring() << endl;
}

string replace(string str, string toReplace, string replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

vector<string> split(string str, string sep)
{
	vector<string> ret;
	size_t index;
	while (true)
	{
		index = str.find(sep);
		if (index == string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}
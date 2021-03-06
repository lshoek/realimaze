#include "ObjectLoader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
/*
std::string replace(std::string str, std::string toReplace, std::string replacement)
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

std::vector<std::string> split(std::string str, std::string sep)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(sep);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}
*/

using namespace std;

inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}




ObjModel::ObjModel(std::string fileName)
{
	std::string dirName = fileName;
	if (dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if (dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if (fileName == dirName)
		dirName = "";


	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open())
	{
		printf("ERROR OPENING %s\n", fileName.c_str());
	}


	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;


	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);

		line = replace(line, "\t", " ");
		while (line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
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
		if (line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "v")
			vertices.push_back(::Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vn")
			normals.push_back(::Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vt")
			texcoords.push_back(::Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for (size_t i = ii - 3; i < ii; i++)
				{
					Vertex vertex;
					std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
					if (indices.size() >= 1)
						vertex.position = atoi(indices[0].c_str()) - 1;
					if (indices.size() == 2) //texture 
						vertex.texcoord = atoi(indices[1].c_str()) - 1;
					if (indices.size() == 3)
					{
						if (indices[1] != "")
						{
							vertex.texcoord = atoi(indices[1].c_str()) - 1;
						}
						vertex.normal = atoi(indices[2].c_str()) - 1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if (params[0] == "s")
		{

		}
		else if (params[0] == "mtllib")
		{
			loadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for (size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if (currentGroup->materialIndex == -1)
				cout << "Could not find material name " << params[1] << endl;
		}
	}
	groups.push_back(currentGroup);
}


ObjModel::~ObjModel(void)
{

}

void ObjModel::draw()
{
	for (auto group : groups)
	{
		if (materials[group->materialIndex]->hasTexture)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, materials[group->materialIndex]->texture->getTextureId());
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
		}

		glBegin(GL_TRIANGLES);
		for (auto face : group->faces)
		{
			if (face.vertices.size() == 3)
			{
				//alles oke
			}

			if (face.vertices.size() != 3)
			{
				//probeem
				//glBegin
				//4 ken ik fixen
			}
			for (auto vertex : face.vertices)
			{
				glNormal3f(normals[vertex.normal].x, normals[vertex.normal].y, normals[vertex.normal].z);
				glTexCoord2f(texcoords[vertex.texcoord].x, texcoords[vertex.texcoord].y);
				glVertex3f(vertices[vertex.position].x, vertices[vertex.position].y, vertices[vertex.position].z);
			}
		
		}
		glEnd();
	}

	/*

	glBegin(GL_QUADS);
	//groups[1]->faces.size();
	for(int i = 0; i<groups.size();i++)
	{
	//Face* naam = groups[i]->faces;
	for(int a = 0; a<groups[i]->faces.size();a++)
	{
	//list<Face> faces= groups[i]->faces.front;

	auto face = groups[i]->faces;
	//groups[i]->faces
	//std::advance(l_front, 4);
	//face.begin();
	auto vert = face.begin()->vertices;
	for(int b = 0; b<vert.size();b++)
	{
	//auto vertice = vertices[b];
	auto vertice = vert.begin();
	auto norm = vertice->normal;
	//vertice.

	glNormal3f(normals[norm].x, normals[norm].y,normals[norm].z);

	auto pos = vertice->position;
	glVertex3f(vertices[pos].x,vertices[pos].y,vertices[pos].z);
	//vertice
	//		std::next(vertice,1);
	}
	//std::next(face,1);
	}

	}*/
}

void ObjModel::loadMaterialFile(std::string fileName, std::string dirName)
{
	std::ifstream pFile(fileName.c_str());

	MaterialInfo* currentMaterial = NULL;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);

		line = replace(line, "\t", " ");
		while (line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
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
		if (line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "newmtl")
		{
			if (currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		/*else if (params[0] == "ka")
		{
			currentMaterial->ka = params[1]
		}*/

		else if (params[0] == "map_kd")
		{
			currentMaterial->hasTexture = true;

			currentMaterial->texture = new Texture(dirName + "/" + params[1]);
		}
		else
			cout << "Didn't parse " << params[0] << " in material file" << endl;
	}
	if (currentMaterial != NULL)
		materials.push_back(currentMaterial);

}
/*
void ObjModel::getColorRGBA(aiColor3D *pColor)
{
	        ai_assert(NULL != pColor);
	
		        float r, g, b;
		        m_DataIt = getFloat<DataArrayIt>(m_DataIt, m_DataItEnd, r);
		        pColor->r = r;
	
			        m_DataIt = getFloat<DataArrayIt>(m_DataIt, m_DataItEnd, g);
		        pColor->g = g;
	
			        m_DataIt = getFloat<DataArrayIt>(m_DataIt, m_DataItEnd, b);
		        pColor->b = b;
		}
*/
ObjModel::MaterialInfo::MaterialInfo()
{
	hasTexture = false;
}


::Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
::Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
::Vec3f::Vec3f(Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& ::Vec3f::operator [](int index)
{
	return v[index];
}



::Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
::Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
::Vec2f::Vec2f(Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& ::Vec2f::operator [](int index)
{
	return v[index];
}

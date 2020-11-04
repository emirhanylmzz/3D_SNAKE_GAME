#include "Snake.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;
Snake::Snake(glm::vec3 startPos)
{ 
	head = startPos;
	tail = glm::vec3(startPos.x - 1, startPos.y, startPos.z);
	pos.push_back(head);
	pos.push_back(tail);
}

void Snake::snakegrow(Bait& bait)
{
	if ((int)pos[0].x == (int)bait.pos.x && (int)pos[0].y == (int)bait.pos.y && (int)pos[0].z == (int)bait.pos.z)
	{
		bait.check = false;
		pos.push_back(glm::vec3(pos[0].x - 1, pos[0].y, pos[0].z));
	}
	if (bait.check == false)
		bait.createBait();
}

bool Snake::isGameOver() const
{
	for (unsigned int i = 0; i < pos.size(); ++i)
	{
		if (pos[0] == pos[i] && i != 0)
			return false;
	}
	return true;
}

void Snake::moveRight()
{
	if (pos[0].x < 9.0)
	{
		Sleep(100);
		for (unsigned int i = pos.size() - 1; i > 0; i--)
		{
			if(i != 0)
				pos[i] = glm::vec3(pos[i-1].x, pos[i-1].y, pos[i-1].z);
		}
		pos[0] = glm::vec3(pos[0].x + 1, pos[0].y, pos[0].z);
	}

}

void Snake::moveLeft()
{
	if (pos[0].x > -10.0)
	{
		Sleep(100);
		for (unsigned int i = pos.size()-1; i > 0; i--)
		{
			if(i != 0)
				pos[i] = glm::vec3(pos[i-1].x, pos[i-1].y, pos[i-1].z);
		}
		pos[0] = glm::vec3(pos[0].x - 1, pos[0].y, pos[0].z);
	}
}

void Snake::moveUp()
{
	if (pos[0].z > -9.0)
	{
		Sleep(100);
		for (unsigned int i = pos.size() - 1; i > 0; i--)
		{
			if (i != 0)
				pos[i] = glm::vec3(pos[i-1].x, pos[i-1].y, pos[i-1].z);
		}
		pos[0] = glm::vec3(pos[0].x, pos[0].y, pos[0].z - 1);
	}
}

void Snake::moveDown()
{
	if (pos[0].z < 10.0)
	{
		Sleep(100);
		for (unsigned int i = pos.size() - 1; i > 0; i--)
		{
			if(i != 0)
				pos[i] = glm::vec3(pos[i-1].x, pos[i-1].y, pos[i-1].z);
		}
		pos[0] = glm::vec3(pos[0].x, pos[0].y, pos[0].z + 1);
	}
}
void Bait::createBait()
{
	int r = rand() % 2;
	int x = rand() % 10;
	int z = rand() % 10;
	if (r == 1)
		x = x * -1;
	else
		z = z * -1;
	pos = glm::vec3(x, -5.0f, z);
	check = true;
}

Bait::Bait(glm::vec3 pos)
{
	this->pos = pos;
}

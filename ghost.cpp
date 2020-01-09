#include "ghost.h"
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GL/glut.h>

Ghost::Ghost(int x, int y)
{
    this->x = x;
    this->y = y;

    step = 1;
    direction = 0;

    was_hit = false;
    is_moving = false;
	count = 0; //±±¨î A*°õ¦æÀW²v
}

Ghost::~Ghost()
{
}

bool Ghost::canMove(int direction)
{
    switch (direction) {
    case 1:
        return Wall::isWall(*(map + (maxY - y - step) * maxY + x));
    case 2:
        return Wall::isWall(*(map + (maxY - y) * maxY + x + step));
    case 3:
        return Wall::isWall(*(map + (maxY - y + step) * maxY + x));
    case 0:
        return Wall::isWall(*(map + (maxY - y) * maxY + x - step));
    default:
        return false;
    }
}

void Ghost::setMap(char* map, int maxX, int maxY)
{
    this->map = map;
    this->maxX = maxX;
    this->maxY = maxY;
}

void Ghost::draw(int pacmanX, int pacmanY)
{
}
int Ghost::getNextX()
{
	switch (direction) {
	case 0:
		return x - 1;
	case 2:
		return x + 1;
	default:
		return x;
	}
}

int Ghost::getNextY()
{
	switch (direction) {
	case 1:
		return y + 1;
	case 3:
		return y - 1;
	default:
		return y;
	}
}

void Ghost::move(int pacmanX, int pacmanY)
{
	
}


void Ghost::Texture(char* path)
{
	/*unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);
	glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, 0); //two triangle
	glBindTexture(GL_TEXTURE_2D, TexBufferA);
	int w, h, n;
	unsigned char *data = stbi_load(path, &w, &h, &n, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load texture fail" << std::endl;
	}*/
		
	   /*texture = loadTexture(path, 32, 32);
       glBindTexture(GL_TEXTURE_2D, texture); 
       glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
       glTexParameterf(GL_TEXTURE_2D,
                       GL_TEXTURE_MIN_FILTER,
                       GL_LINEAR_MIPMAP_NEAREST); 
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
                                                                         
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       //gluBuild2DMipmaps(GL_TEXTURE_2D, 4, 8, 8, GL_RGBA, GL_UNSIGNED_BYTE, data); // build our texture mipmaps*/
}
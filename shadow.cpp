#include "shadow.h"
#include "glm/glm/vec2.hpp"
#include "glm/glm/vec3.hpp"

//#include <GL/glew.h>
//#include <GL/glut.h>
//#include "glm/glm.h"


Shadow::Shadow(int x, int y) : Ghost(x, y)
{
	Texture("../media/images/ghost1.png");
}

Shadow::~Shadow()
{
}

void Shadow::draw(int pacmanX, int pacmanY)
{
	Shadow::move(pacmanX, pacmanY);

    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor4f(SHADOW_RED, SHADOW_GREEN, SHADOW_BLUE, 0);
    glutSolidSphere(0.7, 20, 20);
	
	//right eyes
	glPushMatrix();
		glTranslatef(0.3, 0.2, 0);
		glColor4f(1, 1, 1, 0);
		glutSolidSphere(0.2, 20, 20);
		glTranslatef(0.2-0.1, 0, 0);
		glColor4f(0, 0, 0, 0);
		glutSolidSphere(0.1, 20, 20);
	glPopMatrix();
	//left eyes
	glTranslatef(-0.3, 0.2, 0);
	glColor4f(1, 1, 1, 0);
	glutSolidSphere(0.2, 20, 20);
	glTranslatef(0.2 - 0.1, 0, 0);
	glColor4f(0, 0, 0, 0);
	glutSolidSphere(0.1, 20, 20);

	glPopMatrix();
    
}

void Shadow::move(int pacmanX, int pacmanY)  //random
{
	if (is_moving) {
		direction = (rand() % 4);
		/*if (count % 4 == 0) {
			direction = (rand() % 4);
			count++;
		}
		else if(count %4 == 1){
			count++;
		}
		else {

			count++;
		}*/
		int newX = getNextX() - 5;
		int newY = getNextY() - 4;

		move_Ghost = true;
		char type = *(map + (maxY - newY) * maxX + newX);

		if (Wall::isWall(type))
			move_Ghost = false;

		if (x == pacmanX && y == pacmanY) {
			was_hit = true;
		}

		if (move_Ghost) {
			switch (direction) {
			case 0:
				x -= 1;
				break;
			case 1:
				y += 1;
				break;
			case 2:
				x += 1;
				break;
			case 3:
				y -= 1;
				break;
			}
		}

	}
}
#include "pokey.h"
#include "Utils.h"
#include "glm/glm/vec2.hpp"
#include "glm/glm/vec3.hpp"


Pokey::Pokey(int x, int y) : Ghost(x, y)
{
}

Pokey::~Pokey()
{
}

void Pokey::draw(int pacmanX, int pacmanY)
{
	Pokey::move(pacmanX, pacmanY);

    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor4f(POKEY_RED, POKEY_GREEN, POKEY_BLUE, 0);
    glutSolidSphere(0.7, 20, 20);
	//right eyes
	glPushMatrix();
		glTranslatef(0.3, 0.2, 0);
		glColor4f(1, 1, 1, 0);
		glutSolidSphere(0.2, 20, 20);
		glTranslatef(0.2 - 0.1, 0, 0);
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

void Pokey::move(int pacmanX, int pacmanY) //a*
{
	if (is_moving) {
		if (count % 4 == 0) {
			glm::vec2 start = glm::vec2(28 - (x - 4), 36 - (y - 4));
			glm::vec2 end = glm::vec2(28 - (pacmanX - 4), 36 - (pacmanY - 4));
			glm::vec2 next = Utils::aStar(start, end, amap);

			if (28 - next.x > x - 4) {
				direction = 2;
			}
			else if (28 - next.x < x - 4) {
				direction = 0;
			}
			else if (36 - next.y > y - 4) {
				direction = 1;
			}
			else if (36 - next.y < y - 4) {
				direction = 3;
			}
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
			count += rand() % 3;
		}
		else {
			count++;

		}
	}
}
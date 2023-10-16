#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 24

float playerX = 8.0f;
float playerY = 8.0f;
float playerAngle = 0.0f;

char *map =
    "##########"
    "#........#"
    "#........#"
    "#........#"
    "#........#"
    "#........#"
    "#........#"
    "#........#"
    "#........#"
    "##########";

int main()
{
    char screen[WIDTH * HEIGHT];

    while (1)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            float rayAngle = (playerAngle - FOV / 2.0f) + ((float)x / (float)WIDTH) * FOV;
            float distanceToWall = 0.0f;
            int hitWall = 0;

            float eyeX = sin(rayAngle);
            float eyeY = cos(rayAngle);

            while (!hitWall && distanceToWall < MAX_DEPTH)
            {
                distanceToWall += STEP_SIZE;

                int testX = (int)(playerX + eyeX * distanceToWall);
                int testY = (int)(playerY + eyeY * distanceToWall);

                if (testX < 0 || testX >= WIDTH || testY < 0 || testY >= HEIGHT)
                {
                    hitWall = 1;
                    distanceToWall = MAX_DEPTH;
                }
                else if (map[testY * WIDTH + testX] == '#')
                {
                    hitWall = 1;
                }
            }

            int ceilingHeight = (float)(HEIGHT / 2.0) - HEIGHT / ((float)distanceToWall);
            int floorHeight = HEIGHT - ceilingHeight;

            for (int y = 0; y < HEIGHT; y++)
            {
                if (y <= ceilingHeight)
                {
                    screen[y * WIDTH + x] = ' ';
                }
                else if (y > ceilingHeight && y <= floorHeight)
                {
                    screen[y * WIDTH + x] = '#';
                }
                else
                {
                    screen[y * WIDTH + x] = '.';
                }
            }
        }

        // Render the screen
        system("clear");
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                printf("%c", screen[y * WIDTH + x]);
            }
            printf("\n");
        }

        // Update player position and angle
        // ...

    }

    return 0;
}

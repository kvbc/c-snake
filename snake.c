#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#define sleep Sleep
#else
#include <unistd.h>
#endif


#define FOOD_CHAR			'*'
#define SNAKE_CHAR			'#'
#define SNAKE_SPEED			100
#define SNAKE_SLOWDOWN		3
#define BRD_WIDTH			60
#define BRD_HEIGHT			30
#define MAX_SNAKE_SIZE		SNAKE_SPEED / SNAKE_SLOWDOWN - 1


int main()
{
	srand(time(NULL));

	int i = 0;
	int l = 1;
	int t = SNAKE_SPEED;
	int fx = rand() % BRD_WIDTH;
	int fy = rand() % BRD_HEIGHT;
	int dx = 0;
	int dy = 0;
	char lc = 0;
	int* s = (int*)malloc(MAX_SNAKE_SIZE * sizeof(int) * 2);

	int oi = 0;
	int o1 = BRD_WIDTH * BRD_HEIGHT + BRD_HEIGHT * 3 + BRD_WIDTH + 3;
	int o2 = BRD_WIDTH + 3;
	int oe = o1 + o2;
	char* o = (char*)malloc((oe + 1) * sizeof(char));

	o[oi++] = '/';
	o[o1] = '\\';
	for(int j = 0; j < BRD_WIDTH; ++j)
	{
		o[oi++]   = '-';
		o[o1+j+1] = '-';
	}
	o[oi++] = '\\';
	o[oi++] = '\n';
	o[oe-2] = '/';
	o[oe-1] = '\n';
	o[oe] = '\0';

	s[i++] = BRD_WIDTH  / 2 - 1;
	s[i++] = BRD_HEIGHT / 2 - 1;

	for(;;)
	{
		if(_kbhit())
		{
			char c = _getch();
			if(((c == 'w')		    ||
			    (c == 'a')		    ||
			    (c == 's')		    ||
			    (c == 'd'))		    &&!
			   ((c == lc)		    ||
			    (c=='w' && lc=='s') ||
			    (c=='s' && lc=='w') ||
			    (c=='a' && lc=='d') ||
			    (c=='d' && lc=='a')))
			{
				switch(c)
				{
					case 'w':
						dx = 0;
						dy = -1;
						break;
					case 'a':
						dx = -1;
						dy = 0;
						break;
					case 's':
						dx = 0;
						dy = 1;
						break;
					case 'd':
						dx = 1;
						dy = 0;
						break;
				}
			}
			lc = c;
		}

		for(int j = i - 1; j > 1; j -= 2)
		{
			s[j]   = s[j-2];
			s[j-1] = s[j-3];
		}
		s[0] = ((s[0] += dx) < 0 ? BRD_WIDTH  - 1 : s[0] % BRD_WIDTH);
		s[1] = ((s[1] += dy) < 0 ? BRD_HEIGHT - 1 : s[1] % BRD_HEIGHT);

		for(int y = 0; y < BRD_HEIGHT; ++y)
		{
			o[oi++] = '|';
			for(int x = 0; x < BRD_WIDTH; ++x)
			{
				int a = 0;
				char c = ' ';
				if(x == fx && y == fy)
				{
					if(s[0] == fx && s[1] == fy)
					{
						i += 2;
						c = SNAKE_CHAR;
						t += SNAKE_SLOWDOWN;
						int m = ++l == MAX_SNAKE_SIZE;
						fx = m ? -1: rand() % BRD_WIDTH;
						fy = m ? -1 : rand() % BRD_HEIGHT;
					}
					else c = FOOD_CHAR;
				}
				else for(int j = 0; j < i; j += 2)
				{
					if(s[j] == x && s[j+1] == y)
					{
						if(++a > 1)
						{
							free(s);
							free(o);
							puts("Game over!");
							sleep(1000);
							_getch();
							return 0;
						}
						else c = SNAKE_CHAR;
					}
				}
				o[oi++] = c;
			}
			o[oi++] = '|';
			o[oi++] = '\n';
		}

		oi = o2;
		printf("%s", o);
		sleep(t);
	}
}

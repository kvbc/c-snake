#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


#define SNAKE_CHAR			'#'
#define SNAKE_SPEED			100
#define SNAKE_SLOWDOWN		3

#define FOOD_CHAR			'*'
#define FOOD_MOVES			3

#define BRD_WIDTH			60
#define BRD_HEIGHT			30
#define MAX_SNAKE_SIZE		(BRD_WIDTH + BRD_HEIGHT) / 2


int main()
{
	srand(time(NULL));

	int i = 0;
	int l = 1;
	int f = 0;
	int t = SNAKE_SPEED;
	int m = FOOD_MOVES - 1;
	int fx = -1;
	int fy = -1;
	int dx = 0;
	int dy = 0;
	char lc = 0;
	int* s = malloc(MAX_SNAKE_SIZE * sizeof(int) * 2);

	int oi = 0;
	int o1 = BRD_WIDTH * BRD_HEIGHT + BRD_HEIGHT * 3 + BRD_WIDTH + 3;
	int o2 = BRD_WIDTH + 3;
	int oe = o1 + o2;
	char* o = malloc((oe + 1) * sizeof(char));

	o[oi++] = '/';
	o[o1] = '\\';
	for(int j = 0; j < BRD_WIDTH; ++j)
	{
		o[oi++] = '-';
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
				if(!f && (++m == FOOD_MOVES))
				{
					m = 0;
					f = 1;
					fx = rand() % BRD_WIDTH;
					fy = rand() % BRD_HEIGHT;
				}
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

		for(int j = i - 1; j > 1; --j)
		{
			s[j]   = s[j-2];
			s[--j] = s[j-2];
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
				if(f && fx == x && fy == y)
				{
					if(s[0] == fx && s[1] == fy)
					{
						m = 0;
						f = (++l == MAX_SNAKE_SIZE);
						t += SNAKE_SLOWDOWN;
						fx = -1;
						fy = -1;
						s[i++] = s[i-1] + dx;
						s[i++] = s[i-2] + dy;
						c = SNAKE_CHAR;
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
							puts("Game over!");
							Sleep(1000);
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
		Sleep(t);
	}
}

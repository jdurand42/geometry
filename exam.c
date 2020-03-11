#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int ft_error(int i)
{
	if (i == 0)
		printf("error: Argument\n");
	if (i == 1)
		printf("error: File corrupted\n");
	return (1);
}

void print_plan(char **plan, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			write(1, &plan[i][j], 1);
		}
		write(1, "\n", 1);
		
	}
}

int main(int ac, char **av)
{
	int i =0;
	char **plan;
	char ce = 0;
	int h, w;
	FILE *file = NULL;

	if (ac != 2)
		return (ft_error(0));
	if (!(file = fopen(av[1], "r")))
		return (ft_error(1));
	int ret = 0;

	if ((ret = fscanf(file, " %d %d %c ", &w, &h, &ce)) != 3)
		return (ft_error(1));
	if (w <= 0 || w > 300 || h <= 0 || h > 300)
		return (ft_error(1));
	plan = malloc(h * sizeof(char*));
	for (int j = 0; j < h; j++)
	{
		plan[j] = malloc(w * sizeof(char));
		memset(plan[j], ce, w);
	}
	char type, c;
	double xc, yc, r, dist;
	int x = 0, y = 0;
	while ((ret = fscanf(file, " %c %lf %lf %lf %c ", &type, &xc, &yc, &r, &c)) != -1)
	{
		x = 0; y = 0;
		dist = 0;
		if (ret != 5)
			return (ft_error(1));
		if ((type !='c' && type != 'C') || r <= 0)
			return (ft_error(1));
		printf("ret %d, %f %f\n", ret, xc, yc);
		if (type == 'C')
		{
			while (y < h)
			{
				while (x < w)
				{
					dist = sqrtf(powf(xc - x, 2) + powf(yc - y, 2));
					if (dist <= r)
					 	plan[y][x] = c;
					x++;
				}
				x = 0; y++;
			}
		}
		else if (type == 'c')
		{
			while (y < h)
			{
				while (x < w)
				{
					dist = sqrtf(powf(xc - x, 2) + powf(yc - y, 2));
					if (dist <= r && dist >= r - 1)
					 	plan[y][x] = c;
					x++;
				}
				x = 0; y++;
			}
		}
	}	  
	print_plan(plan, h, w);
	return (0);
}
	

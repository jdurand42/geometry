/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:01:03 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/28 15:08:53 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

void 	ft_exit(int code)
{
	printf("File corrupted\n");
	exit(1);
}

int	main(int ac, char **av)
{
	char **plan;
	int i = 0;
	int j =0;
	char *b;
	FILE *file;

	int w=0;
	int h=0;
	int ret = 0;
	char empty = 0;

	b = NULL;
	if (ac != 2)
		exit(1);
	if (!(file = fopen(av[1], "r")))
	{
		printf("%s\n", "No file\n");
		exit(1);
	}
	//first line
	ret = fscanf(file, "%d %d %c", &w, &h, &empty);
	printf("ret %d, w; %d, h: %d, empty: %c\n", ret, w, h, empty);
	if (ret != 3 || empty == 0 || h <= 0 || h > 300 || w <= 0 || w > 300)
		ft_exit(1);
	char n;
	ret = fscanf(file, "%c", &n);
	if (n != '\n')
		ft_exit(1);
	printf("%c\n", n);
	plan = malloc(h * sizeof(char*));
	while(i < h)
	{
		plan[i] = malloc((w) * sizeof(char));
		while (j < w)
		{
			plan[i][j] = empty;
			j++;
		}
		j = 0;
		i++;
	}
	float x_center, y_center, r;
	int x, y;
	char c;
	char type;
	x = 0;
	y = 0;

	while (ret != -1 & ret != 0)
	{
		ret = fscanf(file, " %c %f %f %f %c", &type, &x_center, &y_center,
		&r, &c);
		if (ret != 5 && ret != -1)
			ft_exit(1);
		//ret = fscanf(file, "%c", &n);
		//printf("%d\n", ret);
		printf("%c %f %f %f %c\n", type, x_center, y_center, r, c);
		if (type == 'C')
		{
			while (y < h)
			{
				while (x < w)
				{
					if (sqrt(pow(x - x_center, 2) + pow(y - y_center, 2)) <= r)
						plan[y][x] = c;
					x++;
				}
				x = 0;
				y++;
			}
		}
		else if (type == 'c')
		{
			while (y < h)
			{
				while (x < w)
				{
					if (sqrt(pow(x - x_center, 2) + pow(y - y_center, 2)) <= r
					 && (sqrt(pow(x - 1 - x_center, 2) + pow(y - y_center, 2)) > r ||
				 		sqrt(pow(x + 1 - x_center, 2) + pow(y - y_center, 2)) > r ||
						sqrt(pow(x - x_center, 2) + pow(y - 1 - y_center, 2)) > r ||
						sqrt(pow(x - x_center, 2) + pow(y + 1 - y_center, 2)) > r))
							plan[y][x] = c;
					x++;
				}
				x = 0;
				y++;
			}
		}
		x = 0; y = 0;
	}

	//ret = fscanf(file, "%c %f %f %f %c", &type, &x_center, &y_center,
	//	&r, &c);
	//printf("ret: %d\n", ret);
	//if (ret != 5)
	//	ft_exit(1);
	//printf("%c %f %f %f %c\n", type, x_center, y_center, r, c);
	for (int k = 0; k < h; k++)
		printf("%.*s\n", w, plan[k]);

}

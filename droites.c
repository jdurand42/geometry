/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   droites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:45:02 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/07 17:24:58 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#define X_MAX 30
#define Y_MAX 30
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"


void 	show_tab(char **tab)
{
	for (int j = 0; j < Y_MAX; j++)
	{
		for (int i = 0; i < X_MAX; i++)
		{
			if (tab[j][i] != '@')
				printf("%c ", tab[j][i]);
			else
				printf(GREEN "%c " RESET, tab[j][i]);
		}
		printf("\n");
	}
}

void 	ft_setup(char **tab)
{
	for (int i = 0; i < Y_MAX; i++)
	{
		for (int j = 0; j < X_MAX; j++)
			tab[i][j] = '0';
	}
}

int main(int ac, char **av)
{
	char **tab;
	int x1;
	int x2;
	int y1;
	int y2;
	float dx;
	float dy;
	float x_next;
	float y_next;

	tab = malloc(Y_MAX * sizeof(char*));
	for (int i =0; i < Y_MAX; i++)
		tab[i] = malloc(X_MAX * sizeof(char));
	if (ac != 5)
	{
		printf("<exec> x1 y1 x2 y2\n");
		return (0);
	}
	ft_setup(tab);
	x1 = atoi(av[1]);
	y1 = atoi(av[2]);
	x2 = atoi(av[3]);
	y2 = atoi(av[4]);
	if (x1 > x2)
	{
		x_next = x1;
		x1 = x2;
		x2 = x_next;
		y_next = y1;
		y1 = y2;
		y2 = y_next;
	}
	dx = x2 - x1;
	dy = y2 - y1;
	tab[y1][x1] = '@';
	tab[y2][x2] = '@';
	x_next = x1 + 1;
	while (x_next < x2)
	{
		y_next = y1 + dy * (x_next - x1) / dx;
		tab[(int)y_next][(int)x_next] = '@';
		x_next++;
	}


	show_tab(tab);
}

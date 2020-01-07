/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:22:13 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/07 17:25:47 by jdurand          ###   ########.fr       */
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
	int y1;
	int lo;
	int la;

	tab = malloc(Y_MAX * sizeof(char*));
	for (int i =0; i < Y_MAX; i++)
		tab[i] = malloc(X_MAX * sizeof(char));
	if (ac != 5)
	{
		printf("<exec> x y length width\n");
		return (0);
	}
	ft_setup(tab);
	x1 = atoi(av[1]);
	y1 = atoi(av[2]);
	lo = atoi(av[3]);
	la = atoi(av[4]);
	int y = y1;
	int x = x1;
	if (y1 + lo >= Y_MAX)
		lo = Y_MAX - y1;
	if (x1 + la >= X_MAX)
		la = X_MAX - x1;
	while (y < y1 + lo)
	{
		while (x < x1 + la)
		{
			tab[y][x] = '@';
			x++;
		}
		x = x1;
		y++;
	}
	show_tab(tab);
}

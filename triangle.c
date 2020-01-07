/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:19:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/07 17:26:37 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   droites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:45:02 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/20 16:07:41 by jdurand          ###   ########.fr       */
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
	int x_start;
	int y_start;
	int y;
	int line;
	int line_id;
	int story;
	float dx;
	float dy;

	tab = malloc(Y_MAX * sizeof(char*));
	for (int i =0; i < Y_MAX; i++)
		tab[i] = malloc(X_MAX * sizeof(char));
	if (ac != 4)
	{
		printf("<exec> x_top y_top n_story\n");
		return (0);
	}
	ft_setup(tab);
	x_start = atoi(av[1]);
	y_start = atoi(av[2]);
	story = atoi(av[3]);
	line = 1;
	line_id = line;
	tab[y_start][x_start] = '@';
	y = y_start + 1;
	while (story && y < Y_MAX)
	{
		line_id = line;
		tab[y][x_start] = '@';
		while (line_id)
		{
			if (x_start - line_id >= 0)
				tab[y][x_start - line_id] = '@';
			if (x_start + line_id < X_MAX)
				tab[y][x_start + line_id] = '@';
			line_id--;
		}
		line++;
		story--;
		y++;
	}
	show_tab(tab);
}

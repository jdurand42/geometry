#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

double	ft_atoi_f(char *s, int *i)
{
	double res = 0;
	double dec = 0;
	int r = 0;
	
	while (s[*i] != 0 && s[*i] != '\n' && s[*i] == 32)
		*i += 1;
	while (s[*i] != 0 && s[*i] != '\n' &&
		s[*i] >= '0' && s[*i] <= '9' && s[*i] != '.')
	{
		res = 10 * res + s[*i] - '0';
		*i += 1;
	}
	if (s[*i] == '.')
	{
		*i += 1;
		while (s[*i] != 0 && s[*i] != '\n' && s[*i] >= '0' && s[*i] <= '9')
		{
			dec = dec * 10 + s[*i] - '0';
			*i += 1;
			r++;;
		}
		while (r--)
			dec /= 10;
	}
	res = res + dec;
	return (res);
}

int	error_1(void)
{
	printf("erreur controlee\n");
	return (1);
}

void	show_tab(char **tab, int w, int h)
{
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			printf("%c ", tab[j][i]);
		}
		printf("\n");
	}
}
void 	draw_empty(char **tab, int w, int h, double cx, double cy, double r, char c);
void parse_a_circle(char **tab, int w, int h, char *buffer, int *i);
void 	draw_full(char **tab, int w, int h, double cx, double cy, double r, char c);

int main(int ac, char **av)
{
	char buffer[1024];
	int i = 0;
	int ret;
	char **tab;
	FILE *fd;
	
	double test = ft_atoi_f("12310.11110", &i);
	printf("%lf %d\n", test, i);
	
	i = 0;
	int w = 0; int h = 0; char empty = 0;
	fd = fopen(av[1], "r");
	if (fd == NULL)
		return (error_1());
	ret = fread(buffer, sizeof(char), 1022, fd);
	if (ret <= 0)
		return (error_1());
	buffer[ret] = 0;
	printf("%s\n", buffer); 	
	
	// parse 1 line
	w = ft_atoi_f(buffer, &i);
	h = ft_atoi_f(buffer, &i);
	i++;
	empty = buffer[i++];
	printf("%d, %d, %c\n", w, h, empty);
	if (buffer[i] != '\n')
		return (error_1());
	i++;
	tab = malloc(h * sizeof(char*));
	for (int j = 0; j < h; j++)
	{
		tab[j] = malloc(w * sizeof(char));
		for (int k = 0; k < w; k++)
			tab[j][k] = empty;
	}
	show_tab(tab, w, h);
	
// fin parsing tab
	while (buffer[i] != 0)
		parse_a_circle(tab, w, h, buffer, &i);	
	show_tab(tab, w, h);
	return (0);
}

void parse_a_circle(char **tab, int w, int h, char *buffer, int *i)
{
	double cx = -1;
	double cy = -1;
	double r = 0;
	char c = 0;
	int flag = 0;

	if (buffer[*i] == 'C')
		flag = 0;
	else if (buffer[*i] == 'c')
		flag = 1;
	*i += 1;
	cx = ft_atoi_f(buffer, i);
	cy = ft_atoi_f(buffer, i);
	r = ft_atoi_f(buffer, i);
	if (buffer[*i] != 0) // && \n
		*i += 1;
	c = buffer[*i];
	printf("line: %lf, %lf, %lf, %c, %d\n", cx, cy, r, c, flag);
	if (cx <= 0 || cy <= 0 || r == 0 || cx >= w || cy >= h || c == 0 || flag == -1)
		return ;
	
	if (flag == 1)
	{
		draw_empty(tab, w, h, cx, cy, r, c);
		return ;
	}
	if (flag == 0)
		draw_full(tab, w, h, cx, cy, r, c);
}

void 	draw_full(char **tab, int w, int h, double cx, double cy, double r, char c)
{
	double distc;
	int x = 0;
	int y = 0;

	while (y < h)
	{
		while (x < w)
		{
			distc = sqrt(powf(x - cx, 2) + powf(y - cy, 2));
			if (distc < r)
				tab[y][x] = c;
			x++;
		}
		y++;
		x = 0;
	}
}

double	get_dist(double dx, double dy)
{
	return (sqrt(powf(dx, 2) + powf(dy, 2)));
}

void 	draw_empty(char **tab, int w, int h, double cx, double cy, double r, char c)
{
	double distc;
	int x = 0;
	int y = 0;

	while (y < h)
	{
		while (x < w)
		{
			distc = get_dist(x - cx, y - cy);
			if (distc < r)
			{
				if (!(get_dist(x - 1 - cx, y - cy) < r && get_dist(x + 1 - cx, y - cy) < r 
				&& get_dist(x - cx, y - 1 - cy) < r && get_dist(x - cx, y + 1 - cy) < r))
					tab[y][x] = c;
			} 
			x++;
		}
		y++;
		x = 0;
	}
}

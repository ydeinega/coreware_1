/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:23:41 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/07/02 22:00:14 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void		check_color(int pos, t_player **players, WINDOW *win)
{
	int			i;
	int			st;
	int			len;
	int			fd;

	i = -1;
	fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND);
	while (players[++i])
	{
		st = players[i]->start;
		len = players[i]->len;
		if (pos == st)
			wattron(win, A_REVERSE | A_BLINK);
		if (pos >= st && pos < st + len)
			wattron(win, COLOR_PAIR(i + 1));
		else if (pos >= st + len && (!players[i + 1] || pos <= players[i + 1]->start))
		{
			if (i == 0)
				wattroff(win, COLOR_PAIR(1));
			else
				wattroff(win, COLOR_PAIR(i));
		}
	}
}

void			write_value(int pl, unsigned char val, int pos, WINDOW *win)
{
	int			x;
	int			y;
	char		*buff;

	y = pos / 64 + 1;
	x = (pos % 64) * 3 + 1;
	wattron(win, COLOR_PAIR(pl + 1));
	mvwprintw(win, y, x, (buff = ft_itoa_base_mod(val, 16, 2)));
	wattroff(win, A_REVERSE | A_BLINK);
	pos % 64 == 63 ? wprintw(win, "\n ") : wprintw(win, " ");
	ft_strdel(&buff);
}

void			draw_procs(unsigned char *map, WINDOW *win)
{
	t_process	*curr;
	char		*buff;

	buff = NULL;
	curr = g_procs;
	while (curr)
	{
		wattroff(win, A_REVERSE | A_BLINK);
		write_value(curr->player, map[curr->prev], curr->prev, win);
		wattron(win, A_REVERSE | A_BLINK);
		write_value(curr->player, map[curr->pos], curr->pos, win);
		wattroff(win, A_REVERSE | A_BLINK);
		curr = curr->next;
	}
}

void			draw_map(t_player **pl, WINDOW *win, unsigned char *map)
{
	int			i;
	char		*buff;

	i = -1;
	buff = NULL;
	mvwprintw(win, 0, 0, "\n ");
	while (++i < MAP_SIZE)
	{
		ft_strdel(&buff);
		check_color(i, pl, win);
		wprintw(win, "%s", (buff = ft_itoa_base_mod(map[i], 16, 2)));
		wattroff(win, A_REVERSE | A_BLINK);
		i % 64 == 63 && i > 0 ? wprintw(win, "\n ") : wprintw(win, " ");
	}
	ft_strdel(&buff);
}

void				draw_changes(t_change **changes, unsigned char *map, WINDOW *win)
{
	t_change	*curr;
	t_change	*prev;

	if (changes == NULL || !(curr = *changes))
		return (NULL);
	while ((prev = curr))
	{
		write_value(curr->player, curr->value, curr->pos, win);
		curr = curr->next;
		free(prev);
	}
	*changes = NULL;
}

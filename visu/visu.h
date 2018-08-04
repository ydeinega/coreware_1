/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:49:36 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/07/02 21:36:46 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# define MAP_SIZE 64 * 64
# include <ncurses.h>

void			draw_all(WINDOW *win);
WINDOW			*visual_init(void);
char			*ft_itoa_base_mod(intmax_t nb, int base, int flag);

#endif

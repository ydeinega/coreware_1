/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:25:43 by dgonor            #+#    #+#             */
/*   Updated: 2018/07/20 21:25:45 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

void		verb_print_lives(int p_num)
{
//	ft_printf("6 SEGFOLT?\n");
	int 		i;
	int 		num_players;
	t_player	*player;

	i = -1;
	num_players = g_game.players;
	player = g_game.player;
	while (++i < num_players)
	{
		if (player[i].num == -p_num)
			ft_printf("Player %i (%s) is said to be alive\n", i + 1, player[i].name);
	}
}

void		verb_print_ctd(int ctd)
{
	if ((2 & g_game.number_v) > 0)
		ft_printf("Cycle to die is now %i\n", ctd);
}

void		verb_print_cycles(int cycle)
{
//	ft_printf("5 SEGFOLT?\n");
	if ((2 & g_game.number_v) > 0)
		ft_printf("It is now cycle %i\n", cycle);
	// if ((g_verb.ctd_change))
	// 	ft_printf("Cycle to die is now %i\n", g_verb.ctd);
}

void		verb_print_op(t_process *proc, t_arg_type *arg_type, unsigned int *arg)
{
	t_op 		op;
	int 		i;

	i = -1;
	op = op_tab[proc->opcode - 1];
	if ((4 & g_game.number_v) > 0)
	{
		
		ft_printf("P%5i | ", proc->num);
		ft_printf("%s", op.op);
		while (++i < op.arg_num)
		{
			ft_printf(" ");
			if (arg_type[i] == T_REG)
			{
				if (op.arg[i] == T_REG)
				{
					ft_printf("r");
					ft_printf("%i", arg[i]);
				}
				else
					ft_printf("%i", arg_fin(proc, arg[i], arg_type[i]));
			}
			else
				ft_printf("%i", arg[i]);	
		}
		if (op.opcode == 9 && proc->carry == 1)
			ft_printf(" OK");
		else if (op.opcode == 9 && proc->carry == 0)
			ft_printf(" FAILED");
		ft_printf("\n");
		//sti!!!
	}
	if ((1 & g_game.number_v) > 0 && proc->opcode == 1)
		verb_print_lives((int)(*arg));
}

void		verb_print_death(int proc_num, int cycles_not_live)
{
//	ft_printf("3 SEGFOLT?\n");
	if ((8 & g_game.number_v) > 0)
	{
		ft_printf("Process %i ", proc_num);
		ft_printf("hasn't lived for %i cycles ", cycles_not_live);
		if ((g_verb.ctd_change))
			ft_printf("(CTD %i)\n", g_game.ctd);
	}
	//	ft_printf("Process %i hasn't lived for %i cycles (CTD %i)\n", op->proc_num, death->cycles_not_live, g_verb.ctd);
}

void		verb_print_pc(int pc_prev, int pc_new, int move, unsigned char *board)
{
	int 	i;

	i = -1;
	if ((16 & g_game.number_v) > 0)
	{
		ft_printf("ADV %i ", move);
		pc_prev == 0 ? ft_printf("(0x0000 -> "): ft_printf("(%#.4x -> ", pc_prev);
		pc_new == 0 ? ft_printf("0x0000) ") : ft_printf("%#.4x) ", pc_new);
		while (++i < move)
			ft_printf("%.2x ", board[(pc_prev + i) % MEM_SIZE]);
		ft_printf("\n");
	}

//	ft_printf("2 SEGFOLT?\n");
	// t_list_pc	*pc;
	// int 		i;

	// i = -1;
	// pc = g_verb.pc;
	// if (g_verb.pc)
	// {
	// 	ft_printf("ADV %i ", pc->move);
	// 	pc->pc_prev == 0 ? ft_printf("(0x0000 -> "): ft_printf("(%#.4x -> ", pc->pc_prev);
	// 	pc->pc_new == 0 ? ft_printf("0x0000)") : ft_printf("%#.4x)", pc->pc_new);
	// 	while (++i < pc->move)
	// 		ft_printf(" %.2x", pc->line[i]);
	// 	ft_printf("\n");
	// }
//	ft_printf("%s %i (%#.4x -> %#.4x) %s\n","ADV", pc->move, pc->pc_prev, pc->pc_new, pc->line);
}

#include "corewar.h"

void	exec_sti(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int				value;
	int				delta;

	value = arg_fin(process, arg[0], arg_type[0]);
	delta = arg_fin(process, arg[1], arg_type[1]) + arg_fin(process, arg[2], arg_type[2]);
	store_value(process, value, delta, IDX_MOD);
}

void	exec_fork(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int			delta;
	int			pc;
	t_process	*new;

	new = NULL;
	delta = arg_fin(process, arg[0], arg_type[0]);
	pc = (process->pc + (delta % IDX_MOD)) % MEM_SIZE;//???
	new = new_process(NULL, process, pc);
	add_process(&(g_game.proc), new);
	g_game.proc_num++;
}

void	exec_lld(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]);
	process->reg[arg[1] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_lldi(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	unsigned int	res;
	int				delta;
	int				dst;

	dst = arg_fin(process, arg[2], arg_type[2]);
	delta = arg_fin(process, arg[0], arg_type[0]) + arg_fin(process, arg[1], arg_type[1]);
	res = extract_ind(process->pc, delta, 0);
	process->reg[dst - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_lfork(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int			delta;
	int			pc;
	t_process	*new;

	new = NULL;
	delta = arg_fin(process, arg[0], arg_type[0]);
	pc = (process->pc + delta) % MEM_SIZE;
	new = new_process(NULL, process, pc);
	add_process(&(g_game.proc), new);
	g_game.proc_num++;
}

void	exec_aff(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]);
	res = res % 256;
	ft_printf("%c", res);//???
}

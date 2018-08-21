#include "corewar.h"

static int				get_length(t_arg_type arg_type, t_op op)
{
	int	length;

	length = 0;
	if (arg_type == T_REG)
		length = 1;
	else if (arg_type == T_DIR)
		length = op.label;
	else if (arg_type == T_IND)
		length = IND_SIZE;
	return (length);
}

// static unsigned int		get_arg(t_op op, t_arg_type arg_type, unsigned int res, int pc)
// {
// 	if (pc < 0)
// 		return (0);
// 	if (arg_type == T_REG)
// 		res = (unsigned int)((unsigned char)res);
// 	else if (arg_type == T_DIR && op.label == 2)
// 		res = (unsigned int)((short)res);
// 	else if (arg_type == T_IND)
// 		res = (unsigned int)((short)res);
// 	return (res);
// }

unsigned int			*extract_arg(t_op op, int pc, t_arg_type *arg_type)//ПРИ СЧИТЫВАНИИ АРГУМЕНТЫ НУЖНО КАСТИТЬ!
{
	int				i;
	int				length;
	int				pc_copy;
	unsigned int	*arg;
	unsigned char	*line;

	i = 0;
	length = 0;
	pc_copy = pc;
	pc = op.codage ? (pc + 2) % MEM_SIZE : (pc + 1) % MEM_SIZE;
	arg = (unsigned int *)malloc(sizeof(unsigned int) * op.arg_num);//if !line malloc failed
	line = NULL;
	while (i < op.arg_num)
	{
		length = arg_type ? get_length(arg_type[i], op) : op.label;
		line = extract_line(pc, length);//под вопросом
		arg[i] = conv_hex(line, length);
		// if (arg_type)
		// 	arg[i] = get_arg(op, arg_type[i], conv_hex(line, length), pc_copy);
		// else
		// 	arg[i] = get_arg(op, op.arg[0], conv_hex(line, length), pc_copy);
		free(line);
		i++;
		pc = (pc + length) % MEM_SIZE;//???
	}
	return (arg);
}

unsigned char		*extract_line(int pc, int length)
{
	int 			i;
	unsigned char	*line;

	i = 0;
	line = (unsigned char *)malloc(sizeof(unsigned char) * length);//if !line malloc failed
	while (i < length)
	{
		line[i] = g_game.board[pc];
		i++;
		pc = (pc + 1) % MEM_SIZE;
	}
	return (line);
}

unsigned int			extract_ind(int pc, int delta, int base)//BASE???
{
	unsigned char	*line;
	unsigned int	res;
	int				pc_new;

	line = NULL;
	res = 0;
	pc_new = 0;
	if (base)
		pc_new = (pc + (delta % base)) % MEM_SIZE;
	else
		pc_new = (pc + delta) % MEM_SIZE;
	line = extract_line(pc, 4);
	res = conv_hex(line, 4);
	free(line);
	return (res);		
}

// unsigned int			extract_ind(int pc, int delta, int base)//BASE???
// {
// 	unsigned char	*line;
// 	unsigned int	res;
// 	int				pc_new;

// 	line = NULL;
// 	res = 0;
// 	pc_new = 0;
// 	if (base)
// 		pc_new = (pc + (delta % base)) % MEM_SIZE;
// 	else
// 		pc_new = (pc + delta) % MEM_SIZE;
// 	line = extract_line(pc, 4);
// 	res = conv_hex(line, 4);
// 	free(line);
// 	return (res);		
// }

unsigned int			arg_fin(t_process *process, unsigned int arg, t_arg_type arg_type)
{
	unsigned int	res;
	unsigned int	base;

	res = 0;
	base = IDX_MOD;
	if (arg_type == T_REG)
		res = process->reg[arg - 1];
	else if (arg_type == T_DIR)
		res = arg;
	else if (arg_type == T_IND)
	{
		if (process->opcode == 13)
			base = 0;
		res = extract_ind(process->pc, arg, base);
	}
	return (res);
}

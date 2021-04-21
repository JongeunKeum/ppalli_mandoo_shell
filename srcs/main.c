#include "minishell.h"

void	minishell(char *argv, char **envp)
{
	int 	status;
	char	*cmdlines;
	char	**cmds;
	t_cmd	*list;

	int		i;

	status = 1;
	while (status)
	{
		write(1, "> ", 2);
		read_cmd(&cmdlines);
		cmds = sep_cmdline(cmdlines , ';');
		free(cmdlines);
		i = 0;
		while (cmds && cmds[i])
		{
			// list return
			list = get_parsed_list(cmds[i]);
			// run
			i++;
		}
		i = 0;
		while (cmds && cmds[i])
			free(cmds[i++]);
		if (cmds != NULL)
			free(cmds);

	}
}

void	init_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input ����
	term.c_lflag |= ECHO;		// �Է½� �͹̳ο� ���̵���
	term.c_cc[VMIN] = 1;        // �ּ� �Է� ���� ũ��
	term.c_cc[VTIME] = 0;       //���� ���� �ð� (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int		main(int argc, char **argv, char **envp)
{
	init_termios();
	minishell(argv[0], envp);
}

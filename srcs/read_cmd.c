#include "read_cmd.h"

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

int	read_cmd(char **line)
{
	int	c;

	*line = NULL;
	while (read(0, &c, sizeof(c)) > 0)
	{
		*line = ft_str_char_join(*line, c);
		if (c == '\n')
			break;
		c = 0;
	}
	return (1);
}

// int	read_cmd(char **line)
// {
// 	struct termios	term;
// 	char			c;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~ICANON;    // non-canonical input ����
// 	term.c_lflag &= ECHO;      // �Է� �� �͹̳ο� ���̵���
// 	term.c_cc[VMIN] = 1;        // �ּ� �Է� ���� ũ��
// 	term.c_cc[VTIME] = 0;       //���� ���� �ð� (timeout)
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);

// 	*line = NULL;
// 	while (read(0, &c, sizeof(c)) > 0 && c != '\n')
// 		*line = ft_str_char_join(*line, c);
// 	return (1);
// }



// int	main()
// {
// 	struct termios term;
// 	char c;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~(ICANON|~ECHO);    // non-canonical input ����
// 	// term.c_lflag &= ~ICANON;    // non-canonical input ����
// 	// term.c_lflag &= ~ECHO;      // �Է� �� �͹̳ο� ������ �ʰ�
// 	term.c_cc[VMIN] = 1;        // �ּ� �Է� ���� ũ��
// 	term.c_cc[VTIME] = 0;       //���� ���� �ð� (timeout)
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);

// 	int i = 0;
// 	while (read(0, &c, sizeof(c)) > 0 && c != '\n')
// 	{
// 		i++;
// 		// printf("%c\n", c);
// 	}
// }

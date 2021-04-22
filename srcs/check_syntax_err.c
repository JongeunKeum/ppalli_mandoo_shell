#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}

int	check_syntax_err(char *line)
{
	char	sflag;
	// char	c;
	// char	*str;
	int		i;

	sflag = 0;
	// str = line;
	int num = 0;
	i = 0;
	printf("%s\n", line);
	while (line[i])
	{
		if (ft_strchr(" \t\n", line[i]))
		{
printf("space\n");
			i++;

		}
		// else if (ft_strchr_to_c("><|;", line[i], &c))
		else if (line[i] == '\'')
		{
printf("\'\n");
			if (sflag & S_QUOTE)						// if s_quote on
				sflag ^= S_QUOTE;						// s_quote off
			else if (!((sflag & D_QUOTE) == D_QUOTE))	// if d_quote off
				sflag |= S_QUOTE;						// s_quote on
			i++;
		}												// if d_quote on -> Do not on s_quote
		else if (line[i] == '\"')
		{
printf("\"\n");
			if (sflag & D_QUOTE)						// if d_quote on
				sflag ^= D_QUOTE;						// d_quote off
			else if (!((sflag & S_QUOTE) == S_QUOTE))	// if s_quote off
				sflag |= D_QUOTE;						// d_quote on
			i++;
		}												// if s_quote on -> Do not on d_quote
		else if ((line[i] == '>' || line[i] == '<') && (sflag & S_QUOTE) == 0 && (sflag & D_QUOTE) == 0)
		{	// when outside quote
printf(">\n");
			if (sflag & REDIRECT)						// if redirect already on (echo 123 > > file)
				return (0);								// syntax err
			sflag |= REDIRECT;							// redirect on
			// sflag ^= POSSIBLE;
			if (line[i] == '>' && line[i + 1] == '>')	// if append case
				i += 2;
			else										// if not append case
				i++;
		}
		else if (line[i] == '|' && (sflag & S_QUOTE) == 0 && (sflag & D_QUOTE) == 0)
		{	// when outside quote
printf("|\n");
			if (sflag & REDIRECT)						// if redirect on	(>  | )
				return (0);								// syntax err
			if (((sflag & POSSIBLE) == 0) && (sflag & CMD) == 0)	// if impossible and cmd off (    | | )
				return (0);								// syntax err
			sflag |= PIPE;								// pipe on
			sflag ^= CMD + POSSIBLE;					// cmd and possible off
			i++;
		}
		else if (line[i] == ';' && (sflag & S_QUOTE) == 0 && (sflag & D_QUOTE) == 0)
		{	// when outside quote
printf(";\n");
			if ((sflag & REDIRECT) || (sflag & PIPE))	// if redirect or pipe on (echo 123 > ;)
				return (0);								// syntax err
			if (((sflag & CMD) == 0) && ((sflag & POSSIBLE) == 0))	// if cmd and possible off (  ;) (echo 123;;)
				return (0);								// syntax err
			sflag = 0;									// flag zero set
			i++;
		}
		else
		{
printf("else\n");
			if (sflag & REDIRECT)
				sflag = (sflag ^ REDIRECT) | POSSIBLE;
			else if (sflag & PIPE)
			{
				sflag ^= PIPE;
				sflag |= CMD + POSSIBLE;
			}
			else if (((sflag & REDIRECT) == 0) && ((sflag & PIPE) == 0))
				sflag |= CMD;
			i++;
		}
	}
	if ((sflag & REDIRECT) || (sflag & PIPE))		// if redirect or pipe on at the end (echo 123 > )
		return (0);
	return (1);
}

int main()
{
	// char a = 1;
	// printf("%d\n", a & 1);
	if(!check_syntax_err("echo > feasd > fed < ede >> edsd;"))
		printf("\nsyntax error\n\n");
	return (0);
}

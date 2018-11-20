/*
**	msg_exit : a printf for crashing cleanly.
**	USAGE : msg_exit("error %[d, s]...", memory)
**		%s = string (char*)
**		%d = int
**	When %[...] is read,
**	 msg_exit will interpret memory as pointing to the specified datatype.
*/

#include "fdf.h"

void	msg_exit(char *msg, void *data)
{
	size_t	len;
	char	*var;

	if (msg)
	{
		len = 0;
		while (msg[len] && msg[len] != '%')
			++len;
		write(2, (void *)msg, len);
		if (msg[len] == '%')
		{
			msg = &msg[len + 1];
			var = NULL;
			if (*msg == 'd')
				var = ft_itoa(*(int*)data);
			else if (*msg == 's')
				var = (char*)data;
			if (var)
			{
				len = ft_strlen(var);
				write(2, var, len);
			}
		}
		write(2, "\n", 1);
	}
	write(1, "error\n", 6);
	exit(EXIT_FAILURE);
}

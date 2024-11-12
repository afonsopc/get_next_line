/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:28:23 by afpachec          #+#    #+#             */
/*   Updated: 2024/11/11 23:48:31 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	line = NULL;
	bytes_read = 1;
	while ((fd >= 0 || BUFFER_SIZE > 0) && bytes_read > 0)
	{
		if (buff[0])
		{
			line = str_join_buff(line, buff);
			if (!line)
				return (NULL);
			if (line[ft_strlen(line, '\n') - 1] == '\n')
				break ;
		}
		else
		{
			bytes_read = read(fd, buff, BUFFER_SIZE);
			if (bytes_read < 0)
				return (free(line), NULL);
			buff[bytes_read] = '\0';
		}
	}
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("!%s!\n", line);
	line = get_next_line(fd);
	printf("!%s!\n", line);
	return (0);
} */
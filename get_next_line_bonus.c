/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:18:59 by afpachec          #+#    #+#             */
/*   Updated: 2024/11/08 21:12:48 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	dup = malloc(ft_strlen(s1) + 1);
	if (dup == NULL)
		return (dup);
	i = -1;
	while (s1[++i])
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}

ssize_t	memchr_distance(const void *str, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	uc;

	ptr = (unsigned char *)str;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*ptr == uc)
			return ((char *)ptr - (char *)str);
		ptr++;
	}
	return (-1);
}

char	*read_line(char buff[BUFFER_SIZE + 1], char *str[3], ssize_t distance)
{
	str[2] = ft_substr(buff, 0, distance);
	if (!str[2])
	{
		free(str[1]);
		return (NULL);
	}
	str[0] = ft_strjoin(str[1], str[2]);
	free(str[2]);
	free(str[1]);
	if (!str[0])
		return (NULL);
	ft_memmove(buff, &buff[distance + 1], BUFFER_SIZE - distance - 1);
	ft_memset(&buff[BUFFER_SIZE - distance - 1], '\0', distance + 1);
	str[1] = str[0];
	str[0] = ft_strjoin(str[1], "\n");
	free(str[1]);
	if (!str[0])
		return (NULL);
	return (str[0]);
}

ssize_t	read_fd(int fd, char buff[BUFFER_SIZE + 1])
{
	ssize_t		read_bytes;

	read_bytes = read(fd, buff, BUFFER_SIZE);
	if (read_bytes <= 0)
		ft_memset(buff, '\0', BUFFER_SIZE);
	else
		buff[read_bytes] = '\0';
	return (read_bytes);
}

char	*get_next_line(int fd)
{
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	char		*str[3];
	ssize_t		distance;
	ssize_t		read_bytes;

	str[0] = ft_strdup("");
	if (!str[0])
		return (NULL);
	read_bytes = 1;
	while (str[0] && read_bytes > 0)
	{
		str[1] = str[0];
		distance = memchr_distance(buff[fd], '\n', BUFFER_SIZE);
		if (distance >= 0)
			return (read_line(buff[fd], str, distance));
		str[0] = ft_strjoin(str[1], buff[fd]);
		free(str[1]);
		if (!str[0])
			return (NULL);
		read_bytes = read_fd(fd, buff[fd]);
	}
	if (read_bytes >= 0 && ft_strlen(str[0]))
		return (str[0]);
	free(str[0]);
	return (NULL);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("!%s!\n", line);
// 	close(fd);
// }
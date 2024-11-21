/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:06:28 by mniemaz           #+#    #+#             */
/*   Updated: 2024/11/21 15:18:42 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*extract_line(char *buffer)
{
	int		nl_idx;
	char	*line;

	if (!buffer)
		return (NULL);
	nl_idx = ft_strchr_idx((const char *)buffer, '\n');
	line = ft_strndup(buffer, nl_idx + (nl_idx >= 0));
	return (line);
}

void	rm_line(char *buffer)
{
	int	nl_idx;
	int	i;

	if (!buffer)
		return ;
	nl_idx = ft_strchr_idx(buffer, '\n');
	if (!buffer[nl_idx])
	{
		buffer[0] = '\0';
		return ;
	}
	i = 0;
	while (buffer[nl_idx + i + 1])
	{
		buffer[i] = buffer[nl_idx + i + 1];
		i++;
	}
	buffer[i] = '\0';
}

char	*read_file(char *str, char *buffer, int fd)
{
	ssize_t	bytes_read;
	char	*new_str;

	bytes_read = -1;
	while (ft_strchr_idx(buffer, '\n') == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(str);
			buffer[0] = '\0';
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		new_str = ft_strjoin(str, buffer);
		free(str);
		str = new_str;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*str;
	char		*line;

	str = NULL;
	if (buffer[fd][0] != '\0')
	{
		str = ft_strndup(buffer[fd], -1);
		if (!str)
			return (NULL);
	}
	str = read_file(str, buffer[fd], fd);
	if (!str)
		return (NULL);
	line = extract_line(str);
	rm_line(buffer[fd]);
	free(str);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd;

	// fd = open("./only_nl.txt", O_RDONLY);
	fd = open("./text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	fd = open("./other_text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:17:38 by jhesso            #+#    #+#             */
/*   Updated: 2023/12/30 21:00:53 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

#ifdef BONUS

int[]	open_files(int ac, char **av)
{
	int	i;
	int	fds[ac - 1];

	while (i < ac)
	{
		fds[i] = open(av[i], O_RDONLY);
		i++;
	}
	if (ac < 3)
		fds[1] = STDIN_FILENO;
	return (fds);
}

void	close_fds(int ac, int[] fds)
{
	int	i;

	i = 0;
	while (i < ac)
		close(fds[i++]);
}

void	check_bonus(int ac, char **av)
{
	int		fds[ac - 1];
	char	*s;
	int		i;

	if (ac < 3)
		printf("reading from STDIN as second fd");
	open_files(ac, av);
	i = 0;
	s = get_next_line(fds[i++]);
	printf("%s", s);
	while (s)
	{
		s = get_next_line(fs[i]);
		printf("%s", s);
		i++;
	}
	close_fds(ac, fds);
}
#endif

int	main(int ac, char **av)
{
	int	fd;
	char	*str;

	#ifndef BONUS
		if (ac == 1)
		{
			dprintf(STDERR_FILENO, "Usage: %s <file_to_read>\n", av[0]);
			return (0);
		}
		fd = open(av[1], O_RDONLY);
		printf("reading from %s\n", av[1]);
		str = get_next_line(fd);
		while (str)
		{
			printf("%s", str);
			str = get_next_line(fd);
			if (str)
				free(str);
		}
		close(fd);
		if (str)
			free(str);
	#endif

	#ifdef BONUS
		check_bonus(ac, av);
	#endif

	// system("leaks a.out");
	return (0);
}

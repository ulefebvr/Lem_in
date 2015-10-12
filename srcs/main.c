/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 10:17:05 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/12 14:48:41 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

#include <stdlib.h>

void		ft_exit(t_info *ret)
{
	t_lem	*list;
	t_paths	*paths;

	list = (!ret) ? NULL : ret->list;
	paths = (!ret) ? NULL : ret->paths;
	if (ret->error)
		write(1, "\nERROR\n", 7);
	if (ret != NULL)
		free(ret);
	free_list(list);
	free_paths(paths);
	sleep(10);
}

void		ft_usage(int help)
{
	ft_fdprint(2, "usage : ./Lem-in [-dhq] < map_file\n");
	if (help)
	{
		ft_fdprint(2, "-d   found path with real distance calculated from "
			"coordinates\n");
		ft_fdprint(2, "-q   quiet mode activated\n");
		ft_fdprint(2, "-h   help\n");
	}
}

int			main(int ac, char **av)
{
	t_info	*info;
	int		i;
	int		opt;

	if (((i = ft_option(ac, av, "dhq", &opt)) < 0) || (ac - i) || (opt & OPT_H))
		return (ft_usage(opt & OPT_H ? 1 : 0), 0);
	info = ft_parse(opt);
	info->no_path = 0;
	if (info->no_ant && info->list && (info->paths = get_allpaths(info, NULL)))
	{
		set_prorata_len(info);
		if (!(info->option & OPT_Q))
			ft_print("\n");
		sendtopath(info);
	}
	else
		info->error = 1;
	ft_exit(info);
	return (1);
}

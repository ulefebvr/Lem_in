/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:32:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/30 14:45:09 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

typedef struct				s_lem
{
	int						no;
	char					*name;
	int						ant;
	int						link[128];
	struct s_lem			*next;
}							t_lem;

#endif
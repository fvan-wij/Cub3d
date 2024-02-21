/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:35:52 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/01 14:08:24 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*head;
	t_list	*current;
	void	*ptr;

	head = NULL;
	current = lst;
	while (current)
	{
		ptr = f(current->content);
		temp = ft_lstnew(ptr);
		if (!temp)
		{
			ft_lstclear(&head, del);
			del(ptr);
			return (0);
		}
		ft_lstadd_back(&head, temp);
		current = current->next;
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:02:07 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/10/31 15:21:48 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

// int	main(void)
// {
// 	t_list *head;
// 	head = malloc(sizeof(t_list));
// 	head->content = (void *) 50;
// 	head->next = NULL;
// 	t_list *new_node;
// 	new_node = malloc(sizeof(t_list));
// 	ft_lstadd_back(&head, new_node);
// 	printf("%s", (void *)new_node->content);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:45:00 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/10/31 15:30:16 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

// int	main(void)
// {
// 	t_list *head;
// 	head = (t_list *) malloc(sizeof(t_list));
// 	if (!head)
// 		return (0);
// 	t_list *new_node;
// 	new_node = (t_list *) malloc(sizeof(t_list));
// 	if (!new_node)
// 		return (0);
// 	head->content = (void *) 20;
// 	head->next = new_node;
// 	head->next->content = (void *) 50;
// 	head->next->next = NULL;
// 	printf("\nAmount of nodes = %d\n", ft_lstsize(head));
// }
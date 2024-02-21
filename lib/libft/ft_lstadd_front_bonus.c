/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:22:09 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/10/22 18:22:09 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	char clarence[] = "FRIENDS....";
// 	char friend[] = "Sassy the Sasquatch";
// 	//Linked list
// 	t_list	*head;
// 	head = (t_list *) malloc(sizeof(t_list));
// 	if (!head)
// 		return (0);
// 	head->content = (void *)clarence;
// 	head->next = NULL;
// 	//The new to-be-added linked list
// 	t_list	*new_node;
// 	new_node = (t_list *) malloc(sizeof(t_list));
// 	if (!new_node)
// 		return (0);
// 	new_node->content = (void *)friend;
// 	new_node->next = NULL;
// 	head = ft_lstadd_front(head, new_node);
// 	printf("\n%s\n", new_node->content);
// }
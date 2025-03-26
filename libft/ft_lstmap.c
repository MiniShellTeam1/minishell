/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:07:39 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/16 20:09:02 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_mapped_node(void *(*f)(void *),
									void *content, void (*del)(void *))
{
	void	*new_content;
	t_list	*mapped_node;

	new_content = f(content);
	if (!new_content)
		return (NULL);
	mapped_node = ft_lstnew(new_content);
	if (!mapped_node)
	{
		del(new_content);
		return (NULL);
	}
	return (mapped_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*mapped_node;

	new_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		mapped_node = create_mapped_node(f, lst->content, del);
		if (!mapped_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, mapped_node);
		lst = lst->next;
	}
	return (new_list);
}

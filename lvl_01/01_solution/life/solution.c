/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:47:05 by jquinodo          #+#    #+#             */
/*   Updated: 2025/11/19 12:31:00 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac , char **av)
{
	if(ac != 4)
		return(putchar('e'), 1);

	int width = atoi(av[1]);
	int heigheight = atoi(av[2]);
	int iter = atoi(av[3]);
	int pen = 0;
	int x = 1;
	int y = 1;
	int tab[2][width+2][height+2];

	for(int i = 0 ; i < 2 ; i++)
		for(int h = 0; h < height + 2 ; h++)
			for(int l = 0; l < width + 2 ; l++)
				tab[i][l][h] = 0;
			
	char cmd;
	while(read(0, &cmd, 1) > 0)
	{
		if 		(cmd == 'w' && y > 1 )	y--;
		else if (cmd == 'a' && x > 1)	x--;
		else if (cmd == 's' && y < height)	y++;
		else if (cmd == 'd' && x < width)	x++;
		else if (cmd == 'x' )	 pen = !pen;

		if(pen)
			tab[0][x][y] = 1;
	}

	for(int i = 0 ; i < iter; i++){
		for(int h = 1; h <= height; h++){
			for(int l = 1; l <= width; l++){
				 	int nb = 0;
         
				for(int dy = -1; dy < 2; dy++){
					for(int dx = -1; dx < 2 ; dx++){
						if(dx || dy)
							nb += tab[i % 2][dx + l][dy + h];
					}
				}

				if(tab[i % 2][l][h] == 1)
					if(nb == 2 || nb == 3)
						tab[(i+1)%2][l][h] = 1;
					else
						tab[(i+1)%2][l][h] = 0;
				else
					if (nb == 3)
						tab[(i+1)%2][l][h] = 1;
					else
						tab[(i+1)%2][l][h] = 0;
			}
		}
	}
	for(int h = 1; h <= height; h++){
		for(int l = 1; l <= width; l++){
			putchar(tab[iter % 2][l][h] ? 'O': ' ');
			}
			putchar('\n');
			}
	return 0;
}
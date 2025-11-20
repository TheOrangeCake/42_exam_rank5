/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:52:25 by hoannguy          #+#    #+#             */
/*   Updated: 2025/11/20 12:47:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av) {
    int width = 0;
    int height = 0;
    int iter = 0;
    int pen = 0;
    int x = 1;
    int y = 1;

    if (ac != 4) {
        putchar('e');
        return 1;
    }
    width = atoi(av[1]);
    height = atoi(av[2]);
    iter = atoi(av[3]);
    int tab[2][height + 2][width + 2];

    // initiate the map
    for (int i = 0; i < 2; i++) {
        for (int h = 0; h < height + 2; h++)
            for (int w = 0; w < width + 2; w++)
                tab[i][h][w] = 0;
    }

    // get the command
    char cmd;
    while (read(0, &cmd, 1) > 0) {
        if (cmd == 'w' && y > 1)
            y--;
        else if (cmd == 's' && y < height)
            y++;
        else if (cmd == 'a' && x > 1)
            x--;
        else if (cmd == 'd' && x < width)
            x++;
        else if (cmd == 'x')
            pen = !pen;
        if (pen)
            tab[0][y][x] = 1;
    }

    // iter
    for (int i = 0; i < iter; i++) {
        // reset 
        for (int h = 0; h < height + 2; h++) {
            for (int w = 0; w < width + 2; w++) {
                tab[(i + 1) % 2][h][w] = 0;
            }
        }

        for (int h = 1; h <= height; h++) {
            for (int w = 1; w <= width; w++) {
                int nb = 0;
                // calculate neighbor
                for (int y = -1; y < 2; y++) {
                    for (int x = -1; x < 2; x++) {
                        if (x == 0 && y == 0)
                            continue;
                        nb += tab[i % 2][y + h][x + w];
                    }
                }
                // populate
                if (tab[i % 2][h][w] == 1) {
                    if (nb == 2 || nb == 3)
                        tab[(i + 1) % 2][h][w] = 1;
                    else
                        tab[(i + 1) % 2][h][w] = 0;
                } else {
                    if (nb == 3)
                        tab[(i + 1) % 2][h][w] = 1;
                    else
                        tab[(i + 1) % 2][h][w] = 0;
                }
            }
        }
    }

    // print
    for (int h = 1; h <= height; h++) {
        for (int w = 1; w <= width; w++) {
            if (tab[iter % 2][h][w] == 0)
                putchar(' ');
            else
                putchar('O');
        }
        putchar('\n');
    }
    return 0;
}
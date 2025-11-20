/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:34:36 by hoannguy          #+#    #+#             */
/*   Updated: 2025/11/20 12:34:36 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av) {
    if (ac != 4) {
        putchar('e');
        return 1;
    }

    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iter = atoi(av[3]);
    int y = 1;
    int x = 1;
    int pen = 0;
    int tab[2][height + 2][width + 2];

    for (int i = 0; i < 2; i++) {
        for (int y = 0; y < height + 2; y++) {
            for (int x = 0; x < width + 2; x++) {
                tab[i][y][x] = 0;
            }
        }
    }
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

        if (pen) {
            tab[0][y][x] = 1;
        }
    }

    for (int i = 0; i < iter; i++) {
        for (int h = 0; h < height + 2; h++) {
            for (int w = 0; w < width + 2; w++) {
                tab[(i + 1) % 2][h][w] = 0;
            }
        }
        for (int h = 1; h < height + 1; h++) {
            for (int w = 1; w < width + 1; w++) {
                int nb = 0;
                for (int y = -1; y < 2; y++) {
                    for (int x = -1; x < 2; x++) {
                        if (x == 0 && y == 0)
                            continue;
                        nb += tab[i % 2][y + h][x + w];
                    }
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
    }
    for (int h = 1; h < height + 1; h++) {
        for (int w = 1; w < width + 1; w++) {
            if (tab[iter % 2][h][w] == 1)
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void free_map(char **map, int height) {
    if (map == NULL)
        return;
    for (int y = 0; y < height; y++) {
        free(map[y]);
    }
    free(map);
}

char **init_map(int width, int height) {
    char **map = malloc(sizeof(char*) * height);
    if (map == NULL)
        return NULL;
    for (int y = 0; y < height; y++) {
        map[y] = malloc(sizeof(char) * width);
        if (map[y] == NULL) {
            free_map(map, height);
            return NULL;
      }
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x] = ' ';
        }
    }
    return map;
}

void print_map(char **map, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            putchar(map[y][x]);
        }
        putchar('\n');
    }
}

int neigbors(char **map, int height, int width, int y, int x) {
    int count = 0;
    for (int yi = y - 1; yi <= y + 1; yi++) {
        for (int xi = x - 1; xi <= x + 1; xi++) {
            if (yi == y && xi == x)
                continue;
            if (yi >= 0 && xi >= 0 && yi < height && xi < width) {
                if (map[yi][xi] == 'O')
                    count++;
            }
        }
    }
    return count;
}

void iter_map(char **map, int height, int width) {
    char **temp = init_map(width, height);
    if (temp == NULL)
        return;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int count = neigbors(map, height, width, y, x);
            if (map[y][x] == 'O') {
                if (count == 2 || count == 3)
                    temp[y][x] = 'O';
            } else {
                if (count == 3)
                    temp[y][x] = 'O';
            }
        }
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            map[y][x] = temp[y][x];
    }
    free_map(temp, height);
}

int main(int ac, char **av) {
    if (ac != 4)
        return -1;
    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iter = atoi(av[3]);
    if (width <= 0 || height <= 0 || iter < 0)
        return -1;
    char **map = init_map(width, height);
    if (map == NULL)
        return -1;
    int penX = 0;
    int penY = 0;
    int penDown = 0;
    char command;
    while (read(0, &command, 1) > 0) {
        if (penDown)
            map[penY][penX] = 'O';
        switch(command) {
            case 'w':
                if (penY > 0)
                    penY--;
                continue;
            case 's':
                if (penY < height - 1)
                    penY++;
                continue;
            case 'a':
                if (penX > 0)
                    penX--;
                continue;
            case 'd':
                if (penX < width - 1)
                    penX++;
                continue;
            case 'x':
                penDown = !penDown;
                continue;
        }
    }
    for (int i = 0; i < iter; i++)
        iter_map(map, height, width);
    print_map(map, height, width);
    free_map(map, height);
    return 0;
}
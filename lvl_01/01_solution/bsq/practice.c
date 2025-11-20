#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_map {
	int height;
	int width;
	char full;
	char empty;
	char obstacle;
	char **map;
}	t_map;

int ft_strlen(char *str) {
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

int ft_atoi(char *str) {
	int result = 0;
	int i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9') {
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return result;
}

int minmin(int a, int b, int c) {
	if (a < b && a < c) 
		return a;
	if (b < a && b < c)
		return b;
	if (c < a && c < b)
		return c;
}

void free_all(t_map *map) {
	if (map == NULL)
		return;
	if (map->map == NULL) {
		free(map);
		return;
	}
	for (int i = 0; i < map->height; i++) {
		free(map->map[i]);
	}
	free(map->map);
	free(map);
}

t_map *parse_file(char *file_name) {
	FILE *file;

	if (file_name == NULL)
		file = stdin;
	else
		file = fopen(file_name, "r");
	if (file == NULL)
		return NULL;
	t_map *map = malloc(sizeof(t_map));
	if (map == NULL) {
		if (file_name)
			fclose(file);
		return NULL;
	}

	// parse first line
	char *fline = NULL;
	size_t flen = 0;
	if (getline(&fline, &flen, file) < 0) {
		free(fline);
		free(map);
		if (file_name)
			fclose(file);
		return NULL;
	}
	int len = ft_strlen(fline);
	if (len < 4) {
		free(fline);
		free(map);
		if (file_name)
			fclose(file);
		return NULL;
	}
	if (fline[len - 1] == '\n')
		len -= 1;
	map->full = fline[len - 1];
	map->obstacle = fline[len - 2];
	map->empty = fline[len - 3];
	fline[len - 3] = '\0';
	for (int i = 0; fline[i] != '\0'; i++) {
		if (fline[i] < '0' || fline[i] > '9') {
			free(fline);
			free(map);
			if (file_name)
				fclose(file);
			return NULL;
		}
	}
	map->height = ft_atoi(fline);
	free(fline);

	// parse map
	map->map = malloc(sizeof(char *) * map->height);
	if (map->map == NULL) {
		free_all(map);
		if (file_name)
			fclose(file);
		return NULL;
	}
	for (int i = 0; i < map->height; i++) {
		char* line = NULL;
		if (getline(&line, &flen, file) < 0) {
			free(line);
			free_all(map);
			if (file_name)
				fclose(file);
			return NULL;
		}
		int len = ft_strlen(line);
		if (line[len - 1] == '\n') {
			line[len - 1] = '\0';
			len -= 1;
		}
		if (i == 0)
			map->width = len;
		if (len != map->width) {
			free(line);
			free_all(map);
			if (file_name)
				fclose(file);
			return NULL;
		}
		map->map[i] = line;
	}
	if (file_name)
			fclose(file);
	return map;
}

int validate(t_map *map) {
	if (map->height < 0 || map->width < 0)
		return -1;
	if (map->empty == map->obstacle ||
		map->empty == map->full ||
		map->obstacle == map->full)
		return -1;
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			if (map->map[y][x] != map->empty && map->map[y][x] != map->obstacle)
				return -1;
		}
	}
	return 0;
}

void print(t_map *map) {
	for (int y = 0; y < map->height; y++)
		fprintf(stdout, "%s\n", map->map[y]);
}

void solve(t_map *map) {
	int **temp = malloc(sizeof(int *) * map->height);
	if (temp == NULL)
		return;
	for (int y = 0; y < map->height; y++) {
		temp[y] = malloc(sizeof(int) * map->width);
	}
	int max_size = 0;
	int best_x = 0;
	int best_y = 0;
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			if (map->map[y][x] == map->obstacle)
				temp[y][x] = 0;
			else if (y == 0 || x == 0)
				temp[y][x] = 1;
			else
				temp[y][x] = minmin(temp[y - 1][x], temp[y][x - 1], temp[y - 1][x - 1]) + 1;
			if (temp[y][x] > max_size) {
				max_size = temp[y][x];
				best_x = x;
				best_y = y;
			}
		}
	}
	int start_x = best_x - max_size + 1;
	int start_y = best_y - max_size + 1;
	for (int y = start_y; y < start_y + max_size; y++) {
		for (int x = start_x; x < start_x + max_size; x++) {
			map->map[y][x] = map->full;
		}
	}
	for (int y = 0; y < map->height; y++)
		free(temp[y]);
	free(temp);
}

void start(char *file_name) {
	t_map *map = parse_file(file_name);
	if (map == NULL || validate(map) < 0) {
		free_all(map);
		fprintf(stderr, "map error\n");
		return;
	}
	solve(map);
	print(map);
	free_all(map);
}

int main(int ac, char **av) {
	if (ac == 1)
		start(NULL);
	else {
		for (int i = 1; i < ac; i++)
			start(av[i]);
	}
	return 0;
}
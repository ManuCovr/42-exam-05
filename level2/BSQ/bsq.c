#include "bsq.h"

void destructor(char **map, int size) {
	while (size && (free(*(map + --size)), 1));
	free(map);
}

int parsing(FILE *stream, meta *info) {
	if (fscanf(stream, "%d%c%c%c%c\n", &info->height, &info->empty, &info->obstacle, &info->full, (char *)&info->width) != 5
		|| info->width != 10 || !info->height || !info->empty || !info->obstacle || !info->full
		|| info->empty == info->obstacle || info->empty == info->full || info->obstacle == info->full)
		printf("Error: invalid map\n");
	else errno = EXIT_SUCCESS;
	return errno;
}

int storing(FILE *stream, bsq *data) {
	data->map = malloc(8 * data->info.height);
	if (!data->map) { printf("Error: failure memory allocation\n"); return errno; }
	for (int i = 0; i < data->info.height + 1; i++) {
		char  *line = NULL;
		size_t len  = 0;
		ssize_t r   = getline(&line, &len, stream);
		if (errno) { printf("Error: failure memory allocation\n"); destructor(data->map, i); break; }
		if (r == -1) {
			if (i == data->info.height) break;
			printf("Error: invalid map\n"); destructor(data->map, i); errno = EXIT_FAILURE; break;
		}
		if (line[r - 1] == '\n') line[r - 1] = 0;
		len = 0;
		while (*(line + len) && ++len);
		if ((i && (int)len != data->info.width) || !len) errno = EXIT_FAILURE;
		else data->info.width = len;
		data->map[i] = line;
		while (!errno && *line) {
			if (*line != data->info.empty && *line != data->info.obstacle) errno = EXIT_FAILURE;
			++line;
		}
		if (errno) { destructor(data->map, i + 1); printf("Error: invalid map\n"); break; }
	}
	return errno;
}

int minimoon(int a, int b, int c) {
	if (!a || !b || !c) return 1;
	if (a > b) a = b;
	if (a > c) a = c;
	return a + 1;
}

void selectSquire(bsq data) {
	for (int i = 0; i < data.info.height; i++)
		for (int j = 0; j < data.info.width; j++)
			if (data.solve.db[i][j] == 1) {
				if (i && j) data.solve.db[i][j] = minimoon(data.solve.db[i-1][j], data.solve.db[i-1][j-1], data.solve.db[i][j-1]);
				if (data.solve.size < data.solve.db[i][j]) {
					data.solve.size = data.solve.db[i][j];
					data.solve.i = i - data.solve.size + 1;
					data.solve.j = j - data.solve.size + 1;
				}
			}
	for (int i = data.solve.i; i < data.solve.i + data.solve.size; i++)
		for (int j = data.solve.j; j < data.solve.j + data.solve.size; j++)
			data.map[i][j] = data.info.full;
	for (int i = 0; i < data.info.height; i++) printf("%s\n", data.map[i]);
}

int duplicate(bsq *data) {
	data->solve.db = malloc(8 * data->info.height);
	if (!data->solve.db) { printf("Error: failure memory allocation\n"); return errno; }
	for (int i = 0; i < data->info.height; i++) {
		data->solve.db[i] = malloc(4 * data->info.width);
		if (!data->solve.db[i]) { destructor((char **)data->solve.db, i); printf("Error: failure memory allocation\n"); errno = EXIT_FAILURE; break; }
		for (int j = 0; j < data->info.width; j++)
			data->solve.db[i][j] = data->map[i][j] != data->info.obstacle;
	}
	return errno;
}

void biggest_square(FILE *stream) {
	bsq data = {0};
	if (parsing(stream, &data.info) || storing(stream, &data)) return;
	if (!duplicate(&data)) { selectSquire(data); destructor((char **)data.solve.db, data.info.height); }
	destructor(data.map, data.info.height);
}

int main(int argc, char **argv) {
	errno = EXIT_FAILURE;
	if (argc == 1) biggest_square(stdin);
	else if (argc == 2) {
		FILE *stream = fopen(*++argv, "r");
		if (stream) { biggest_square(stream); fclose(stream); }
		else printf("Error: cannot open file %s\n", *argv);
	}
	else printf("Error: too many arguments\n");
	return errno;
}

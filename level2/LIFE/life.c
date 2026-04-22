#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 4) return 1;
	int w = atoi(argv[1]), h = atoi(argv[2]), it = atoi(argv[3]);
	if (w <= 0 || h <= 0 || it < 0) return 1;
	int grid[2][h + 2][w + 2];
	for (int i = 0; i < 2; i++)
		for (int y = 0; y < h + 2; y++)
			for (int x = 0; x < w + 2; x++) grid[i][y][x] = 0;
	int py = 1, px = 1, pen = 0;
	char cmd;
	while (read(0, &cmd, 1) > 0) {
		if      (cmd == 'x')           pen = !pen;
		else if (cmd == 'w' && px > 1) px--;
		else if (cmd == 'a' && py > 1) py--;
		else if (cmd == 's' && px < h) px++;
		else if (cmd == 'd' && py < w) py++;
		if (pen) grid[0][px][py] = 1;
	}
	for (int i = 0; i < it; i++)
		for (int y = 1; y <= h; y++)
			for (int x = 1; x <= w; x++) {
				int nb = 0;
				for (int dy = -1; dy <= 1; dy++)
					for (int dx = -1; dx <= 1; dx++)
						if (dy || dx) nb += grid[i % 2][y + dy][x + dx];
				grid[(i + 1) % 2][y][x] = ((nb == 2 || nb == 3) && grid[i % 2][y][x]) || nb == 3;
			}
	for (int y = 1; y <= h; y++) {
		for (int x = 1; x <= w; x++) putchar(grid[it % 2][y][x] ? 'O' : ' ');
		putchar('\n');
	}
	return 0;
}

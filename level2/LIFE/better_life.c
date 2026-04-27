#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 4)
		return 1;

	int cols = atoi(argv[1]);
	int rows = atoi(argv[2]);
	int iterations = atoi(argv[3]);

	if (cols <= 0 || rows <= 0 || iterations < 0)
		return 1;

	int grid[2][rows + 2][cols + 2];

	for (int buf = 0; buf < 2; buf++)
		for (int r = 0; r < rows + 2; r++)
			for (int c = 0; c < cols + 2; c++)
				grid[buf][r][c] = 0;

	int pen_row = 1;
	int pen_col = 1;
	int drawing = 0;
	char cmd;

	while (read(0, &cmd, 1) > 0)
	{
		if      (cmd == 'x')                    drawing = !drawing;
		else if (cmd == 'w' && pen_row > 1)     pen_row--;
		else if (cmd == 'a' && pen_col > 1)     pen_col--;
		else if (cmd == 's' && pen_row < rows)  pen_row++;
		else if (cmd == 'd' && pen_col < cols)  pen_col++;

		if (drawing)
			grid[0][pen_row][pen_col] = 1;
	}

	for (int step = 0; step < iterations; step++)
	{
		int cur  = step % 2;
		int next = (step + 1) % 2;

		for (int r = 1; r <= rows; r++)
		{
			for (int c = 1; c <= cols; c++)
			{
				int nb = 0;
				for (int dr = -1; dr <= 1; dr++)
					for (int dc = -1; dc <= 1; dc++)
						if (dr || dc)
							nb += grid[cur][r + dr][c + dc];

				int alive_now = grid[cur][r][c];
				grid[next][r][c] = (alive_now && (nb == 2 || nb == 3))
				                   || (!alive_now && nb == 3);
			}
		}
	}

	int final_buf = iterations % 2;
	for (int r = 1; r <= rows; r++)
	{
		for (int c = 1; c <= cols; c++)
			putchar(grid[final_buf][r][c] ? 'O' : ' ');
		putchar('\n');
	}

	return 0;
}

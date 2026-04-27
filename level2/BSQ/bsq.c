#include "bsq.h"

void	free_map(char **map, int rows)
{
	while (rows > 0)
		free(map[--rows]);
	free(map);
}

void	free_dp(int **dp, int rows)
{
	while (rows > 0)
		free(dp[--rows]);
	free(dp);
}

int	error(const char *msg)
{
	printf("%s\n", msg);
	return (0);
}

int	parse_header(FILE *stream, t_map *m)
{
	char	nl;

	if (fscanf(stream, "%d%c%c%c%c",
		&m->rows, &m->empty, &m->obstacle, &m->full, &nl) != 5
		|| nl != '\n' || m->rows <= 0
		|| m->empty == m->obstacle
		|| m->empty == m->full
		|| m->obstacle == m->full)
		return error("Error: invalid map");
	return (1);
}

int	read_map(FILE *stream, t_map *m)
{
	m->grid = malloc(sizeof(char *) * m->rows);
	if (!m->grid)
		return error("Error: malloc failure");
	m->cols = 0;
	for (int i = 0; i < m->rows; i++)
	{
		char	*line = NULL;
		size_t	cap   = 0;
		ssize_t	len   = getline(&line, &cap, stream);

		if (len > 0 && line[len - 1] == '\n')
			line[--len] = '\0';
		if (len <= 0 || (m->cols > 0 && (int)len != m->cols))
		{
			free(line);
			free_map(m->grid, i);
			return error("Error: invalid map");
		}
		m->cols = (int)len;
		for (int j = 0; j < (int)len; j++)
		{
			if (line[j] != m->empty && line[j] != m->obstacle)
			{
				free(line);
				free_map(m->grid, i);
				return error("Error: invalid map");
			}
		}
		m->grid[i] = line;
	}
	return (1);
}

int	min3(int a, int b, int c)
{
	if (a > b) a = b;
	if (a > c) a = c;
	return (a);
}

void	solve(t_map *m)
{
	int	**dp = malloc(sizeof(int *) * m->rows);
	if (!dp) { error("Error: malloc failure"); return ; }
	for (int i = 0; i < m->rows; i++)
	{
		if (!(dp[i] = malloc(sizeof(int) * m->cols)))
		{
			free_dp(dp, i);
			error("Error: malloc failure");
			return ;
		}
		for (int j = 0; j < m->cols; j++)
			dp[i][j] = (m->grid[i][j] != m->obstacle);
	}

	int	best = 0, br = 0, bc = 0;
	for (int i = 0; i < m->rows; i++)
		for (int j = 0; j < m->cols; j++)
		{
			if (dp[i][j] && i > 0 && j > 0)
				dp[i][j] = min3(dp[i-1][j], dp[i-1][j-1], dp[i][j-1]) + 1;
			if (dp[i][j] > best)
			{
				best = dp[i][j];
				br = i - best + 1;
				bc = j - best + 1;
			}
		}
	free_dp(dp, m->rows);

	for (int i = br; i < br + best; i++)
		for (int j = bc; j < bc + best; j++)
			m->grid[i][j] = m->full;
	for (int i = 0; i < m->rows; i++)
		printf("%s\n", m->grid[i]);
}

void	run(FILE *stream)
{
	t_map	m = {0};

	if (!parse_header(stream, &m) || !read_map(stream, &m))
		return ;
	solve(&m);
	free_map(m.grid, m.rows);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		run(stdin);
	else if (argc == 2)
	{
		FILE	*f = fopen(argv[1], "r");
		if (!f)
		{
			printf("Error: cannot open file %s\n", argv[1]);
			return (1);
		}
		run(f);
		fclose(f);
	}
	else
		printf("Error: too many arguments\n");
	return (0);
}
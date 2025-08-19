#include "bsq.h"

typedef struct s_info{
    int width, line;
    char full, empty, obstacle;
    char **map;
    FILE *file;
} t_info;

void ft_free_map(char **map)
{
    for(int i = 0; map[i]; i++)
    {
        free (map[i]);
    }
    free(map);
}

void ft_free_tab(int **tab, int row)
{
    for(int i = 0; i < row; i++)
    {
        free (tab[i]);
    }
    free(tab);
}

t_info *ft_read_map(char *map_name)
{
    t_info *Map = malloc(sizeof(t_info));
    Map->file = fopen(map_name, "r");
    if (!Map->file)
        return NULL;
    if(fscanf(Map->file, "%d %c %c %c\n", &Map->line, &Map->empty, &Map->obstacle, &Map->full) != 4)
    {
        fprintf(stderr, "map error\n");
        free (Map);
        if (Map->file)
            fclose(Map->file);
        return NULL;
    }
    Map->map =  malloc((Map->line + 1) * sizeof(char *));
    int i = 0;
    for (i; i < Map->line ; i++)
    {
        size_t len = 0;
        char *line = NULL;
        if (getline(&line, &len, Map->file) == -1)
        {
            ft_free_map(Map->map);
            free(Map);
            if (Map->file)
                fclose(Map->file);
            //peut etre free map ici
            return NULL;
        }
        int len_line = strlen(line);
        if (line[len_line - 1] == '\n')
            line[len_line - 1] = '\0';
        Map->width = strlen(line);
        Map->map[i] = line;
    }
    Map->map[i] = NULL;
    return Map;
}

t_info *ft_read_map_terminal()
{
    t_info *Map = malloc(sizeof(t_info));
    Map->file = stdin;
    if (!Map->file)
        return NULL;
    if(fscanf(Map->file, "%d %c %c %c\n", &Map->line, &Map->empty, &Map->obstacle, &Map->full) != 4)
    {
        fprintf(stderr, "map error\n");
        free (Map);
        return NULL;
    }
    Map->map =  malloc((Map->line + 1) * sizeof(char *));
    int i = 0;
    for (i; i < Map->line ; i++)
    {
        size_t len = 0;
        char *line = NULL;
        if (getline(&line, &len, Map->file) == -1)
        {
            ft_free_map(Map->map);
            free(Map);
            return NULL;
        }
        int len_line = strlen(line);
        if (line[len_line - 1] == '\n')
            line[len_line - 1] = '\0';
        Map->width = strlen(line);
        Map->map[i] = line;
    }
    Map->map[i] = NULL;
    return Map;
}

int ft_map_valid(t_info *map)
{
    if (!map || map->line <= 0 || map->width <= 0)
        return 1;
    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full)
        return 1;
    for (int i = 0; i < map->line ; i++)
    {
        if(strlen(map->map[i]) != map->width)
            return 1;
        for (int j = 0; j < map->width ; j++)
        {
            if (map->map[i][j] != map->empty && map->map[i][j] != map->obstacle)
                return 1;
        }
    }
    return 0;
    
}

void ft_print_map(t_info *map, int best, int best_i, int best_j)
{
    for (int i = 0; i < map->line; i++)
    {
        for (int j = 0; j < map->width ; j++)
        {
            if (i > best_i - best && i <= best_i && j > best_j - best && j <= best_j)
                printf("%c", map->full);
            else
                printf("%c", map->map[i][j]);
        }
        printf("\n");
    }
}
int ft_min3(int a, int b, int c)
{
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}
void ft_bsq(t_info *map)
{
    int **tab = malloc(map->line * sizeof(int *));
    for (int i = 0; i < map->line ; i++)
        tab[i] = calloc(map->width, sizeof(int));
    int best = 0, best_i = 0, best_j = 0;
    for (int i = 0; i < map->line ; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if (map->map[i][j] == map->obstacle)
                tab[i][j] = 0;
            else if (i == 0 || j == 0)
                tab[i][j] = 1;
            else
                tab[i][j] = ft_min3(tab[i - 1][j], tab[i][j - 1], tab[i - 1][j - 1]) + 1;
            if (tab[i][j] > best)
            {
                best = tab[i][j];
                best_i = i;
                best_j = j;
            }
        }

    }
    ft_print_map(map, best, best_i, best_j);
    ft_free_tab(tab, map->line);
}

int main(int ac, char **av)
{
    if (ac > 1)
        for (int i = 1; i < ac ; i++)
        {
            t_info *Map;
            Map = ft_read_map(av[i]);
            if (ft_map_valid(Map))
            {
                if (Map->file)
                    fclose(Map->file);
                ft_free_map(Map->map);
                free (Map);
                fprintf(stderr, "map error\n");
                continue;
            }
            ft_bsq(Map);
            if (Map->file)
                    fclose(Map->file);
            ft_free_map(Map->map);
            free (Map);
        }
    else
    {
        t_info *Map;
        Map = ft_read_map_terminal();
        if (ft_map_valid(Map))
        {
            ft_free_map(Map->map);
            free (Map);
            fprintf(stderr, "map error\n");
        }
        else
        {
            ft_bsq(Map);
            ft_free_map(Map->map);
            free (Map);
        }
    }
}
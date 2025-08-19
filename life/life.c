#include "life.h"

typedef struct s_info
{
    int height, width, iteration;
    int **map;
}t_info;

void ft_free_tab(int **tab, int row)
{
    for (int i = 0; i < row + 2; i++)
    {
        free (tab[i]);
    }
    free (tab);
}

void ft_read(t_info *game)
{
    char c;
        int i = 1, j = 1;
        int pen_status = 0; //stylo leve au debut
        while (read(0, &c, 1) > 0)
        {
            if (c == 'x')
               pen_status = !pen_status;
            else if (c == 'w' && i > 1)
                i--;    
            else if (c == 'a' && j > 1)
                j--;
            else if (c == 's' && i < game->height)
                i++;
            else if (c == 'd' && j < game->width)
                j++;
            else    
                continue;
            if (pen_status && i > 1 && j > 1 && i < game->height && j < game->width)
                game->map[i][j] = 1;
        }
}

int ft_count(t_info *game, int i, int dj)
{
    int count = 0;
    int j;
    for (j = dj - 1; j <= dj + 1; j++) //ca compte haut et bas
    {
        if (game->map[i - 1][j] == 1)
            count++;
        if (game->map[i + 1][j] == 1)
            count++;
    }
    if (game->map[i][dj - 1] == 1) // gauche
        count++;
    if (game->map[i][dj + 1] == 1) //droite
        count++;
    return count;
}

int **ft_life(t_info *game)
{
    int **new_map = malloc((game->height + 2)* sizeof(int *));
    for (int i = 0; i < game->height + 2; i++)
    {
        new_map[i] = calloc((game->width + 2), sizeof(int));
    }
    for (int i = 1; i <= game->height; i++)
    {
        for (int j = 1; j <= game->width; j++)
        {
           int numb_cell = ft_count(game, i, j);
           if(game->map[i][j] == 1)
           {
                if (numb_cell == 2 || numb_cell == 3)
                    new_map[i][j] = 1;
                else
                    new_map[i][j] = 0;
           }
           else
           {
                if (numb_cell == 3)
                    new_map[i][j] = 1;
           }
        }
    }
    ft_free_tab(game->map, game->height);
    game->map = new_map;
}

void ft_print_grid(t_info *game)
{
    for (int i = 1; i <= game->height; i++)
    {
        for (int j = 1; j <= game->width; j++)
        {
            if (game->map[i][j] == 0)
                putchar(' ');
            else if (game->map[i][j] == 1)
                putchar('0');
        }
        putchar('\n');
    }
}
int main(int ac, char **av)
{
    t_info *game;
    game = malloc(sizeof(t_info));
    if (ac == 4)
    {
        game->width = atoi(av[1]);
        game->height = atoi(av[2]);
        game->iteration = atoi(av[3]);
        game->map = malloc((game->height + 2)* sizeof(int *));
        for (int i = 0; i < game->height + 2; i++)
        {
            game->map[i] = calloc((game->width + 2), sizeof(int));
        }
        ft_read(game);
        ft_print_grid(game);
        for (int i = 0; i < game->iteration; i++)
        {            
            // printf("----------------------------------\n"); //a supprimer surement au vu de comment on veut l affichage a l examen 
            usleep(1000000);
            printf("\033[H\033[J");
            printf("generation n°%d\n", i);
            ft_life(game);
            ft_print_grid(game);
        }
        ft_free_tab(game->map, game->height);
        free(game);
    }
    else
    {
        return 1;
    }
}
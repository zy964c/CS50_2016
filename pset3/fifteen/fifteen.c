/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// move number
bool moved = true;

// blank space position
int blank[] = {0, 0};

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    int pos = (d * d) - 1;
    int i, j;
    for(i = 0; i < d; i++)
    {
        for(j = 0; j < d; j++)
        {
            board[i][j] = pos;
            pos -= 1;
        }
    }
    if(((d * d) % 2) == 0)
    {
        for(int k = 0; k < d; k++)
        {
            for(int l = 0; l < d; l++)
            {
                if(board[k][l] == 2)
                {
                    board[k][l] = 1;
                    board[k][l + 1] = 2;
                    break;
                }
            }
        }
        
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    int i, j;
    for(i = 0; i < d; i++)
    {
        for(j = 0; j < d; j++)
        {
            if(board[i][j] == 0)
            {
                printf(" _ ");
            }
            else
            {
                printf("%2d ", board[i][j]);
            }
            if(j == (d - 1))
            {
                printf("\n");
            }
        }
    }       
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    if(moved == true)
    {
        blank[0] = d - 1;
        blank[1] = d - 1;
        moved = false;
    }
    int i, j;
    if(tile > 0 && tile < (d * d))
    {
        for(i = 0; i < d; i++)
        {
            for(j = 0; j < d; j++)
            {
                if(board[i][j] == tile)
                {
                    if(blank[0] == i)
                    {
                        if(blank[1] == j || blank[1] == (j + 1) || blank[1] == (j - 1))
                        {
                            board[blank[0]][blank[1]] = tile;
                            board[i][j] = 0;
                            blank[0] = i;
                            blank[1] = j;
                            return true;
                        }   
                    }
                    else if(blank[0] == (i + 1) || blank[0] == (i - 1))
                    {
                        if(blank[1] == j)
                        {
                            board[blank[0]][blank[1]] = tile;
                            board[i][j] = 0;
                            blank[0] = i;
                            blank[1] = j;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int i, j;
    int prev = 0;
    for(i = 0; i < d; i++)
        {
            for(j = 0; j < d; j++)
            {
                if(board[i][j] == 0 && prev == ((d * d) - 1))
                {
                    return true;
                }
                else if((board[i][j] - 1) == prev)
                {
                    prev += 1;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
    return false;
}
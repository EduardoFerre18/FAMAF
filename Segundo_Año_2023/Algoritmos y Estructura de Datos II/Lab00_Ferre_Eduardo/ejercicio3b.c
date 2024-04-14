#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define CELL_MAX (5 * 5 - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[5][5])
{
    int cell = 0;

    print_sep(5);
    for (int row = 0; row < 5; ++row) {
        for (int column = 0; column < 5; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(5);
    }
}

char get_winner_row(char board[5][5], unsigned int row)
{

    char winner = board[row][0];

    for (unsigned int column = 0; (column < 5) && (winner != '-'); column++)
    {
        if (winner != board[row][column])
        {
            winner = '-';
        }

    }

    return winner;
}

char get_winner_column(char board[5][5], unsigned int column)
{

    char winner = board[0][column];

    for (unsigned int row = 0; (row < 5) && (winner != '-'); row++)
    {
        if (winner != board[row][column])
        {
            winner = '-';
        }

    }

    return winner;
}

char get_winner_1diagonal(char board[5][5])
{

    char winner = board[0][0];

    for (unsigned int j = 0; (j < 5) && (winner != '-'); j++)
    {
        if (winner != board[j][j])
        {
            winner = '-';
        }

    }

    return winner;
}

char get_winner_2diagonal(char board[5][5])
{

    char winner = board[4][0];

    for (unsigned int j = 0; (j < 5) && (winner != '-'); j++)
    {
        if (winner != board[4-j][j])
        {
            winner = '-';
        }

    }

    return winner;
}



char get_winner(char board[5][5])
{
    
    char winner = get_winner_1diagonal(board);

    if (winner == '-')
    {
        winner = get_winner_2diagonal(board);

    }

    for (unsigned int j = 0; j < 5 && winner == '-'; j++)
    {
        winner = get_winner_row (board, j);
        
        if (winner == '-')
        {
            winner = get_winner_column(board, j);
        }
    }

    return winner;
} 

bool has_free_cell(char board[5][5])
{
    bool free_cell=false;
    int i;
    int j;
    //
    // TODO: COMPLETAR
    //
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
        
            if (board[i][j] == '-') {
                
                return true;
                
            }
                        
        }
                        
    }
    
    
    
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[5][5] = {
        { '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / 5;
            int colum = cell % 5;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Gana %c\n", winner);
    }
    return 0;
}
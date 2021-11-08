/* This is for the isWonRow function which returns whether or not a game
 * of tic-tac-toe has been won by the given player and in a row, if the
 * game has been won, the funciton returns 1 and if not, returns 0
 */

 #include <stdio.h>

int isWonRow(char player, char game[3][3], int rowNum)
{
    int won = 1;
    for (int i = 0; i < 3; i++) {
        if (game[rowNum][i] != player) {
            won = 0;
        }
    }
    return won;

}

int main(void)
{
    char game[3][3] = {{'X', 'O', ' '},{'X', 'X', 'X'}, {' ', ' ', ' '}};
    printf("%d\n", isWonRow('X', game, 1));

    char game2[3][3] = {{'X', 'O', ' '},{' ', ' ', ' '}, {'X', 'X', 'O'}};
    printf("%d\n", isWonRow('X', game2, 2));
}

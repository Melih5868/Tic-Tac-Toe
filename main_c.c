#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
// Global Değişkenler
char board[3][3];
const char player = 'X';
const char computer = 'O';

void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard()
{
    // Windows için ekranı temizler (Linux/Mac için 'clear' yapabilirsin)
    system("cls");
     printf("\n --- XOX OYUNU ---\n\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}
int checkFreeSpaces()
{
    int freeSpace = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpace--;
            }
        }
    }
    return freeSpace;
}
void playerMove()
{
    int x, y;
    do
    {

        printf("Satir giriniz (1-3):");
        scanf("%d", &x);
        x--;// Kullanıcı 1 girecek, biz 0. indexe çevireceğiz

        printf("Sutun giriniz (1-3):");
        scanf("%d", &y);
        y--;
         // Dizi sinirlari kontrolu eklendi
        if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ')
        {
            printf("Gecersiz hamle! Tekrar dene.\n");
        }
        else
        {
            board[x][y] = player;
            break;
        }

    } while (1);
}
void computermove()
{
  // Rastgele hamle yapma mantığı
    
    int x, y;
    if (checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = computer;
    }
}
char checkWinner()
{
    // Satırları kontrol et
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    // Sütunları kontrol et
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }
    // Çaprazları kontrol et
    if (board[0][0]!=' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }
    return ' ';
}
void printWinner(char winner)
{
    if (winner == player)
    {
        printf("TEBRIKLER! KAZANDIN!\n");
    }
    else if (winner == computer)
        printf("UZGUNUM, KAYBETTIN.\n");
    else
        printf("BERABERE!\n");
}

int main()
{
   srand(time(0));
    char winner = ' ';
    char again = ' ';
    
    do
    {
        winner = ' ';
        again = ' ';
        resetBoard();
        while (winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();
            // Oyuncu Hamlesi
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
            // Bilgisayar Hamlesi
            computermove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
            printBoard();
            
        }
         printWinner(winner);
        printf("Tekrar oynamak istermisin? (E/H)");

        scanf(" %c", &again);
        again = toupper(again);

    } while (again == 'E');
  
    printf("Oynadigin icin tesekkurler");

   
    return 0;
}

#include <stdio.h> 
#include <stdbool.h>

bool isFirstPlayerTurn = true;

bool isFinish(char field[3][3], bool endFlag)
{
    for (int i = 0; i < 3; i++) {
        if ((field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][0] != '.') ||
            (field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[0][i] != '.') ||
            (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] != '.') ||
            (field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[0][2] != '.')) {
            if (endFlag != true) {
                printf("\nFIRST player win!\n");
            }
            else {
                printf("\nSECOND player win!\n");
            }
            return true;
        }
    }

    int drawScore = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] != '.') {
                drawScore++;
            }
        }
    }

    if (drawScore > 8) {
        printf("\nDRAW!\n");
        return true;
    }

    return false;
}

void reloadField(char field[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            field[i][j] = '.';
        }
    }
}

void printField(char field[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", field[i][j]);
        }
        printf("\n");
    }
}

void turn(char field[3][3], bool firstPlayerFlag)
{
    char playerChar;

    if (firstPlayerFlag == true) {
        printf("\nFIRST player turn.\n");
        isFirstPlayerTurn = !isFirstPlayerTurn;
        playerChar = 'X';
    } 
    else {
        printf("\nSECOND player turn.\n");
        isFirstPlayerTurn = !isFirstPlayerTurn;
        playerChar = 'O';
    }

    do {
        int row = 0;
        int column = 3;

        int index = scanInput();
        while (index > 3)
        {
            row += 1;
            index -= 3;
        }
        column = index;

        if (field[row][column] == '.') {
            field[row][column] = playerChar;
            break;
        }
        else {
            printf("\nCell is occupied! Try again.\n\n");
        }
    } while (1);
    printField(field);
}

int scanInput()
{
    int index;

    do {
        printf("Enter index of selected cell(0..8) : ");
        if (scanf_s("%d", &index) != 1 || index < 0 || index > 8) {
            printf("Index error! Try again:\n");
            while (getchar() != '\n');
        }
        else {
            return index;
        }
    } while (1);
}

int main(void)
{
    char field[3][3];
    printf("Press any key to start:");
    getchar();

    reloadField(field);
    printField(field);

    bool finish = false;
    while (finish != true) {
        turn(field, isFirstPlayerTurn);
        finish = isFinish(field, isFirstPlayerTurn);
    }

    return 0;
}

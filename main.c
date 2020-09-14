#include <stdio.h>
#include <stdlib.h>
/*Takes a 9x9 Sudoku Puzzle and prints the answer*/
/*By Ryan Ling 13/7/2020*/
/*Note that copy board does not actually get changed (only the first coord) in the final parsing function because of recursion where the first function will change only the first value of the checking board.*/

void everything_one(int board[9][9], int rcoord[], int ccoord[], int num); /*Don't actually need this*/
void print_board(int board[9][9]);
int num_given_coord(int board[9][9]);
void record_given_coord(int *r, int *c, int board[9][9]);
int checkifgiven_num(int r, int c, int rcoord[], int ccoord[], int num);
int check_square(int r, int c, int board[9][9]);
int check_row(int board[9][9], int r, int c);
int check_column(int board[9][9], int r, int c);
int final_parsing_check(int board[9][9], int row, int column, int given_row_coord[], int given_column_coordinate[], int num);

int main()
{   /*n is the number of provided coordinates*/
    int sudoku_board[9][9] = {0}, r, c, digit = getchar(), *given_row_coord, *given_col_coord, n, check_given, confirm_num, checking_board[9][9];
    /*To get the board*/
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            while (digit == ' ' || digit == '\n') {
                digit = getchar();
            }

            digit = digit - '0';
            sudoku_board[r][c] = digit;
            digit = getchar();

        }
        printf("\n");
    }

    printf("\nThis is the puzzle:\n");
    print_board(sudoku_board);

    n = num_given_coord(sudoku_board);

    given_row_coord = (int*)malloc(n * sizeof(int));
    given_col_coord = (int*)malloc(n * sizeof(int));


    record_given_coord(given_row_coord, given_col_coord, sudoku_board);


    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            checking_board[r][c] = sudoku_board[r][c];
        }
    }

    printf("\nThis is the solution:\n");
    final_parsing_check(checking_board, 0, 0, given_row_coord, given_col_coord, n);


    free(given_row_coord);
    free(given_col_coord);

    return 0;
}

void print_board(int board[9][9]) {
    int r, c;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            printf("%d ", board[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void everything_one(int board[9][9], int rcoord[], int ccoord[], int num) {
    int r, c, check;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            check = checkifgiven_num(r, c, rcoord, ccoord, num);
            if (check == 0) {
                board[r][c] = 1;
            }
        }
    }
}

int num_given_coord(int board[9][9]) {
    int r, c, count = 0;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            if (board[r][c] != 0) {
                count += 1;
            }
        }
    }
    return count;
}

void record_given_coord(int *r, int *c, int board[9][9]) {
    int row, column, i = 0;
    for (row = 0; row < 9; row++) {
        for (column = 0; column < 9; column++) {
            if (board[row][column] != 0) {
                r[i] = row;
                c[i] = column;
                i += 1; /*The given coordinates of the given values are recorded into variables given_row_coord/column in 2 corresponding arrays*/
            }
        }
    }

}

int checkifgiven_num(int r, int c, int rcoord[], int ccoord[], int num) { /*here we need to input the current position (r and c), along with the arrays we have recorded the given coordinates in, which is given_row/column_coord)*/
    int i = 0;
    for (i = 0; i < num; i++) {
        if (rcoord[i] == r && ccoord[i] == c) { /*if the current coordinate equals to the stored coordinate (in the 2 corresponding arrays) it means the current position is a given position, and will return 1*/
            return 1; /*1 if it is given, 0 if it is not*/
        }
    }
    return 0;
}

int check_square(int r, int c, int board[9][9]) {
    int row, column, array[9] = {0}, i = 0, test = 0, count = -1, b;

    /*square 1*/
    if (r >= 0 && r <= 2 && c >= 0 && c <= 2) {
        for (row = 0; row <= r; row++) { /*This is to convert the 2D matrix coordinate into a number from 1-9*/
            if (row == r) {
                for (column = 0; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 0; column <= 2; column++) {
                    count += 1;
                }
            }
        }
        for (row = 0; row <= 2; row++) { /*This is to make an array of the existing numbers*/
            for (column = 0; column <= 2; column++) {
                 if (i != count) { /*This leaves the current number blank so that it only compares with the other 8 no.s*/
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) { /*This indicates whether there already is another value inside*/
            if (array[b] == board[r][c]) {
                return 1; /*If there are is already a value inside, this function will return 1*/
            }
        }
    }

    /*square 2*/
    else if (r >= 0 && r <= 2 && c >= 3 && c <= 5) {
        for (row = 0; row <= r; row++) {
            if (row == r) {
                for (column = 3; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 3; column <= 5; column++) {
                    count += 1;
                }
            }
        }
        for (row = 0; row <= 2; row++) {
            for (column = 3; column <= 5; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }


    /*square 3*/
    else if (r >= 0 && r <= 2 && c >= 6 && c <= 8) {
        for (row = 0; row <= r; row++) {
            if (row == r) {
                for (column = 6; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 6; column <= 8; column++) {
                    count += 1;
                }
            }
        }
        for (row = 0; row <= 2; row++) {
            for (column = 6; column <= 8; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }


    /*square 4*/
    else if (r >= 3 && r <= 5 && c >= 0 && c <= 2) {
        for (row = 3; row <= r; row++) {
            if (row == r) {
                for (column = 0; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 0; column <= 2; column++) {
                    count += 1;
                }
            }
        }
        for (row = 3; row <= 5; row++) {
            for (column = 0; column <= 2; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }


    /*square 5*/
    else if (r >= 3 && r <= 5 && c >= 3 && c <= 5) {
        for (row = 3; row <= r; row++) {
            if (row == r) {
                for (column = 3; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 3; column <= 5; column++) {
                    count += 1;
                }
            }
        }
        for (row = 3; row <= 5; row++) {
            for (column = 3; column <= 5; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }


    /*square 6*/
    else if (r >= 3 && r <= 5 && c >= 6 && c <= 8) {
        for (row = 3; row <= r; row++) {
            if (row == r) {
                for (column = 6; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 6; column <= 8; column++) {
                    count += 1;
                }
            }
        }
        for (row = 3; row <= 5; row++) {
            for (column = 6; column <= 8; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }


    /*square 7*/
    else if (r >= 6 && r <= 8 && c >= 0 && c <= 2) {
        for (row = 6; row <= r; row++) {
            if (row == r) {
                for (column = 0; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 0; column <= 2; column++) {
                    count += 1;
                }
            }
        }
        for (row = 6; row <= 8; row++) {
            for (column = 0; column <= 2; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }


    /*square 8*/
    else if (r >= 6 && r <= 8 && c >= 3 && c <= 5) {
        for (row = 6; row <= r; row++) {
            if (row == r) {
                for (column = 3; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 3; column <= 5; column++) {
                    count += 1;
                }
            }
        }
        for (row = 6; row <= 8; row++) {
            for (column = 3; column <= 5; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }


    /*square 9*/
    else if (r >= 6 && r <= 8 && c >= 6 && c <= 8) {
        for (row = 6; row <= r; row++) {
            if (row == r) {
                for (column = 6; column <= c; column ++) {
                    count += 1;
                }
            }
            else {
                for (column = 6; column <= 8; column++) {
                    count += 1;
                }
            }
        }
        for (row = 6; row <= 8; row++) {
            for (column = 6; column <= 8; column++) {
                 if (i != count) {
                    array[i] = board[row][column];
                }
                i += 1;
                }
            }

        for (b = 0; b < 9; b++) {
            if (array[b] == board[r][c]) {
                return 1;
            }
        }
    }

  return 0;
}

int check_row(int board[9][9], int r, int c) {
    int array[9] = {0}, i; /*Checks horizontal rows*/
    for (i = 0; i < 9; i++) { /*creates an array containing all other values in row excluding current*/
        if (i != c) {
            array[i] = board[r][i];
        }
    }
    /*printf("\n");
    for (i = 0; i < 9; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");*/
    for (i = 0; i < 9; i++) {
        if (array[i] == board[r][c]) {
            return 1;
        }
    }
    return 0;
}

int check_column(int board[9][9], int r, int c) {
    int array[9] = {0}, i; /*Checks horizontal rows*/
    for (i = 0; i < 9; i++) { /*creates an array containing all other values in row excluding current*/
        if (i != r) {
            array[i] = board[i][c];
        }
    }
    /*printf("\n");
    for (i = 0; i < 9; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");*/
    for (i = 0; i < 9; i++) {
        if (array[i] == board[r][c]) {
            return 1;
        }
    }
    return 0;


}

int final_parsing_check(int board[9][9], int row, int column, int given_row_coord[], int given_column_coordinate[], int num) {
    int copy_board[9][9] = {0}, possible_choices[9] = {0}, value = 0, i, r, square_check, row_check, column_check, num_possible_values = 0, check;
    /*This checks if the number was given by the puzzle i.e if check == 0, it was not given*/
    /*printf("\nvalue = %d\n", value);
    printf("I am at row %d column %d\n\n", row, column);*/
    check = checkifgiven_num(row, column, given_row_coord, given_column_coordinate, num);
    if (check == 0) {
    /*Here we form an array of all possible values that can be put in a the particular coordinate*/


        for (i = 0; i < 9; i++) {
            board[row][column] = board[row][column] + 1; /*since the square is input as 0, we add 1 and test if the number is a possibility.*/
            square_check = check_square(row, column, board); /*here I run all the checks i.e. if check == 0, the number has passed the check*/
            row_check = check_row(board, row, column);
            column_check = check_column(board, row, column);

            if (square_check == 0 && row_check == 0 && column_check == 0 && board[row][column] != 0 && board[row][column] < 10) {
                possible_choices[i] = board[row][column]; /*If the number is possible, it is added to an array*/
                num_possible_values += 1; /*to keep count of the number of possibilities*/
            }

        }

        /*printf("\nPossible values\n");
        for (i = 0; i < 9; i++) {
                printf("%d ", possible_choices[i]);
        }
        printf("\nNumber possible values: %d\n", num_possible_values);*/

        if (row == 9 && value == 0) {
            value = 1;
            print_board(board);
            return value;
        }
        /*base case*/
        else if (num_possible_values == 0) {
            /*print_board(board);*/
            board[row][column] = 0; /*because the board is a pointer, i need to change this back to 0 as it would be 9 after checking the possiblities.*/
            /*printf("\nchanged to 0\n");*/

            return 0;
        }


        for (i = 0; i < 9; i++) {

            if (possible_choices[i] != 0) { /*as long as the possible array values are not 0, the loop will jump to the next possibility*/

                board[row][column] = possible_choices[i];
                /*printf("board[%d][%d] = %d\n", row, column, possible_choices[i]);
                print_board(board);*/
                if (column == 8 && value == 0) {
                    value = final_parsing_check(board, row + 1, 0, given_row_coord, given_column_coordinate, num); /*for when it reaches the end of a row*/
                    board[row][column] = 0;
                }
                /*else if (row == 9 && value == 0) {
                    value = possible_choices[i];
                    return value;
                }*/

                else if (value == 0) {
                    /*printf("I am at row %d column %d\n\n", row, column);*/
                    value = final_parsing_check(board, row, column + 1, given_row_coord, given_column_coordinate, num); /*to go to the next column*/
                    board[row][column] = 0; /*needs to be reset to 0 when it comes out of the loop so that the possibliities can be refound*/
                }

                if (value != 0) {
                    return value;
                }

            }

        }
    }

    else if (check == 1) {
        if (column == 8) {
            value = final_parsing_check(board, row + 1, 0, given_row_coord, given_column_coordinate, num);
        }
        else if (row == 8 && column == 8) {
            value = possible_choices[i];
            return value;
        }

        else if (value == 0) {
            value = final_parsing_check(board, row, column + 1, given_row_coord, given_column_coordinate, num);
        }

        if (value != 0) {
            return value;
        }

    }

    return 0;
}

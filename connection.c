#include <stdio.h>
#include <string.h>
#define NUM 8 
/*connected by a line*/
int line_connected(int matrix[NUM][NUM], int x1, int y1, int x2, int y2) {
    int i, barrier, begin, end;
    /*connected by a line*/
    barrier = 0;
    if(x1 == x2) {
        begin = y1 < y2 ? y1 : y2;
        end   = y1 > y2 ? y1 : y2;
        for (i = begin + 1; i < end; ++i) {
            if (matrix[x1][i]) {
                barrier = 1;
            }
        }
        if (!barrier) {
            return 1;
        }
    }
    barrier = 0;
    if (y1 == y2) {
        begin = x1 < x2 ? x1 : x2;
        end   = x1 > x2 ? x1 : x2;
        for (i = begin+1; i < end; ++i) {
            if (matrix[i][y1]) {
                barrier = 1;
            }
        }
        if (!barrier) {
            return 1;
        }
    }
    return 0;
}
/*connected by a cross*/
int cross_connected(int matrix[NUM][NUM], int x1, int y1, int x2, int y2) {
    int x, y;
    x = x1, y = y2;
    if (matrix[x][y] == 0 && line_connected(matrix, x1, y1, x, y) && 
                line_connected(matrix, x2, y2, x, y)) {
        return 1;
    }
    x = x2, y = y1;
    if (matrix[x][y]==0 && line_connected(matrix, x1, y1, x, y) && 
                line_connected(matrix, x2, y2, x, y)) {
        return 1;
    }
    return 0;
}

/*is connected ?*/
int connected(int matrix[NUM][NUM], int x1, int y1, int x2, int y2) {
    int x, y;
    /*connected by line or a cross*/
    if(line_connected(matrix, x1, y1, x2, y2) ||
            cross_connected(matrix, x1, y1, x2, y2)) {
        return 1;
    }
    /*connected by two crosses*/
    for (x = 0; x < NUM; ++x) {
        if (matrix[x][y1] == 0 && line_connected(matrix, x, y1, x1, y1) && 
                cross_connected(matrix, x, y1, x2, y2)) {
            return 1;
        }
    }
    for (y = 0; y < NUM; ++y) {
        if (matrix[x1][y] == 0 && line_connected(matrix, x1, y, x1, y1) && 
                cross_connected(matrix, x1, y, x2, y2)) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int i;
    int matrix[NUM][NUM] = {
        {0, 1, 0, 1, 1, 1, 0 ,0},
        {1, 1, 1, 0, 0, 1, 1 ,1},
        {1, 0, 0, 0, 1, 1, 1 ,1},
        {1, 1, 0, 1, 1, 1, 1 ,0},
        {0, 1, 0, 1, 1, 0, 1 ,1},
        {1, 1, 0, 0, 0, 1, 1 ,0},
        {1, 1, 0, 1, 0, 0, 1 ,1},
        {1, 0, 0, 0, 1, 1, 0 ,1}
    };
    /*print the matrix*/ 
    for (i < 0; i < NUM*NUM; ++i) {
        printf("%d ", matrix[i/NUM][i%NUM]);
        if ((i+1)%NUM == 0) {
            printf("\n");
        }
    }
    printf("\n");

    printf("connection of (7, 0), (7, 4): %d expected: 1\n", connected(matrix, 7, 0, 7, 4));
    printf("connection of (7, 0), (7, 5): %d expected: 0\n", connected(matrix, 7, 0, 7, 5));
    printf("connection of (2, 0), (2, 4): %d expected: 1\n", connected(matrix, 2, 0, 2, 4));
    printf("connection of (2, 0), (3, 4): %d expected: 0\n", connected(matrix, 2, 0, 3, 4));
    printf("connection of (2, 0), (1, 5): %d expected: 1\n", connected(matrix, 2, 0, 1, 5));
    printf("connection of (2, 0), (7, 4): %d expected: 1\n", connected(matrix, 2, 0, 7, 4));
    printf("connection of (2, 0), (7, 5): %d expected: 0\n", connected(matrix, 2, 0, 7, 5));
    printf("connection of (2, 0), (7, 0): %d expected: 1\n", connected(matrix, 2, 0, 7, 0));
    printf("connection of (3, 3), (5, 5): %d expected: 1\n", connected(matrix, 3, 3, 5, 5));
    printf("connection of (3, 3), (6, 5): %d expected: 0\n", connected(matrix, 3, 3, 6, 5));
    return 0;
}

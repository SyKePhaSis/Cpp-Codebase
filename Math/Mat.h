#pragma once
#ifndef Mat
#define Mat

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int rows;
    int columns;
    float *sp;
} matrix;

#define MatAt(m, i, j) (m).sp[(i) * (m).rows + j]

// THESE ARE THE DECLARED FUNCTIONS
matrix MatAllocate(int rows, int columns);
matrix MatAdd(matrix mat1, matrix mat2);
matrix MatTranspose(matrix m);
float MatTrace(matrix m);
void MatScalarMult(matrix m, float s);
void MatRand(matrix mat, int m, int M);
void MatPrint(matrix m);
void MatFill(matrix m, float x);
bool isMatSymetrical(matrix m);



// FUNCTIONS
matrix MatAllocate(int rows, int columns)
{
    matrix m;
    m.rows = rows;
    m.columns = columns;
    m.sp = (float *)malloc(sizeof(m.sp) * rows * columns);
    return m;
}

void MatRand(matrix mat, int m, int M)
{
    srand(time(0));
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.columns; j++)
        {
            MatAt(mat, i, j) = m + (((float)rand() / (float)RAND_MAX) * (M - m));
        }
    }
}

matrix MatAdd(matrix mat1, matrix mat2)
{
    if (mat1.rows == mat2.rows && mat1.columns == mat2.columns)
    {
        matrix m = MatAllocate(mat1.rows, mat1.columns);
        for (int i = 0; i < m.rows; i++)
        {
            for (int j = 0; j < m.columns; j++)
            {
                MatAt(m, i, j) = MatAt(mat1, i, j) + MatAt(mat2, i, j);
            }
        }
        return m;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void MatFill(matrix m, float x)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            MatAt(m, i, j) = x;
        }
    }
}

void MatPrint(matrix m)
{
    printf("\n[\n");
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            printf("%f ", MatAt(m, i, j));
        }
        printf("\n");
    }
    printf("]\n");
}

void MatScalarMult(matrix m, float s)
{
  for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
	       MatAt(m,i,j) = s*MatAt(m,i,j);
        }
    }
}

matrix MatTranspose(matrix m)
{
    matrix y = MatAllocate(m.columns,m.rows);
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            MatAt(y,j,i) = MatAt(m,i,j);
        }
    }
    return y;
}

bool isMatSymetrical(matrix m)
{
    return m.rows == m.columns;
}

float MatTrace(matrix m)
{
    float s = 0;
    if(isMatSymetrical(m)){
        for(int i = 0; i < m.rows; i++)
        {
            s += MatAt(m,i,i);
        }
    }
    return s;
}

// TODO:
//  -Dot Product
//  -Cross Product?
//  -Determinant ?

#endif

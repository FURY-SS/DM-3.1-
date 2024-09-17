# include <stdio.h>
# include <malloc.h>
# include <stdbool.h>
# include <assert.h>

typedef struct matrix {
    int** values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

// размещает в динамической памяти матрицу размером nRows на nCols.
matrix getMemMatrix(int nRows, int nCols) {
    int** values = (int**)malloc(sizeof(int*) * nRows);

    for (int i = 0; i < nRows; i++)
        values[i] = (int*)malloc(sizeof(int) * nCols);

    return (matrix) { values, nRows, nCols };
}

// возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int* a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

// освобождает память, выделенную под хранение матрицы m.
void freeMemMatrix(matrix* m) {
    for (int i = 0; i < m->nRows; i++)
        free(m->values[i]);

    free(m->values);

    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}

// вывод матрицы m.
void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);

        printf("\n");
    }
}

// проверяет включение матриц отношений
bool includingMatrixOfRelations(matrix* A, matrix* B) {
    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            if (A->values[i][j] > B->values[i][j])
                return 0;

    return 1;
}

// проверяет равенство матриц отношений
bool equalityMatrixOfRelations(matrix* A, matrix* B) {
    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            if (A->values[i][j] != B->values[i][j])
                return 0;

    return 1;
}

// проверяет строгое включение матриц отношений
bool strictlyIncludingMatrixOfRelations(matrix* A, matrix* B) {
    bool is_less_one = 0;

    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            if (A->values[i][j] > B->values[i][j])
                return 0;
            else if (A->values[i][j] < B->values[i][j])
                is_less_one = 1;

    return is_less_one;
}

// выводит объединение матриц отношений
matrix unionMatrixOfRelations(matrix* A, matrix* B) {
    matrix uni = getMemMatrix(A->nRows, A->nCols);

    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            uni.values[i][j] = A->values[i][j] || B->values[i][j];

    return uni;
}

// выводит пересечение матриц отношений
matrix intersectionMatrixOfRelations(matrix* A, matrix* B) {
    matrix intersct = getMemMatrix(A->nRows, A->nCols);

    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            intersct.values[i][j] = A->values[i][j] && B->values[i][j];

    return intersct;
}

// выводит разность матрицы отношений A и матрицы отношений B
matrix differenceMatrixOfRelations(matrix* A, matrix* B) {
    matrix diff = getMemMatrix(A->nRows, A->nCols);

    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            diff.values[i][j] = A->values[i][j] && (!B->values[i][j]);

    return diff;
}

// выводит симметрическую разность матрицы отношений A и матрицы отношений B
matrix symmetricalDifferenceMatrixOfRelations(matrix* A, matrix* B) {
    matrix sym_diff = getMemMatrix(A->nRows, A->nCols);

    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            sym_diff.values[i][j] = (A->values[i][j] && (!B->values[i][j])) || ((!A->values[i][j]) && B->values[i][j]);

    return sym_diff;
}

// выводит дополнение к матрице отношений
matrix complementMatrixOfRelations(matrix* A) {
    matrix comp = getMemMatrix(A->nRows, A->nCols);

    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            comp.values[i][j] = !A->values[i][j];

    return comp;
}

// выводит обращение матрицы отношений
matrix requestMatrixOfRelations(matrix A) {
    matrix req = A;

    for (int i = 0; i < req.nRows; i++)
        for (int j = 0; j < req.nCols; j++)
            if (i < j) {
                int temp = req.values[i][j];

                req.values[i][j] = req.values[j][i];
                req.values[j][i] = temp;
            }

    return req;
}

// выводит композицию матриц отношений
matrix compositionMatrixOfRelations(matrix *A, matrix* B) {
    matrix compos = getMemMatrix(A->nRows, A->nCols);

    for (int i = 0; i < A->nRows; i++)
        for (int j = 0; j < A->nCols; j++)
            for (int z = 0; z < A->nCols; z++)
                if (A->values[i][z] && B->values[z][j]) {
                    compos.values[i][j] = 1;
                    break;
                }
                else
                    compos.values[i][j] = 0;

    return compos;
}

// выводит степень отношения матрицы отношений
matrix degreeOfRelationMatrixOfRelations(matrix A, int degree_of_relation) {
    assert(degree_of_relation > -1);

    matrix deg_of_rel;

    if (degree_of_relation == 0) {
        deg_of_rel = getMemMatrix(A.nRows, A.nCols);

        for (int i = 0; i < A.nRows; i++)
            for (int j = 0; j < A.nCols; j++)
                if (i == j)
                    A.values[i][j] = 1;
    }
    else if (degree_of_relation == 1)
        return A;
    else{
        deg_of_rel = A;
        matrix* old_deg_of_rel;

        for (int i = 0; i < degree_of_relation - 1; i++)
            deg_of_rel = compositionMatrixOfRelations(&deg_of_rel, &A);
    }

    return deg_of_rel;
}

int main() {
    matrix A = createMatrixFromArray((int[])
                                        {0,0,0,0,0,0,1,1,1,1,
                                  0,0,0,0,0,0,0,1,1,1,
                                  0,0,0,0,0,0,0,0,1,1,
                                  0,0,0,0,0,0,0,0,0,1,
                                  0,0,0,0,0,0,0,0,0,0,
                                  0,0,0,0,0,0,0,0,0,0,
                                  1,0,0,0,0,0,0,0,0,0,
                                  1,1,0,0,0,0,0,0,0,0,
                                  1,1,1,0,0,0,0,0,0,0,
                                  1,1,1,1,0,0,0,0,0,0},10,10);


    matrix B = createMatrixFromArray((int[])
                                                 {0,0,0,0,0,0,0,0,0,0,
                                                  0,1,0,1,0,1,0,1,0,1,
                                                  0,0,0,0,0,0,0,0,0,0,
                                                  0,1,0,1,0,1,0,1,0,1,
                                                  0,0,0,0,0,0,0,0,0,0,
                                                  0,1,0,1,0,1,0,1,0,1,
                                                  0,0,0,0,0,0,0,0,0,0,
                                                  0,1,0,1,0,1,0,1,0,1,
                                                  0,0,0,0,0,0,0,0,0,0,
                                                  0,1,0,1,0,1,0,1,0,1},10,10);

    matrix C = createMatrixFromArray((int[])
                                             {0,0,0,0,0,0,1,1,1,1,
                                              0,0,0,0,0,0,0,1,1,1,
                                              0,0,0,0,0,0,0,0,1,1,
                                              0,0,0,0,0,0,0,0,0,1,
                                              0,0,0,0,0,0,0,0,0,0,
                                              0,0,0,0,0,0,0,0,0,0,
                                              1,0,0,0,0,0,0,0,0,0,
                                              1,1,0,0,0,0,0,0,0,0,
                                              1,1,1,0,0,0,0,0,0,0,
                                              1,1,1,1,0,0,0,0,0,0},10,10);


    matrix F = compositionMatrixOfRelations(&A,&B);

    matrix G = intersectionMatrixOfRelations(&F,&A);

    matrix D = differenceMatrixOfRelations(&G,&C);
    outputMatrix(D);
}

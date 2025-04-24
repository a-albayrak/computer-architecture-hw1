#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This function initializes and returns a dense matrix 
 * as a dynamic two-dimensional array.
 */
DenseMatrix initDenseMatrix(int columnLength, int rowLength) {
	//TODO: Fill this function.
	DenseMatrix denseMatrix = (DenseMatrix)malloc(sizeof(*denseMatrix));
	if (denseMatrix == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for denseMatrix\n");
		return NULL;
	}

	denseMatrix->rowLength = rowLength;
	denseMatrix->columnLength = columnLength;
	
	denseMatrix->matrix = (int**)calloc(rowLength, sizeof(int*));
	if (denseMatrix->matrix == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for denseMatrix.matrix\n");
		free(denseMatrix);
		return NULL;
	}

	for (int i = 0; i < rowLength; i++) {
		denseMatrix->matrix[i] = (int*)calloc(columnLength, sizeof(int));
		if (denseMatrix->matrix[i] == NULL) {
			fprintf(stderr, "Error: Memory allocation failed for denseMatrix.matrix[i]\n");
			freeDenseMatrix(denseMatrix);
		}
	}
	return denseMatrix;
}

/**
 * This function deallocates all the rows and 
 * columns of the given dense matrix.
 */
void freeDenseMatrix(DenseMatrix denseMatrix) {
	//TODO: Fill this function.
	for (int i = 0; i < denseMatrix->rowLength; i++) {
        free(denseMatrix->matrix[i]);
        denseMatrix->matrix[i] = NULL;
    }
    free(denseMatrix->matrix);
    denseMatrix->matrix = NULL;
    free(denseMatrix);
}

/**
 * This function creates a dense matrix and fills 
 * the elements in the given parse matrix as a set.
 */
DenseMatrix parseMatrixToDenseMatrix(Set parseMatrix, int columnLength, int rowLength) {
	//TODO: Fill this function.
    DenseMatrix denseMatrix = initDenseMatrix(columnLength, rowLength);
    if (denseMatrix == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for denseMatrix\n");
        return NULL;
    }

    for (int i = 0; i < parseMatrix->cardinality; i++) {
        Element element = parseMatrix->elements[i];

        if (element->type == MATRIX_POINT) {
            int* matrixPoint = (int*)element->data;
            int x = matrixPoint[0];
            int y = matrixPoint[1];
            int data = matrixPoint[2];

            if (x >= 0 && x < columnLength && y >= 0 && y < rowLength) {
                denseMatrix->matrix[y][x] = data;
            }
        }
    }
    return denseMatrix;
}

/**
 * This function creates and returns a parse matrix 
 * as a set depending on the given dense matrix's elements.
 */
Set denseMatrixToParseMatrix(DenseMatrix denseMatrix) {
	//TODO: Fill this function.
    Set resultSet = initSet();
    if (resultSet == NULL) {
        printf("Error: Memory allocation failed for set.\n");
        return NULL;
    }

    for (int row = 0; row < denseMatrix->rowLength; row++) {
        for (int col = 0; col < denseMatrix->columnLength; col++) {
            int data = denseMatrix->matrix[row][col];
            
            if (data != 0) {
                Element element = createMatrixPointElement(col, row, data);
                if (element == NULL) {
                    printf("Error: Memory allocation failed for matrix.element\n");
                    free(resultSet);
                    return NULL;
                }

                if (!insertElement(resultSet, element)) {
                    printf("Error: Element insertion failed\n");
                    free(resultSet);
                    return NULL;
                }
            }
        }
    }
    return resultSet;
}

/**
 * This matrix creates a new dense matrix, and the 
 * matrix is the addition of the given two matrices.
 */
DenseMatrix addDenseMatrices(DenseMatrix dm1, DenseMatrix dm2) {
	//TODO: Fill this function.
    if (dm1->rowLength != dm2->rowLength || dm1->columnLength != dm2->columnLength) {
        printf("Error: Matrices have different dimensions addDenseMatrices failed.\n");
        return NULL;
    }

    DenseMatrix resultMatrix = initDenseMatrix(dm1->columnLength, dm1->rowLength);
    if (resultMatrix == NULL) {
        printf("Error: Memory allocation failed for denseMatrix\n");
        return NULL;
    }

    for (int row = 0; row < dm1->rowLength; row++) {
        for (int col = 0; col < dm1->columnLength; col++) {
            resultMatrix->matrix[row][col] = dm1->matrix[row][col] + dm2->matrix[row][col];
        }
    }
    return resultMatrix;
}

/**
 * This matrix creates a new sparse matrix as a set, 
 * and the matrix is the addition of the given 
 * two sparse matrices.
 */
Set addSparseMatrices(Set sm1, Set sm2, int columnLength, int rowLength) {
    //TODO: Fill this function.
    Set resultSet = initSet();
    if (!resultSet) {
        printf("Failed to create result set.\n");
        return NULL;
    }

    int i = 0, j = 0;
    while (i < sm1->cardinality || j < sm2->cardinality) {
        Element element1 = i < sm1->cardinality ? sm1->elements[i] : NULL;
        Element element2 = j < sm2->cardinality ? sm2->elements[j] : NULL;

        if (element1 && element2) {
            int* mp1 = (int*)element1->data;
            int* mp2 = (int*)element2->data;
            if (mp1[0] == mp2[0] && mp1[1] == mp2[1]) {
                int sum = mp1[2] + mp2[2];
                if (sum != 0) {
                    insertElement(resultSet, createMatrixPointElement(mp1[0], mp1[1], sum));
                }
                i++; j++;
            } else {
                Element newElem = (mp1[0] < mp2[0] || (mp1[0] == mp2[0] && mp1[1] < mp2[1]))
                                  ? createMatrixPointElement(mp1[0], mp1[1], mp1[2])
                                  : createMatrixPointElement(mp2[0], mp2[1], mp2[2]);
                if (newElem->type == MATRIX_POINT && ((int*)newElem->data)[2] != 0) {
                    insertElement(resultSet, newElem);
                } else {
                    free(newElem->data);
                    free(newElem);
                }
                mp1[0] < mp2[0] || (mp1[0] == mp2[0] && mp1[1] < mp2[1]) ? i++ : j++;
            }
        } else {
            Element elem = element1 ? element1 : element2;
            int* mp = (int*)elem->data;
            if (mp[2] != 0) {
                insertElement(resultSet, createMatrixPointElement(mp[0], mp[1], mp[2]));
            }
            element1 ? i++ : j++;
        }
    }
    return resultSet;
}

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    

/**
 * This function initializes a set without an element and returns it.
 */
Set initSet() {
	//TODO: Fill this function.
	Set set = (Set)malloc(sizeof(Set_t));
	if (set== NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set\n");
		return NULL;
	}
	set->elements = NULL;
	set->cardinality = 0;
	return set;
}

/**
 * This function creates an integer-typed element and returns it. 
 * It allocates memory for both the element and the integer.
 */
Element createIntegerElement(int data) {
	//TODO: Fill this function.
	Element element = (Element)malloc(sizeof(Element_t));
		if (element== NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set.element\n");
		return NULL;
	}

	element->type = INTEGER;
	
	element->data = malloc(sizeof(int));
	if (element->data == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set.element.data\n");
		free(element);
		return NULL;
	}
	*(int*)(element->data) = data;
	return element;
}

/**
 * This function creates an float-typed element and returns it. 
 * It allocates memory for both the element and the float.
 */
Element createFloatElement(float data) {
	//TODO: Fill this function.
	Element element = (Element)malloc(sizeof(Element_t));
		if (element== NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set.element\n");
		return NULL;
	}

	element->type = FLOAT;
	
	element->data = malloc(sizeof(float));
	if (element->data == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set.element.data\n");
		free(element);
		return NULL;
	}
	*(float*)(element->data) = data;
	return element;
}

/**
 * This function creates an string-typed element and returns it. 
 * It allocates memory for both the element and the string.
 * This function uses the `strlen` and the `strcpy` functions.
 */
Element createStringElement(char* data) {
	//TODO: Fill this function.
	Element element = (Element)malloc(sizeof(Element_t));
		if (element== NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set.element\n");
		return NULL;
	}

	element->type = STRING;
	
	element->data = malloc(strlen(data) + 1);
	if (element->data == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set.element.data\n");
		free(element);
		return NULL;
	}
	*strcpy((char*)element->data, data);
	return element;
}

/**
 * This function creates an matrix-point-typed element and returns it. 
 * It allocates memory for both the element and the matrix point.
 */
Element createMatrixPointElement(int x, int y, int data) {
	//TODO: Fill this function.
	Element element = (Element)malloc(sizeof(Element_t));
		if (element== NULL) {
		fprintf(stderr, "Error: Memory allocation failed for set.element\n");
		return NULL;
	}

	element->type = MATRIX_POINT;
    element->data = malloc(sizeof(int) * 3);
    if (element->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for set.element.data\n");
        free(element);
        return NULL;
    }

    int* matrixPoint = (int*)element->data;
    matrixPoint[0] = x;   
    matrixPoint[1] = y;
    matrixPoint[2] = data; 
	return element;
}

/**
 * This function compares two elements to see if they are identical. 
 * First, it checks if the types are identical. If they are the same, 
 * it checks if the data are the same. However, this function does not 
 * compare addresses because the value from two different addresses 
 * can be the same. It returns one if the elements are the same; 
 * otherwise, it returns zero. This function uses the `strcmp` function.
 */
int isSame(Element e1, Element e2) {
	//TODO: Fill this function.
	if (e1->type != e2->type) {
        return 0;
    }

    switch (e1->type) {
        case INTEGER:
            return (*(int*)e1->data == *(int*)e2->data);

        case FLOAT:
            return (*(float*)e1->data == *(float*)e2->data);

        case STRING:
            return (strcmp((char*)e1->data, (char*)e2->data) == 0);

        case MATRIX_POINT: {
            int* mp1 = (int*)e1->data;
            int* mp2 = (int*)e2->data;
            return (mp1[0] == mp2[0] && mp1[1] == mp2[1] && mp1[2] == mp2[2]);
        }
        default:
            return 0;
    }
}

/**
 * This function checks if the given element is in the set or not. 
 * It does not compare the addresses. It returns one if the given 
 * element is in the set; otherwise, it returns zero.
 */
int in(Set set, Element element) {
	//TODO: Fill this function.
	for (int i = 0; i < set->cardinality; i++) {
		if (isSame(set->elements[i], element)) {
			return 1;
		}
	}
	return 0;
}

/**
 * This function inserts an element into the given set. 
 * The same element cannot be twice in the same set.
 * It returns one if the inserting element is successful; 
 * otherwise, it returns zero. This function uses the 
 * `realloc` function.
 */
int insertElement(Set set, Element element) {
	//TODO: Fill this function.
    if (in(set, element)) {
        return 0;
    }

    Element* newElements = realloc(set->elements, sizeof(Element) * (set->cardinality + 1));
    if (newElements == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for realloc set.element\n");
        return 0;
    }

    set->elements = newElements;
    set->elements[set->cardinality] = element;
    set->cardinality++;
    return 1;
}

/**
 * This function removes the given element in the set. 
 * It returns one if removal is successful; otherwise, 
 * it returns zero. This function uses the `realloc` function.
 */
int removeElement(Set set, Element element) {
	//TODO: Fill this function.
    int index = -1;
    for (int i = 0; i < set->cardinality; i++) {
        if (isSame(set->elements[i], element)) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return 0;
    }

    free(set->elements[index]->data);
    free(set->elements[index]);

    for (int i = index; i < set->cardinality - 1; i++) {
        set->elements[i] = set->elements[i + 1];
    }

    Element* newElements = realloc(set->elements, sizeof(Element) * (set->cardinality - 1));
    if (newElements == NULL && set->cardinality > 1) {
        fprintf(stderr, "Error: Memory allocation failed for realloc set.element\n");
        return 0;
    }

    set->elements = newElements;
    set->cardinality--;
    return 1;
}

/**
 * This function creates and returns a new set, which is united of the given sets.
 */
Set unite(Set s1, Set s2) {
	Set resultSet = initSet();

    if (resultSet == NULL) {
		printf("United set creation failed.\n");
        return NULL; 
    }

    for (int i = 0; i < s1->cardinality; i++) {
        Element element = s1->elements[i];
        if (!in(resultSet, element)) {
            if (!insertElement(resultSet, element)) {
				printf("Element insertion to united set failed.\n");
                free(resultSet);
                return NULL;
            }
        }
    }

    for (int i = 0; i < s2->cardinality; i++) {
        Element element = s2->elements[i];
        if (!in(resultSet, element)) {
            if (!insertElement(resultSet, element)) {
				printf("Element insertion to united set failed.\n");
                free(resultSet);
                return NULL;
            }
        }
    }
    return resultSet;
}

/**
 * This function creates and returns a new set, which is intersected of the given sets.
 */
Set intersect(Set s1, Set s2) {
	//TODO: Fill this function.
	Set resultSet = initSet();

    if (resultSet == NULL) {
        printf("Intersection set creation failed.\n");
        return NULL;
    }

    for (int i = 0; i < s1->cardinality; i++) {
        Element element = s1->elements[i];

        if (in(s2, element)) {
            if (!insertElement(resultSet, element)) {
                printf("Element insertion to intersected set failed.\n");
                free(resultSet);
                return NULL;
            }
        }
    }
    return resultSet;
}

/**
 * This function creates and returns a new set, which is 
 * subtracted from the first given set by the second one.
 */
Set substract(Set s1, Set s2) {
	//TODO: Fill this function.
	Set resultSet = initSet();

    if (resultSet == NULL) {
        printf("Subtraction set creation failed.\n");
        return NULL;
    }

    for (int i = 0; i < s1->cardinality; i++) {
        Element element = s1->elements[i];

        if (!in(s2, element)) {
            if (!insertElement(resultSet, element)) {
                printf("Element insertion to subtracted set failed.\n");
                free(resultSet);
                return NULL;
            }
        }
    }
    return resultSet;
}

/**
 * This function prints the given element depending on its type.
 */
void printElement(Element element) {
	//TODO: Fill this function.
	if (element == NULL) {
        printf("Null element. Failed to print.\n");
        return;
    }

    switch (element->type) {
        case INTEGER:
            printf("INTEGER ELEMENT: %d\n", *(int*)element->data);
            break;

        case FLOAT:
            printf("FLOAT ELEMENT: %.2f\n", *(float*)element->data);
            break;

        case STRING:
            printf("STRING ELEMENT: %s\n", (char*)element->data);
            break;

        case MATRIX_POINT: {
            int* mp = (int*)element->data;
            printf("MATRIX POINT ELEMENT: (%d, %d, %d)\n", mp[0], mp[1], mp[2]);
            break;
        }
        default:
            break;
    }
}

/**
 * This function prints the given set element by element depending on its type.
 */
void printSet(Set set) {
	//TODO: Fill this function.
	    if (set == NULL) {
        printf("Set is NULL\n");
        return;
    }

    printf("Elements in the set:\n");
    for (int i = 0; i < set->cardinality; i++) {
        Element element = set->elements[i];
        printElement(element);
    }
}

/**
 * This element deallocates all data in the given set and the set itself.
 */
void freeSet(Set set) {
	//TODO: Fill this function. 
	// Will not be graded.
}
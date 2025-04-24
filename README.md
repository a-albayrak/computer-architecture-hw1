# CENG 311 - Computer Architecture

## Programming Assignment #1  

---

### Assignment  
Check the given codes `main.c`, `matrix.c`, `matrix.h`, `set.c`, and `set.h`.  
Fill out the empty functions as instructed on the given comment blocks for each function.  
Test your code.  
Then, submit just `matrix.c` and `set.c`.  

❗ Do not modify `matrix.h` or `set.h`.  
❗ Do not change the return type, function name, and parameters, and do not add or remove parameters.

---

### Preliminary  
You must know the fundamental set theory, sparse and dense matrices, and C programming language.

---

### Matrix Representation  

All the matrices are represented dynamically in this assignment.  
A **dense matrix** can be represented as a two-dimensional array.  
Therefore, `matrix[i][j]` in the code corresponds to matrixᵢⱼ in mathematics.  

A **sparse matrix** can be represented as a set.  
This set has only **matrix points**, a dynamic integer array that includes **three integers**.  
The first element represents the `i` coordinate,  
the second element represents the `j` coordinate,  
and the last element represents the point’s value.  

Therefore, aᵢⱼ = data corresponds to (i, j, data).  
Since the main reason for using sparse matrices is to save storage,  
we do **not** keep the points where their data is **zero**.  
The data is zero if there is no coordinate in the set.

---

### Warnings  

- You may need to use some functions like `realloc()`, `strcmp()`, `strcpy()`, and `strlen()`.  
  You can search how to use them and what they do.  
- You can use other functions; however, **do not include another library**.  
  Use the functions defined in:
  - `stdio.h`  
  - `stdlib.h`  
  - `string.h`  

- You can define helper functions if needed; however, **do not change the structure** of the provided functions.  
- **Do not modify the defined structures.**  
- You can use the given **makefile**, but you **do not have to**.

---

### References  
- https://en.wikipedia.org/wiki/Set_theory  
- https://en.wikipedia.org/wiki/Sparse_matrix  
- https://devdocs.io/c/

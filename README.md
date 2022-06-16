## MatrixLib  
**MatrixLib содержит класс matrix и дочерние классы:**  
- idmatrix;  единичная  
-diagmatrix;  диагональная  
-lowtriangmatrix;   нижняя треугольная  
-uptriangmatrix;  верхняя треугольная  
-symmatrix;  симметричная  
-vect;  вектор  
***
**Перегружены операторы:**  
<<, +, -, *  
***
**Mетоды:**  
-hadaьard(matrix &m1, matrix& m2)  возвращает matrix - произведение Хадамара  
-center()  центрирование  
-scale()  шкалирование  
-matrixnorm()  возвращает double - норму матрицы  
-matrixdet()  возвращает double - детерминант матрицы  
-matrixrank()  возвращает int - ранг матрицы  
-hadanard(matrix &m1, matrix& m2)  возвращает matrix - произведение Хадамара  
-transpose()  транспонирование матрицы (работает для всех матриц)  
-trace()  возвращает double - след матрицы  
-inverse()  возвращает matrix -  обратную матрицу (если есть)  
***
**запись и чтение из бинарного файла**  
-void writebinmatrix(const char* filename, matrix &m)  
-matrix readbinmatrix()  
***  
**Класс PCA** позволяет делать NIPALS разложение через метод void nip()  
метод void showdata() выводит на экран матрицы E,P, T.  





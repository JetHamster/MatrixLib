# MatrixLib
**MatrixLib содержит класс matrix и дочерние классы:**
*idmatrix; <sub> единичная </sub>
*diagmatrix; <sub> диагональная </sub>
*lowtriangmatrix;  <sub> нижняя треугольная </sub>
*uptriangmatrix; <sub> верхняя треугольная </sub>
*symmatrix; <sub> симметричная </sub>
*vect; <sub> вектор </sub>

**Перегружены операторы:**
<<, +, -, *

**Mетоды:**
*hadanard(matrix &m1, matrix& m2) <sub> возвращает matrix - произведение Хадамара </sub>
*center() <sub> центрирование </sub>
*scale() <sub> шкалирование </sub>
*matrixnorm() <sub> возвращает double - норму матрицы </sub>
*matrixdet() <sub> возвращает double - детерминант матрицы</sub>
*matrixrank()  <sub> возвращает int - ранг матрицы </sub>
*hadanard(matrix &m1, matrix& m2) <sub> возвращает matrix - произведение Хадамара</sub>
*transpose() <sub> транспонирование матрицы (работает для всех матриц) </sub>
*trace() <sub> возвращает double - след матрицы </sub>
*inverse() <sub> возвращает matrix -  обратную матрицу (если есть) </sub>

**запись и чтение из бинарного файла**
*void writebinmatrix(const char* filename, matrix &m)
*matrix readbinmatrix()

**Класс PCA** позволяет делать NIPALS разложение через метод void nip();
метод void showdata() выводит на экран матрицы E,P, T.





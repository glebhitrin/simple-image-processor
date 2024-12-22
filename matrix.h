#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

template <typename T>
class Matrix {
public:
    // Ожидаемые (стандартом) псевдонимы для типов данных, производных от T
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = value_type&;
    using const_reference = const value_type&;

    //Представляет абстракцию над строчкой матрицы,
    //самодостаточную и компактную для копирования по значению
    class Row {
        friend class Matrix<T>;

    public:
        T& operator[](size_t colnum) {
            return matrix_->operator()(rownum_, colnum);
        }

        size_t Size() {
            return matrix_->GetCollsNum();
        };

    protected:
        // Разрешаем доступ к конструктору только матрице
        Row(Matrix<T>* m, size_t rownum) : rownum_(rownum), matrix_(m) {
        }

    protected:
        size_t rownum_;
        Matrix<T>* matrix_;
    };

    class ConstRow {
        friend class Matrix<T>;

    public:
        T operator[](size_t colnum) const {
            return matrix_->operator()(rownum_, colnum);
        }
        size_t Size() {
            return matrix_->GetCollsNum();
        };

    protected:
        // Разрешаем доступ к конструктору только матрице
        ConstRow(const Matrix<T>* m, size_t rownum): rownum_(rownum), matrix_(m) {
        }

    protected:
        size_t rownum_;
        const Matrix<T>* matrix_;
    };


    //Представляет абстракцию над столбцом матрицы,
    //самодостаточную и компактную для копирования по значению
    class Col {
        friend class Matrix<T>;

    public:
        T& operator[](size_t rownum) {
            return matrix_->operator()(rownum, colnum_);
        }

    protected:
        // Разрешаем доступ к конструктору только матрице
        Col(Matrix<T>* m, size_t colnum) : colnum_(colnum), matrix_(m) {
        }

    protected:
        size_t colnum_;
        Matrix<T>* matrix_;
    };

    class ConstCol {
        friend class Matrix<T>;

    public:
        T operator[](size_t rownum) const {
            return matrix_->operator()(rownum, colnum_);
        }

    protected:
        // Разрешаем доступ к конструктору только матрице
        ConstCol(const Matrix<T>* m, size_t colnum): colnum_(colnum), matrix_(m) {
        }

    protected:
        size_t colnum_;
        const Matrix<T>* matrix_;
    };

public:
    Matrix(const Matrix<T>&) = delete;

    // Конструктор создаёт матрицу размера m x n и задаёт значение элементов по умолчанию
    // Если один из параметров не равен 0, то другой тоже. Иначе кидаем исключительную ситуацию
    Matrix(size_t rows_num = 0, size_t cols_num = 0, T def = T{}) {
        if (rows_num == 0 && cols_num == 0) {
            rows_num_ = 0;
            cols_num_ = 0;
            table_ = nullptr;
            return;
        }

        if (rows_num == 0 || cols_num == 0) {
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }
        rows_num_ = rows_num;
        cols_num_ = cols_num;
        table_ = AllocateMatrix(rows_num_, cols_num_);

        for (size_t i = 0; i < rows_num; ++i) {
            for (size_t j = 0; j < cols_num; ++j) {
                this->operator()(i, j) = def;
            }
        }
    };

    ~Matrix() {
        Clear();
    };

    // Возвращает i,j -й элемент матрицы
    T operator()(size_t i, size_t j) const {
        return GetIJEl(table_, i, j, cols_num_);
        //return table_[i * cols_num_ + j];
    }

    T& operator()(size_t i, size_t j) {
        return GetIJEl(table_, i, j, cols_num_);
        //return table_[i * cols_num_ + j];
    }

    // Возвращает i-ю строку, обёрнутую в абстракцию
    Row operator[](size_t i) {
        return Row(this, i);
    }

    ConstRow operator[](size_t i) const {
        return ConstRow(this, i);
    };

    Col operator()(size_t i) {
        return Col(this, i);
    };

    ConstCol operator()(size_t i) const {
        return ConstCol(this, i);
    };

    T At(size_t i, size_t j) const {
        if (i < rows_num_ && j < cols_num_) {
            return this->operator()(i, j);
        }
        throw std::out_of_range("IOJ (matrix).");
    };

    reference At(size_t i, size_t j) {
        if (i < rows_num_ && j < cols_num_) {
            return this->operator()(i, j);
        }
        throw std::out_of_range("IOJ (matrix).");
    };

public:
    void Resize(size_t new_rows, size_t new_cols, T def = T{}) {
        if (new_rows == rows_num_ && new_cols == cols_num_) {
            return;
        }
        if (new_rows == 0 && new_cols == 0) {
            Clear();
            return;
        }
        if (new_rows == 0 || new_cols == 0) {
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }

        T* new_table = AllocateMatrix(new_rows, new_cols);

        for (size_t i = 0; i < new_rows; ++i) {
            for (size_t j = 0; j < new_cols; ++j) {
                if (i >= rows_num_ || j >= cols_num_) {
                    GetIJEl(new_table, new_rows - i - 1, new_cols - j - 1, new_cols) = def;
                } else {
                    GetIJEl(new_table, new_rows - i - 1, j, new_cols) = GetIJEl(table_, rows_num_ - i - 1, j, cols_num_);
                }
            }
        }
        delete[] table_;
        table_ = new_table;
        rows_num_ = new_rows;
        cols_num_ = new_cols;
    }

    void Clear() {
        if (!table_) {
            return;
        }
        delete[] table_;
        rows_num_ = 0;
        cols_num_ = 0;
    };

    size_t GetRowsNum() const {
        return rows_num_;
    }

    size_t GetColsNum() const {
        return cols_num_;
    }

    T* GetPtr() {
        return table_;
    }

    const T* GetPtr() const {
        return table_;
    }

    // Вспомогательная функция, позволяющая по 3 параметрам получать правильное место элемента в массиве 4 параметра

    static reference GetIJEl(T* arr, size_t i, size_t j, size_t cols_num) {
        return arr[i * cols_num + j];
    }

protected:
    // Метод аллоцирует память в кучу для заданных параметров n и m
    // Методу от this ничего не надо, поэтому он статический
    static T* AllocateMatrix(size_t newRowsNum, size_t newColsNum) {
        T* ans = new T[newRowsNum * newColsNum];
        return ans;
    };

protected:
    T* table_;
    size_t rows_num_;
    size_t cols_num_;
};

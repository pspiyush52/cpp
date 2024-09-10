/**
 * This header contains the declaration and implementation of the Matrix class
 * which can be used to create Matrix objects for mathematical operations like
 * addition, subtraction, multiplication, etc., of matrices.
 * 
 * NOTE: Define the macro __MATRIX_H_DEBUG to show the creation, destruction
 * and copy/move prompts for Matrix objects.
*/
#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <exception>
#include <string>
#include <concepts>

#define __repeater_ui(N) for (unsigned int i{}; i < N; ++i)
#define __repeater(N, i) for (i = 0; i < N; ++i)
int terminate_set{0};

/**
 * @brief Base exception class to derive other matrix related exceptions from.
*/
class ExceptionBase : public std::exception{
    public:
        ExceptionBase(const char* error_msg) : msg(new std::string{error_msg}){}
        const char* what() const noexcept{
            return "Exception occurred.\n";
        }
        /**
         * @brief The exceptions used in this Matrix code add and extra
         * method other than the usual 'what()' method of the standard
         * exceptions of C++.
         * The 'desc()' method provides a clearer description of the error.
        */
        virtual void desc() const noexcept = 0;
        virtual ~ExceptionBase(){ delete msg; }
    
    protected:
        std::string* msg{};
};

/**
 * @brief A class representing all Size related exceptions.
*/
class SizeError : public ExceptionBase{
    public:
        SizeError(const char* error_message) : ExceptionBase(error_message){}
        const char* what() const noexcept override{
            return "SizeError: Invalid size.\n";
        }
        /**
         * @brief Print a description of the Exception.
        */
        void desc() const noexcept override{
            std::cout << "SizeError: " << *msg << '\n';
        }
};

/**
 * @brief A class representing all element access related exceptions.
*/
class IndexError : public ExceptionBase{
    public:
        IndexError(const char* error_message) : ExceptionBase(error_message){}
        const char* what() const noexcept override{
            return "IndexError: Invalid index.\n";
        }
        /**
         * @brief Print a description of the Exception.
        */
        void desc() const noexcept override{
            std::cout << "IndexError: " << *msg << '\n';
        }
};

/**
 * @brief A class representing exceptions which occur when a calculation
 * cannot be carried out.
*/
class UndefinedError : public ExceptionBase{
    public:
        UndefinedError(const char* error_message) : ExceptionBase(error_message){}
        const char* what() const noexcept override{
            return "UndefinedError: Invalid operation.\n";
        }
        void desc() const noexcept override{
            std::cout << "UndefinedError: " << *msg << '\n';
        }
};

/**
 * @brief A function to set-up the terminate mechanism to suit the Exceptions
 * structure defined in this file.
 * This function is automatically triggered upon creation of the first Matrix
 * object and is not triggered afterwards for any object creation.
*/
void __set_terminator(){
    terminate_set = 1;
    std::set_terminate([](){
        std::exception_ptr eptr = std::current_exception();
        try{
            if (eptr){
                std::cout << "Unhandled Exception\n  ";
                std::rethrow_exception(eptr);
            }
        }

        // First catch clause catches the exceptions defined in this file.
        catch(ExceptionBase& ex){
            ex.desc();
        }

        // For exceptions other than the ones defined in this file.
        catch(std::exception& ex){
            std::cout << ex.what();
        }
        std::abort();
    });
}

template<typename ContainerType>
concept NumContents = requires (ContainerType a){
    static_cast<double>(a[0]);
    a.size();
};

class Matrix{
	public:
        explicit Matrix(unsigned int row_col);
		Matrix(unsigned int rows, unsigned int cols);
		Matrix(unsigned int rows, unsigned int cols, double default_value);
        Matrix(unsigned int rows, unsigned int cols, std::initializer_list<double> args);
        Matrix(std::initializer_list<double> args);
        template<typename ContainerType>
        requires NumContents<ContainerType>
        Matrix(const ContainerType& src);
        template<typename ContainerType>
        requires NumContents<ContainerType>
        Matrix(unsigned int rows, unsigned int cols, const ContainerType& src);
        template<typename ContainerType>
        requires NumContents<ContainerType>
        Matrix(unsigned int row_col, const ContainerType& src);
        Matrix(const Matrix& src);
        Matrix(Matrix&& src) noexcept;

        /**
         * @brief Access element at (i, j) location in the matrix with bounds
         * checking.
         * Throws IndexError if index values are invalid.
         * @param i Row index.
         * @param j Column index.
         * @returns A reference to the matrix element at (i, j).
         * @throw Throws IndexError if any index is out of range.
        */
        double& get(unsigned int i, unsigned int j);
        
        /**
         * @brief Access element at (i, j) location in the matrix with bounds
         * checking.
         * Throws IndexError if index values are invalid.
         * @param i Row index.
         * @param j Column index.
         * @returns A const reference to the matrix element at (i, j).
         * @throw Throws IndexError if any index is out of range.
        */
        const double& get(unsigned int i, unsigned int j) const;
        
        /**
         * @brief Return the number of rows of the matrix.
        */
        unsigned int get_rows() const;
        /**
         * @brief Return the number of columns of the matrix.
        */
        unsigned int get_cols() const;

        Matrix& set_row(unsigned int row, double val);
        Matrix& set_col(unsigned int col, double val);

        Matrix& add_row(double val);
        Matrix& add_col(double val);

        Matrix& operator=(const double& rhs);
        Matrix& operator=(double&& rhs);
        Matrix& operator=(const Matrix& src);
        Matrix& operator=(Matrix&& src);
        Matrix& operator=(std::initializer_list<double> l);

        template<typename ContainerType>
        requires NumContents<ContainerType>
        Matrix& operator=(const ContainerType& src);
        
        /**
         * @brief Check if the matrix consists of only zero values.
         * @return A boolean value indicating if the matrix contains only
         * zeroes.
        */
        bool is_zero() const;

        /**
         * @brief Check if the matrix is a square matrix.
         * @return A boolean value indicating if the matrix is a square
         * matrix.
        */
        bool is_square() const;

        /**
         * @brief Fills the matrix with a single value.
         * @param value The value to fill the matrix with.
         * @return A reference to the matrix object.
        */
        Matrix& fill(double value);
        Matrix& fill(const std::initializer_list<double>& args);

        /**
         * @brief Fills the diagonal of a square matrix with a single value.
         * Rest elements are made equal to zero. This operation modifies the
         * matrix in place.
         * @param value The value to fill the diagonal with.
         * @return A reference to the matrix object.
         * @throw Throws SizeError if the matrix is not a square matrix
        */
        Matrix& make_diagonal(double value);

        /**
         * @brief Resize the matrix to a new size in place. Any additional
         * elements created as a result of the resize operation will be
         * initialized to zero.
         * @param new_rows Number of columns in the resized matrix.
         * @param new_cols Number of columns in the resized matrix.
         * @return A reference to the matrix object.
         * @throw Throws SizeError if any of new_rows and new_cols is zero.
         * @throw Throws SizeError if resizing reduces the number of elements
         * in the matrix which will cause data to be lost.
         * @remark No data loss.
        */
        Matrix& resize(unsigned int new_rows, unsigned int new_cols);

        /**
         * @brief Create and return a new matrix with the same data but with
         * the provided dimensions. Any additional elements created as a
         * result of the resize operation will be initialized to zero.
         * @param new_rows Number of columns in the resized matrix.
         * @param new_cols Number of columns in the resized matrix.
         * @return A new matrix object.
         * @throw SizeError if any of the new_rows and new_cols is zero.
         * @note No exceptions will be thrown if resizing results in a matrix
         * with fewer elements than the original matrix.
        */
        Matrix get_resized(unsigned int new_rows, unsigned int new_cols) const;

        /**
         * @brief Transpose the matrix in-place. Modifies the matrix.
         * @return A reference to the matrix object.
        */
        Matrix& transpose();

        /**
         * @brief Create and return a new matrix object which is a transpose
         * of the current matrix.
         * @return A new matrix object which is a transpose of the current
         * matrix.
        */
        Matrix get_transpose() const;

        /**
         * @brief Swap the elements of row r1 with the elements of row r2.
         * @return A reference to the matrix object.
         * @throw Throws IndexError if any of the row indices are out of
         * range.
         * @note If r1 == r2 then does nothing and simply returns a reference.
        */
        Matrix& swap_rows(unsigned int r1, unsigned int r2);

        /**
         * @brief Swap the elements of column c1 with the elements of column
         * c2.
         * @return A reference to the matrix object.
         * @throw Throws IndexError if any of the column indices are out of
         * range.
         * @note If c1 == c2 then does nothing and simply returns a reference.
        */
        Matrix& swap_cols(unsigned int c1, unsigned int c2);

        /**
         * @brief Calculate the determinant of a square matrix.
         * @return The value of the determinant.
         * @throw Throws SizeError if the matrix is not a square matrix
         * or if the number of rows/columns is less than two.
        */
        double determinant() const;

        /**
         * @brief Calculate the co-factor of the matrix element at (i, j).
         * @throw Throws IndexError if any of the row or column indices are
         * out of range.
        */
        double co_factor(unsigned int i, unsigned int j) const;

        /**
         * @brief Calculate and return the Adjoint matrix of the current
         * matrix.
         * @return A new matrix object which is the Adjoint of the current
         * matrix.
         * @throw Throws SizeError if the matrix is not a square matrix or
         * if the matrix has fewer than two rows/columns.
        */
        Matrix adjoint() const;

        /**
         * @brief Calculate and return the Inverse of the current matrix.
         * @return A new matrix object which is the Inverse of the current
         * matrix.
         * @throw Throws SizeError if the matrix is not a square matrix or
         * if the matrix has fewer than two rows/columns.
         * @throw Throws UndefinedError if the matrix is not invertible i.e.,
         * the determinant of the matrix evaluated to zero.
        */
        Matrix inverse() const;

        /**
         * @brief Create and return a new matrix object with row del_row
         * deleted from the matrix.
         * @param del_row Index of the row to be deleted.
         * @return A new matrix oject with a row specified by del_row removed
         * from the matrix.
         * @throw Throws IndexError if the row index is out of range.
         * @throw Throws SizeError if attempting to delete the only row in the
         * matrix.
        */
        Matrix get_row_delete(unsigned int del_row) const;

        /**
         * @brief Create and return a new matrix object with columns del_col
         * deleted from the matrix.
         * @param del_col Index of the column to be deleted.
         * @return A new matrix oject with a column specified by del_col
         * removed from the matrix.
         * @throw Throws IndexError if the column index is out of range.
         * @throw Throws SizeError if attempting to delete the only column in
         * the matrix.
        */
        Matrix get_col_delete(unsigned int del_col) const;

        /**
         * @brief Create and return a new matrix object with row del_row and
         * column del_col deleted from the matrix.
         * @param del_row Index of the row to be deleted.
         * @param del_col Index of the column to be deleted.
         * @return A new matrix object with a row and a column removed from
         * the matrix.
         * @throw Throws IndexError if the row or the column indices are out
         * of range.
         * @throw Throws SizeError if attempting to delete an only row or an
         * only column of the matrix.
        */
        Matrix get_rc_delete(unsigned int del_row, unsigned int del_col) const;

        double operator()() const;
        Matrix operator+(const Matrix& rhs) const;
        friend Matrix operator+(const Matrix& lhs, const double& rhs);
        friend Matrix operator+(const double& lhs, const Matrix& rhs);
        Matrix& operator+=(const Matrix& rhs);
        Matrix& operator+=(const double& rhs);
        Matrix operator-();
        Matrix operator-(const Matrix& rhs) const;
        Matrix operator-(const double& rhs) const;
        Matrix& operator-=(const Matrix& rhs);
        Matrix& operator-=(const double& rhs);
        Matrix operator*(const Matrix& rhs) const;
        friend Matrix operator*(const double& lhs, const Matrix& rhs);
        friend Matrix operator*(const Matrix& lhs, const double& rhs);
        Matrix& operator*=(const Matrix& rhs);
        Matrix& operator*=(const double& rhs);
        friend Matrix operator/(const Matrix& lhs, const double& rhs);
        friend Matrix operator/(const double& lhs, const Matrix& rhs);
        Matrix& operator/=(const double& rhs);
        bool operator==(const Matrix& rhs) const;

        // Element access without bounds checking
		double* operator[](unsigned int i);
		const double* operator[](unsigned int i) const;

		~Matrix();
		friend std::ostream& operator<<(std::ostream& output, const Matrix& M);

        /**
         * @brief Create and return a (size x size) identity matrix (a square
         * matrix in which all the diagonal elements are equal to one).
         * @return A new (size x size) identity matrix object.
        */
        static Matrix identity_matrix(unsigned int size);

        /**
         * @brief Create and return a (size x size) zero matrix (a square
         * matrix having all the elements equal to zero).
         * @return A new (size x size) zero matrix object.
        */
        static Matrix zero_matrix(unsigned int size);

        /**
         * @brief Create and return a (size x size) square matrix in which
         * every element has a value equal to fill_value.
         * @param fill_value The value to fill the matrix with. Has a default
         * value of 0.
         * @return A new (size x size) square matrix object.
        */
        static Matrix square_matrix(unsigned int size, double fill_value = 0);

        /**
         * @brief Create and return a (size x size) square matrix in which
         * every diagonal element i.e., elements having indices of the form
         * (i, i) are equal to fill_value.
        */
        static Matrix diagonal_matrix(unsigned int size, double fill_value);
        Matrix() : Matrix(2){}

	protected:
		double* matrix_arr{nullptr};
		unsigned int nrows{};
		unsigned int ncols{};

        //Helpers

        // Matrix() = default;
        Matrix(unsigned int size, double value, int, int);
		void invalidate();
        bool is_dim_same(const Matrix& M) const;
        unsigned int dim_sum() const;
        unsigned int dim_prod() const;
        Matrix __get_row_delete(unsigned int del_row) const;
        Matrix __get_col_delete(unsigned int del_col) const;
        Matrix __get_rc_delete(unsigned int, unsigned int) const;
        void __element_swapper(double& x, double& y);
        double __get_determinant() const;
        double __get_co_factor(unsigned int i, unsigned int j) const;
};

Matrix::Matrix(unsigned int row_col) : Matrix(row_col, row_col){}

Matrix::Matrix(unsigned int rows, unsigned int cols){
    if (!terminate_set)
        __set_terminator();

#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix created at " << this << '\n';
#endif  // __MATRIX_H_DEBUG
    
    unsigned int size = rows * cols;
    if (!size)
        throw SizeError("Invalid Matrix dimensions.");

    this->matrix_arr = new double[size];
    this->nrows = rows;
    this->ncols = cols;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double default_value):
    Matrix(rows, cols){
        double* ptr = this->matrix_arr;
        for (unsigned int i{}; i < (rows * cols); ++i, ++ptr)
            *ptr = default_value;
    }

Matrix::Matrix(unsigned int rows, unsigned int cols, std::initializer_list<double> args):
Matrix(rows, cols){
    const double* start = args.begin();
    const double* end = args.end();
    unsigned int i{}, size{rows * cols};

    for (; (start != end) && (i < size); ++i, ++start)
        this->matrix_arr[i] = *start;
    for (; i < size; ++i)
        this->matrix_arr[i] = 0;
}

Matrix::Matrix(std::initializer_list<double> args){
    if (!terminate_set)
        __set_terminator();
    if (args.size() < 2)
        throw SizeError("Incomplete Matrix dimensions.");
    
    const double* start = args.begin();
    const double* end = args.end();
    
    this->nrows = *(start);
    this->ncols = *(start + 1);
    if (!(this->nrows && this->ncols))
        throw SizeError("Invalid Matrix dimensions.");
    
#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix created at " << this << " using initializer list.\n";
#endif  // __MATRIX_H_DEBUG

    unsigned int i{}, size{nrows * ncols};
    
    this->matrix_arr = new double[size];

    for (start += 2; (start != end) && (i < size); ++i, ++start)
        this->matrix_arr[i] = *start;
    for (; i < size; ++i)
        this->matrix_arr[i] = 0;
}

template<typename ContainerType>
requires NumContents<ContainerType>
Matrix::Matrix(const ContainerType& src){
    if (!terminate_set)
        __set_terminator();
    if (src.size() < 2)
        throw SizeError("Incomplete Matrix dimensions.");

#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix created at " << this << " using a container.\n";
#endif  // __MATRIX_H_DEBUG

    this->nrows = src[0];
    this->ncols = src[1];
    unsigned int i{}, matrix_size{this->dim_prod()};
    this->matrix_arr = new double[matrix_size];

    for (; (i < matrix_size) && (i < src.size()); ++i)
        this->matrix_arr[i] = src[i];
    for (; i < matrix_size; ++i)
        this->matrix_arr[i] = 0;
}

template<typename ContainerType>
requires NumContents<ContainerType>
Matrix::Matrix(unsigned int rows, unsigned int cols, const ContainerType& src){
    if (!terminate_set)
        __set_terminator();
    if (!(rows * cols))
        throw SizeError("Invalid Matrix dimensions.");

#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix created at " << this << " using a container with explicit dimensions.\n";
#endif  // __MATRIX_H_DEBUG

    this->nrows = rows;
    this->ncols = cols;
    unsigned int i{}, matrix_size{rows * cols};
    this->matrix_arr = new double[matrix_size];

    for (; (i < matrix_size) && (i < src.size()); ++i)
        this->matrix_arr[i] = src[i];
    for (; i < matrix_size; ++i)
        this->matrix_arr[i] = 0;
}

template<typename ContainerType>
requires NumContents<ContainerType>
Matrix::Matrix(unsigned int row_col, const ContainerType& src):
    Matrix(row_col, row_col, src){}

Matrix::Matrix(const Matrix& src) : Matrix(src.nrows, src.ncols){

#ifdef __MATRIX_H_DEBUG
    std::cout << "    Copied from " << &src << '\n';
#endif  // __MATRIX_H_DEBUG
    
    memcpy(this->matrix_arr, src.matrix_arr, sizeof(double) * (nrows * ncols));
}

Matrix::Matrix(Matrix&& src) noexcept {

#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix created by moving matrix from " << &src << " to " << this << '\n';
#endif  // __MATRIX_H_DEBUG

    this->matrix_arr = src.matrix_arr;
    this->nrows = src.nrows;
    this->ncols = src.ncols;
    src.invalidate();
}

Matrix::Matrix(unsigned int size, double value, int, int) : Matrix(size){
    for (unsigned int i{}; i < size; ++i)
        for (unsigned int j{}; j < size; ++j)
            (*this)[i][j] = (i == j) ? value : 0;
}

double& Matrix::get(unsigned int i, unsigned int j){
    if (i >= this->nrows)
        throw IndexError("Row index out of bounds.");
    if (j >= this->ncols)
        throw IndexError("Column index out of bounds.");
    return (*this)[i][j];
}

const double& Matrix::get(unsigned int i, unsigned int j) const{
    if (i >= this->nrows)
        throw IndexError("Row index out of bounds.");
    if (j >= this->ncols)
        throw IndexError("Column index out of bounds.");
    return (*this)[i][j];
}

unsigned int Matrix::get_rows() const{
    return this->nrows;
}

unsigned int Matrix::get_cols() const{
    return this->ncols;
}

Matrix& Matrix::set_row(unsigned int row, double val) {
    if (row >= this->nrows)
        throw IndexError("Row index out of bounds.");
    double* row_ptr = (*this)[row];
    for (unsigned int i{}; i < this->ncols; ++i)
        (*(row_ptr++)) = val;
    return *this;
}

Matrix& Matrix::set_col(unsigned int col, double val) {
    if (col >= this->ncols)
        throw IndexError("Column index out of bounds.");
    double* col_ptr = (*this)[0] + col;
    for (unsigned int i{}; i < this->ncols; ++i, col_ptr += this->nrows)
        *col_ptr = val;
    return *this;
}

Matrix& Matrix::add_row(double val) {
    unsigned int arr_size = this->dim_prod();
    double* new_arr = new double[arr_size + this->ncols];
    memcpy(new_arr, this->matrix_arr, arr_size * sizeof(double));
    for (unsigned int i{arr_size}; i < arr_size + this->ncols; ++i)
        new_arr[i] = val;
    ++(this->nrows);
    delete[] this->matrix_arr;
    this->matrix_arr = new_arr;
    return *this;
}

Matrix& Matrix::add_col(double val) {
    unsigned int arr_size{this->dim_prod()}, i{}, j{1};
    double* new_arr = new double[arr_size + this->nrows];
    double* mptr = this->matrix_arr;
    ++(this->ncols);
    for (; i < arr_size + this->nrows; ++i, ++j)
        new_arr[i] = (j % (this->ncols)) ? (*(mptr++)) : val;
    delete[] this->matrix_arr;
    this->matrix_arr = new_arr;
    return *this;
}

Matrix& Matrix::operator=(const double& rhs){
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] = rhs;
    
    return *this;
}

Matrix& Matrix::operator=(double&& rhs){
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] = rhs;
    
    return *this;
}

bool Matrix::is_dim_same(const Matrix& M) const{
    return ((this->nrows == M.nrows) && (this->ncols == M.ncols));
}

Matrix& Matrix::operator=(const Matrix& src){
    if (this == &src)
        return *this;

#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix at " << &src << " copied(=) to matrix at " << this << '\n';
#endif  // __MATRIX_H_DEBUG

    unsigned int size = src.dim_prod();
    delete[] this->matrix_arr;
    this->matrix_arr = new double[size];
    memcpy(this->matrix_arr, src.matrix_arr, sizeof(double) * size);
    this->nrows = src.nrows;
    this->ncols = src.ncols;
    return *this;
}

Matrix& Matrix::operator=(Matrix&& src){
    if (this == &src)
        return *this;

#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix at " << &src << " moved(=) to matrix at " << this << '\n';
#endif  // __MATRIX_H_DEBUG

    delete[] this->matrix_arr;
    this->matrix_arr = src.matrix_arr;
    this->nrows = src.nrows;
    this->ncols = src.ncols;
    src.invalidate();
    return *this;
}

Matrix& Matrix::operator=(std::initializer_list<double> l){
    if (l.size() == 0){
        delete[] this->matrix_arr;
        this->invalidate();
    }
    const double* start = l.begin();
    const double* end = l.end();
    unsigned int i, matrix_size{this->dim_prod()};
    for (i = 0; (start != end) && (i < matrix_size); ++i, ++start)
        this->matrix_arr[i] = *start;
    
    for (; i < matrix_size; ++i)
        this->matrix_arr[i] = 0;
    
    return *this;
}

template<typename ContainerType>
requires NumContents<ContainerType>
Matrix& Matrix::operator=(const ContainerType& src){
    if (src.size() == 0)
        return *this;
    
    unsigned int i{};
    for (; (i < this->dim_prod()) && (i < src.size()); ++i)
        this->matrix_arr[i] = src[i];
    
    for (; i < this->dim_prod(); ++i)
        this->matrix_arr[i] = 0;
    
    return *this;
}

bool Matrix::is_zero() const{
    __repeater_ui(this->dim_prod())
        if (this->matrix_arr[i] != 0)
            return false;
    
    return true;
}

bool Matrix::is_square() const{
    return (this->nrows == this->ncols);
}

Matrix& Matrix::fill(double value){
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] = value;
    return *this;
}
Matrix& Matrix::fill(const std::initializer_list<double>& args) {
    auto it = args.begin();
    for(unsigned int i{}; i < this->dim_prod() && it != args.end(); ++i, ++it)
        this->matrix_arr[i] = *it;
    return *this;
}

Matrix& Matrix::make_diagonal(double value){
    if (!this->is_square())
        throw SizeError("Matrix needs to be square to make it a diagonal matrix.");
    for (unsigned int i{}; i < this->nrows; ++i)
        for (unsigned int j{}; j < this->ncols; ++j)
            (*this)[i][j] = (i == j) ? value : 0;
    return *this;
}

Matrix& Matrix::resize(unsigned int new_rows, unsigned int new_cols){
    if (!(new_rows && new_cols))
        throw SizeError("Invalid matrix size to resize to.");
    
    unsigned int cur_size{this->dim_prod()}, new_size{new_rows * new_cols};
    if (new_size < cur_size)
        throw SizeError("Resizing to a matrix with fewer elements.\nData loss will occur.");
    
    double* cur_data = this->matrix_arr;
    this->matrix_arr = new double[new_size];

    unsigned int i{};
    for (; (i < cur_size) && (i < new_size); ++i)
        this->matrix_arr[i] = cur_data[i];
    for (; i < new_size; ++i)
        this->matrix_arr[i] = 0;
    
    this->nrows = new_rows;
    this->ncols = new_cols;
    delete[] cur_data;

    return *this;
}

Matrix Matrix::get_resized(unsigned int new_rows, unsigned int new_cols) const {
    if (!(new_rows && new_cols))
        throw SizeError("Invalid matrix size to resize.");
    
    unsigned int cur_size{this->dim_prod()}, new_size{new_rows * new_cols}, i{};
    Matrix tmp(new_rows, new_cols);

    for (; (i < cur_size) && (i < new_size); ++i)
        tmp.matrix_arr[i] = this->matrix_arr[i];
    for (; i < new_size; ++i)
        tmp.matrix_arr[i] = 0;

    return tmp;
}

Matrix& Matrix::transpose(){
    Matrix tmp(this->ncols, this->nrows);
    for (unsigned int i{}; i < this->nrows; ++i)
        for (unsigned int j{}; j < this->ncols; ++j)
            tmp[j][i] = (*this)[i][j];
    *this = std::move(tmp);
    
    return *this;
}

Matrix Matrix::get_transpose() const{
    Matrix tmp(this->ncols, this->nrows);
    for (unsigned int i{}; i < this->nrows; ++i)
        for (unsigned int j{}; j < this->ncols; ++j)
            tmp[j][i] = (*this)[i][j];
    return tmp;
    
    return *this;
}

Matrix& Matrix::swap_rows(unsigned int r1, unsigned int r2){
    if (r1 >= this->nrows || r2 >= this->nrows)
        throw IndexError("Invalid row index.");
    if (r1 == r2)
        return *this;
    
    __repeater_ui(this->ncols)
        __element_swapper((*this)[r1][i], (*this)[r2][i]);
    
    return *this;
}

Matrix& Matrix::swap_cols(unsigned int c1, unsigned int c2){
    if (c1 >= this->ncols || c2 >= this->ncols)
        throw IndexError("Invalid column index.");
    if (c1 == c2)
        return *this;
    
    __repeater_ui(this->nrows)
        __element_swapper((*this)[i][c1], (*this)[i][c2]);
    
    return *this;
}

double Matrix::determinant() const{
    if (!this->is_square())
        throw SizeError("Determinant can only be calculated for square matrices.");
    if (this->nrows < 2)
        throw SizeError("Determinant cannot be calculated for matrix with less than two rows/columns.");
    
    return this->__get_determinant();
}

double Matrix::co_factor(unsigned int i, unsigned int j) const{
    if (!this->is_square())
        throw SizeError("Matrix must be square in order to calculate co-factor.");
    if (this->nrows < 2)
        throw UndefinedError("Co-factor cannot be defined for matrix smaller than (2x2).");
    if (i >= this->nrows)
        throw IndexError("Invalid row index.");
    if (j >= this->ncols)
        throw IndexError("Invalid column index.");
    
    return this->__get_co_factor(i, j);
}

Matrix Matrix::adjoint() const{
    if (!this->is_square())
        throw SizeError("Cannot calculate adjoint for a non-square matrix.");
    if (this->nrows < 2)
        throw SizeError("Matrix too small to calculate adjoint.\n  Minimum (2x2).");
    
    Matrix tmp{*this};
    unsigned int i{}, j{};
    __repeater(this->nrows, i)
        __repeater(this->ncols, j)
            tmp[j][i] = this->__get_co_factor(i, j);
    
    return tmp;
}

Matrix Matrix::inverse() const{
    if (!this->is_square())
        throw SizeError("Cannot calculate inverse for a non-square matrix.");
    if (this->nrows < 2)
        throw SizeError("Matrix too small to calculate inverse.\n  Minimum (2x2).");
    
    double det{this->__get_determinant()};
    if (!det)
        throw UndefinedError("Matrix not invertible.\n  Determinant evaluated to zero.");
    return (this->adjoint() / det);
}

Matrix Matrix::get_row_delete(unsigned int del_row) const{
    if (del_row >= this->nrows)
        throw IndexError("Invalid row index.");
    if (this->nrows == 1)
        throw SizeError("Cannot delete the only row in the matrix.");
    
    return this->__get_row_delete(del_row);
}

Matrix Matrix::get_col_delete(unsigned int del_col) const{
    if (del_col >= this->ncols)
        throw IndexError("Invalid column index.");
    if (this->ncols == 1)
        throw SizeError("Cannot delete the only column in the matrix.");
    
    return this->__get_col_delete(del_col);
}

Matrix Matrix::get_rc_delete(unsigned int del_row, unsigned int del_col) const{
    if (del_row >= this->nrows)
        throw IndexError("Invalid row index.");
    if (del_col >= this->ncols)
        throw IndexError("Invalid column index.");
    if (this->nrows == 1)
        throw SizeError("Cannot delete the only row in the matrix.");
    if (this->ncols == 1)
        throw SizeError("Cannot delete the only column in the matrix.");
    
    return this->__get_rc_delete(del_row, del_col);
}

double Matrix::operator()() const{
    return this->determinant();
}

Matrix Matrix::operator+(const Matrix& rhs) const{
    if (!is_dim_same(rhs))
        throw SizeError("Matrices must have the same dimensions to be added.");
    
    Matrix res(this->nrows, this->ncols);
    __repeater_ui(this->dim_prod())
        res.matrix_arr[i] = this->matrix_arr[i] + rhs.matrix_arr[i];
    
    return res;
}

Matrix operator+(const Matrix& lhs, const double& rhs){
    Matrix res(lhs.nrows, lhs.ncols);
    __repeater_ui(lhs.dim_prod())
        res.matrix_arr[i] = lhs.matrix_arr[i] + rhs;
    
    return res;
}

Matrix operator+(const double& lhs, const Matrix& rhs){
    return (rhs + lhs);
}

Matrix& Matrix::operator+=(const Matrix& rhs){
    if (!this->is_dim_same(rhs))
        throw SizeError("Matrices must have the same dimensions to be added.");
    
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] += rhs.matrix_arr[i];
    
    return *this;
}

Matrix& Matrix::operator+=(const double& rhs){
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] += rhs;
    
    return *this;
}

Matrix Matrix::operator-(){
    Matrix res(this->nrows, this->ncols);
    __repeater_ui(this->dim_prod())
        res.matrix_arr[i] = -this->matrix_arr[i];
    return res;
}

Matrix Matrix::operator-(const Matrix& rhs) const{
    if (!this->is_dim_same(rhs))
        throw SizeError("Matrices must have the dimensions to be subtracted.");
    
    Matrix res(this->nrows, this->ncols);
    __repeater_ui(this->dim_prod())
        res.matrix_arr[i] = this->matrix_arr[i] - rhs.matrix_arr[i];
    
    return res;
}

Matrix Matrix::operator-(const double& rhs) const{
    Matrix res(this->nrows, this->ncols);
    __repeater_ui(this->dim_prod())
        res.matrix_arr[i] = this->matrix_arr[i] - rhs;
    
    return res;
}

Matrix& Matrix::operator-=(const Matrix& rhs){
    if (!this->is_dim_same(rhs))
        throw SizeError("Matrices must have the dimensions to be subtracted.");
    
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] -= rhs.matrix_arr[i];
    
    return *this;
}

Matrix& Matrix::operator-=(const double& rhs){
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] -= rhs;
    
    return *this;
}

Matrix Matrix::operator*(const Matrix& rhs) const{
    if (this->ncols != rhs.nrows)
        throw SizeError("Matrices not multiplicable.\n  (LHS.columns != RHS.rows)");
    
    Matrix res(this->nrows, rhs.ncols);
    for (unsigned int i{}; i < res.nrows; ++i){
        for (unsigned int j{}; j < res.ncols; ++j){
            res[i][j] = 0;
            for (unsigned int k{}; k < this->ncols; ++k)
                res[i][j] += ((*this)[i][k] * rhs[k][j]);
        }
    }

    return res;
}

Matrix operator*(const double& lhs, const Matrix& rhs){
    Matrix res(rhs.nrows, rhs.ncols);
    __repeater_ui(rhs.dim_prod())
        res.matrix_arr[i] = lhs * rhs.matrix_arr[i];
    
    return res;
}

Matrix operator*(const Matrix& lhs, const double& rhs){
    return (rhs * lhs);
}

Matrix& Matrix::operator*=(const Matrix& rhs){
    if (this->ncols != rhs.nrows)
        throw SizeError("Matrices not multiplicable.\n  (LHS.columns != RHS.rows)");
    (*this) = (*this) * rhs;
    return *this;
}

Matrix& Matrix::operator*=(const double& rhs){
    __repeater_ui(this->dim_prod())
        this->matrix_arr[i] *= rhs;
    return *this;
}

Matrix operator/(const Matrix& lhs, const double& rhs){
    return (lhs * ( 1.0 / rhs));
}

Matrix operator/(const double& lhs, const Matrix& rhs){
    Matrix res(rhs.nrows, rhs.ncols);
    __repeater_ui(rhs.dim_prod())
        res.matrix_arr[i] = (lhs / (rhs.matrix_arr[i]));
    
    return res;
}

Matrix& Matrix::operator/=(const double& rhs){
    (*this) = (*this) / rhs;
    return *this;
}

bool Matrix::operator==(const Matrix& rhs) const{
    if (!(this->is_dim_same(rhs)))
        return false;
    __repeater_ui(this->dim_prod())
        if (this->matrix_arr[i] != rhs.matrix_arr[i])
            return false;
    return true;
}

double* Matrix::operator[](unsigned int i){
    return (matrix_arr + (i * ncols));
}

const double* Matrix::operator[](unsigned int i) const{
    return (matrix_arr + (i * ncols));
}

Matrix::~Matrix(){
    delete[] this->matrix_arr;
    this->invalidate();

#ifdef __MATRIX_H_DEBUG
    std::cout << "Matrix at " << this << " destroyed.\n";
#endif

}

void Matrix::invalidate(){
    this->matrix_arr = nullptr;
    this->nrows = this->ncols = 0;
}

unsigned int Matrix::dim_sum() const{
    return (this->nrows + this->ncols);
}

unsigned int Matrix::dim_prod() const{
    return (this->nrows * this->ncols);
}

Matrix Matrix::__get_row_delete(unsigned int del_row) const{
    Matrix tmp(this->nrows - 1, this->ncols);
    unsigned int i{}, j{}, k{};
    __repeater(this->nrows, i)
        __repeater(this->ncols, j)
            if (i != del_row)
                tmp.matrix_arr[k++] = (*this)[i][j];
    
    return tmp;
}

Matrix Matrix::__get_col_delete(unsigned int del_col) const{
    Matrix tmp(this->nrows, this->ncols - 1);
    unsigned int i{}, j{}, k{};
    __repeater(this->nrows, i)
        __repeater(this->ncols, j)
            if (j != del_col)
                tmp.matrix_arr[k++] = (*this)[i][j];
    
    return tmp;
}

Matrix Matrix::__get_rc_delete(unsigned int del_row, unsigned int del_col) const{
    Matrix tmp(this->nrows - 1, this->ncols - 1);
    for (unsigned int i{}, k{}; i < this->nrows; ++i)
        for (unsigned int j{}; j < this->ncols; ++j)
            if ((i != del_row) && (j != del_col))
                tmp.matrix_arr[k++] = (*this)[i][j];
    
    return tmp;
}

void Matrix::__element_swapper(double& x, double& y){
    double tmp = x;
    x = y;
    y = tmp;
}

double Matrix::__get_determinant() const{
    if ((this->nrows == 2)){
        return (
            (this->matrix_arr[0] * this->matrix_arr[3]) -
                (this->matrix_arr[1] * this->matrix_arr[2])
        );
    }
    double total{}, cur{};
    for (unsigned int i{}; i < this->nrows; ++i){
        cur = (this->__get_rc_delete(0, i).__get_determinant()) * (this->matrix_arr[i]);
        total = total + ((i % 2) ? (-cur) : cur);
    }
    return total;
}

double Matrix::__get_co_factor(unsigned int i, unsigned int j) const{
    double det;
    if (this->nrows == 2)
        det = (*this)[j][i];
    else
        det = this->__get_rc_delete(i, j).__get_determinant();
    
    if ((i + j) % 2)
        det *= (-1.0);
    return det;
}

std::ostream& operator<<(std::ostream& output, const Matrix& M){
    unsigned int i;
    output << "\n{\n";
    for (i = 0; i < (M.nrows * M.ncols); ++i)
        std::cout << std::setw(10) << M.matrix_arr[i] << (((i+1) % M.ncols) ? '\0' : '\n');
    output << "}\n Matrix at " << &M;

    return output;
}

inline Matrix Matrix::identity_matrix(unsigned int size){
    return Matrix(size, 1, 0, 0);
}

inline Matrix Matrix::zero_matrix(unsigned int size){
    return Matrix(size, size, 0);
}

inline Matrix Matrix::square_matrix(unsigned int size, double fill_value){
    return Matrix(size, size, fill_value);
}

inline Matrix Matrix::diagonal_matrix(unsigned int size, double fill_value){
    return Matrix(size, fill_value, 0, 0);
}

template<unsigned int size>
class SMatrix : public Matrix{
	public:
		SMatrix() : Matrix(size){}
		SMatrix(std::initializer_list<double> args) : Matrix(size){
			const double* iter = args.begin();
			unsigned int i{};
			for (; (iter != args.end()) && (i < (size * size)); ++i, ++iter)
				this->matrix_arr[i] = *iter;
			for (; i < (size * size); ++i)
				this->matrix_arr[i] = 0;
		}
};

#endif  // __MATRIX_H
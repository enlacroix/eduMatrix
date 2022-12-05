#pragma once
namespace linalg {
template <typename T>
Matrix<T>::Matrix()
{
	m_rows = 0;
	m_cols = 0;
	m_ptr = nullptr;
}
// 
template <typename T>
Matrix<T>::Matrix(int rows, int columns)
{
	m_rows = rows;
	m_cols = columns;
	m_ptr = new T[m_rows * m_cols];
}
// Заполняет все ячейки матрицы заданным значением defaultvalue. привет numpy.zeroes((row, col))
template <typename T>
Matrix<T>::Matrix(int rows, int columns, T defaultvalue)
{
	m_rows = rows;
	m_cols = columns;
	m_ptr = new T[m_rows * m_cols];

	for (int i = 0; i < m_rows * m_cols; i++)
	{
		m_ptr[i] = defaultvalue;
	}
}
// Конструктор копирования
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
	m_rows = other.m_rows;
	m_cols = other.m_cols;
	m_ptr = new T[m_rows * m_cols];
	for (int i = 0; i < m_rows * m_cols; i++)
	{
		m_ptr[i] = other.m_ptr[i];
	}
}
template <typename T>
int Matrix<T>::rows() const
{
	return m_rows;
}
template <typename T>
int Matrix<T>::columns() const
{
	return m_cols;
}
template <typename T>
// Такой способ проверки ПОД большим жирным вопросом. 
bool Matrix<T>::empty() const
{
	return nullptr == m_ptr;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& M)
{
	for (int i = 0; i < M.m_rows; ++i) {
		os << "|" << M.m_ptr[i];
		for (int j = 1; j < M.m_cols; ++j) {
			os << "\t" << M.m_ptr[i + j]; 
		}
		os << "|" << std::endl;
	}
	return os;
}
}



#pragma once
#include <vector>
#include <array>
#include <ranges>
#include <type_traits>
#include <stdexcept>
#include <iostream>
#include <format>
#include <cmath>
#include <tuple>
#include <iomanip>
#include <string>
#include <chrono>


class Timer
{
	using clock_t = std::chrono::high_resolution_clock;
	using microseconds = std::chrono::microseconds;
public:
	Timer()
		: start_(clock_t::now())
	{
	}
	double Stop()
	{
		const auto finish = clock_t::now();
		const auto us =
			std::chrono::duration_cast<microseconds>
			(finish - start_).count();
		return us / 1000000.0;
	}
	~Timer()
	{

	}
private:
	const clock_t::time_point start_;
};

template<typename _ElemType>
struct InitStruct
{
	_ElemType init_value;
};

template<typename _ElemType,size_t M, size_t N>
	requires (M > 1 && N == 1) || (M == 1 && N > 1) || (M > 1 && N > 1)
class Matrix
{
public:
	Matrix()
	{};
	auto& operator[](size_t i) & 
	{
		return _container[i];
	}
	Matrix(const Matrix<_ElemType, M, N>& other) :_container(other._container)
	{}
	Matrix(Matrix<_ElemType, M, N>&& other)
	{
		_container = std::move(other._container);
	}
	Matrix(InitStruct<_ElemType> init_struct)
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j] = init_struct.init_value;
			}
		}
	}
	
	auto& operator=(Matrix<_ElemType, M, N>&& other)&
	{
		_container = std::move(other._container);
		return *this;
	}
	auto&& T() &&
	{
		Matrix<_ElemType,N,M> new_matrix;
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				new_matrix._container[j][i] = _container[i][j];
			}
		}
		return std::move(new_matrix);
	}
	auto&& T()&
	{
		Matrix<_ElemType, N, M> new_matrix;
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				new_matrix._container[j][i] = _container[i][j];
			}
		}
		return std::move(new_matrix);
	}
	auto&& operator+(Matrix<_ElemType, M, N>&& other) &&
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j]+= other._container[i][j];
			}
		}
		return std::move(*this);
	}
	auto&& operator+(Matrix<_ElemType, M, N>&& other) &
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				other._container[i][j] += _container[i][j];
			}
		}
		return std::move(other);
	}
	auto&& operator+(Matrix<_ElemType, M, N>& other)&&
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j] += other._container[i][j];
			}
		}
		return std::move(*this);
	}
	auto operator+(Matrix<_ElemType, M, N>& other)&
	{
		Matrix<_ElemType, M, N> new_matrix;
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				new_matrix._container[i][j] = _container[i][j] + other._container[i][j];
			}
		}
		return new_matrix;
	}

	void operator+=(Matrix<_ElemType, M, N>&& other)&
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j] += other._container[i][j];
			}
		}
	}

	void operator+=(Matrix<_ElemType, M, N>& other)&
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j] += other._container[i][j];
			}
		}
	}

	void operator*=(_ElemType alpha)
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j] *= alpha;
			}
		}
	}


	auto&& operator-(Matrix<_ElemType, M, N>&& other)&&
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j] -= other._container[i][j];
			}
		}
		return std::move(*this);
	}
	auto&& operator-(Matrix<_ElemType, M, N>&& other)&
	{
		Matrix<_ElemType, M, N> new_matrix;
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				new_matrix._container[i][j] = _container[i][j] - other._container[i][j];
			}
		}
		return std::move(new_matrix);
	}
	auto&& operator-(Matrix<_ElemType, M, N>& other)&&
	{
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_container[i][j] -= other._container[i][j];
			}
		}
		return std::move(*this);
	}
	auto&& operator-(Matrix<_ElemType, M, N>& other)&
	{
		Matrix<_ElemType, M, N> new_matrix;
		for (size_t i = 0; i < M; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				new_matrix._container[i][j] = _container[i][j] - other._container[i][j];
			}
		}
		return std::move(new_matrix);
	}

	template<size_t other_N>
	auto&& operator*(Matrix<_ElemType, N, other_N>&& other)&&
	{
		if constexpr ((M == other_N) && (M == 1))
		{
			_ElemType sum{ 0.0 };
			for (size_t i = 0; i < N; i++)
			{
				sum += _container[0][i] * other._container[i][0];
			}
			return std::move(sum);
		}
		else if constexpr ((other_N==M)&&(M == N))
		{
			for (size_t i = 0; i < M; i++)
			{
				std::array<_ElemType, N> buffer;

				for (size_t j = 0; j < other_N; j++)
				{
					_ElemType sum{ 0.0 };
					for (size_t k = 0; k < N; k++)
					{
						sum += _container[i][k] * other._container[k][j];
					}
					buffer[j] = sum;
				}
				_container[i] = std::move(buffer);
			}
			return std::move(*this);
		}
		else
		{
			Matrix<_ElemType, M, other_N> new_matrix;
			for (size_t i = 0; i < M; i++)
			{
				for (size_t j = 0; j < other_N; j++)
				{
					_ElemType sum{ 0.0 };
					for (size_t k = 0; k < N; k++)
					{
						sum += _container[i][k] * other._container[k][j];
					}
					new_matrix._container[i][j] = sum;
				}
			}
			return std::move(new_matrix);
		}

	}

	template<size_t other_N>
	auto&& operator*(Matrix<_ElemType, N, other_N>& other)&
	{
		if constexpr ((M == other_N) && (M == 1))
		{
			_ElemType sum{ 0.0 };
			for (size_t i = 0; i < N; i++)
			{
				sum += _container[0][i] * other._container[i][0];
			}
			return std::move(sum);
		}
		else {
			Matrix<_ElemType, M, other_N> new_matrix;
			for (size_t i = 0; i < M; i++)
			{
				for (size_t j = 0; j < other_N; j++)
				{
					_ElemType sum{ 0.0 };
					for (size_t k = 0; k < N; k++)
					{
						sum += _container[i][k] * other._container[k][j];
					}
					new_matrix[i][j] = sum;
				}
			}
			return std::move(new_matrix);
		}
	}

	template<size_t other_N>
	auto&& operator*(Matrix<_ElemType, N, other_N>& other)&&
	{
		if constexpr ((M==other_N) && (M==1))
		{
			_ElemType sum{ 0.0 };
			for (size_t i = 0; i < N; i++)
			{
				sum += _container[0][i] * other._container[i][0];
			}
			return std::move(sum);
		}
		else if constexpr ((other_N == M) && (M == N))
		{
			for (size_t i = 0; i < M; i++)
			{
				std::array<_ElemType, N> buffer;

				for (size_t j = 0; j < other_N; j++)
				{
					_ElemType sum{ 0.0 };
					for (size_t k = 0; k < N; k++)
					{
						sum += _container[i][k] * other._container[k][j];
					}
					buffer[j] = sum;
				}
				_container[i] = std::move(buffer);
			}
			return std::move(*this);
		}
		else
		{
			Matrix<_ElemType, M, other_N> new_matrix;
			for (size_t i = 0; i < M; i++)
			{
				for (size_t j = 0; j < other_N; j++)
				{
					_ElemType sum{ 0.0 };
					for (size_t k = 0; k < N; k++)
					{
						sum += _container[i][k] * other._container[k][j];
					}
					new_matrix._container[i][j] = sum;
				}
			}
			return std::move(new_matrix);
		}

	}

	template<size_t other_N>
	auto&& operator*(Matrix<_ElemType, N, other_N>&& other)&
	{
		if constexpr ((M == other_N) && (M == 1))
		{
			_ElemType sum{ 0.0 };
			for (size_t i = 0; i < N; i++)
			{
				sum += _container[0][i] * other._container[i][0];
			}
			return std::move(sum);
		}
		else {
			Matrix<_ElemType, M, other_N> new_matrix;
			for (size_t i = 0; i < M; i++)
			{
				for (size_t j = 0; j < other_N; j++)
				{
					_ElemType sum{ 0.0 };
					for (size_t k = 0; k < N; k++)
					{
						sum += _container[i][k] * other._container[k][j];
					}
					new_matrix._container[i][j] = sum;
				}
			}
			return std::move(new_matrix);
		}
	}


	void PrintRow(size_t index_of_row,bool single_mod,size_t num_of_matrices)
	{

		if (index_of_row == 0)
		{
			std::cout << "\t|";
			for (size_t j = 0; j < N; j++)
			{	
				std::cout << std::format("{:.5f} ", _container[0][j]);
			}
			std::cout << std::format("|{}x{}\t", M, N);
		}
		else if (index_of_row <= (M - 1))
		{
			std::cout << "\t|";
			for (size_t j = 0; j < N; j++)
			{
				std::cout << std::format("{:.5f} ", _container[index_of_row][j]);
			}
			std::cout <<"|\t" ;
		}
		else if(single_mod==false)
		{
			for (size_t i = 0; i < N*5+(N-1)+2; i++)
			{
				std::cout << "#";
			}
			std::cout << " ";

		}
		else if (single_mod == true)
		{
			for (size_t i = 0; i < N * 5 + (N - 1) + 2; i++)
			{
				std::cout << "#";
			}
			std::cout << " ";

		}
	}
	void PrintSelf()
	{
		std::cout << "\t|";
		for (size_t j = 0; j < N; j++)
		{
			std::cout << std::format("{:.5f} ", _container[0][j]);
		}
		std::cout << std::format("|{}x{}",M,N) << std::endl;

		for (size_t i = 1; i < M; i++)
		{
			std::cout << "\t|";
			for (size_t j = 0; j < N; j++)
			{
				std::cout << std::format("{:.5f} ",_container[i][j]);
			}
			std::cout << "|" << std::endl;
		}
	}

	std::array<std::array<_ElemType,N>,M> _container;
};

template<typename _ElemType,size_t M,size_t N>
auto&& operator*(_ElemType alpha, Matrix<_ElemType, M, N>&& A)
{
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			A._container[i][j] *= alpha;
		}
	}
	return std::move(A);
}

template<typename _ElemType, size_t M, size_t N>
auto&& operator*(Matrix<_ElemType, M, N>&& A, _ElemType alpha)
{
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			A._container[i][j] *= alpha;
		}
	}
	return std::move(A);
}

template<typename _ElemType, size_t M, size_t N>
auto&& operator*(_ElemType alpha, Matrix<_ElemType, M, N>& A)
{
	Matrix<_ElemType, M, N> new_matrix;
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			new_matrix._container[i][j] = alpha*A._container[i][j];
		}
	}
	return std::move(new_matrix);
}

template<typename _ElemType, size_t M, size_t N>
auto&& operator*(Matrix<_ElemType, M, N>& A,_ElemType alpha)
{
	Matrix<_ElemType, M, N> new_matrix;
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			new_matrix._container[i][j] = alpha * A._container[i][j];
		}
	}
	return std::move(new_matrix);
}


template<size_t num_of_matrices, size_t index_of_matrix, size_t index_of_row, size_t max_num_of_rows, typename ... Matrices>
void print_i_th_j_th_row(std::tuple<Matrices ...>& tuple_with_matrices)
{
	if constexpr (num_of_matrices == 1)
	{
		std::get<index_of_matrix>(tuple_with_matrices).PrintRow(index_of_row, true, num_of_matrices);
	}
	else {
		std::get<index_of_matrix>(tuple_with_matrices).PrintRow(index_of_row, false, num_of_matrices);
	}

	if constexpr ((index_of_matrix <= (num_of_matrices - 2)) && (num_of_matrices > 1))
	{
		print_i_th_j_th_row<num_of_matrices, index_of_matrix + 1, index_of_row, max_num_of_rows, Matrices ...>(tuple_with_matrices);
	}
	else if constexpr ((index_of_row < (max_num_of_rows)) && (num_of_matrices == 1))
	{
		std::cout << std::endl;

		print_i_th_j_th_row<num_of_matrices, 0, index_of_row + 1, max_num_of_rows, Matrices ...>(tuple_with_matrices);

	}
	else if constexpr ((index_of_matrix <= (num_of_matrices - 2)) == false && (index_of_row < max_num_of_rows))
	{
		std::cout << std::endl;
		print_i_th_j_th_row<num_of_matrices, 0, index_of_row + 1, max_num_of_rows, Matrices ...>(tuple_with_matrices);

	}
}

template<size_t num_of_matrices, size_t max_num_of_rows, typename ... Matrices>
void print_matrices(std::tuple<Matrices ...>& tuple_with_matrices)
{
	print_i_th_j_th_row<num_of_matrices, 0, 0, max_num_of_rows, Matrices...>(tuple_with_matrices);
}

template<typename ... Matrices>
void PrintMatrix(Matrices&&... matrices)
{	
	static_assert(sizeof...(matrices) != 0, "an attempt to print nothing");
	std::cout << std::endl;
	std::tuple<Matrices ...> tuple_with_matrices(matrices ...);
	if constexpr (sizeof...(matrices) == 1)
	{
		std::get<0>(tuple_with_matrices).PrintSelf();
	}
	else {
		print_matrices<sizeof...(matrices), 2, Matrices ...>(tuple_with_matrices);
	}
	
}

template<typename Last>
void print_wstrings(Last last)
{
	std::wcout << last;
}

template<typename First, typename ...Rest>
void print_wstrings(First first, Rest... rest)
{
	std::wcout << first << " ";
	print_wstrings(rest ...);
}

template<typename ...PrintableData>
void Print(PrintableData... data)
{
	std::wcout <<"\t";
	print_wstrings(data ...);
	std::wcout << std::endl;
}


 



#include "stdafx.h"
#include "matrix.h"
	
	
template <typename T>
void CMatrix<T>::resize( int rows, int cols )
{
	int rs = this->rows();
	int cs = this->cols();
 
	if ( rows == rs && cols == cs )
	{
		return;
	}
	else if ( rows == rs && cols != cs )
	{
		for ( int i = 0; i < rows; ++i )
		{
			m_array[i].resize( cols );
		}
	}
	else if ( rows != rs && cols == cs )
	{
		m_array.resize( rows );
		for ( int i = rs; i < rows; ++i )
		{
			m_array[i].resize( cols );
		}
	}
	else
	{
		m_array.resize( rows );
		for ( int i = 0; i < rows; ++i )
		{
			m_array[i].resize( cols );
		}
	}
}

template <typename T>
void CMatrix<T>::swap_row( int row1, int row2 )
{
	if ( row1 != row2 && row1 >=0 &&
		row1 < rows() && row2 >= 0 && row2 < rows() )
	{
        std::vector<T>& v1 = m_array[row1];
        std::vector<T>& v2 = m_array[row2];
        std::vector<T> tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
}
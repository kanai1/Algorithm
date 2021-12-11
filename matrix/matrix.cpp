#include "matrix.h"

matrix::matrix(int row, int col)
{
    this->m_size.row = row;
    this->m_size.col = col;

    data = new long long*[this->m_size.row];
    for(int i = 0; i < this->m_size.row; i++)
    {
        data[i] = new long long[this->m_size.col]{};
    }
}

matrix::matrix(matrix_size m_size)
{
    this->m_size.row = m_size.row;
    this->m_size.col = m_size.col;

    data = new long long*[this->m_size.row];
    for(int i = 0; i < this->m_size.row; i++)
    {
        data[i] = new long long[this->m_size.col]{};
    }
}

matrix::matrix(const void* other, int row, int col)
{
    this->m_size.row = row;
    this->m_size.col = col;

    int *data = (int*)other;

    this->data = new long long*[this->m_size.row];
    for(int i = 0, k = 0; i < this->m_size.row; i++)
    {
        this->data[i] = new long long[this->m_size.col];
        for(int j = 0; j < this->m_size.col; j++)
        {
            this->data[i][j] = data[k++];
        }
    }
}

matrix::matrix(const std::vector<std::vector<int>>& other)
{
    m_size.row = other.size();
    m_size.col = other[0].size();

    data = new long long*[m_size.row];
    for(int i = 0; i < m_size.row; i++)
    {
        data[i] = new long long[m_size.col];
        for(int j = 0; j < m_size.col; j++)
        {
            data[i][j] = other[i][j];
        }
    }
}

matrix::matrix(const matrix& other)
{
    this->m_size.row = other.m_size.row;
    this->m_size.col = other.m_size.col;

    data = new long long*[this->m_size.row];
    for(int i = 0; i < this->m_size.row; i++)
    {
        data[i] = new long long[this->m_size.col];
        for(int j = 0; j < this->m_size.col; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

matrix::~matrix()
{
    for(int i = 0; i < m_size.row; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

matrix operator*(const matrix& mt, const int num)
{
    matrix result(mt.m_size);

    for(int i = 0; i < mt.m_size.row; i++)
    {
        for(int j = 0; j < mt.m_size.col; j++)
        {
            result.data[i][j] = mt.data[i][j] * num;
        }
    }

    return result;
}

matrix operator+(const matrix& mt1, const matrix& mt2)
{
    if(mt1.m_size != mt2.m_size)
    {
        throw "out of size";
    }

    matrix result(mt1.m_size);

    for(int i = 0; i < mt1.m_size.row; i++)
    {
        for(int j = 0; j < mt1.m_size.col; j++)
        {
            result.data[i][j] = mt1.data[i][j] + mt2.data[i][j];
        }
    }

    return result;
}

matrix operator-(const matrix& mt1, const matrix& mt2)
{
    if(mt1.m_size != mt2.m_size)
    {
        throw "out of size";
    }

    matrix result(mt1.m_size);

    for(int i = 0; i < mt1.m_size.row; i++)
    {
        for(int j = 0; j < mt1.m_size.col; j++)
        {
            result.data[i][j] = mt1.data[i][j] - mt2.data[i][j];
        }
    }

    return result;
}

matrix operator*(const matrix& mt1, const matrix& mt2)
{
    if(mt1.m_size.col != mt2.m_size.row)
    {
        throw "out of size";
    }

    matrix result(mt1.m_size.row, mt2.m_size.col);

    for(int i = 0; i < mt1.m_size.row; i++)
    {
        for(int j = 0; j < mt2.m_size.col; j++)
        {
            for(int k = 0; k < mt1.m_size.col; k++)
            {
                result.data[i][j] += mt1.data[i][k] * mt2.data[k][j];
            }
        }
    }

    return result;
}

long long matrix::det(const matrix& mt) const
{
    if(mt.m_size.col != mt.m_size.row)
    {
        throw "out of size";
    }


}

matrix matrix::submtx(int r_s, int c_s, int r_e, int c_e)
{
    if(m_size.row < r_s || r_s > r_e || m_size.col < c_s || c_s > c_e)
    {
        throw "out of size";
    }

    matrix result(r_e - r_s + 1, c_e - c_s + 1);

    for(int i = 0; i < result.m_size.row; i++)
    {
        for(int j = 0; j < result.m_size.col; i++)
        {
            result.data[i][j] = data[i + r_s - 1][j + c_s - 1];
        }
    }

    return result;
}

long long& matrix::element(int x, int y)
{
    if(x <= 0 || x > m_size.row || y <= 0 || y > m_size.col)
        throw "out of range";
    return data[x - 1][y - 1]; 
}

long long& matrix::at(int x, int y)
{
    while(x <= 0) x += m_size.row;
    while(y <= 0) y += m_size.col;
    while(x > m_size.row) x -= m_size.row;
    while(y > m_size.col) y -= m_size.col;

    return data[x][y];
}

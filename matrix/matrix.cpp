#include "matrix.h"

matrix::matrix(int row, int col)
{
    this->row = row;
    this->col = col;

    data = new long long*[this->row];
    for(int i = 0; i < this->row; i++)
    {
        data[i] = new long long[this->col]{};
    }
}

matrix::matrix(const void* other, int row, int col)
{
    this->row = row;
    this->col = col;

    int *data = (int*)other;

    this->data = new long long*[this->row];
    for(int i = 0, k = 0; i < this->row; i++)
    {
        this->data[i] = new long long[this->col];
        for(int j = 0; j < this->col; j++)
        {
            this->data[i][j] = data[k++];
        }
    }
}

matrix::matrix(const std::vector<std::vector<int>>& other)
{
    row = other.size();
    col = other[0].size();

    data = new long long*[row];
    for(int i = 0; i < row; i++)
    {
        data[i] = new long long[col];
        for(int j = 0; j < col; j++)
        {
            data[i][j] = other[i][j];
        }
    }
}

matrix::matrix(const matrix& other)
{
    this->row = other.row;
    this->col = other.col;

    data = new long long*[this->row];
    for(int i = 0; i < this->row; i++)
    {
        data[i] = new long long[this->col];
        for(int j = 0; j < this->col; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

matrix::~matrix()
{
    for(int i = 0; i < row; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

long long& matrix::element(int x, int y)
{
    if(x <= 0 || x > row || y <= 0 || y > col)
        throw "out of range";
    return data[x - 1][y - 1]; 
}

#include <vector>

struct matrix_size
{
    size_t row;
    size_t col;

    bool operator==(const matrix_size s) const
    {
        return this->row == s.row && this->col == s.col;
    }

    bool operator!=(const matrix_size s) const
    {
        return !(*this == s);
    }
};

class matrix
{
private:
    matrix_size m_size;
    long long** data;

public:
    matrix(int col, int row);
    matrix(matrix_size size);
    matrix(const void* other, int row, int col);
    matrix(const std::vector<std::vector<int>>& other);
    matrix(const matrix& other);

    ~matrix();

    friend matrix operator*(const matrix& mt, const int num);

    friend matrix operator+(const matrix& mt1, const matrix& mt2);
    friend matrix operator-(const matrix& mt1, const matrix& mt2);
    friend matrix operator*(const matrix& mt1, const matrix& mt2);

    friend matrix transopse(const matrix& mt);
    friend long long det(const matrix& mt);
    friend long long trace(const matrix& mt);

    matrix_size size() const { return m_size; }

    long long& element(int x, int y);

private:
    long long& at(int x, int y);
};

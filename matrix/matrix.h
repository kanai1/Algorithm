#include <vector>

class matrix
{
private:
    size_t row, col;
    long long** data;

public:
    matrix(int col, int row);
    matrix(const void* other, int row, int col);
    matrix(const std::vector<std::vector<int>>& other);
    matrix(const matrix& other);

    ~matrix();

    friend matrix operator*(const matrix& mt, const int num);

    friend matrix operator+(const matrix& mt1, const matrix mt2);
    friend matrix operator-(const matrix& mt1, const matrix mt2);
    friend matrix operator*(const matrix& mt1, const matrix mt2);

    friend matrix transopse(const matrix& mt);
    friend long long det(const matrix& mt);
    friend long long trace(const matrix& mt);

    long long& element(int x, int y);
};

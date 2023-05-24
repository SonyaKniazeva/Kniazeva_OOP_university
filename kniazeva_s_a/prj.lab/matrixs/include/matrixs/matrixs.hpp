#pragma once
#ifndef MATRIXS_MATRIXS_HPP_20230524
#define MATRIXS_MATRIXS_HPP_20230524

#include <tuple>
#include <stdexcept>
#include <vector>
#include<iostream>


class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

public:
    explicit MatrixS(const SizeType& size = { 0, 0 });
    MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n); //m - строка, n - столбец
    ~MatrixS() {
        delete[] earr;
        delete[] iarr;
    };

    MatrixS(const MatrixS& other);
    MatrixS& operator=(const MatrixS& other);

    [[nodiscard]] int& at(const SizeType& elem);
    [[nodiscard]] const int& at(const SizeType& elem) const;
    [[nodiscard]] int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
    [[nodiscard]] const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

    void resize(const SizeType& new_size);
    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);

    [[nodiscard]] const SizeType& ssize() const noexcept;

    [[nodiscard]] std::ptrdiff_t nRows() const noexcept;

    [[nodiscard]] std::ptrdiff_t nCols() const noexcept;


private:
    int* earr = nullptr;
    std::ptrdiff_t* iarr = nullptr;
    std::ptrdiff_t m_;
    std::ptrdiff_t n_;
};

#endif
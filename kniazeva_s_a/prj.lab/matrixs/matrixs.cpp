#include <matrixs/matrixs.hpp>

#include <tuple>
#include <stdexcept>
#include <vector>
#include<iostream>

MatrixS::MatrixS(const SizeType& size) {
    std::get<0>(sz) = std::get<0>(size);
    std::get<1>(sz) = std::get<1>(size);
    iarr = new std::ptrdiff_t[std::get<0>(sz)];
    for (std::ptrdiff_t i = 0; i < std::get<0>(sz); i++) {
        iarr[i] = i * std::get<1>(sz);
    }

    earr = new int[std::get<0>(sz) * std::get<1>(sz)];
    std::fill_n(earr, std::get<0>(sz) * std::get<1>(sz), 0);
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) {
    std::get<0>(sz) = m;
    std::get<1>(sz) = n;
    iarr = new std::ptrdiff_t[m];
    for (std::ptrdiff_t i = 0; i < m; i++) {
        iarr[i] = i * n;
    }

    earr = new int[m * n];
    std::fill_n(earr, m * n, 0);
}

MatrixS::MatrixS(const MatrixS& other) {
    this->earr = new int[std::get<1>(other.sz) * std::get<0>(other.sz)];
    this->iarr = new std::ptrdiff_t[std::get<0>(other.sz)];
    std::copy(other.earr, other.earr + std::get<1>(other.sz) * std::get<0>(other.sz), this->earr);
    std::copy(other.iarr, other.iarr + std::get<0>(other.sz), this->iarr);
    std::get<0>(this->sz) = std::get<0>(other.sz);
    std::get<1>(this->sz) = std::get<1>(other.sz);

}

MatrixS& MatrixS::operator=(const MatrixS& other) {
    this->resize(std::get<0>(other.sz), std::get<1>(other.sz));
    std::copy(other.earr, other.earr + std::get<1>(other.sz) * std::get<0>(other.sz), this->earr);
    std::copy(other.iarr, other.iarr + std::get<0>(other.sz), this->iarr);
    std::get<0>(this->sz) = std::get<0>(other.sz);
    std::get<1>(this->sz) = std::get<1>(other.sz);

    return *this;
}

int& MatrixS::at(const SizeType& elem) {
    auto i = std::get<0>(elem);
    auto j = std::get<1>(elem);
    if (i >= std::get<0>(sz) || i < 0 || j >= std::get<1>(sz) || j < 0) {
        throw std::out_of_range("index out of range");
    }
    else {
        return earr[iarr[i] + j];;
    }
}

const int& MatrixS::at(const SizeType& elem) const {
    auto i = std::get<0>(elem);
    auto j = std::get<1>(elem);

    return earr[iarr[i] + j];
}

int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i >= std::get<0>(sz) || i < 0 || j >= std::get<1>(sz) || j < 0) { //нумерация с 0 до std::get<0>(sz) - 1 и с 0 до std::get<1>(sz) - 1
        throw std::out_of_range("index out of range");
    }
    else {

        return earr[iarr[i] + j];
    }
}

const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
    if (i >= std::get<0>(sz) || i < 0 || j >= std::get<1>(sz) || j < 0) {
        throw std::out_of_range("index out of range");
    }
    else {

        return earr[iarr[i] + j];
    }
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i > 0 && j > 0) {
        int* tmpearr;
        std::ptrdiff_t* tmpiarr;
        if (i < std::get<0>(sz) && j < std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * std::get<1>(sz), j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }
            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }
        else if (i >= std::get<0>(sz) && j >= std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < std::get<0>(sz); k += 1) {
                std::copy_n(this->earr + k * std::get<1>(sz), std::get<1>(sz), tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        else if (i <= std::get<0>(sz) && j >= std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * std::get<1>(sz), std::get<1>(sz), tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        else if (i >= std::get<0>(sz) && j <= std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < std::get<0>(sz); k += 1) {
                std::copy_n(this->earr + k * std::get<1>(sz), j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }
    }
    else {
        throw std::invalid_argument("size can't be < 0");
    }
}


void MatrixS::resize(const SizeType& new_size) {
    auto i = std::get<0>(new_size);
    auto j = std::get<1>(new_size);
    if (i > 0 && j > 0) {
        int* tmpearr;
        std::ptrdiff_t* tmpiarr;
        if (i < std::get<0>(sz) && j < std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * std::get<1>(sz), j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }
        if (i >= std::get<0>(sz) && j >= std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < std::get<0>(sz); k += 1) {
                std::copy_n(this->earr + k * std::get<1>(sz), std::get<1>(sz), tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        if (i <= std::get<0>(sz) && j >= std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * std::get<1>(sz), std::get<1>(sz), tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        if (i >= std::get<0>(sz) && j <= std::get<1>(sz)) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < std::get<0>(sz); k += 1) {
                std::copy_n(this->earr + k * j, j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            std::get<0>(sz) = i;
            std::get<1>(sz) = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }
    }
    else {
        throw std::invalid_argument("size can't be < 0");
    }
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept {
    return sz;
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
    return std::get<0>(sz);
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
    return std::get<1>(sz);
}
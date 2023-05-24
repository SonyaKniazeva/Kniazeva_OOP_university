#include <matrixs/matrixs.hpp>

#include <tuple>
#include <stdexcept>
#include <vector>
#include<iostream>

MatrixS::MatrixS(const SizeType& size) {
    m_ = std::get<0>(size);
    n_ = std::get<1>(size);
    iarr = new std::ptrdiff_t[m_];
    for (std::ptrdiff_t i = 0; i < m_; i++) {
        iarr[i] = i * n_;
    }

    earr = new int[m_ * n_];
    std::fill_n(earr, m_ * n_, 0);
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) {
    m_ = m;
    n_ = n;
    iarr = new std::ptrdiff_t[m];
    for (std::ptrdiff_t i = 0; i < m; i++) {
        iarr[i] = i * n;
    }

    earr = new int[m * n];
    std::fill_n(earr, m * n, 0);
}

MatrixS::MatrixS(const MatrixS& other) {
    this->earr = new int[other.n_ * other.m_];
    this->iarr = new std::ptrdiff_t[other.m_];
    std::copy(other.earr, other.earr + other.n_ * other.m_, this->earr);
    std::copy(other.iarr, other.iarr + other.m_, this->iarr);
    this->m_ = other.m_;
    this->n_ = other.n_;

}

MatrixS& MatrixS::operator=(const MatrixS& other) {
    this->resize(other.m_, other.n_);
    std::copy(other.earr, other.earr + other.m_ * other.n_, this->earr);
    std::copy(other.iarr, other.iarr + other.m_, this->iarr);

    this->m_ = other.m_;
    this->n_ = other.n_;

    return *this;
}

int& MatrixS::at(const SizeType& elem) {
    auto i = std::get<0>(elem);
    auto j = std::get<1>(elem);
    if (i >= m_ || i < 0 || j >= n_ || j < 0) {
        throw std::out_of_range("index out of range");
    }
    else {
        return earr[iarr[i] + j];;
    }
}

const int& MatrixS::at(const SizeType& elem) const {
    auto i = std::get<0>(elem);
    auto j = std::get<1>(elem);
    std::ptrdiff_t k = 0;
    while (i != iarr[k] && !(i > iarr[k] && i < iarr[k + 1])) {
        k++;
    }
    return earr[k * n_ + j];
}

int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i >= m_ || i < 0 || j >= n_ || j < 0) { //нумерация с 0 до m_ - 1 и с 0 до n_ - 1
        throw std::out_of_range("index out of range");
    }
    else {
        std::ptrdiff_t k = 0;
        while (i != iarr[k] && !(i > iarr[k] && i < iarr[k + 1])) {
            k++;
        }
        return earr[k * n_ + j];
    }
}

const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
    if (i >= m_ || i < 0 || j >= n_ || j < 0) {
        throw std::out_of_range("index out of range");
    }
    else {
        std::ptrdiff_t k = 0;
        while (i != iarr[k] && !(i > iarr[k] && i < iarr[k + 1])) {
            k++;
        }
        return earr[k * n_ + j];
    }
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i > 0 && j > 0) {
        int* tmpearr;
        std::ptrdiff_t* tmpiarr;
        if (i < m_ && j < n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * n_, j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }
            m_ = i;
            n_ = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }
        else if (i >= m_ && j >= n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < m_; k += 1) {
                std::copy_n(this->earr + k * n_, n_, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            m_ = i;
            n_ = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        else if (i <= m_ && j >= n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * n_, n_, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            m_ = i;
            n_ = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        else if (i >= m_ && j <= n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < m_; k += 1) {
                std::copy_n(this->earr + k * n_, j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            m_ = i;
            n_ = j;

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
        if (i < m_ && j < n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * n_, j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            m_ = i;
            n_ = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }
        if (i >= m_ && j >= n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < m_; k += 1) {
                std::copy_n(this->earr + k * n_, n_, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            m_ = i;
            n_ = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        if (i <= m_ && j >= n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < i; k += 1) {
                std::copy_n(this->earr + k * n_, n_, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            m_ = i;
            n_ = j;

            delete[] this->iarr;
            this->iarr = tmpiarr;
            tmpiarr = nullptr;

            delete[] this->earr;
            this->earr = tmpearr;
            tmpearr = nullptr;
        }

        if (i >= m_ && j <= n_) {
            tmpearr = new int[i * j];
            std::fill_n(tmpearr, i * j, 0);
            for (std::ptrdiff_t k = 0; k < m_; k += 1) {
                std::copy_n(this->earr + k * j, j, tmpearr + k * j);
            }

            tmpiarr = new std::ptrdiff_t[i];
            for (std::ptrdiff_t h = 0; h < i; h++) {
                tmpiarr[h] = h * j;
            }

            m_ = i;
            n_ = j;

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
    auto tpl = std::make_tuple(m_, n_);
    const MatrixS::SizeType& sizee = std::cref(tpl);
    return sizee;
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
    return m_;
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
    return n_;
}
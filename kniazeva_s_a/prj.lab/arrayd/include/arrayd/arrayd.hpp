#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230426
#define ARRAYD_ARRAYD_HPP_20230426

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <vector>

class ArrayD {
public:
    explicit ArrayD(const std::ptrdiff_t capacity = 0);
    ArrayD(const ArrayD&);
    ArrayD& operator= (const ArrayD&);
    ~ArrayD() {
        delete[] arr;
    };

    ArrayD(std::initializer_list<double>);

    [[nodiscard]] double& operator[](const std::ptrdiff_t i);
    [[nodiscard]] const double& operator[](const std::ptrdiff_t i) const;

    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;

    void resize(const std::ptrdiff_t new_size);

    void insert(const std::ptrdiff_t i, const double value);

    void remove(const std::ptrdiff_t i);


private:
    ptrdiff_t size_ = 0;
    ptrdiff_t capacity_ = 0;
    double* arr = nullptr;
};

#endif

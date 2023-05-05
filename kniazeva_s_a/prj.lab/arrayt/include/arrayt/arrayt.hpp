#pragma once
#ifndef ARRAYT_ARRAYT_HPP_20230504
#define ARRAYT_ARRAYT_HPP_20230504

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <vector>

template<typename T>
class ArrayT {
public:
    explicit ArrayT(const std::ptrdiff_t capacity = 0);
    ArrayT(const ArrayT&);
    ArrayT& operator= (const ArrayT&);
    ~ArrayT() {
        delete[] arr;
    };

    ArrayT(std::initializer_list<T>);

    [[nodiscard]] T& operator[](const std::ptrdiff_t i);
    [[nodiscard]] const T& operator[](const std::ptrdiff_t i) const;

    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;

    void resize(const std::ptrdiff_t new_size);

    void insert(const std::ptrdiff_t i, const T value);

    void remove(const std::ptrdiff_t i);


private:
    ptrdiff_t size_ = 0;
    ptrdiff_t capacity_ = 0;
    T* arr = nullptr;
};

#endif

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


template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size) {
	if (size < 0) throw std::invalid_argument("size can't be < 0");

	if (size > 0) {
		this->size_ = size;
		arr = new T[size];
		std::fill_n(arr, size, 0);
		this->capacity_ = size;
	}
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT& other) :ArrayT(static_cast<int>(other.size_)) {
	if (other.size_ > this->size_) {
		std::copy(other.arr, other.arr + other.size_, this->arr);
		this->size_ = other.size_;
	}
	else {
		std::copy(other.arr, other.arr + other.size_, this->arr);
		this->size_ = other.size_;
	}
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& other) {
	if (other.size_ > this->size_) {
		this->resize(other.size_);
		std::copy(other.arr, other.arr + other.size_, this->arr);
		this->size_ = other.size_;
	}
	else {
		this->resize(other.size_);
		std::copy(other.arr, other.arr + other.size_, this->arr);
	}
	return *this;
}


template<typename T>
ArrayT<T>::ArrayT(std::initializer_list<T> lst) :ArrayT(static_cast<int>(lst.size())) {
	std::copy(lst.begin(), lst.end(), arr);
	this->size_ = lst.size();
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize()  const noexcept { return this->size_; }


template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t new_size) {
	if (new_size <= 0) throw std::invalid_argument("size can't be <= 0");
	T* tmparr;
	if (new_size < this->size_) {
		std::fill_n(this->arr + new_size, this->size_ - new_size, 0);
		std::cout << std::endl;
		for (int count{ 0 }; count < size_; ++count)
			std::cout << this->arr[count] << ' ';
		std::cout << std::endl;
		if (new_size <= (capacity_ / 2)) {
			tmparr = new T[new_size];
			std::copy_n(this->arr, new_size, tmparr);
			this->capacity_ = new_size;
			std::cout << std::endl;
			for (int count{ 0 }; count < size_; ++count)
				std::cout << this->arr[count] << ' ';
			std::cout << std::endl;
			delete[] this->arr;
			this->arr = tmparr;
			tmparr = nullptr;
		}
		this->size_ = new_size;
	}
	else {
		if (new_size > this->capacity_) {
			auto new_capacity = capacity_ * 2;
			if (new_size > new_capacity) {
				new_capacity = new_size;
			}
			tmparr = new T[new_size];
			std::fill_n(tmparr, new_size, 0);
			std::copy_n(this->arr, this->size_, tmparr);
			this->capacity_ = new_capacity;
			delete[] arr;
			this->arr = tmparr;
			this->size_ = new_size;
			tmparr = nullptr;
		}
	}
}

template<typename T>
void ArrayT<T>::insert(const std::ptrdiff_t index, const T value) {
	if (index < 0 || index > this->size_) throw std::out_of_range("index out of range [0,size]");
	if (this->size_ == this->capacity_) {
		this->resize(this->size_ + 1);
	}
	for (ptrdiff_t i = this->size_ - 1; i >= index; i--) {
		this->arr[i + 1] = this->arr[i];
	}
	this->arr[index] = value;
	this->size_;
}

template<typename T>
void ArrayT<T>::remove(const std::ptrdiff_t index) {
	if (index < 0 || index >= this->size_) throw std::out_of_range("index out of range [0,size)");

	for (ptrdiff_t i = index; i < this->size_; i++) {
		this->arr[i] = this->arr[i + 1];
	}
	this->resize(this->size_ - 1);
}


template<typename T>
T& ArrayT<T>::operator[](const std::ptrdiff_t index) {
	if (index < 0 || index >= this->size_) throw std::out_of_range("index out of range [0,size)");
	return this->arr[index];
}

template<typename T>
const T& ArrayT<T>::operator[](const std::ptrdiff_t index) const {
	if (index < 0 || index >= this->size_) throw std::out_of_range("index out of range [0,size)");
	return this->arr[index];
}

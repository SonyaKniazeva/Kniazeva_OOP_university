#include <arrayd/arrayd.hpp>

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <vector>

ArrayD::ArrayD(const std::ptrdiff_t size) {
	if (size < 0) throw std::invalid_argument("size can't be < 0");

	if (size > 0) {
		this->size_ = size;
		arr = new double[size];
		std::fill_n(arr, size, 0);
		this->capacity_ = size;
	}
}

ArrayD::ArrayD(const ArrayD& other) :ArrayD(static_cast<int>(other.size_)) {
	if (other.size_ > this->size_) {
		std::copy(other.arr, other.arr + other.size_, this->arr);
		this->size_ = other.size_;
	}
	else {
		std::copy(other.arr, other.arr + other.size_, this->arr);
		this->size_ = other.size_;
	}
}

ArrayD& ArrayD::operator=(const ArrayD& other) {

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


ArrayD::ArrayD(std::initializer_list<double> lst) :ArrayD(static_cast<int>(lst.size())) {
	std::copy(lst.begin(), lst.end(), arr);
	this->size_ = lst.size();
}

std::ptrdiff_t ArrayD::ssize()  const noexcept { return this->size_; }


void ArrayD::resize(const std::ptrdiff_t new_size) {
	if (new_size <= 0) throw std::invalid_argument("size can't be <= 0");
	double* tmparr;
	if (new_size < this->size_) {
		std::fill_n(this->arr + new_size, this->size_ - new_size, 0);
		std::cout << std::endl;
		for (int count{ 0 }; count < size_; ++count)
			std::cout << this->arr[count] << ' ';
		std::cout << std::endl;
		if (new_size <= (capacity_ / 2)) {
			tmparr = new double[new_size];
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
			tmparr = new double[new_size];
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

void ArrayD::insert(const std::ptrdiff_t index, const double value) {
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

void ArrayD::remove(const std::ptrdiff_t index) {
	if (index < 0 || index >= this->size_) throw std::out_of_range("index out of range [0,size)");

	for (ptrdiff_t i = index; i < this->size_; i++) {
		this->arr[i] = this->arr[i + 1];
	}
	this->resize(this->size_ - 1);
}


double& ArrayD::operator[](const std::ptrdiff_t index) {
	if (index < 0 || index >= this->size_) throw std::out_of_range("index out of range [0,size)");
	return this->arr[index];
}

const double& ArrayD::operator[](const std::ptrdiff_t index) const {
	if (index < 0 || index >= this->size_) throw std::out_of_range("index out of range [0,size)");
	return this->arr[index];
}

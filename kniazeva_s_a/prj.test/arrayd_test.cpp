#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>

TEST_CASE("constructor") {
    ArrayD arr(5);
    CHECK(arr[0] == 0);
    CHECK(arr.ssize() == 5);
    arr[0] = 1;
    arr[1] = 2;
    ArrayD arr2 = ArrayD(arr);
    CHECK(arr2.ssize() == arr.ssize());
    CHECK(arr2[0] == arr[0]);
    CHECK(arr2[1] == arr[1]);

}

TEST_CASE("initialization") {
    ArrayD arr(1);
    arr[0] = 10;
    ArrayD arr25(25);
    arr25[24] = 100;
    CHECK(arr25[24] == 100);
}

TEST_CASE("operator=") {
    ArrayD arr1 = { 99, 88 };
    ArrayD arr2 = { 11, 22, 33, 44, 55 };
    ArrayD arr3 = arr1;
    CHECK(arr3.ssize() == arr1.ssize());
    CHECK(arr3[0] == arr1[0]);
    CHECK(arr3[1] == arr1[1]);
    CHECK(arr1[0] == 99);
    CHECK(arr1[1] == 88);
    arr1 = arr2;
    CHECK(arr2.ssize() == arr1.ssize());
    CHECK(arr2[0] == arr1[0]);
    CHECK(arr2[1] == arr1[1]);
    CHECK(arr2[2] == arr1[2]);
    CHECK(arr2[3] == arr1[3]);
    CHECK(arr2[4] == arr1[4]);
    arr2 = arr3;
    CHECK(arr3.ssize() == arr2.ssize());
    CHECK(arr3[0] == arr2[0]);
    CHECK(arr3[1] == arr2[1]);
}
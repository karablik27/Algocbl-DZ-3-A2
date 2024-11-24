#include "array_generator.h"

#include <chrono>
#include <random>
#include <algorithm>

ArrayGenerator::ArrayGenerator(int max_size, int min_val, int max_val)
    : max_size_(max_size), min_val_(min_val), max_val_(max_val) {
  GenerateRandomArray();
  GenerateReverseSortedArray();
  GenerateSortedArray();
}

// Генерация случайного массива
void ArrayGenerator::GenerateRandomArray() {
  random_array.resize(max_size_);
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(min_val_, max_val_);
  std::generate(random_array.begin(), random_array.end(), [&]() { return dist(rng); });
}

// Генерация массива, отсортированного в обратном порядке
void ArrayGenerator::GenerateReverseSortedArray() {
  reverse_sorted_array.resize(max_size_);
  std::iota(reverse_sorted_array.rbegin(), reverse_sorted_array.rend(), 1);
}

// Генерация отсортированного массива
void ArrayGenerator::GenerateSortedArray() {
  almost_sorted_array.resize(max_size_);
  std::iota(almost_sorted_array.begin(), almost_sorted_array.end(), 1);
}

// Получение случайного массива заданного размера
std::vector<int> ArrayGenerator::GetRandomArray(int size) {
  size = std::min(size, max_size_);
  return std::vector<int>(random_array.begin(), random_array.begin() + size);
}

// Получение массива, отсортированного в обратном порядке, заданного размера
std::vector<int> ArrayGenerator::GetReverseSortedArray(int size) {
  size = std::min(size, max_size_);
  return std::vector<int>(reverse_sorted_array.begin(), reverse_sorted_array.begin() + size);
}

// Получение почти отсортированного массива
std::vector<int> ArrayGenerator::GetAlmostSortedArray(int size, int swaps) {
  size = std::min(size, max_size_);
  std::vector<int> subarray(almost_sorted_array.begin(), almost_sorted_array.begin() + size);

  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(0, size - 1);

  for (int i = 0; i < swaps; ++i) {
    std::swap(subarray[dist(rng)], subarray[dist(rng)]);
  }

  return subarray;
}

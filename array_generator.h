//
// Created by Верховный Маг on 24.11.2024.
//

#ifndef ALGOC__ARRAY_GENERATOR_H_
#define ALGOC__ARRAY_GENERATOR_H_

#include <vector>

class ArrayGenerator {
 public:
  ArrayGenerator(int max_size = 10000, int min_val = 0, int max_val = 6000);

  std::vector<int> GetRandomArray(int size);
  std::vector<int> GetReverseSortedArray(int size);
  std::vector<int> GetAlmostSortedArray(int size, int swaps = 10);

 private:
  int max_size_;
  int min_val_;
  int max_val_;

  std::vector<int> random_array;
  std::vector<int> reverse_sorted_array;
  std::vector<int> almost_sorted_array;

  void GenerateRandomArray();
  void GenerateReverseSortedArray();
  void GenerateSortedArray();
};
#endif //ALGOC__ARRAY_GENERATOR_H_

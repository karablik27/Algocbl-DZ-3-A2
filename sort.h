//
// Created by Верховный Маг on 24.11.2024.
//

#ifndef ALGOC__SORT_H_
#define ALGOC__SORT_H_
#include <vector>

class Sort {
 public:
  void MeasureMergeSort(const std::vector<int>& array, long long& time_ms);
  void MeasureHybridMergeInsertionSort(const std::vector<int>& array,
                                       int threshold, long long& time_ms);

 private:
  void MergeSort(std::vector<int>& array, int left, int right);
  void Merge(std::vector<int>& array, int left, int mid, int right);
  void HybridMergeInsertionSort(std::vector<int>& array, int left, int right,
                                int threshold);
  void InsertionSort(std::vector<int>& array, int left, int right);
};
#endif //ALGOC__SORT_H_

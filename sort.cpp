//
// Created by Верховный Маг on 24.11.2024.
//
#include "sort.h"

// Merge Sort: Разделение и слияние
void Sort::MergeSort(std::vector<int>& array, int left, int right) {
  if (left >= right) return;

  int mid = left + (right - left) / 2;

  MergeSort(array, left, mid);
  MergeSort(array, mid + 1, right);
  Merge(array, left, mid, right);
}

// Слияние двух отсортированных частей массива
void Sort::Merge(std::vector<int>& array, int left, int mid, int right) {
  std::vector<int> temp(right - left + 1);

  int i = left, j = mid + 1, k = 0;

  // Слияние двух частей в один временный массив
  while (i <= mid && j <= right) {
    temp[k++] = (array[i] <= array[j]) ? array[i++] : array[j++];
  }

  // Копирование оставшихся элементов
  while (i <= mid) temp[k++] = array[i++];
  while (j <= right) temp[k++] = array[j++];

  // Перенос временного массива в исходный
  std::copy(temp.begin(), temp.end(), array.begin() + left);
}

// Hybrid Merge + Insertion Sort
void Sort::HybridMergeInsertionSort(std::vector<int>& array, int left,
                                    int right, int threshold) {
  if (left >= right) return;

  if (right - left + 1 <= threshold) {
    InsertionSort(array, left, right); // Если массив маленький, используем Insertion Sort
  } else {
    int mid = left + (right - left) / 2;
    HybridMergeInsertionSort(array, left, mid, threshold);
    HybridMergeInsertionSort(array, mid + 1, right, threshold);
    Merge(array, left, mid, right);
  }
}

// Insertion Sort
void Sort::InsertionSort(std::vector<int>& array, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int key = array[i];
    int j = i - 1;

    while (j >= left && array[j] > key) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

// Измерение времени работы Merge Sort
void Sort::MeasureMergeSort(const std::vector<int>& array, long long& time_ns) {
  std::vector<int> arr = array;
  auto start = std::chrono::high_resolution_clock::now();

  MergeSort(arr, 0, arr.size() - 1);

  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
}

// Измерение времени работы Hybrid Merge + Insertion Sort
void Sort::MeasureHybridMergeInsertionSort(const std::vector<int>& array,
                                           int threshold,
                                           long long& time_ns) {
  std::vector<int> arr = array;
  auto start = std::chrono::high_resolution_clock::now();

  HybridMergeInsertionSort(arr, 0, arr.size() - 1, threshold);

  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
}

#include "array_generator.h"
#include "sort.h"

#include <fstream>
#include <vector>

void WriteResultsToFile(const std::string& file_name,
                        const std::string& header,
                        const std::vector<long long>& results) {
  std::ofstream file(file_name, std::ios::app); // Открываем файл в режиме добавления
  file << header << "\n";
  for (const auto& time : results) {
    file << time / 1000.0 << ' ';  // Переводим время в миллисекунды
  }
  file << "\n";
  file.close();
}

int main() {
  ArrayGenerator generator;
  Sort sort;

  std::vector<int> sizes;  // Размеры массивов
  for (int size = 500; size <= 10000; size += 100) {
    sizes.push_back(size);
  }

  std::vector<int> thresholds = {1000};  // Пороговые значения для гибридного алгоритма

  const std::string merge_sort_file = "merge_sort_results3.txt";
  const std::string hybrid_sort_file = "hybrid_sort_results3.txt";

  // Замеры для MERGE SORT
  std::vector<long long> random_times, reverse_times, almost_sorted_times;

  for (int size : sizes) {
    int repeat_count = 50;

    // Рандомные массивы
    long long total_time = 0;
    for (int i = 0; i < repeat_count; ++i) {
      auto array = generator.GetRandomArray(size);
      long long time;
      sort.MeasureMergeSort(array, time);
      total_time += time;
    }
    random_times.push_back(total_time / repeat_count);

    // Обратно отсортированные массивы
    total_time = 0;
    for (int i = 0; i < repeat_count; ++i) {
      auto array = generator.GetReverseSortedArray(size);
      long long time;
      sort.MeasureMergeSort(array, time);
      total_time += time;
    }
    reverse_times.push_back(total_time / repeat_count);

    // Почти отсортированные массивы
    total_time = 0;
    for (int i = 0; i < repeat_count; ++i) {
      auto array = generator.GetAlmostSortedArray(size, 10);
      long long time;
      sort.MeasureMergeSort(array, time);
      total_time += time;
    }
    almost_sorted_times.push_back(total_time / repeat_count);
  }

  WriteResultsToFile(merge_sort_file, "Рандомные массивы (мс):", random_times);
  WriteResultsToFile(merge_sort_file, "Обратно отсортированные массивы (мс):", reverse_times);
  WriteResultsToFile(merge_sort_file, "Почти отсортированные массивы (мс):", almost_sorted_times);

  // Замеры для HYBRID MERGE+INSERTION SORT
  for (int threshold : thresholds) {
    std::vector<long long> random_times_hybrid, reverse_times_hybrid, almost_sorted_times_hybrid;

    for (int size : sizes) {
      int repeat_count = 50;

      // Рандомные массивы
      long long total_time = 0;
      for (int i = 0; i < repeat_count; ++i) {
        auto array = generator.GetRandomArray(size);
        long long time;
        sort.MeasureHybridMergeInsertionSort(array, threshold, time);
        total_time += time;
      }
      random_times_hybrid.push_back(total_time / repeat_count);

      // Обратно отсортированные массивы
      total_time = 0;
      for (int i = 0; i < repeat_count; ++i) {
        auto array = generator.GetReverseSortedArray(size);
        long long time;
        sort.MeasureHybridMergeInsertionSort(array, threshold, time);
        total_time += time;
      }
      reverse_times_hybrid.push_back(total_time / repeat_count);

      // Почти отсортированные массивы
      total_time = 0;
      for (int i = 0; i < repeat_count; ++i) {
        auto array = generator.GetAlmostSortedArray(size, 10);
        long long time;
        sort.MeasureHybridMergeInsertionSort(array, threshold, time);
        total_time += time;
      }
      almost_sorted_times_hybrid.push_back(total_time / repeat_count);
    }

    WriteResultsToFile(hybrid_sort_file, "Рандомные массивы (мс):", random_times_hybrid);
    WriteResultsToFile(hybrid_sort_file, "Обратно отсортированные массивы (мс):", reverse_times_hybrid);
    WriteResultsToFile(hybrid_sort_file, "Почти отсортированные массивы (мс):", almost_sorted_times_hybrid);
  }

  return 0;
}

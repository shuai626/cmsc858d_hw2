#include "rank_support.h"
#include <chrono>
#include <stdlib.h>

using namespace std;

int experiment (int size, int capacity, int rank1_operations) {
    sdsl::bit_vector bs_(size);
    srand(time(NULL));

    int i;
    for (i = 0; i < capacity; i++) {
      int X = rand() % bs_.size();

      bs_[X]=1;
    }

    rank_support r_(&bs_);
    

    auto start = chrono::high_resolution_clock::now();
    for (i = 0; i < rank1_operations; i++) {
      // int X = rand() % SIZE + 1;
      int X = i % bs_.size() + 1;

      r_.rank1(X);
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    return duration.count();
}

int main (int argc, char **argv) {
    int i;

    int size = atoi(argv[1]);

    sdsl::bit_vector bs_(size);

    rank_support r(&bs_);

    int capacity = bs_.size()/2;
    int rank1_operations = 100;
    int trials = 100;

    float avg = 0;

    for (i = 0; i < trials; i++) {
      avg += experiment(size, capacity, rank1_operations);
    }
    avg /= trials;
    cout << "Average time (in microseconds): " << avg << endl;
    cout << "Overhead (in bits): " << r.overhead() << endl;

    return 0;
}
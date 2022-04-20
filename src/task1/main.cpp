#include <sdsl/suffix_arrays.hpp> 
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/archives/binary.hpp>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

// Return index i such that all e in sa[:i] have e < x, and all e in a[i:] have e >= x.
int bisect_left(string p, string t, sdsl::csa_bitcompressed<>* sa) {
  int l = 0;
  int r = sa->size();

  while (l < r) {
    int c = floor((l+r)/2);

    bool pgt = false;

    int x = 0;

    while (x < p.length() && (*sa)[c]+x < t.length()) {
      if (p[x] > t[(*sa)[c]+x]) {
        pgt = true;
        break;
      }
      else if (p[x] < t[(*sa)[c]+x]) {
        break;
      }

      x += 1;
    }

    if (pgt) {
      l = c + 1;
    }
    else {
      r = c;
    }
  }
  return l;
}

// Return index i such that all e in sa[:i] have e <= p, and all e in sa[i:] have e > x
int bisect_right(string p, string t, sdsl::csa_bitcompressed<>* sa) {
  int l = 0;
  int r = sa->size();

  while (l < r) {
    int c = floor((l+r)/2);

    bool plt = false;

    int x = 0;

    while (x < p.length() && (*sa)[c]+x < t.length()) {
      if (p[x] < t[(*sa)[c]+x]) {
        plt = true;
        break;
      }
      else if (p[x] > t[(*sa)[c]+x]) {
        break;
      }

      x += 1;
    }

    if (plt) {
      r = c;
    }
    else {
      l = c+1;
    }
  }
  return l;
}

int binary_search(int i, int j, string p, string t, sdsl::csa_bitcompressed<>* sa) {
  int l = i;
  int r = j;

  // Binary search algorithm
  while (true) {
    int c = floor ((l+r)/2);

    // Determine whether p < T[sa[c]:] starting from LHS
    bool plt = true;

    int x = 0;

    while (x < p.length() && (*sa)[c]+x < t.length()) {
      if (p[x] < t[(*sa)[c]+x]) {
        break;
      }
      else if (p[x] > t[(*sa)[c]+x]) {
        plt = false;
        break;
      }

      x += 1;
    }

    if (plt) {
      if (c == l + 1) {
        return c;
      }
      r = c;
    }
    else {
      if (c == r - 1) {
        return r;
      }
      l = c;
    }
  }
}

int build_sa(int k, string in, string out) {
  // Given FASTA file, read the entire file into an in-memory string
  ifstream f(in);
  string line;
  string genome = "";

  while (!f.eof()) {
    getline(f,line);

    if (line.length() == 0 || line[0] == '>')
      continue;
    else
      genome += line;
  }

  // Convert all characters to upper case
  for (auto & c: genome) c = toupper(c);

  // Convert n/N nucleotides pseudorandomly to A C T G
  for (auto & c: genome) {
    if (c == 'N') {
      int i = rand() % 4;

      if (i == 0) c = 'A';
      else if (i == 1) c = 'C';
      else if (i == 2) c = 'T';
      else if (i == 3) c = 'G';
    }
  }
  genome += "$";

  // Build the suffix array
  sdsl::csa_bitcompressed<> sa;

  sdsl::construct_im(sa, genome, 1);

  // Build secondary hash table index (when requested)
  map<string, tuple<int, int>> index;
  if (k) {
    // For every k-mer in genome... 
    for (int i = 0; i < genome.length() - k; i++) {
      string kmer = genome.substr(i, k);

      if ( index.find(kmer) == index.end() ) {
        // Find searchable interval range and store result in index map
        int left = bisect_left(kmer, genome, &sa);
        int right = bisect_right(kmer, genome, &sa);

        tuple<int,int> x {left, right};

        index.insert( { kmer, x } );
      }
    }
  }

  // Write the string and suffix array (and secondary index) to binary file
  std::ofstream os(out, std::ios::binary);
  cereal::BinaryOutputArchive archive( os );
  archive( genome, index);
  store_to_file(sa, out+".sa");

  return 0;
}

int main (int argc, char **argv) {
  string in, out;
  int k = 0;

  if (argc == 5) {
    if (!strcmp(argv[1], "--preftab")) {
      k = stoi(argv[2]);
      in = argv[3];
      out = argv[4];

      return build_sa(k, in, out);
    }

  } 
  else if (argc == 3) {
    in = argv[1];
    out = argv[2];

    return build_sa(k, in, out);
  } 

  cout << "buildsa: <--preftab k> <reference> <output>" << endl; 
  return -1;
}
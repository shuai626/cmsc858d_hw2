#include "utils.h"

using namespace std;

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

  auto start = chrono::high_resolution_clock::now();

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
        int left = bisect_left(0, sa.size(), kmer, genome, &sa, false, 0);
        int right = bisect_right(0, sa.size(), kmer, genome, &sa, false, 0);

        tuple<int,int> x {left, right};

        index.insert( { kmer, x } );
      }
    }
  }

  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

  // Write the string and suffix array (and secondary index) to binary file
  ofstream os(out+".data", ios::binary);
  cereal::BinaryOutputArchive archive( os );
  archive( genome, k, index);
  store_to_file(sa, out+".sa");

  cout << "Duration: " << duration.count() << " microseconds" << endl;

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
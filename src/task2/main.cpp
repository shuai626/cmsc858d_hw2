#include "utils.h"

using namespace std;

int query_sa(string in, string qs, string out, bool simpaccel) {
  // Load the suffix array
  sdsl::csa_bitcompressed<> sa;
  sdsl::load_from_file(sa, in+".sa");

  // Load genome and prefix table
  string genome;
  int k;
  map<string, tuple<int, int>> index;

  ifstream is(in+".data", ios::binary);
  cereal::BinaryInputArchive archive( is );
  archive( genome, k, index );

  // Read each query from queries
  ifstream f(qs);
  ofstream res(out);
  string line;

  while (!f.eof()) {
    getline(f, line);

    // For each query
    if (line[0] == '>') {
      string p;
      getline(f, p);

      string pref = p.substr(0, k);

      map<string, tuple<int, int>>::iterator it;

      it = index.find(pref);

      int i = 0;
      int j = 0;
      // If prefix exists in table, set starting interval to [i, j)
      if ( it != index.end() ) {
        i = get<0>(it->second);
        j = get<1>(it->second);
      }

      // Find searchable interval range for query
      int left = bisect_left(i, j, p, genome, &sa, simpaccel);
      int right = bisect_right(i, j, p, genome, &sa, simpaccel);

      // Write output to a new file
      res << line.substr(1) << " " << (right - left);

      for (int i = left; i < right; i++) {
        res << " " << sa[i];
      }
      res << endl;
    }
  }

  return 0;
}

int main (int argc, char **argv) {
  string in, qs, out;

  if (argc == 5) {
    in = argv[1];
    qs = argv[2];
    out = argv[4];

    if (!strcmp(argv[3], "naive")) {
      return query_sa(in, qs, out, false);
    }
    else if (!strcmp(argv[3], "simpaccel")) {
      return query_sa(in, qs, out, true);
    }
  } 

  cout << "querysa: <sa file prefix> <queries file> <naive/simpaccel> <output>" << endl; 
  return -1;
}
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
#include <chrono>

using namespace std;

// Return index i such that all e in sa[:i] have e < x, and all e in a[i:] have e >= x.
int bisect_left(int i, int j, string p, string t, sdsl::csa_bitcompressed<>* sa, bool simpaccel, int k) {
  int l = i;
  int r = j;
  int lcp_lp = k;
  int lcp_rp = k;

  while (l < r) {
    int c = floor((l+r)/2);

    bool pgt = false;

    int x = 0;
    if (simpaccel) {
      x = min(lcp_lp, lcp_rp);
    }

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
      lcp_lp = x;
    }
    else {
      r = c;
      lcp_rp = x;
    }
  }
  return l;
}

// Return index i such that all e in sa[:i] have e <= p, and all e in sa[i:] have e > x
int bisect_right(int i, int j, string p, string t, sdsl::csa_bitcompressed<>* sa, bool simpaccel, int k) {
  int l = i;
  int r = j;
  int lcp_lp = k;
  int lcp_rp = k;

  while (l < r) {
    int c = floor((l+r)/2);

    bool plt = false;

    int x = 0;
    if (simpaccel) {
      x = min(lcp_lp, lcp_rp);
    }

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
      lcp_rp = x;
    }
    else {
      l = c+1;
      lcp_lp = x;
    }
  }
  return l;
}

int binary_search(int i, int j, string p, string t, sdsl::csa_bitcompressed<>* sa, bool simpaccel) {
  int l = i;
  int r = j;
  int lcp_lp = 0;
  int lcp_rp = 0;

  // Binary search algorithm
  while (true) {
    int c = floor ((l+r)/2);

    // Determine whether p < T[sa[c]:] starting from LHS
    bool plt = true;

    int x = 0;
    if (simpaccel) {
      x = min(lcp_lp, lcp_rp);
    }

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
      lcp_rp = x;  
    }
    else {
      if (c == r - 1) {
        return r;
      }
      l = c;
      lcp_lp = x;
    }
  }
}
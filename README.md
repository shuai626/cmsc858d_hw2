# Intro
The following full text indexing is written in C++. It depends on `cereal` for binary serialization and `sdsl-lite` for compressed suffix array implementations.

The specification for these tasks inside the `src` directory be [here](https://rob-p.github.io/CMSC858D_S22/assignments/02_suffix_arrays)

# Resources
In creating `buildsa` and `querysa`, the following resources were consulted.

1. [sdsl: Tutorial of how to use `sdsl::csa_bitcompressed](http://simongog.github.io/assets/data/sdsl-slides/tutorial#33)

2. [C++: Ignore lines of an ifstream](http://www.cplusplus.com/forum/beginner/86013/)

3. [C++: Convert all characters in a string to uppercase](https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case)

4. [cereal: Tutorial of how to serialize data into binary files](https://github.com/USCiLab/cereal)

5. [Reference slide 1 for Suffix Array Full Text Indexing](https://rob-p.github.io/CMSC858D_S22/static_files/presentations/CMSC858D_S22_11.pdf)

6. [Reference slide 2 for Suffix Array Full Text Indexing](http://www.biocomp.unibo.it/piero/P4B/2014-2015/slides/sarray.pdf)

7. [Reference slide 3 for Suffix Array Full Text Indexing](https://rob-p.github.io/CSE549F17/lectures/Lec05.pdf)

8. [Python source code for bisect_left and bisect_right](https://svn.python.org/projects/python/branches/pep-0384/Lib/bisect.py)
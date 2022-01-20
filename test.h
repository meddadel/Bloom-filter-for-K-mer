#ifndef TEST_H    // To make sure you don't declare the function more than once by including the header multiple times.

#include <iostream>
#include <fstream>


using std::string;
char  nexDnaChar(string file);
int encode(char c);
int encodeR(char c);
uint64_t encodeK(string Kmer);
uint64_t encodeKR(string Kmer);
uint64_t encodeKPlus(string Kmer,char c);

#endif
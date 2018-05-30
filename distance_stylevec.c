//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.



// This is based on Mikolov's word2vec (https://code.google.com/archive/p/word2vec/, https://github.com/tmikolov/word2vec).
// The modified points from original `word2vec/distance.c` are as follows:
//  - Extended to show the results of word vector, style vector, and syntactic/semantic vector respectively.
//
// Reina Akama @ 2018



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

const long long max_size = 2000;         // max length of strings
const long long N = 15;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

int ArgPos(char *str, int argc, char **argv) {
  int a;
  for (a = 1; a < argc; a++) if (!strcmp(str, argv[a])) {
    if (a == argc - 1) {
      printf("Argument missing for %s\n", str);
      exit(1);
    }
    return a;
  }
  return -1;
}


int main(int argc, char **argv) {
  // remove some unused variables
  // add some variables for stylistic and syntactic/semantic vectors
  FILE *f;
  char st1[max_size];
  char *bestw[N];
  char file_name[max_size], st[100][max_size];
  float dist, len, len1, len2, bestd[N], vec[max_size];
  long long words, size, a, b, c, d, cn, bi[100];
  long long sizes = -1, sized;
  float *M, *M1, *M2;
  char *vocab;
  // usage
  if (argc < 2) {
    printf("Usage:\n");
    printf("./distance_stylevec -load vec.bin\n");
    printf("\nOptions:\n");
    printf("\t-load <file>\n");
    printf("\t\t<file> contains word projections in the BINARY FORMAT\n");
    printf("\t-d <int>\n");
    printf("\t\tSet size of style vectors; default is half size of the whole vector\n\n");
    return 0;
  }
  int argi;
  if ((argi = ArgPos((char *)"-load", argc, argv)) > 0) strcpy(file_name, argv[argi + 1]);
  if ((argi = ArgPos((char *)"-d", argc, argv)) > 0) sizes = atoi(argv[argi + 1]);

  f = fopen(file_name, "rb");
  if (f == NULL) {
    printf("Input file not found\n");
    return -1;
  }
  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);

  /* size of stylistic (sizes) and syntactic/semantic (sized) vector */
  if (sizes == -1){
      sizes = size / 2;
  }
  sized = size - sizes;

  vocab = (char *)malloc((long long)words * max_w * sizeof(char));
  for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));
  M = (float *)malloc((long long)words * (long long)size * sizeof(float));
  M1 = (float *)malloc((long long)words * (long long)sizes * sizeof(float));        //stylistic
  M2 = (float *)malloc((long long)words * (long long)sized * sizeof(float));        //syntactic/semantic
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;
  }
  for (b = 0; b < words; b++) {
    a = 0;
    while (1) {
      vocab[b * max_w + a] = fgetc(f);
      if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
      if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
    }
    vocab[b * max_w + a] = 0;
    for (a = 0; a < size; a++){
        fread(&M[a + b * size], sizeof(float), 1, f);
        if (a < sizes) M1[a + b * sizes] = M[a + b * size];
        else M2[(a - sizes) + b * sized] = M[a + b * size];
    }

    len = 0;
    len1 = 0;   // stylistic
    len2 = 0;   // syntactic/semantic
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    for (a = 0; a < sizes; a++) len1 += M1[a + b * sizes] * M1[a + b * sizes];   // stylistic
    for (a = 0; a < sized; a++) len2 += M2[a + b * sized] * M2[a + b * sized];   // syntactic/semantic
    len = sqrt(len);
    len1 = sqrt(len1);  // stylistic
    len2 = sqrt(len2);  // syntactic/semantic
    for (a = 0; a < size; a++) M[a + b * size] /= len;
    for (a = 0; a < sizes; a++) M1[a + b * sizes] /= len1;  // stylistic
    for (a = 0; a < sized; a++) M2[a + b * sized] /= len2;  // syntactic/semantic
  }
  fclose(f);

  while (1) {
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    printf("Enter word or sentence (EXIT to break): ");
    a = 0;
    while (1) {
      st1[a] = fgetc(stdin);
      if ((st1[a] == '\n') || (a >= max_size - 1)) {
        st1[a] = 0;
        break;
      }
      a++;
    }
    if (!strcmp(st1, "EXIT")) break;
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
      st[cn][b] = st1[c];
      b++;
      c++;
      st[cn][b] = 0;
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {
        cn++;
        b = 0;
        c++;
      }
    }
    cn++;
    for (a = 0; a < cn; a++) {
      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
      if (b == words) b = -1;
      bi[a] = b;
      printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
      if (b == -1) {
        printf("Out of dictionary word!\n");
        break;
      }
    }
    if (b == -1) continue;

    /* word vectors */
    printf("\ndim[0, %lld)                                 Word       Cosine distance\n------------------------------------------------------------------------\n", size);
    for (a = 0; a < size; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
      if (bi[b] == -1) continue;
      for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
    }
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    for (a = 0; a < size; a++) vec[a] /= len;

    for (a = 0; a < N; a++) bestd[a] = -1;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
      a = 0;
      for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
      if (a == 1) continue;
      dist = 0;
      for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
      for (a = 0; a < N; a++) {
        if (dist > bestd[a]) {
          for (d = N - 1; d > a; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[a] = dist;
          strcpy(bestw[a], &vocab[c * max_w]);
          break;
        }
      }
    }
    for (a = 0; a < N; a++) printf("%50s\t\t%f (%llu)\n", bestw[a], bestd[a], a+1);


    /* stylistic vectors */
    printf("\ndim[0, %lld) for Style                       Word       Cosine distance\n------------------------------------------------------------------------\n", sizes);
    for (a = 0; a < sizes; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
      if (bi[b] == -1) continue;
      for (a = 0; a < sizes; a++) vec[a] += M1[a + bi[b] * sizes];
    }
    len1 = 0;
    for (a = 0; a < sizes; a++) len1 += vec[a] * vec[a];
    len1 = sqrt(len1);
    for (a = 0; a < sizes; a++) vec[a] /= len1;
    for (a = 0; a < N; a++) bestd[a] = -1;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
      a = 0;
      for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
      if (a == 1) continue;
      dist = 0;
      for (a = 0; a < sizes; a++) dist += vec[a] * M1[a + c * sizes];
      for (a = 0; a < N; a++) {
        if (dist > bestd[a]) {
          for (d = N - 1; d > a; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[a] = dist;
          strcpy(bestw[a], &vocab[c * max_w]);
          break;
        }
      }
    }
    for (a = 0; a < N; a++) printf("%50s\t\t%f (%llu)\n", bestw[a], bestd[a], a+1);


    /* syntactic/semantic vectors */
    printf("\ndim[%lld, %lld) for Syntactic/semantic       Word       Cosine distance\n------------------------------------------------------------------------\n", sizes, size);
    for (a = 0; a < sized; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
      if (bi[b] == -1) continue;
      for (a = 0; a < sized; a++) vec[a] += M2[a + bi[b] * sized];
    }
    len2 = 0;
    for (a = 0; a < sized; a++) len2 += vec[a] * vec[a];
    len2 = sqrt(len2);
    for (a = 0; a < sized; a++) vec[a] /= len2;
    for (a = 0; a < N; a++) bestd[a] = -1;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
      a = 0;
      for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
      if (a == 1) continue;
      dist = 0;
      for (a = 0; a < sized; a++) dist += vec[a] * M2[a + c * sized];
      for (a = 0; a < N; a++) {
        if (dist > bestd[a]) {
          for (d = N - 1; d > a; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[a] = dist;
          strcpy(bestw[a], &vocab[c * max_w]);
          break;
        }
      }
    }
    for (a = 0; a < N; a++) printf("%50s\t\t%f (%llu)\n", bestw[a], bestd[a], a+1);
  }
  return 0;
}

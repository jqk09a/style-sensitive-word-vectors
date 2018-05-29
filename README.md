# Style-sensitive Word Vectors
Style-sensitive word vectors, which are proposed on our paper "Unsupervised Learning of Style-sensitive Word Vectors", represent stylistic similarity of words.
Our paper introduced the notion of stylistic similarity and proposed a method to model stylistic similarity via a purely unsupervised manner without employing predefined stylistic classes/dimensions. The project page for this work is [here](https://jqk09a.github.io/style-sensitive-word-vectors/).

This repository contains code for learning style-sensitive word vectors and analyzing them.


## Note
This is based on Mikolov's word2vec: [google code](https://code.google.com/archive/p/word2vec/), [github](https://github.com/tmikolov/word2vec).

The modified points from original word2vec are as follows:
- Learning
    - Learning style-sensitive word vectors separately from the syntactic/semantic-sensitive word vectors.
    - The vector consists of two parts (style and syntactic/semantic vector) and they are updated separately based on our sampling strategy.
    - Unimplemented the skip-gram and the hierarchical softmax.
    - Added some options for arguments.
    - Added some comments to make it easier to understand.
- Analyzing
    - Extended to show the results of word vector, style vector, and syntactic/semantic vector respectively.


Reina Akama @ 2018


## How to run
Preparation:
```
$ git clone https://github.com/jqk09a/style-sensitive-word-vectors.git
$ cd style-sensitive-word-vectors
$ gcc word2stylevec.c -o word2stylevec -lm -pthread -O3 -march=native -Wall -Wextra -funroll-loops -Wno-unused-result
$ gcc distance_stylevec.c -o distance_stylevec -lm -pthread -O3 -march=native -Wall -Wextra -funroll-loops -Wno-unused-result
```

To learn:
```
$ ./stylisticword2vec -train data.txt -output vec.bin
```
- `data.txt` requires being a text file and being formatted that 1 line has 1 utterance.

To analyze:
```
$ ./distance_stylevec -load vec.bin
```
- Only binary files are available for `vec.bin`.



To show help:
```
$ ./stylisticword2vec
```
```
$ ./distance_stylevec
```


## Reference
If you use anything in this repository, please cite:

Reina Akama, Kento Watanabe, Sho Yokoi, Sosuke Kobayashi and Kentaro Inui. **Unsupervised Learning of Style-sensitive Word Vectors**. *Proceedings of the 56th Annual Meeting of the Association for Computational Linguistics*, July. 2018.

```
@InProceedings{akama2018stylevec,
  title={Unsupervised Learning of Style-sensitive Word Vectors},
  author={Reina Akama and Kento Watanabe and Sho Yokoi and Sosuke Kobayashi and Kentaro Inui},
  booktitle={Proceedings of the 56th Annual Meeting of the Association for Computational Linguistics},
  year={2018}
}
```

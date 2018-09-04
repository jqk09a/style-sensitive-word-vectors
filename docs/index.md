---
title: Style-sensitive Word Vectors
layout: default
---

# About
This is the project page for our paper titled **"Unsupervised Learning of Style-sensitive Word Vectors"** at ACL2018.

<!-- > We changed the title of this paper at the time of camera-ready submission. [The official website](http://acl2018.org/programme/papers/) has our previous title, "Learning Style-sensitive Word Vectors from Stylistically Consistent Utterances". -->

<!-- # Research
Style-sensitive word vectors, which are proposed on our paper "Unsupervised Learning of Style-sensitive Word Vectors", represent stylistic similarity of words. Our paper introduced the notion of stylistic similarity and proposed a method to model stylistic similarity via a purely unsupervised manner without employing predefined stylistic classes/dimensions.

<center>
![space]({{ site.url }}/docs/assets/figs/space.png)
</center>

The contributions of the paper are as follows.
- We propose a novel **architecture** that acquires style-sensitive word vectors in an unsupervised manner.<br>
- We construct a novel **dataset** for style, which consists of pairs of style-sensitive words with each pair scored according to its stylistic similarity.<br>
- We **demonstrate** that our word vectors capture the stylistic similarity between two words successfully.


### Architecture
Our key idea is to extend the continuous bag of words (CBOW) model by distinguishing nearby contexts and wider contexts under the intuitive and reasonable assumption that a style persists throughout every single utterance in a dialog.
- simple な update strategy により
Vectors yw and y˜w indicate the syntactic/semantic-sensitive part of vw and v˜w respectively. For training, when the context words are near the target word, we update both the style-sensitive vectors and the syntactic/semantic-sensitive vectors. Conversely, when the context words are far from the target word, we only update the style-sensitive vectors. The following figure shows the overview of our model.

- mikolov word2vec のシンプルな拡張により，2種類の類似性を分離して捕捉する単語ベクトルを構築するモデル．
- 獲得するベクトルは2種類のベクトルとして利用可能．

### Dataset
- 提案したスタイルベクトルの性能を確かめるための定量評価指標：stylistic word similarity task を提案．
- そのための評価データセットをクラウドソーシングにより作成した．399ペア，5段階のスコアリング．

### Demonstration
- word2vec・提案意味ベクトル・提案スタイルベクトルの定量評価結果（統語情報評価いる？）
- 提案意味ベクトル・提案スタイルベクトルの空間top5？3？


In this paper, our experiment demonstrated that our method leads word vectors to distinguish the stylistic aspect and other semantic or syntactic aspects.<br>

The following table shows the top similar words for the style-sensitive and syntactic/semantic vectors learned with the proposed model.


<center>
![sim1]({{ site.url }}/docs/assets/figs/sim1.png)
</center>

<center>
![sim2]({{ site.url }}/docs/assets/figs/sim2.png)
</center>

<center>
![sim3]({{ site.url }}/docs/assets/figs/sim3.png)
</center>

<center>
![sim4]({{ site.url }}/docs/assets/figs/sim4.png)
</center> -->

<!--
<table align="center">
  <tr><th align="center">Header A</th><th align="center">Header B</th><th align="center">Header C</th></tr>
  <tr><td>Content a1</td><td>Content b1</td><td>Content c1</td></tr>
  <tr><td>Content a2</td><td>Content b2</td><td>Content c2</td></tr>
  <tr><td>Content a3</td><td>Content b3</td><td>Content c3</td></tr>
</table>


<center>
|hoge|hoge|hoge|
|:---:|:---:|:---:|
|a|b|c|
|a|b|c|
</center>
 -->

# Code
Our training script is available on [here](https://github.com/jqk09a/style-sensitive-word-vectors). <br>
This repository contains code for learning style-sensitive word vectors and analyzing them.

# Data
Our dataset is available on [here](). <br>
It is the evaluation dataset for stylistic word similarity task, which we proposed.

# Reference
If you need, we would appreciate citations to the following paper:

Reina Akama, Kento Watanabe, Sho Yokoi, Sosuke Kobayashi and Kentaro Inui. **Unsupervised Learning of Style-sensitive Word Vectors.** Proceedings of *the 56th Annual Meeting of the Association for Computational Linguistics*, July. 2018.

```
@InProceedings{akama2018stylevec,
  title={Unsupervised Learning of Style-sensitive Word Vectors},
  author={Reina Akama and Kento Watanabe and Sho Yokoi and Sosuke Kobayashi and Kentaro Inui},
  booktitle={Proceedings of the 56th Annual Meeting of the Association for Computational Linguistics},
  year={2018}
}
```

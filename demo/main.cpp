#include "glove.h"

int main(int argc, char **argv) {
  const char* corpus = "text8";
  const char* vocab = "vocab.txt";
  const char* cooccurence = "cooccurence.bin";
  const char* cooccurenceShuf = "cooccurence.shuf.bin";
  const char* gradsq = "gradsq";
  const char* save = "vectors";

  VocabCountArgs vArgs;
  createVocabCountArgs(&vArgs);
  vArgs.verbose = 2;
  vArgs.minCount = 5;
  vocabCount(&vArgs, corpus, (char*)vocab);

  CooccurArgs cArgs;
  createCooccurArgs(&cArgs);
  cArgs.verbose = 2;
  cArgs.memory = 24.f;  // if you don't have 32 GB of RAM, you might want to change this
  cooccur(&cArgs, corpus, vocab, (char*)cooccurence);

  ShuffleArgs sArgs;
  createShuffleArgs(&sArgs);
  sArgs.verbose = 2;
  shuffle(&sArgs, cooccurence, (char*)cooccurenceShuf);

  GloveArgs gArgs;
  createGloveArgs(&gArgs);
  gArgs.verbose = 2;
  gArgs.binary = 2;
  gArgs.threads = 12; // if you don't have 12 logical cores, you might want to change this
  gArgs.xMax = 10;
  gArgs.iter = 15;
  glove(&gArgs, cooccurenceShuf, vocab, (char*)save, (char*)gradsq);

  return 0;
}

#include "glove.h"

int main(int argc, char **argv) {
  VocabCountArgs vArgs;
  createVocabCountArgs(&vArgs);
  vArgs.verbose = 2;
  vArgs.minCount = 5;
  vocabCount(&vArgs);

  CooccurArgs cArgs;
  createCooccurArgs(&cArgs);
  cArgs.verbose = 2;
  cArgs.memory = 16.f;
  cooccur(&cArgs);

  ShuffleArgs sArgs;
  createShuffleArgs(&sArgs);
  sArgs.verbose = 2;
  shuffle(&sArgs);

  GloveArgs gArgs;
  createGloveArgs(&gArgs);
  gArgs.verbose = 2;
  gArgs.binary = 2;
  gArgs.threads = 12;
  gArgs.xMax = 10;
  glove(&gArgs);

  return 0;
}
//
//  Copyright (c) 2016 Galen Cochrane
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
//

#ifndef GLOVE_H_H
#define GLOVE_H_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * cooccur
 * Constructs word-word cooccurrence statistics from a corpus. The user should supply a vocabulary file, as produced by
 * `vocabCount.` Arguments:
 *
 * 	verbose <int>
 *		Set verbosity: 0 (default), 1, or 2
 *	symmetric <int>
 *		If <int> = 0, only use left context; if <int> = 1 (default), use left and right
 *	windowSize <int>
 *		Number of context words to the left (and to the right, if symmetric = 1); default 15
 *	vocabFile <char*>
 *		File containing vocabulary (truncated unigram counts, produced by 'vocabCount'); default vocab.txt
 *	memory <float>
 *		Soft limit for memory consumption, in GB -- based on simple heuristic, so not extremely accurate; default 4.0
 *	maxProduct <int>
 *		Limit the size of dense cooccurrence array by specifying the max product <int> of the frequency counts of the two
 *		cooccurring words. This value overrides that which is automatically produced by '-memory'. Typically only needs
 *		adjustment for use with very large corpora. Ignored if <= 0; default -1
 *	overflowLength <int>
 *		Limit to length <int> the sparse overflow array, which buffers cooccurrence data that does not fit in the dense
 *		array, before writing to disk. This value overrides that which is automatically produced by '-memory'. Typically
 *		only needs adjustment for use with very large corpora; Ignored if <= 0; default -1
 *	overflowFile <char*>
 *		Filename, excluding extension, for temporary files; default overflow
 *
 * Use createCooccurArgs to get a default-valued set of arguments for the cooccur call.
 */
typedef struct _CooccurArgs {
    int verbose, symmetric, windowSize;
    char *vocabFile;
    float memory;
    int maxProduct, overflowLength;
    char *overflowFile;
} CooccurArgs;
int createCooccurArgs(CooccurArgs* emptyArgs);
int cooccur(const CooccurArgs* args);

/**
 * glove
 * Train the GloVe model on the specified cooccurrence data, which typically will be the output of the `shuffle` tool.
 * The user should supply a vocabulary file, as given by `vocab_count.` Arguments:
 *
 * 	verbose <int>
 *		Set verbosity: 0 (default), 1, or 2
 *	vectorSize <int>
 *		Dimension of word vector representations (excluding bias term); default 50
 *	threads <int>
 *		Number of threads; default 8
 *	iter <int>
 *		Number of training iterations; default 25
 *	eta <float>
 *		Initial learning rate; default 0.05
 *	alpha <float>
 *		Parameter in exponent of weighting function; default 0.75
 *	xMax <float>
 *		Parameter specifying cutoff in weighting function; default 100.0
 *	binary <int>
 *		Save output in binary format (0: text, 1: binary, 2: both); default 0
 *	model <int>
 *		Model for word vector output (for text output only); default 2
 *		   0: output all data, for both word and context word vectors, including bias terms
 *		   1: output word vectors, excluding bias terms
 *		   2: output word vectors + context word vectors, excluding bias terms
 *	inputFile <char*>
 *		Binary input file of shuffled cooccurrence data (produced by 'cooccur' and 'shuffle'); default
 *		cooccurrence.shuf.bin
 *	vocabFile <char*>
 *		File containing vocabulary (truncated unigram counts, produced by 'vocab_count'); default vocab.txt
 *	saveFile <char*>
 *		Filename, excluding extension, for word vector output; default vectors
 *	gradsqFile <char*>
 *		Filename, excluding extension, for squared gradient output; ignored if saveGradsq == 0; default gradsq
 *	saveGradsq <int>
 *		Save accumulated squared gradients; default 0 (off);
 *	checkpointEvery <int>
 *		Checkpoint a  model every <int> iterations; default 0 (off)
 *
 * Use createGloveArgs to get a default-valued set of arguments for the glove call.
 */
typedef struct _GloveArgs {
    int verbose, vectorSize, threads, iter;
    float eta, alpha, xMax;
    int binary, model;
    char *inputFile, *vocabFile, *saveFile, *gradsqFile;
    int saveGradsq, checkpointEvery;
} GloveArgs;
int createGloveArgs(GloveArgs* emptyArgs);
int glove(const GloveArgs* args);

/**
 * shuffle
 * Shuffles the binary file of cooccurrence statistics produced by `cooccur`. For large files, the file is automatically
 * split into chunks, each of which is shuffled and stored on disk before being merged and shuffled togther. Arguments:
 *
 * 	verbose <int>
 *		Set verbosity: 0 (default), 1, or 2
 *	memory <float>
 *		Soft limit for memory consumption, in GB; default 4.0
 *	arraySize <int>
 *		Limit to length <int> the buffer which stores chunks of data to shuffle before writing to disk.
 *		This value overrides that which is automatically produced by '-memory'; Ignored if <= 0; default -1
 *	tempFile <char*>
 *		Filename, excluding extension, for temporary files; default temp_shuffle
 *
 * Use createShuffleArgs to get a default-valued set of arguments for the shuffle call.
 */
typedef struct _ShuffleArgs {
    int verbose;
    float memory;
    int arraySize;
    char* tempFile;
} ShuffleArgs;
int createShuffleArgs(ShuffleArgs* emptyArgs);
int shuffle(const ShuffleArgs* args);

/**
 * vocabCount
 * Constructs unigram counts from a corpus, and optionally thresholds the resulting vocabulary based on total vocabulary
 * size or minimum frequency count. Arguments:
 *
 * 	verbose <int>
 *		Set verbosity: 0 (default), 1, or 2
 *	maxVocab <int>
 *		Upper bound on vocabulary size, i.e. keep the <int> most frequent words. The minimum frequency words are randomly
 *		sampled so as to obtain an even distribution over the alphabet; Ignored if <= 0; default -1
 *	minCount <int>
 *		Lower limit such that words which occur fewer than <int> times are discarded; if < 1 defaults to 1; default 1
 *
 * Use createVocabCountArgs to get a default-valued set of arguments for the vocabCount call.
 */
typedef struct _VocabCountArgs {
    int verbose, maxVocab, minCount;
} VocabCountArgs;
int createVocabCountArgs(VocabCountArgs* emptyArgs);
int vocabCount(const VocabCountArgs* args);

#ifdef __cplusplus
}
#endif

#endif //GLOVE_H_H

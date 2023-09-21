#ifndef HASH_H_
#define HASH_H_

#include <math.h>
#include <assert.h>

/**
 * @brief Contains polynomial hash informations
 */
struct Hash {
    static const unsigned int COEFF = 257;
    static const unsigned long long MOD = 1000000000;

    unsigned long long coeff_pow_len = 1;
    unsigned long long hash = 0;

    size_t elem_size = 0;
};

/**
 * @brief Creates hash for empty stack
 *
 * @param elem_size stack element sizeof()
 * @return Hash
 */
Hash hash_init(size_t elem_size);

/**
 * @brief Calculates new hash by pushing one element
 *
 * @param hash
 * @param elem pushed element
 */
void hash_push(Hash* hash, const void* elem);

/**
 * @brief Calculates new hash from stack
 *
 * @param hash
 * @param data stack array
 * @param len
 */
void hash_create(Hash* hash, const void* data, const size_t len);

#endif

#include "hash.h"

Hash hash_init(size_t elem_size) {
    Hash hash = {};
    hash.elem_size = elem_size;
    return hash;
}

void hash_push(Hash* hash, const void* elem) {
    for (size_t i = 0; i < hash->elem_size; i++) {
        hash->hash = (hash->hash + *((const char*)elem + i) * hash->coeff_pow_len) % hash->MOD;
        hash->coeff_pow_len = (hash->coeff_pow_len * hash->COEFF) % hash->MOD;
    }
}

void hash_create(Hash* hash, const void* data, size_t len) {
    *hash = hash_init(hash->elem_size);

    for (size_t i = 0; i < hash->elem_size * len; i++) {
        hash->hash = (hash->hash + *((const char*)data + i) * hash->coeff_pow_len) % hash->MOD;
        hash->coeff_pow_len = (hash->coeff_pow_len * hash->COEFF) % hash->MOD;
    }
}

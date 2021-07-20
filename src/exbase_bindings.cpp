#include "word_id_hash.hpp"

#include <pybind11/pybind11.h>

std::uint64_t combine_word_id(std::uint64_t w1, std::uint64_t w2){
    hasher_t::value_type hashsum(w1);
    hasher_t::combine(hashsum, w2);
    return word_id_t (hashsum);
}

PYBIND11_MODULE(libpyexbase, m) {
    m.def("combine_word_id", &combine_word_id);
}

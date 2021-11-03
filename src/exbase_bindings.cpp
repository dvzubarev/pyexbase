#include "str2word_id.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

std::uint64_t calc_word_id_(const std::string& s, std::uint8_t lang, bool recode2cp1251 = true){
    return calc_word_id(s, lang_id_t(lang), recode2cp1251);
}

py::list calc_word_ids(const py::list& vs,
                       std::uint8_t lang, bool recode2cp1251 = true){
    py::list ids;

    for(int i = 0; i < len(vs); ++i) {
        py::str s = vs[i];
        ids.append(calc_word_id(s, lang_id_t{lang}, recode2cp1251));
    }

    return ids;
}

py::list detect_lang_calc_word_ids(const py::list& vs, bool recode2cp1251 = true){

    py::list ids;

    for(int i = 0; i < len(vs); ++i) {
        py::str s = vs[i];
        ids.append(detect_lang_calc_word_id(s, recode2cp1251));
    }

    return ids;
}

std::uint32_t lang_of_word_(const std::string& s){
    return static_cast<std::uint32_t>(lang_of_word(s));
}

py::list lang_of_words(const py::list& strs){
    py::list langs;

    for(int i = 0; i < len(strs); ++i) {
        py::str s = strs[i];
        langs.append(lang_of_word_(s));
    }
    return langs;
}

PYBIND11_MODULE(libpyexbase, m) {
    m.def("calc_word_id", &calc_word_id_);
    m.def("detect_lang_calc_word_id", &detect_lang_calc_word_id);
    m.def("calc_word_ids", &calc_word_ids);
    m.def("detect_lang_calc_word_ids", &detect_lang_calc_word_ids);
    m.def("combine_word_id", &combine_word_id);
    m.def("lang_of_word", &lang_of_word_);
    m.def("lang_of_words", &lang_of_words);
}

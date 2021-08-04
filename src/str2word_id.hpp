#include "lang.hpp"
#include "word_id_hash.hpp"

#include <boost/locale/encoding.hpp>

std::uint64_t calc_word_id_impl(const std::string& s,
                                lang_id_t lang){

    //It is compatibility with old code
    //4 is sizeof(lng::ELexemeType)
    hasher_t h(hasher_t::value_type (lang) << 4 * 8 /* | PoS */);
    h.process_bytes(reinterpret_cast<const hasher_t::byte_type*>(s.data()), s.size());
    return std::uint64_t(h());
}

std::uint64_t calc_word_id(const std::string& s, lang_id_t lang, bool recode2cp1251 = true){
    //cyrillic words used to be encoded in cp1251...
    if (recode2cp1251 and lang == lang_id_t::RU){
        std::string out = boost::locale::conv::from_utf(s, "cp1251");
        return calc_word_id_impl(out, lang);
    }
    return calc_word_id_impl(s, lang);

}

std::uint64_t detect_lang_calc_word_id(const std::string& s, bool recode2cp1251 = true){
    lang_id_t lang_id(lang_of_word(s));
    return calc_word_id(s, lang_id, recode2cp1251);
}



std::uint64_t combine_word_id(std::uint64_t w1, std::uint64_t w2){
    hasher_t::value_type hashsum(w1);
    hasher_t::combine(hashsum, w2);
    return word_id_t (hashsum);
}

#include <cstdint>
#include <array>
#include <algorithm>

#include <boost/locale/utf.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>

//TODO Do we need compatibility with old textapp??
enum class lang_id_t : std::uint8_t{
    RU = 0,
    EN = 1,
    UNDEFINED = 15
};

inline lang_id_t lang_of_letter (boost::locale::utf::code_point cp){
    if((0x400 <= cp) && (cp <= 0x4FF))
        return lang_id_t(0);

    if((0x41 <= cp && cp <= 0x5A) || (0x61 <= cp && cp <= 0x7A))
        return lang_id_t(1);

    return lang_id_t::UNDEFINED;
}

lang_id_t lang_of_word (const std::string& s){
    std::array<unsigned, static_cast<unsigned>(lang_id_t::UNDEFINED)+1> ls;

    typedef boost::u8_to_u32_iterator<std::string::const_iterator> iter_t;

    ls.fill(0u);
    for(iter_t it(s.begin()), end(s.end()); it!=end; ++it){
        lang_id_t lid (lang_of_letter(*it));
        ++ls[static_cast<unsigned>(lid)];
    }

    return lang_id_t(
        std::distance(ls.begin(), std::max_element(ls.begin(), ls.end())));

}

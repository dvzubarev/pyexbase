#include <type_traits>
#include <cstdint>

template <typename THash, std::size_t Left
          , std::size_t Right = sizeof(THash) * 8 - Left
          >
struct rotator_t
{
    constexpr static std::size_t left = Left;
    constexpr static std::size_t right = Right;

    inline void operator () (THash & x ) const {rotator_t::rotate(x);}
    static inline void rotate (THash & x ) { x = (x << Left) | (x >> Right);}

};

template <std::size_t Left, typename THash>
inline std::enable_if_t<std::is_integral_v<THash>, THash>
rotate (THash x)
{
    rotator_t<THash, Left>::rotate(x);
    return x;
}


template <std::size_t Size, std::size_t MagicLeftShift = Size * 13 / 32>
struct rot_t
{
    typedef std::uint64_t	value_type;
    typedef unsigned char byte_type;

    constexpr static std::size_t left_shift = MagicLeftShift ;

    rot_t (value_type seed = value_type()) : m_checksum (seed) {}

    const value_type & operator () () const {return m_checksum;}

    inline void process_bytes(const byte_type * bytes, std::size_t length)
    {process_bytes_impl(bytes, length);}

    inline void process_byte(byte_type byte){
        m_checksum += static_cast<unsigned char>(byte);
        m_checksum -= rotate<left_shift>(m_checksum);
    }

    void combine (const value_type & other_checksum)
    {combine(m_checksum, other_checksum);}

    static void combine(value_type & v1, const value_type & v2)
    {v1 ^= rotate<left_shift>(v2); v1 -= rotate<left_shift>(v1); }

private:

    void process_bytes_impl(const byte_type * bytes_begin, std::size_t length){
        for(const byte_type * bytes_end = bytes_begin + length
                ; bytes_begin != bytes_end
                ; process_byte(*(bytes_begin++))
            ){}
    }

    value_type                  m_checksum;

};

typedef std::uint64_t word_id_t;
typedef rot_t <sizeof(word_id_t)*8>		hasher_t;

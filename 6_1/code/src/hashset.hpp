#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <optional>
#include <vector>
#include "record.hpp"

namespace custom {

class HashSet {
public:
    using hash_type = std::size_t;
    using key_type = int;
private:
    // динамическое множество значений
    std::vector<std::optional<Record>> table;
    size_t elements_count;
    void rehash(void);
    static hash_type get_hash(key_type key);
    static hash_type get_probe_hash(key_type key, int n);
public:
    HashSet(std::size_t size);
    std::size_t size(void) const;
    void resize(std::size_t size);
    bool insert(const Record& value);
    std::optional<Record> find(key_type key);
    bool remove(key_type key);
    void display(void);
};

} // namespace custom

#endif

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <memory>

namespace custom {

template <typename Key, typename Value>
struct KVPair {
    using key_type = Key;
    using value_type = Value;

    key_type key;
    value_type value;

    KVPair(Key key, Value value) {
        this->key = key;
        this->value = value;
    }
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashSet {
public:
    using key_type = Key;
    using value_type = Value;
    using pair_type = KVPair<key_type, value_type>;
    using hasher = Hash;
private:
    std::vector<std::shared_ptr<pair_type>> table;
    std::size_t _size = 0;

    void rehash() {
        auto pairs = std::vector<pair_type>();
        pairs.reserve(_size);

        // копируем и удаляем старые записи
        for (auto& ptr : table) {
            if (ptr) {
                pairs.push_back(*ptr);
                ptr = nullptr;
            }
        }

        // вновь добавляем записи
        for (const auto& pair : pairs) {
            insert(pair);
        }
    }

    static std::size_t get_hash(const key_type& key) {
        return hasher{}(key);
    }

    static std::size_t get_probe_hash(const key_type& key, int n) {
        auto old_hash = get_hash(key);
        return old_hash + 1 * n + 1 * n * n;
    }

public:
    HashSet(): table(1) {
        _size = 0;
    }

    std::size_t capacity(void) const {
        return table.size();
    }

    std::size_t size(void) const {
        return _size;
    }

    void reserve(std::size_t count) {
        // выйти, если указанный размер меньше текущего или равен ему
        if (count <= capacity()) {
            return;
        }

        table.resize(count);
        rehash();
    }

    void insert(const pair_type& pair) {
        auto key = pair.key;

        // ключ уже существует
        if (contains(key)) {
            return;
        }

        // если коэффициент нагрузки больше или равен 0.75 - увеличить размер вдвое и рехешировать
        auto load_factor = static_cast<float>(size()) / static_cast<float>(capacity());
        if (load_factor >= 0.75) {
            reserve(capacity() * 2);
        }

        auto index = get_hash(key) % capacity();
        /* индекс уже занят */
        if (table.at(index) != nullptr) {

            /* пробируем индексы, пока не был найден свободный индекс */
            int attempt = 1;
            while (true) {
                index = get_probe_hash(key, attempt);

                /* удвоить размер хеш-таблицы и рехешировать её,
            если индекс выходит за её границы */
                if (index >= capacity()) {
                    reserve(capacity() * 2);
                    return insert(pair);
                }

                /* выйти из цикла, если индекс - свободный */
                if (table.at(index) == nullptr) {
                    break;
                }

                attempt++;
            }
        }

        table.at(index) = std::make_shared<pair_type>(pair);
        _size++;
    }

    bool contains(const key_type& key) {
        auto index = get_hash(key) % capacity();
        const auto& ptr = table.at(index);

        if (ptr) {
            if (key == ptr->key) {
                return true;
            }

            int attempt = 1;
            while (true) {
                index = get_probe_hash(key, attempt);
                if (index >= capacity()) break;
                if (key == table.at(index)->key) {
                    return true;
                }
                attempt++;
            }
        }
        return false;
    }

    value_type& at(const key_type& key) {
        auto index = get_hash(key) % capacity();
        const auto& ptr = table.at(index);

        if (ptr) {
            if (key == ptr->key) {
                return ptr->value;
            }

            int attempt = 1;
            while (true) {
                index = get_probe_hash(key, attempt);
                if (index >= capacity()) break;

                auto ptr = table.at(index);
                if (key == ptr->key) {
                    return ptr->value;
                }
                attempt++;
            }
        }

        throw std::out_of_range("Элемент с заданным ключём не существует");
    }

    value_type find(const key_type& key) {
        if (contains(key)) {
            return at(key);
        } else {
            throw std::out_of_range("Элемент с заданным ключём не найден");
        }
    }

    void remove(const key_type& key) {
        auto index = get_hash(key) % capacity();
        auto& ptr = table.at(index);

        if (ptr) {
            if (key == ptr->key) {
                ptr = nullptr;
                _size--;
                rehash();
                return;
            }

            int attempt = 1;
            while (true) {
                index = get_probe_hash(key, attempt);
                if (index >= capacity()) {
                    return;
                }

                auto ptr = table.at(index);
                if (key == ptr->key) {
                    ptr = nullptr;
                    rehash();
                    return;
                }
                attempt++;
            }
        }
    }

    void display(void) {
        for (const auto& pair : table) {
            if (pair) {
                std::cout << pair->key << ": " << pair->value << std::endl;
            }
        }
    }
};

} // namespace custom

#endif

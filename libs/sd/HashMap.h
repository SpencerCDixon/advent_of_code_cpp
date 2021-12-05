#include "String.h"

#include <functional>

template<typename Key>
struct HashKeyTrait {
    static size_t hash(const Key &);
    static bool equals(const Key &lhs, const Key &rhs);
};

template<>
struct HashKeyTrait<int> {
    static size_t hash(const int &value) { return value; }
    static bool equals(const int &lhs, const int &rhs) { return lhs == rhs; }
};

template<>
struct HashKeyTrait<String> {
    static size_t hash(const String &value)
    {
        unsigned char *p;

        size_t h = 0;
        for (p = (unsigned char *)value.characters(); *p != '\0'; p++)
            h = 31 * h + *p;

        return h;
    }
    static bool equals(const String &lhs, const String &rhs) { return lhs == rhs; }
};

// TODO:
// * convert to growable bucket-based approach

template<typename Key, typename Value, typename Traits = HashKeyTrait<Key>>
class HashMap {
public:
    using KeyPtr = Key*;
    using ValuePtr = Value*;

    static const size_t kHashTableSize = 256;
    struct Entry {
        Key key;
        Value value;
        Entry *next { nullptr };

        Entry(Key key, Value value, Entry *next = nullptr)
            : key(key)
            , value(value)
            , next(next)
        {
        }
    };

    HashMap()
    {
        memset(m_slots, 0, sizeof(m_slots));
    };

    ~HashMap()
    {
        for (size_t i = 0; i < kHashTableSize; ++i) {
            if (!m_slots[i]) {
                continue;
            }

            Entry *iter = m_slots[i];
            while (iter != nullptr) {
                Entry *tmp;
                tmp = iter;
                iter = iter->next;
                delete tmp;
            }
        }
    }

    void for_each(std::function<void(KeyPtr, ValuePtr)> fn)
    {
        for (size_t i = 0; i < kHashTableSize; ++i) {
            if (!m_slots[i]) {
                continue;
            }

            Entry *iter = m_slots[i];
            while (iter != nullptr) {
                Entry *tmp;
                tmp = iter;
                iter = iter->next;

                fn(&tmp->key, &tmp->value);
            }
        }
    }

    Value *get(Key key)
    {
        size_t slot_idx = slot_index(key);
        if (!m_slots[slot_idx]) {
            return nullptr;
        }

        if (Traits::equals(m_slots[slot_idx]->key, key)) {
            return &m_slots[slot_idx]->value;
        }

        Entry *entry = m_slots[slot_idx]->next;
        while (entry != nullptr) {
            if (Traits::equals(entry->key, key)) {
                return &entry->value;
            }
            entry = entry->next;
        }

        return nullptr;
    }

    bool insert(Key key, Value value)
    {
        size_t slot_idx = slot_index(key);

        if (m_slots[slot_idx] == nullptr) {
            m_slots[slot_idx] = new Entry(key, value);
        } else {
            // FIXME: Not handling duplicates of keys, need to implement a replacement strategy
            Entry *current_node = m_slots[slot_idx];
            auto *next = new Entry(key, value);
            current_node->next = next;
            m_slots[slot_idx] = next;
        }

        return true;
    }

private:
    size_t slot_index(const Key &key)
    {
        return Traits::hash(key) % kHashTableSize;
    }

    Entry *m_slots[kHashTableSize];
};

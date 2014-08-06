#ifndef MULTITON_H
#define MULTITON_H

//A Multiton is a standard design pattern. It allows for a singleton map to an object.

#include <map>
#include <string>

template <typename T, typename Key = std::string>
class Multiton
{
public:
    static void destroy()
    {
        for (typename std::map<Key, T*>::const_iterator it = instances.begin(); it != instances.end(); ++it)
            delete (*it).second;
        instances.clear();
    }

    static T* GetPtr(const Key& key) {
        typename std::map<Key, T*>::const_iterator it = instances.find(key);

        if (it != instances.end()) {
            return (T*)(it->second);
        }

        T* instance = new T();
        instances[key] = instance;
        return instance;
    }

    static T& GetPtrRef(const Key& key) {
        return *GetPtr(key);
    }

protected:
    Multiton() {}
    ~Multiton() {}

private:
    Multiton(const Multiton&) {}
    Multiton& operator= (const Multiton&) { return *this; }

    static std::map<Key, T*> instances;
};

template <typename T, typename Key>
std::map<Key, T*> Multiton<T, Key>::instances;

#endif

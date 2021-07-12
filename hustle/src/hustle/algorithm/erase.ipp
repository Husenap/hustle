
namespace hustle {

// erase
namespace _impl {

template <typename _Map, typename _Value>
void erase_map(_Map& map, const _Value& value) {
    for (auto it = map.begin(); it != map.end();) {
        if (it->first == value) {
            it = map.erase(it);
        } else {
            ++it;
        }
    }
}
template <typename _Set, typename _Value>
void erase_set(_Set& set, const _Value& value) {
    for (auto it = set.begin(); it != set.end();) {
        if (*it == value) {
            it = set.erase(it);
        } else {
            ++it;
        }
    }
}

template <typename _MapOrSet, typename _Func>
void erase_if(_MapOrSet& container, const _Func func) {
    for (auto it = container.begin(); it != container.end();) {
        if (func(*it)) {
            it = container.erase(it);
        } else {
            ++it;
        }
    }
}

}  // namespace _impl

template <typename _MapKey, typename _MapValue, typename _Value>
void erase(std::map<_MapKey, _MapValue>& map, const _Value& value) {
    _impl::erase_map(map, value);
}
template <typename _MapKey, typename _MapValue, typename _Value>
void erase(std::unordered_map<_MapKey, _MapValue>& map, const _Value& value) {
    _impl::erase_map(map, value);
}
template <typename _MapKey, typename _MapValue, typename _Value>
void erase(std::multimap<_MapKey, _MapValue>& map, const _Value& value) {
    _impl::erase_map(map, value);
}
template <typename _MapKey, typename _MapValue, typename _Value>
void erase(std::unordered_multimap<_MapKey, _MapValue>& map,
           const _Value&                                value) {
    _impl::erase_map(map, value);
}
template <typename _SetValue, typename _Value>
void erase(std::set<_SetValue>& set, const _Value& value) {
    _impl::erase_set(set, value);
}
template <typename _SetValue, typename _Value>
void erase(std::unordered_set<_SetValue>& set, const _Value& value) {
    _impl::erase_set(set, value);
}
template <typename _SetValue, typename _Value>
void erase(std::multiset<_SetValue>& set, const _Value& value) {
    _impl::erase_set(set, value);
}
template <typename _SetValue, typename _Value>
void erase(std::unordered_multiset<_SetValue>& set, const _Value& value) {
    _impl::erase_set(set, value);
}
template <typename _Container, typename _Value>
void erase(_Container& container, const _Value& value) {
    container.erase(std::remove(container.begin(), container.end(), value),
                    container.end());
}

// erase_if
template <typename _MapKey, typename _MapValue, typename _Predicate>
void erase_if(std::map<_MapKey, _MapValue>& map, _Predicate pred) {
    _impl::erase_if(map, pred);
}
template <typename _SetValue, typename _Predicate>
void erase_if(std::set<_SetValue>& set, _Predicate pred) {
    _impl::erase_if(set, pred);
}
template <typename _MapKey, typename _MapValue, typename _Predicate>
void erase_if(std::unordered_map<_MapKey, _MapValue>& map, _Predicate pred) {
    _impl::erase_if(map, pred);
}
template <typename _SetValue, typename _Predicate>
void erase_if(std::unordered_set<_SetValue>& set, _Predicate pred) {
    _impl::erase_if(set, pred);
}
template <typename _MapKey, typename _MapValue, typename _Predicate>
void erase_if(std::multimap<_MapKey, _MapValue>& map, _Predicate pred) {
    _impl::erase_if(map, pred);
}
template <typename _SetValue, typename _Predicate>
void erase_if(std::multiset<_SetValue>& set, _Predicate pred) {
    _impl::erase_if(set, pred);
}
template <typename _MapKey, typename _MapValue, typename _Predicate>
void erase_if(std::unordered_multimap<_MapKey, _MapValue>& map,
              _Predicate                                   pred) {
    _impl::erase_if(map, pred);
}
template <typename _SetValue, typename _Predicate>
void erase_if(std::unordered_multiset<_SetValue>& set, _Predicate pred) {
    _impl::erase_if(set, pred);
}
template <typename _Container, typename _Predicate>
void erase_if(_Container& container, _Predicate pred) {
    container.erase(std::remove_if(container.begin(), container.end(), pred),
                    container.end());
}

// erase_if_not
template <typename _Container, typename _Predicate>
void erase_if_not(_Container& container, _Predicate pred) {
    erase_if(container, std::not_fn(pred));
}

}  // namespace hustle

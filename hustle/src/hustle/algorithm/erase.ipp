namespace hustle {

namespace _impl {

template <typename _MapOrSet, typename _Func>
void erase_if(_MapOrSet& container, const _Func func) {
    for (auto it = std::cbegin(container); it != std::cend(container);) {
        if (func(*it)) {
            it = container.erase(it);
        } else {
            ++it;
        }
    }
}

}  // namespace _impl

// erase
template <typename _Container, typename _Value>
void erase(_Container& container, const _Value& value) {
    container.erase(
        std::remove(std::begin(container), std::end(container), value),
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
    container.erase(
        std::remove_if(std::begin(container), std::end(container), pred),
        container.end());
}

// erase_if_not
template <typename _Container, typename _Predicate>
void erase_if_not(_Container& container, _Predicate pred) {
    erase_if(container, std::not_fn(pred));
}

}  // namespace hustle

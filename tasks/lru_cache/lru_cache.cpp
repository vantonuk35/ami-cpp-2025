#include "lru_cache.h"

LRUCache::LRUCache(size_t capacity) : capacity_(capacity) {
}

size_t LRUCache::Size() const {
    return helper_.size();
}

size_t LRUCache::Capacity() const {
    return capacity_;
}

void LRUCache::Clear() noexcept {
    unpinned_.clear();
    pinned_.clear();
    helper_.clear();
}
void LRUCache::Propogate(LRUCache::TIterator it, bool pinned) {
    auto& node_holder = pinned ? pinned_ : unpinned_;
    node_holder.splice(node_holder.begin(), node_holder, it);
}
std::optional<int> LRUCache::Get(const std::string& key) {
    auto helper_it = helper_.find(key);
    if (helper_it == helper_.end()) {
        return std::nullopt;
    }
    auto [list_iterator, is_pinned] = helper_it->second;
    Propogate(list_iterator, is_pinned);
    return list_iterator->second;
}

bool LRUCache::Put(const std::string& key, int value) {
    auto helper_it = helper_.find(key);
    if (helper_it == helper_.end()) {
        if (helper_.size() >= capacity_) {
            if (unpinned_.empty()) {
                return false;
            }
            auto key_to_delete = unpinned_.back().first;
            helper_.erase(key_to_delete);
            unpinned_.pop_back();
        }
        unpinned_.emplace_front(key, value);
        helper_.emplace(key, std::pair{unpinned_.begin(), false});
        return true;
    }
    auto [list_iterator, is_pinned] = helper_it->second;
    Propogate(list_iterator, is_pinned);
    list_iterator->second = value;
    return false;
}

bool LRUCache::Erase(const std::string& key) {
    auto helper_it = helper_.find(key);
    if (helper_it == helper_.end()) {
        return false;
    }
    auto [list_iterator, is_pinned] = helper_it->second;
    auto& node_holder = is_pinned ? pinned_ : unpinned_;
    node_holder.erase(list_iterator);
    helper_.erase(helper_it);
    return true;
}

bool LRUCache::Pin(const std::string& key) {
    auto helper_it = helper_.find(key);
    if (helper_it == helper_.end()) {
        return false;
    }
    auto& [list_iterator, is_pinned] = helper_it->second;
    if (is_pinned) {
        return false;
    }
    pinned_.push_front(*list_iterator);
    unpinned_.erase(list_iterator);
    is_pinned = true;
    list_iterator = pinned_.begin();
    return true;
}

bool LRUCache::Unpin(const std::string& key) {
    auto helper_it = helper_.find(key);
    if (helper_it == helper_.end()) {
        return false;
    }
    auto& [list_iterator, is_pinned] = helper_it->second;
    if (!is_pinned) {
        return false;
    }
    unpinned_.push_front(*list_iterator);
    pinned_.erase(list_iterator);
    is_pinned = false;
    list_iterator = unpinned_.begin();
    return true;
}

void LRUCache::Merge(LRUCache& other) {
    for (const auto& [key, metadata] : other.helper_) {
        if (this->helper_.contains(key)) {
            continue;
        }
        Put(key, metadata.first->second);
    }
}

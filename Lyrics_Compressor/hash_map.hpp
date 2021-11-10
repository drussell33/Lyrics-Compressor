#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <vector>
#include <list>
#include <functional>

#include "adt_exception.hpp"

namespace data_structures
{
	using std::list;
	using std::vector;
	using std::function;
	using std::move;
	using std::pair;

	template <class K, class V>
	class HashMap final
	{
	public:
		HashMap() = delete;
		HashMap(const size_t& table_size, const function<int(K key)>& hash_function);

		HashMap(const HashMap& copy);
		auto operator=(const HashMap& rhs)->HashMap&;

		HashMap(HashMap&& copy) noexcept;
		auto operator=(HashMap&& rhs) noexcept -> HashMap&;

		~HashMap() = default;

		auto Insert(const K& key, const V& value) -> void;
		auto HashFunction(const function<int(const K& key)>& hash) -> void;
		auto operator [](const K& key)->V&;
		auto operator [](const K& key) const->V;
		auto Remove(const K& key) -> void;
		auto Traverse(const function<void(const K& key, const V& value)>& visit) const -> void;
		auto Contains(const K& key) -> bool;
		auto Count() const->size_t;

	private:
		vector<list<pair<K, V>>> buckets_{};
		function<int(K key)> hash_function_{ nullptr };
		size_t count_{ 0 };
	};

	template <class K, class V>
	HashMap<K, V>::HashMap(const size_t& table_size, const function<int(K key)>& hash_function)
		:buckets_(table_size), hash_function_(hash_function)
	{
		if (hash_function == nullptr) throw AdtException("Hash function cannot be nullptr");
		if (table_size == 0) throw AdtException("Table size can't be 0.");
	}

	template <class K, class V>
	HashMap<K, V>::HashMap(const HashMap& copy)
	{
		*this = copy;
	}

	template <class K, class V>
	auto HashMap<K, V>::operator=(const HashMap& rhs) -> HashMap&
	{
		if (this != &rhs)
		{
			buckets_ = rhs.buckets_;
			hash_function_ = rhs.hash_function_;
			count_ = rhs.count_;
		}
		return *this;
	}

	template <class K, class V>
	HashMap<K, V>::HashMap(HashMap&& copy) noexcept
	{
		*this = std::move(copy);
	}

	template <class K, class V>
	auto HashMap<K, V>::operator=(HashMap&& rhs) noexcept -> HashMap&
	{
		if (this != &rhs)
		{
			buckets_ = std::move(rhs.buckets_);
			hash_function_ = rhs.hash_function_;
			count_ = rhs.count_;
		}
		return *this;
	}

	template <class K, class V>
	auto HashMap<K, V>::Insert(const K& key, const V& value) -> void
	{
		buckets_[hash_function_(key)].emplace_back(key, value);
		++count_;
	}

	template <class K, class V>
	auto HashMap<K, V>::HashFunction(const function<int(const K& key)>& hash) -> void
	{
		HashMap<K, V> hash_map(buckets_.size(), hash);

		for (auto& bucket : buckets_)
			for (auto& element : bucket)
			{
				hash_map.Insert(element.first, element.second);
			}
		*this = hash_map;
	}

	template <class K, class V>
	auto HashMap<K, V>::operator[](const K& key) -> V&
	{
		auto found = false;
		for (auto& bucket : buckets_)
			for (auto& element : bucket)
			{
				if (key == element.first)
				{
					return element.second;
				}
			}
		if (!found) throw AdtException("Key was not found");
	}

	template <class K, class V>
	auto HashMap<K, V>::operator[](const K& key) const -> V
	{
		auto found = false;
		for (auto& bucket : buckets_)
			for (auto& element : bucket)
			{
				if (key == element.first)
				{
					return element.second;
				}
			}
		if (!found) throw AdtException("Key was not found");
	}

	template <class K, class V>
	auto HashMap<K, V>::Remove(const K& key) -> void
	{
		auto found = false;
		for (auto& bucket : buckets_)
			for (auto& element : bucket)
			{
				if (element.first == key)
				{
					found = true;
					bucket.remove(element);
					--count_;
					break;
				}
			}
		if (!found) throw AdtException("Key was not found");
	}

	template <class K, class V>
	auto HashMap<K, V>::Traverse(const function<void(const K& key, const V& value)>& visit) const -> void
	{
		for (auto& bucket : buckets_)
			for (auto& chain : bucket)
			{
				visit(chain.first, chain.second);
			}
	}

	template <class K, class V>
	auto HashMap<K, V>::Contains(const K& key) -> bool
	{
		auto found = false;
		for (auto& bucket : buckets_)
			for (auto& element : bucket)
			{
				if (element.first == key)
				{
					found = true;
					return found;
				}
			}
		return found;
	}

	template <class K, class V>
	auto HashMap<K, V>::Count() const -> size_t
	{
		return count_;
	}
}
#endif
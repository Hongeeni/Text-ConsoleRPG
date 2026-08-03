#pragma once
#include <vector>
#include <string>
template <typename I>
class Inventory {
public:
	Inventory() = default;

	Inventory(std::initializer_list<I> item_list) {
		for (const auto& item : item_list) {
			Add(item.name_, item.count_);
		}
	}
	void Add(const std::string& name, int count) {
		for (auto& item : items_) {
			if (item.name_ == name) {
				item.count_ += count;
				return;
			}
		}
		items_.push_back(I{ name, count });
	}
	bool Remove(const std::string& name, int count)	{
		for (auto item = items_.begin(); item != items_.end(); ++item)		{
			if (item->name_ == name)			{
				if (item->count_ < count) {
					return false;
				}
				item->count_ -= count;
				if (item->count_ == 0) {
					items_.erase(item);
				}
				return true;
			}
		}
		return false;
	}
	bool Check(const std::string& name, int count) const {
		for (const auto& item : items_) {
			if (item.name_ == name) {
				return item.count_ >= count;
			}
		}
		return false;
	}
	const std::vector<I>& ViewInventory() const {
		return items_;
	}

private:
	std::vector<I> items_;
};
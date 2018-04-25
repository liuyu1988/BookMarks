#include "favorite.h"


favorite::Favorite::Favorite()
{
	root_entry_.SetIndex(0);
	root_entry_.SetName("Favorites");
	root_entry_.SetParent(nullptr);
	root_entry_.SetMetaInfo(Entry::MetaInfo{ Entry::EntryType::Folder });
}

favorite::Favorite::~Favorite()
{

}

bool favorite::Favorite::AddPage(const EntryIndex parentIndex, const PageInfo& pageInfo)
{
	auto parent_entry = FindEntry(root_entry_, parentIndex);
	if (parent_entry == nullptr || parent_entry->GetMetaInfo().type == Entry::EntryType::WebPage)
	{
		return false;
	}

	return parent_entry->AddPage(pageInfo);
}

bool favorite::Favorite::AddFolder(const EntryIndex parentIndex, const std::string& name)
{
	auto parent_entry = FindEntry(root_entry_, parentIndex);
	if (parent_entry == nullptr || parent_entry->GetMetaInfo().type == Entry::EntryType::WebPage)
	{
		return false;
	}

	return parent_entry->AddFolder(name);
}

bool favorite::Favorite::Delete(const EntryIndex index)
{
	auto entry = FindEntry(root_entry_, index);
	if (entry == nullptr)
	{
		return false;
	}

	auto parent = entry->GetParent();
	if (parent == nullptr)
	{
		return false;
	}

	//delete it from its parent
	return parent->Delete(index);
}

bool favorite::Favorite::ModifyPage(const EntryIndex index, const PageInfo& pageInfo)
{
	auto entry = FindEntry(root_entry_, index);
	if (entry == nullptr)
	{
		return false;
	}

	return entry->ModifyPage(pageInfo);
}

bool favorite::Favorite::ModifyFolder(const EntryIndex index, const std::string& name)
{
	auto entry = FindEntry(root_entry_, index);
	if (entry == nullptr)
	{
		return false;
	}

	return entry->ModifyFolder(name);
}

bool favorite::Favorite::Move(const EntryIndex index, const EntryIndex parentIndex, int pos)
{
	auto entry = FindEntry(root_entry_, index); // entry to be moved
	if (entry == nullptr)
	{
		return false;
	}

	auto parent_entry = FindEntry(root_entry_, parentIndex);
	if (parent_entry == nullptr)
	{
		return false;
	}

	auto old_parent_entry = entry->GetParent();
	if (old_parent_entry == nullptr)
	{
		return false;
	}

	if (old_parent_entry == parent_entry) //in the same parent entry
	{
		return MoveInPlace(*parent_entry, *entry, pos);
	}
	else //move to another entry
	{
		return MoveCrossPlace(*old_parent_entry, *parent_entry, *entry, pos);
	}
}

favorite::Entry favorite::Favorite::Query(const EntryIndex index /*= -1*/)
{
	if (index == -1)
	{
		return root_entry_;
	}

	return *FindEntry(root_entry_, index);
}

favorite::Entry* favorite::Favorite::FindEntry(Entry& root, const EntryIndex& index)
{
	if (index == root.GetIndex())
	{
		return &root;
	}

	for (auto& info : root.GetMetaInfo().sub_entries)
	{
		auto ret = FindEntry(info, index);
		if (ret != nullptr)
		{
			return ret;
		}
	}

	return nullptr;
}

bool favorite::Favorite::MoveInPlace(Entry& parent, Entry& entry, int pos)
{
	return parent.Move(entry.GetIndex(), pos);
}

bool favorite::Favorite::MoveCrossPlace(Entry& oldParent, Entry& newParent, Entry& entry, int pos)
{
	//first insert it into new parent entry
	if (!newParent.Insert(entry, pos))
	{
		return false;
	}

	//delete it from old parent entry
	return oldParent.Delete(entry.GetIndex());
}

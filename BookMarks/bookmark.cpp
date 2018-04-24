#include "bookmark.h"

bookmark::Entry::Entry()
{

}

bookmark::Entry::~Entry()
{

}

bool bookmark::Entry::AddPage(const PageInfo& pageInfo)
{
	Entry entry;

	entry.SetName(pageInfo.name);
	entry.SetMetaInfo(MetaInfo{ EntryType::WebPage, pageInfo.page });
	entry.SetIndex(EntryManager::Generate());
	entry.SetParent(std::shared_ptr<Entry>(this));

	meta_info_.sub_entries.push_back(entry);

	return true;
}

bool bookmark::Entry::AddFolder( const std::string & name)
{
	Entry entry;

	entry.SetName(name);
	entry.SetMetaInfo(MetaInfo{ EntryType::Folder });
	entry.SetIndex(EntryManager::Generate());
	entry.SetParent(std::shared_ptr<Entry>(this));

	meta_info_.sub_entries.push_back(entry);

	return true;
}

bool bookmark::Entry::Delete(const EntryIndex& index)
{
	for (auto sub = meta_info_.sub_entries.begin();
		sub != meta_info_.sub_entries.end(); sub++)
	{
		if (index == sub->GetIndex())
		{
			meta_info_.sub_entries.erase(sub);
			return true;
		}
	}
	return false;
}

bool bookmark::Entry::ModifyPage(const PageInfo & pageInfo)
{
	name_ = pageInfo.name;
	meta_info_.page = pageInfo.page;

	return true;
}

bool bookmark::Entry::ModifyFolder(const std::string & name)
{
	name_ = name;
	return true;
}



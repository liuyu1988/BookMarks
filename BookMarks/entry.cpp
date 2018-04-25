#include "entry.h"

favorite::Entry::Entry()
	:name_("default"),
	index_(-1)
{

}

favorite::Entry::~Entry()
{

}

bool favorite::Entry::AddPage(const PageInfo& pageInfo)
{
	Entry entry;

	entry.SetName(pageInfo.name);
	entry.SetMetaInfo(MetaInfo{ EntryType::WebPage, pageInfo.page });
	entry.SetIndex(Generate());
	entry.SetParent(this); //save its parent

	meta_info_.sub_entries.push_back(entry);

	return true;
}

bool favorite::Entry::AddFolder( const std::string & name)
{
	Entry entry;

	entry.SetName(name);
	entry.SetMetaInfo(MetaInfo{ EntryType::Folder }); //sub entries are empty
	entry.SetIndex(Generate());
	entry.SetParent(this); //save its parent

	meta_info_.sub_entries.push_back(entry);

	return true;
}

bool favorite::Entry::Delete(const EntryIndex& subEntryIndex)
{
	for (auto sub = meta_info_.sub_entries.begin();
		sub != meta_info_.sub_entries.end(); sub++)
	{
		if (subEntryIndex == sub->GetIndex()) //found 
		{
			meta_info_.sub_entries.erase(sub);
			return true;
		}
	}
	return false;
}

bool favorite::Entry::Move(const EntryIndex& subEntryIndex, int pos)
{
	if (pos > (int)meta_info_.sub_entries.size() || meta_info_.type == EntryType::WebPage)
	{
		return false;
	}

	bool found = false;
	auto sub = meta_info_.sub_entries.begin();
	for (; sub != meta_info_.sub_entries.end(); sub++)
	{
		if (sub->GetIndex() == subEntryIndex) //found
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		return false;
	}

	auto insert = meta_info_.sub_entries.begin();
	advance(insert, pos); //move to pos

	if (insert == sub)
	{
		return true;
	}


	if (distance(meta_info_.sub_entries.begin(), sub) < pos)
	{
		insert++;
	}

	meta_info_.sub_entries.splice(insert, meta_info_.sub_entries, sub); //reposition
	return true;
}

bool favorite::Entry::Insert(Entry & subEntry, int pos)
{
	if (pos > (int)meta_info_.sub_entries.size() || meta_info_.type == EntryType::WebPage)
	{
		return false;
	}

	subEntry.SetParent(this);
	
	auto it = meta_info_.sub_entries.begin();
	advance(it, pos); // move to pos

	meta_info_.sub_entries.insert(it, subEntry);
	return true;
}

bool favorite::Entry::ModifyPage(const PageInfo & pageInfo)
{
	name_ = pageInfo.name;
	meta_info_.page = pageInfo.page;

	return true;
}

bool favorite::Entry::ModifyFolder(const std::string & name)
{
	name_ = name;
	return true;
}



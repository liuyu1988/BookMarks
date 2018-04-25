#ifndef __favorite_h__
#define __favorite_h__

#include "entry.h"

namespace favorite
{
	class Favorite
	{
	public:
		Favorite();;
		~Favorite();;

	public:
		//add an entry which type is web page to the parent entry
		bool AddPage(const EntryIndex parentIndex, const PageInfo& pageInfo);

		//add an entry which type is folder to the parent entry
		bool AddFolder(const EntryIndex parentIndex, const std::string& name);

		//delete an entry
		bool Delete(const EntryIndex index);

		//modify an entry which type is web page
		bool ModifyPage(const EntryIndex index, const PageInfo& pageInfo);

		//modify an entry which type folder
		bool ModifyFolder(const EntryIndex index, const std::string& name);

		//move an entry to the parent entry
		bool Move(const EntryIndex index, const EntryIndex parentIndex, int pos);

		//query entry info, -1 means the root
		//to-do: implement a wrap class to hide Entry
		Entry Query(const EntryIndex index = -1);

	private:
		//find entry by index
		//to-do: use hash table to accelerate
		Entry* FindEntry( Entry& root, const EntryIndex& index);

		//move an entry in the same parent entry
		bool MoveInPlace(Entry& parent, Entry& entry, int pos);

		//move an entry between different parent entries
		bool MoveCrossPlace(Entry& oldParent, Entry& newParent, Entry& entry, int pos);

	private:
		Entry root_entry_;
	};
}


#endif // !__favorite_h__

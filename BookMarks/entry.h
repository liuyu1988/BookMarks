#ifndef __entry_h__
#define __entry_h__

#include <string>
#include <list>

namespace favorite
{
	typedef unsigned int EntryIndex; //index type

	struct Page
	{
		std::string title;
		std::string url;
	};

	struct PageInfo
	{
		std::string name; //user custom name 
		Page page;
	};
	
	//Entry represents a web page or a folder who contains entries
	class Entry
	{
	public:
		enum EntryType
		{
			Folder,  
			WebPage,

		};

		//store metadata info, page is used when type is webpage, otherwise sub_entries is used
		struct MetaInfo
		{
			EntryType type;

			Page page;
			std::list<Entry> sub_entries;
		};

		Entry();
		~Entry();

	public:
		//unique id for each entry, auto-increment
		static EntryIndex Generate()
		{
			static unsigned int index = 0;
			return ++index;
		}

		//add a sub entry which type is webpage
		bool AddPage(const PageInfo& pageInfo);

		//add a sub entry which type is folder
		bool AddFolder(const std::string& name);

		//delete sub entry
		bool Delete(const EntryIndex& subEntryIndex);

		//move a sub entry which index is subEntryIndex to the pos
		bool Move(const EntryIndex& subEntryIndex, int pos);

		//insert a sub entry to the pos
		bool Insert( Entry& subEntry, int pos);

		//modify page info
		bool ModifyPage(const PageInfo& pageInfo);

		//modify folder info
		bool ModifyFolder(const std::string& name);

	public:
		inline void SetName(const std::string& name)
		{
			name_ = name;
		}

		inline std::string GetName()
		{
			return name_;
		}

		inline void SetIndex(const EntryIndex& index)
		{
			index_ = index;
		}

		inline EntryIndex GetIndex() 
		{
			return index_;
		}

		inline MetaInfo& GetMetaInfo()
		{
			return meta_info_;
		}

		inline void SetMetaInfo(MetaInfo& info)
		{
			meta_info_ = info;
		}

		inline void SetParent(Entry* parent)
		{
			parent_ = parent;
		}

		inline Entry* GetParent()
		{
			return parent_;
		}

	private:
		std::string name_;
		EntryIndex index_;
		MetaInfo meta_info_;
		Entry* parent_;

	};


}


#endif // !__entry_h__

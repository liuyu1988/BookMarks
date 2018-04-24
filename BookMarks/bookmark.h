#ifndef __book_mark__
#define __book_mark__

#include <string>
#include <list>
#include <memory>

namespace bookmark
{
	typedef unsigned int EntryIndex;

	struct Page
	{
		std::string title;
		std::string url;
	} ;


	struct PageInfo
	{
		std::string name;
		Page page;
	};

	enum EntryType
	{
		Folder,
		WebPage,

	};



	class Entry
	{
	public:

		struct MetaInfo
		{
			EntryType type;

			Page page;
			std::list<Entry> sub_entries;

		};

		Entry();
		~Entry();

	public:
		bool AddPage(const PageInfo& pageInfo);
		bool AddFolder(const std::string& name);
		bool Delete(const EntryIndex& index);
		bool ModifyPage(const PageInfo& pageInfo);
		bool ModifyFolder(const std::string& name);

		bool query();

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
			index_ = index_;
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

		inline void SetParent(const std::shared_ptr<Entry> parent)
		{
			parent_ = parent;
		}

		inline std::shared_ptr<Entry> GetParent()
		{
			return parent_;
		}

	private:
		std::string name_;
		EntryIndex index_;
		MetaInfo meta_info_;
		std::shared_ptr<Entry> parent_;

		friend class EntryManager;
	};

	class EntryManager
	{
	public:
		EntryManager() {};
		~EntryManager() {};

	public:
		static EntryIndex Generate()
		{
			static unsigned int index = 0;
			return index++;
		}

		bool AddPage(const EntryIndex parentIndex, const PageInfo& pageInfo)
		{
			auto parent_entry = Find(root_entry_, parentIndex);
			if (parent_entry == nullptr || parent_entry->GetMetaInfo().type == EntryType::WebPage)
			{
				return false;
			}

			return parent_entry->AddPage(pageInfo);

		}
		bool AddFolder(const EntryIndex parentIndex, const std::string& name)
		{
			auto parent_entry = Find(root_entry_, parentIndex);
			if (parent_entry == nullptr || parent_entry->GetMetaInfo().type == EntryType::WebPage)
			{
				return false;
			}

			return parent_entry->AddFolder(name);
		}

		bool Delete(const EntryIndex index)
		{
			auto entry = Find(root_entry_, index);
			if (entry == nullptr)
			{
				return false;
			}

			auto parent = entry->GetParent();
			if (parent == nullptr)
			{
				return false;
			}

			return parent->Delete(index);
		}

		bool ModifyPage(const EntryIndex index, const PageInfo& pageInfo)
		{
			auto entry = Find(root_entry_, index);
			if (entry == nullptr)
			{
				return false;
			}

			return entry->ModifyPage(pageInfo);
		}

		bool ModifyFolder(const EntryIndex index, const std::string& name)
		{
			auto entry = Find(root_entry_, index);
			if (entry == nullptr)
			{
				return false;
			}

			return entry->ModifyFolder(name);
		}

		bool Move(const EntryIndex index, const EntryIndex parentIndex)
		{
			auto parent_entry = Find(root_entry_, parentIndex);
			if (parent_entry == nullptr)
			{
				return false;
			}

			auto entry = Find(root_entry_, index);
			if (entry == nullptr)
			{
				return false;
			}

			auto old_parent_entry = entry->GetParent();
			if (old_parent_entry == nullptr)
			{
				return false;
			}

			if (entry->GetMetaInfo().type == WebPage)
			{
				parent_entry->AddPage({ entry->GetName(), entry->GetMetaInfo().page });
			}
			else
			{
				parent_entry->AddFolder(entry->GetName());
			}

			return old_parent_entry->Delete(index);
		}

	private:
		Entry* Find( Entry& root, const EntryIndex& index)
		{
			if (index == root.GetIndex())
			{
				return &root;
			}

			for (auto& info : root.GetMetaInfo().sub_entries)
			{
				auto ret = Find(info, index);
				if (ret != nullptr)
				{
					return ret;
				}
			}

			return nullptr;
		}
	private:
		Entry root_entry_;
	};
}


#endif // !__book_mark__

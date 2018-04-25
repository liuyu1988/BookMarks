// BookMarks.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "favorite.h"
#include <iostream>
using namespace favorite;

int main()
{
	Favorite fa;

	auto it = fa.Query();
	std::cout << it.GetName()<<it.GetIndex()<<it.GetMetaInfo().type;

	fa.AddPage(0, { "google usa",{ "world", "www.google.com" } });
	fa.AddFolder(0, { "work" });

	fa.AddFolder(0, { "work 2" });

	fa.AddPage(3, { "google hk",{ "world", "www.google.hk" } });
	fa.AddPage(3, { "google cn",{ "world", "www.google.cn" } });

	fa.Delete(2);

	fa.Move(4, 0, 0); //hk -> work - root 0
	fa.Move(4, 0, 2); //hk -> root 0 - 1
    return 0;
}


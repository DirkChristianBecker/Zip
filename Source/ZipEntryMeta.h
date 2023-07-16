#pragma once

#include "Types.h"
#include <sstream>

namespace Zip
{
	struct ZipEntryMeta
	{
		String Name;
		bool IsDirectory;
		String Comment;
		Size UncompressedSize;
		Size Compressed;
		int CrcCheckSum;
		void* HeapData = 0;

		String ToString() const;

		String GetAsText() const { return String((const char*) HeapData); }
	};
}
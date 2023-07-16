#include "ZipEntryMeta.h"

namespace Zip
{
	String ZipEntryMeta::ToString() const
	{
		std::stringstream sstream;
		sstream << Name << " IsDirectory: " << IsDirectory << " Compressed: " << Compressed << " Uncompressed Size: " << UncompressedSize << " " << CrcCheckSum << " Comment: " << Comment;

		return sstream.str();
	}
}
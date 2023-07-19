#pragma once

#include "Archive.h"
#include <ExecutablePath.h>

namespace Zip
{
	Archive::Archive()
	{
		memset(&mArchive, 0, sizeof(mz_zip_archive));
		mFile = "";
		mNoEntries = 0;
	}

	Archive::Archive(const Path& abs_path)
		: mFile(abs_path),
		  mNoEntries(0)
	{
		Open();

		mNoEntries = mz_zip_reader_get_num_files(&mArchive);
		for (int i = 0; i < (int) mNoEntries; i++)
		{
			mz_zip_archive_file_stat file_stat;
			if (!mz_zip_reader_file_stat(&mArchive, i, &file_stat))
			{
				mz_zip_reader_end(&mArchive);
				throw new std::exception("Could not read file statistics.");
			}

			printf("Filename: \"%s\", Comment: \"%s\", Uncompressed size: %u, Compressed size: %u, Is Dir: %u\n", 
				file_stat.m_filename, 
				file_stat.m_comment, 
				(UInt) file_stat.m_uncomp_size, 
				(UInt)file_stat.m_comp_size, 
				mz_zip_reader_is_file_a_directory(&mArchive, i));

			ZipEntryMeta meta;
			meta.Name = String(file_stat.m_filename);
			meta.Comment = String(file_stat.m_comment);
			meta.UncompressedSize = file_stat.m_uncomp_size;
			meta.Compressed = file_stat.m_comp_size;
			meta.CrcCheckSum = file_stat.m_crc32;
			meta.IsDirectory = mz_zip_reader_is_file_a_directory(&mArchive, i) > 0 ? true : false;
			meta.HeapData = 0;

			mEntries.push_back(meta);
		}

		mz_zip_reader_end(&mArchive);
	}

	void Archive::Open()
	{
		memset(&mArchive, 0, sizeof(mz_zip_archive));
		auto status = mz_zip_reader_init_file(&mArchive, mFile.string().c_str(), 0);
		if (!status)
		{
			throw new std::exception("Could not initialze a zip file.");
		}
	}

	Archive::~Archive()
	{
		for (auto e : mEntries)
		{
			if (e.HeapData == 0)
			{
				continue;
			}

			mz_free(e.HeapData);
		}

		mEntries.clear();
	}

	void Archive::Close()
	{
		for (int i = 0; i < mEntries.size(); i++)
		{
			mz_free(mEntries[i].HeapData);
			mEntries[i].HeapData = 0;
		}

		mz_zip_reader_end(&mArchive);
	}

	String Archive::ToString() const
	{
		std::stringstream sstream;
		sstream << mFile << "\n";

		for (auto entry : mEntries)
		{
			sstream << "\t" << entry.ToString() << "\n";
		}

		return sstream.str();
	}

	void* Archive::ExtractToMemory(ZipEntryMeta& e)
	{
		Size uncomp_size;
		e.HeapData = mz_zip_reader_extract_file_to_heap(&mArchive, e.Name.c_str(), &uncomp_size, 0);
		if (!e.HeapData)
		{
			throw new std::exception("Could not extract entry to memory.");
			mz_zip_reader_end(&mArchive);
			return 0;
		}

		return e.HeapData;
	}

	Path Archive::ExtractToFile(ZipEntryMeta& e, const Path& destination)
	{
		std::filesystem::path dest = destination;
		if (std::filesystem::is_directory(destination))
		{
			auto parent_path = Path(e.Name).parent_path();	// Directory without file name.
			auto file_name = Path(e.Name).filename();
			dest = Path(destination);
			dest /= parent_path;
			/// Create the directories.
			std::filesystem::create_directories(dest);
			dest /= file_name;
		}
		else
		{
			auto path = destination.parent_path();
			std::filesystem::create_directories(path);
		}
		
		if (e.IsDirectory)
		{
			return dest;
		}

		auto result = mz_zip_reader_extract_file_to_file(&mArchive, e.Name.c_str(), dest.string().c_str(), 0);
		if (!result)
		{
			throw new std::exception("Could not extract file.");
		}

		return dest;
	}
}
		
#pragma once

#include "miniz.h"
#include "ZipEntryMeta.h"
#include "Types.h"
#include <ExecutablePath.h>

namespace Zip

{
	class Archive
	{
	private:
		mz_zip_archive mArchive;

		Path mFile;
		Size mNoEntries;
		Vector<ZipEntryMeta> mEntries;

	protected:

	public:
		/// <summary>
		/// C-Tor to create an in memory archive.
		/// 
		/// </summary>
		Archive();

		/// <summary>
		/// C-Tor to work with an archive on disk.
		/// 
		/// </summary>
		/// <param name="abs_path"></param>
		Archive(const Path& abs_path);
		~Archive();

		String ToString() const;

		/// <summary>
		/// Return the number of entries in the archive.
		/// 
		/// </summary>
		/// <returns></returns>
		Size GetNumOfEntries() const { return mNoEntries; }

		/// <summary>
		/// Open a file for interactions. Must be the first call before attempting to extract data from a zip file.
		/// 
		/// </summary>
		void Open();

		/// <summary>
		/// Write changes to the file directory to disk and close the file. Frees all heap memory we might have allocated.
		/// 
		/// </summary>
		void Close();

		/// <summary>
		/// Return meta data for the n-th entry.
		/// 
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		ZipEntryMeta& GetEntry(Size n) { return mEntries[n]; }

		/// <summary>
		/// Extracts the data into memory. The data will be referenced inside the given
		/// ZipEntryMeta-Data as well.
		/// 
		/// </summary>
		/// <param name="e"></param>
		/// <returns></returns>
		void* ExtractToMemory(ZipEntryMeta& e);

		/// <summary>
		/// Extracts a file to the given location copying the directory structure of the archive. All sub-directories below the
		/// destination will be created.
		///  
		/// </summary>
		/// <param name="e"></param>
		Path ExtractToFile(ZipEntryMeta& e, const Path& destination);

		/// <summary>
		/// Return the currently used version of miniz.
		/// 
		/// </summary>
		/// <returns></returns>
		static inline String GetMinizVersion() { return String(MZ_VERSION); }
	};
}
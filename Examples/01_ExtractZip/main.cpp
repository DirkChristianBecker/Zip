
#include <Archive.h>
#include <ExecutablePath.h>
#include <string>
#include <iostream>

/**
 * MAIN
 */
// #pragma warning(suppress: 4100)
int main(int argc, char** argv) 
{
    // Everything Zip related lives inside the namespace Zip.
    using namespace Zip;

    // Build path variables relative to the executable.
    auto path = Platform::GetPathRelativeToExecutable("../../Assets/Source.zip");
    auto target = Platform::GetPathRelativeToExecutable("../../Unpacked");

    // Create an archive. Creating an archive initializes file meta data...
    Archive archive(path);
    // ... as shown here.
    std::cout << archive.ToString() << std::endl;

    // Open must be called before any operations on the archive file occur.
    archive.Open();

    // Iterate over all entries in the file
    for (int i = 0; i < archive.GetNumOfEntries(); i++)
    {
        // Retrieve a single entry...
        auto e = archive.GetEntry(i);

        // ...and read the content of that entry from file into memory. 
        archive.ExtractToMemory(e);

        // After we called ExtractToMemory the data will be returned as a void* pointer,
        // but it is also stored in the entry itself, at least as long as no call to Archive::Close() occurs.
        // That´s why we can retrieve the data as a string value here.
        std::cout << "Loaded a file into memory. It´s content is: " << std::endl << e.GetAsText() << std::endl;
    }

    Vector<Path> p;
    Vector<Path> dir;
    
    // Iterate again...
    for (int i = 0; i < archive.GetNumOfEntries(); i++)
    {
        // Retrieve an entry.
        auto e = archive.GetEntry(i);

        // Write it to a file. The target is the destination folder, the name of the file
        // is derrived from the name inside the Zip-Archive. This method will replicate
        // the folder structure of the archive. If the will lives inside a folder in the
        // archive this folder will be created under the target folder on disk.
        auto final_dest = archive.ExtractToFile(e, target);

        // The location of the extracted file is returned and it can be a directory as well. 
        if (std::filesystem::is_directory(final_dest))
        {
            dir.push_back(final_dest);
            std::cout << "Created directory for '" << e.Name << "' at '" << dir[dir.size() - 1].string() << "'." << std::endl;
        }
        else
        {
            p.push_back(final_dest);
            std::cout << "Wrote '" << e.Name << "' to '" << p[p.size() - 1].string() << "'." << std::endl;
        }
    } 

    std::cout << "Press any enter to continue." << std::endl;
    std::getchar();

    // First remove all files
    for (int i = 0; i < p.size(); i++)
    {
        std::cout << "Removing '" << p[i].string() << "'" << std::endl;
        std::filesystem::remove(p[i]);
    }

    // Then remove all directories.
    for (int i = 0; i < dir.size(); i++)
    {
        std::cout << "Removing '" << dir[i].string() << "'" << std::endl;
        std::filesystem::remove_all(dir[i]);
    }

    archive.Close();

    return 0;
}
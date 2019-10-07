#include "IOManagerDefault.hpp"
#include <fstream>

namespace FEngine
{
    IOManagerDefault::IOManagerDefault()
    {
        
    }
    
    IOManagerDefault::~IOManagerDefault()
    {
        
    }
    
    bool IOManagerDefault::GetAssetStream(std::string assetPath, std::vector<char> & buffer)
    {
        std::ifstream assetFile(assetPath.c_str(), std::ios::binary);
        if (!assetFile){
            return false;
        }
        
        // Calculate file size
        assetFile.seekg (0, assetFile.end);
        int fileSize = (int)assetFile.tellg();
        assetFile.seekg (0, assetFile.beg);
        
        buffer.resize(fileSize);
        
        assetFile.read(&buffer[0], fileSize);
        
        assetFile.close();
        
        return true;
    }
   
};


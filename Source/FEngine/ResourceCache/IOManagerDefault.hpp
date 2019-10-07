
#pragma once

#include "IOManager.hpp"

namespace FEngine
{

    /**
     * This is the default file manager using standard C+ fstream libraries for reading files
     */
    class IOManagerDefault : public IOManager
    {
    public:
        IOManagerDefault();
        virtual ~IOManagerDefault();
        
        /**
         * Opens file natively and returns raw data stream.
         */
        //virtual bool GetFileStream(std::string inFile, std::string & dataStream);
        
        virtual bool GetAssetStream(std::string assetPath, std::vector<char> & buffer);
        
        //virtual unsigned int GetGLTextureFromPngFile(std::string pngFile);
        
    private:
        
    };
    
};



#pragma once

#include <string>
#include <vector>


namespace FEngine
{
    /**
     * Abstract class for handing os dependent files
     */
    class IOManager
    {
    public:
        IOManager(){}
        virtual ~IOManager(){}
        
        /**
         * Gets RAW data stream from file
         */
        //virtual bool GetFileStream(std::string inFile, std::string & dataStream) = 0;
        
        virtual bool GetAssetStream(std::string assetPath, std::vector<char> & buffer) = 0;
        
        /**
         * Process PNG file and return OpenGL texture
         */
        //virtual unsigned int GetGLTextureFromPngFile(std::string pngFile) = 0;
        
    };

};


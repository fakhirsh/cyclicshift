
#pragma once


namespace FEngine
{
    /**
     * Abstract class for platform independent rendering
     */
    class Renderer
    {
    public:
        Renderer();
        virtual ~Renderer();
                
        virtual void EnableAlphaBlending();
        
        void ClearColor(float r, float g, float b, float a);
        void Clear();
        
        void SetViewPort(float x, float y, float width, float height);

        void BindTexture(unsigned int textureId);
        void UnBindTexture();
        
        void DeleteTextures(unsigned int size, const unsigned int * textures);

        /*
         * IMPORTANT: The textures MUST be a power of 2, specially on OpenGL ES2. 
         *              Otherwise they won't display properly on the screen. Even
         *              if one of the many textures is mal formed, it will screw
         *              up all others.
         * */
        unsigned int LoadTextureFromPixels32 (unsigned int texWidth, 
                                                unsigned int texHeight, 
                                                bool hasAlpha, 
                                                unsigned int * pixels );

        void GenVertexArrays(unsigned int size, unsigned int * arrays);
        void BindVertexArray(unsigned int arrayId);
        
        /*
         * @param mode GL_TRIANGLE, GL_QUAD etc etc
         * @param firstIndex
         * @param size number of items (i.e vertices) in the vertex array
         *
         * Note: Vertex array is already bound before calling this function.
         *
         */
        void DrawArrays(unsigned int mode, int firstIndex, int size);

        void EnableVertexAttribArray(int attributeLocation);

        void DisableVertexAttribArray(int attributeLocation);

        void VertexAttribPointer(unsigned int index,
                                          int size,
                                          unsigned int type,
                                          bool normalized,
                                          unsigned int stride,
                                          const void * pointer);

        void EnableDepth();

	};

};

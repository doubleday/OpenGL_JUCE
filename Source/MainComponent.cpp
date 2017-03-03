/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#define STRINGIFY(A)  #A
#ifdef JUCE_OPENGL_ES
    #define LOWP lowp
#else
    #define LOWP
#endif

struct Vertex  // class storing the information about a single vertex
{
    float position[3];
    float normal[3];
    float colour[4];
    float texCoord[2];
};


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
//==============================================================================
class MainContentComponent   : public OpenGLAppComponent,
private Timer
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize(800, 600);
        startTimerHz(60);
        x = 0;
        y = 0;
        position = nullptr;
        normal = nullptr;
        textureCoordIn = nullptr;
        sourceColour = nullptr;
        gl = openGLContext.extensions;
        
        openGLContext.setContinuousRepainting(false);
    }
    
    ~MainContentComponent()
    {
        shutdownOpenGL();
    }

    void initialise() override
    {
        createShaders();
        
        auto image = ImageFileFormat::loadFrom(BinaryData::texture_png, (size_t)BinaryData::texture_pngSize);
        texture = new OpenGLTexture();
        texture->loadImage(image);
    }

    void openGLContextClosing() override
    {
        openGLContext.detach();
        
        texture->release();
    }
    
    void shutdown() override
    {
        shader = nullptr;
    }

    void render() override
    {
        
        // Stuff to be done before defining your triangles
        jassert(OpenGLHelpers::isContextActive());

        const float desktopScale =(float) openGLContext.getRenderingScale();
        OpenGLHelpers::clear(Colour::greyLevel(0.1f));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, roundToInt(desktopScale * getWidth()), roundToInt(desktopScale * getHeight()));

        shader->use();

        gl.glGenBuffers(1, &vertexBuffer);
        gl.glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        

        // ************************** TRIANGLES DEFINITION
        // Here you can draw whatever you want
        
        Array<Vertex> vertices;
        Vertex v1 =
        {
            { -0.25f + x, -0.25f + y, 0.0f},
            { 0.5f, 0.5f, 0.5f},
            { 1.0f, 0.0f, 0.0f, 0.5f },
            { 0.5f, 0.5f,}
        };
        vertices.add(v1);
        Vertex v2 =
        {
            { 0.0f + x, 0.25f + y, 0.0f},
            { 0.5f, 0.5f, 0.5f},
            { 1.0f, 0.0f, 1.0f, 0.5f },
            { 0.5f, 0.5f}
        };
        vertices.add(v2);
        Vertex v3 =
        {
            { 0.25f + x, -0.25f + y, 0.0f},
            { 0.5f, 0.5f, 0.5f},
            { 1.0f, 1.0f, 0.0f, 0.5f },
            { 0.5f, 0.5f,}
        };
        vertices.add(v3);
        int indices[] = {0, 1, 2};
        numIndices = 3;
        // ************************************************
        
        // Now prepare this information to be drawn
        gl.glBufferData(
            GL_ARRAY_BUFFER,
           static_cast<GLsizeiptr>(static_cast<size_t>(vertices.size()) * sizeof(Vertex)),
           vertices.getRawDataPointer(), GL_STATIC_DRAW);
        
        gl.glGenBuffers(1, &indexBuffer);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        gl.glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(static_cast<size_t>(numIndices) * sizeof(juce::uint32)),
            indices, GL_STATIC_DRAW);
        
        gl.glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        
        if (position != nullptr)
        {
            gl.glVertexAttribPointer(position->attributeID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            gl.glEnableVertexAttribArray(position->attributeID);
        }
        
        if (normal != nullptr)
        {
            gl.glVertexAttribPointer(normal->attributeID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)(sizeof(float) * 3));
            gl.glEnableVertexAttribArray(normal->attributeID);
        }
        
        if (sourceColour != nullptr)
        {
            gl.glVertexAttribPointer(sourceColour->attributeID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)(sizeof(float) * 6));
            gl.glEnableVertexAttribArray(sourceColour->attributeID);
        }
        
        if (textureCoordIn != nullptr)
        {
            gl.glVertexAttribPointer(textureCoordIn->attributeID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)(sizeof(float) * 10));
            gl.glEnableVertexAttribArray(textureCoordIn->attributeID);
        }
        
        //glPointSize(20.0);
        //glDrawElements(GL_POINTS, numIndices, GL_UNSIGNED_INT, 0);  // Draw triangles!
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);  // Draw triangles!
        
        if (position != nullptr)       gl.glDisableVertexAttribArray(position->attributeID);
        if (normal != nullptr)         gl.glDisableVertexAttribArray(normal->attributeID);
        if (sourceColour != nullptr)   gl.glDisableVertexAttribArray(sourceColour->attributeID);
        if (textureCoordIn != nullptr)  gl.glDisableVertexAttribArray(textureCoordIn->attributeID);
        
        // Reset the element buffers so child Components draw correctly
        gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        gl.glDeleteBuffers(1, &vertexBuffer);
        gl.glDeleteBuffers(1, &indexBuffer);
        
    }
    
    void paint(Graphics& g) override
    {
        // You can add your component specific drawing code here!
        // This will draw over the top of the openGL background.
        
        g.setColour(Colours::white);
        g.setFont(20);
        g.drawText("OpenGL example", 25, 20, 300, 30, Justification::left);
        g.drawLine(20, 20, 170, 20);
        g.drawLine(20, 50, 170, 50);
    }
    
    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        
    }
    
    void createShaders()
    {
        // Here we define the shaders use to draw our triangle. They are very simple.

        vertexShader = STRINGIFY(
        
            attribute vec4 position;
            attribute vec4 sourceColour;
            attribute vec2 textureCoordIn;
            
            varying vec4 destinationColour;
            varying vec2 textureCoordOut;
            
            void main()
            {
                destinationColour = sourceColour;
                textureCoordOut = textureCoordIn;
                gl_Position = position;
            }
                
        );
        
        fragmentShader = STRINGIFY(
        
            \n#ifdef JUCE_OPENGL_ES\n\n#define LOWP lowp\n\n#else\n\n#define LOWP\n\n#endif\n

            varying LOWP vec4 destinationColour;
            varying LOWP vec2 textureCoordOut;
            uniform sampler2D demoTexture;
            
            void main()
            {
               gl_FragColor = destinationColour;
            }
        
        );
        
        ScopedPointer<OpenGLShaderProgram> newShader(new OpenGLShaderProgram(openGLContext));
        String statusText;
        
        if (newShader->addVertexShader(OpenGLHelpers::translateVertexShaderToV3(vertexShader))
            && newShader->addFragmentShader(OpenGLHelpers::translateFragmentShaderToV3(fragmentShader))
            && newShader->link())
        {
            shader = newShader;
            shader->use();
            
            position = BindShaderAttribute(shader, "position");
            sourceColour = BindShaderAttribute(shader, "sourceColour");
            normal = BindShaderAttribute(shader, "normal");
            textureCoordIn = BindShaderAttribute(shader, "textureCoordIn");
            
            statusText = "GLSL: v" + String(OpenGLShaderProgram::getLanguageVersion(), 2);
        }
        else
        {
            statusText = newShader->getLastError();
        }
    }
    
    OpenGLShaderProgram::Attribute* BindShaderAttribute(OpenGLShaderProgram *shader, StringRef name)
    {
        if (gl.glGetAttribLocation(shader->getProgramID(), name) < 0)
        {
            return nullptr;
        }
        else
        {
            return new OpenGLShaderProgram::Attribute(*shader, name);
        }
    }
    
private:
    GLuint vertexBuffer, indexBuffer;
    int numIndices;

    float x;
    float y;

    const char* vertexShader;
    const char* fragmentShader;
    
    ScopedPointer<OpenGLShaderProgram> shader;
    ScopedPointer<OpenGLShaderProgram::Attribute> position, normal, sourceColour, textureCoordIn;
    ScopedPointer<OpenGLTexture> texture;
    String newVertexShader, newFragmentShader;
    
    OpenGLExtensionFunctions gl;
    
    void timerCallback() override
    {
        // Here you move your triangles
        x = x + 0.001;
        y = y + 0.001;
        if (x > 1)
            x -= 2;
        if (y > 1)
            y -= 2;
    }

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

//(This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new MainContentComponent(); }

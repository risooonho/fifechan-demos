#include <fifechan.hpp>
#include <fifechan/sdl/sdlinput.hpp>
#include <fifechan/opengl/openglgraphics.hpp>
#include <fifechan/opengl/openglsdlimageloader.hpp>
#include <SDL2/SDL.h>
#include <sstream>

/**
 * See how an hbox is arranged into a vbox.
 *
 * Test doesn't do any memory management in sake of
 * usability. (and my sanity :) )
 */

int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;
    fcn::SDLInput* input;
    fcn::OpenGLGraphics* graphics;
    fcn::OpenGLSDLImageLoader* imageLoader;
    fcn::ImageFont* font;
    fcn::Gui* gui;
    fcn::Container* top;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("HBox arranged within VBox", 0, 0, 800, 600, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

   
    try
    {
        imageLoader = new fcn::OpenGLSDLImageLoader;
        fcn::Image::setImageLoader(imageLoader);
        
        graphics = new fcn::OpenGLGraphics(800, 600);
        input = new fcn::SDLInput;
        
        font = new fcn::ImageFont("fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        fcn::Widget::setGlobalFont(font);
        
        gui = new fcn::Gui;
        gui->setGraphics(graphics);
        gui->setInput(input);
        
        top = new fcn::Container;
        top->setDimension(fcn::Rectangle(0, 0, 800, 600));
        top->setOpaque(false);
        gui->setTop(top);
        
        fcn::TextBox *txtBox = new fcn::TextBox;
        txtBox->setDimension(fcn::Rectangle(100, 50, 200, 200));
        
        top->add(txtBox);
        
        bool running = true;
        SDL_Event evt;
        while(running)
        {
            SDL_RenderClear(renderer);

            while(SDL_PollEvent(&evt))
            {
                if(evt.type == SDL_QUIT)
                {
                    running = false;
                }
                
                input->pushInput(evt);
            }
            
            gui->logic();
            gui->draw();
            SDL_GL_SwapWindow(window);
        }
    }
    catch(const fcn::Exception& exc)
    {
        std::cerr << exc.getMessage() << " " << exc.getLine() << "\n";
    }
    
    return 0;
}

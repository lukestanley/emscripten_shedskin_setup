#include "builtin.hpp"

#include "enginePyGame.hpp"

namespace __enginePyGame__ {
    
    str *__name__;
    
    
    /**                                                                           
    class HandlerBase                                                               
    */                                                                        
    class_ *cl_HandlerBase;                                                           

    HandlerBase::HandlerBase() 
    { 
        this->__class__ = cl_HandlerBase; 
    }


    void HandlerBase::__static__() 
    {                                              
    }

    class_ *cl_Engine;

    int Engine::mapVal = 1;

    Engine::Engine()
    {
        Engine::instance = this;
    }


    Engine::Engine(int __ss_init)
    {
        // Tell shedkin generated classes that this class corresponds to class
        // with name cl_Engine
        this->__class__ = cl_Engine;
        Engine::instance = this;
        __init__();
    }


    void* Engine::__init__()
    {
        return NULL;
    }


    void* Engine::init()
    {
        PYJS_Draw_init();
        return NULL;
    }


    void* Engine::cleanup()
    {
        PYJS_Draw_cleanup();
        return NULL;
    }

    
    void* Engine::beginPath()
    {
        PYJS_Draw_beginPath();
        return NULL;
    }


    void* Engine::strokeStyle(__ss_int r,
                              __ss_int g,
                              __ss_int b,
                              __ss_int a)
    {
        PYJS_Draw_strokeStyle(r, g, b, a);
        return NULL;
    }


    void* Engine::lineWidth(__ss_int w)
    {
        PYJS_Draw_lineWidth(w);
        return NULL;
    }


    void* Engine::moveTo(__ss_int x, __ss_int y)
    {
        PYJS_Draw_moveTo(x, y);
        return NULL;
    }


    void* Engine::lineTo(__ss_int x, __ss_int y)
    {
        PYJS_Draw_lineTo(x, y);
        return NULL;
    }


    void* Engine::arc(__ss_int x,
                              __ss_int y,
                              __ss_int r,
                              double sAngle,
                              double eAngle)
    {
        PYJS_Draw_arc(x, y, r, sAngle, eAngle);
        return NULL;
    }
        

    void* Engine::stroke()
    {
        PYJS_Draw_stroke();
        return NULL;
    }


    void* Engine::clearRect()
    {
        PYJS_Draw_clearRect();
        return NULL;
    }


    void* Engine::loop()
    {
        PYJS_Draw_loop();
        return NULL;
    }


    void* Engine::stop()
    {
        PYJS_Draw_stop();
        return NULL;
    }


    void* Engine::paint()
    {
        PYJS_Draw_paint();
        return NULL;
    }


    void* Engine::setTimerDelay(__ss_int delay)
    {
        PYJS_Draw_setTimerDelay(delay);
        return NULL;
    }


    void __init() 
    {
        // Set name of corresponding python file as Engine
        __name__ = new str("enginePyGame");

        // // Value of cl_HandlerBase is used in HandlerBase's constructor
        cl_HandlerBase = new class_("HandlerBase"); 

        // Value of cl_Engine is used in Engine's constructor
        cl_Engine = new class_("Engine");
    }


    void mouseDownCbAdaptor(int mapVal, int x, int y, int button)
    {
        std::map<int, Engine::MouseDownPair>::iterator i = Engine::instance->
                                                  _mouseDownCbMap.find(mapVal);
        i->second.first(i->second.second, Engine::instance, x, y, button);
    }


    void mouseMoveCbAdaptor(int mapVal, int x, int y)
    {
        std::map<int, Engine::MouseMovePair>::iterator i = Engine::instance->
                                                  _mouseMoveCbMap.find(mapVal);
        i->second.first(i->second.second, Engine::instance, x, y);
    }


    void mouseUpCbAdaptor(int mapVal, int x, int y, int button)
    {
        std::map<int, Engine::MouseUpPair>::iterator i = Engine::instance->
                                                    _mouseUpCbMap.find(mapVal);
        i->second.first(i->second.second, Engine::instance, x, y, button);
    }


    void quitCbAdaptor(int mapVal)
    {
        std::map<int, Engine::QuitPair>::iterator i = Engine::instance->
                                                       _quitCbMap.find(mapVal);
        i->second.first(i->second.second, Engine::instance);
    }


    void timerCbAdaptor(int mapVal)
    {
        std::map<int, Engine::TimerPair>::iterator i =Engine::instance->
                                                      _timerCbMap.find(mapVal);
        i->second.first(i->second.second, Engine::instance);
    }

} // close module namespace


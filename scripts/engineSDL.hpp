#ifndef __ENGINE_HPP
#define __ENGINE_HPP

#include "SDL.h"
#include <deque>

using namespace __shedskin__;
namespace __enginePyGame__ {

class HandlerBase;
class Engine;
class Canvas;

typedef __ss_bool (*CallbackHandlerEngine)(HandlerBase*, Engine *);
typedef __ss_bool (*CallbackHandlerEngine2xInt)(HandlerBase*, Engine *, __ss_int, __ss_int);
typedef __ss_bool (*CallbackHandlerEngine3xInt)(HandlerBase*, Engine *, __ss_int, __ss_int, __ss_int);


extern str *__name__;


extern class_ *cl_HandlerBase;
class HandlerBase : public pyobj {
public:
    HandlerBase() { this->__class__ = cl_HandlerBase; }
    static void __static__();
};

extern class_ *cl_Engine;
class Engine : public pyobj {

    class SdlLibrary {
        SDL_Surface* __screen;
    public:
        SdlLibrary();
        ~SdlLibrary();
        SDL_Surface* const screen() { return __screen; }
    };
    static SdlLibrary* __sdlLibrary;
    
    Canvas* __canvas;
    
    bool __running;
    int __timerDelay;

    typedef std::deque<std::pair<CallbackHandlerEngine, HandlerBase*> > CallbackHandlerEngineList;
    typedef std::deque<std::pair<CallbackHandlerEngine2xInt, HandlerBase*> > CallbackHandlerEngine2xIntList;
    typedef std::deque<std::pair<CallbackHandlerEngine3xInt, HandlerBase*> > CallbackHandlerEngine3xIntList;

    CallbackHandlerEngineList __timerCallbacks;
    CallbackHandlerEngineList __quitCallbacks;
    CallbackHandlerEngine2xIntList __mouseMoveCallbacks;
    CallbackHandlerEngine3xIntList __mouseButtonDownCallbacks;
    CallbackHandlerEngine3xIntList __mouseButtonUpCallbacks;

    void handleEvent(CallbackHandlerEngineList& callbacks);
    void handleEvent(CallbackHandlerEngine3xIntList& callbacks, int x1, int x2, int x3);
    void handleEvent(CallbackHandlerEngine2xIntList& callbacks, int x1, int x2);

public:

    Engine(): __canvas(0), __timerDelay(0), __running(false) {}
    Engine(int __ss_init) {
        this->__class__ = cl_Engine;
        __init__();
    }
    void *__init__();
    void *init();
    void *cleanup();
    void *setTimerDelay(__ss_int delay);

    // NOTE: couldn't make the compiler digest these without a template method
    template<typename T>
    void *connectTimerCallback(T method, HandlerBase* handler) {
        __timerCallbacks.push_back(std::make_pair((CallbackHandlerEngine)method, handler));
        return NULL;
    }
    template<typename T>
    void *connectQuitCallback(T method, HandlerBase* handler) {
        __quitCallbacks.push_back(std::make_pair((CallbackHandlerEngine)method, handler));
        return NULL;
    }
    template<typename T>
    void *connectMouseButtonDownCallback(T method, HandlerBase* handler) {
        __mouseButtonDownCallbacks.push_back(std::make_pair((CallbackHandlerEngine3xInt)method, handler));
        return NULL;
    }
    template<typename T>
    void *connectMouseButtonUpCallback(T method, HandlerBase* handler) {
        __mouseButtonUpCallbacks.push_back(std::make_pair((CallbackHandlerEngine3xInt)method, handler));
        return NULL;
    }
    template<typename T>
    void *connectMouseMoveCallback(T method, HandlerBase* handler) {
        __mouseMoveCallbacks.push_back(std::make_pair((CallbackHandlerEngine2xInt)method, handler));
        return NULL;
    }

    void *loop();
    void *stop();

    void *beginPath();
    void *strokeStyle(__ss_int r, __ss_int g, __ss_int b, __ss_int a = 255);
    void *lineWidth(__ss_int w);
    void *moveTo(__ss_int x, __ss_int y);
    void *lineTo(__ss_int x, __ss_int y);
    void *arc(__ss_int x, __ss_int y, __ss_int r, double sAngle, double eAngle);
    void *stroke();
    void *paint();
    void *clearRect();
};

void __init();

} // module namespace
#endif

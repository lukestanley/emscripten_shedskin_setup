#ifndef PY_TO_JS_ENGINE_HPP
#define PY_TO_JS_ENGINE_HPP

#include "PYJS_Draw.hpp"
#include <map>
#include <stdio.h>

using namespace __shedskin__;

/**
* @brief Namespace corresponding to python file Engine
*
* Each python file is converted to a namespace by Shedskin. This namespace
* corresponds to file enginePyGame.py
*/
namespace __enginePyGame__ {
    
    /**
    * @brief Name of the python file
    *
    * Shedskin converted code requires this variable for each python file and
    * this variable contains the name of the file
    */
    extern str *__name__;

    extern class_ *cl_HandlerBase;                                                        
    class HandlerBase : public pyobj 
    {                                             
      public:
        HandlerBase();
        static void __static__();                           
    };



    /**
    * @brief Pointer to handle of Engine.
    *
    * This pointer of type class_ is used to register a C++ class as 
    * corresponding to a specific Python class. This registration is done 
    * partly at the constructor and partly in global init() function inside
    * the namespace.
    */
    extern class_ *cl_Engine;
    
    /**
    * @brief The main Engine used to draw 2D objects in JS
    *
    * Engine is used by python class of the same name to draw 2D 
    * objects in HTML canvas using JavaScript. To be continued... 
    */
    class Engine : public pyobj
    {
      public:
        typedef __ss_bool (*CallbackHandlerEngine)(HandlerBase*, Engine *);
        typedef __ss_bool (*CallbackHandlerEngine2xInt)(HandlerBase*, Engine *,
                                                           __ss_int, __ss_int);
        typedef __ss_bool (*CallbackHandlerEngine3xInt)(HandlerBase*, Engine *,
                                                 __ss_int, __ss_int, __ss_int);
        
        typedef CallbackHandlerEngine3xInt MouseDownCb;
        typedef CallbackHandlerEngine2xInt MouseMoveCb;
        typedef CallbackHandlerEngine3xInt MouseUpCb;
        typedef CallbackHandlerEngine QuitCb;
        typedef CallbackHandlerEngine TimerCb;

        typedef std::pair<MouseDownCb, HandlerBase*>  MouseDownPair;
        typedef std::pair<MouseMoveCb, HandlerBase*>  MouseMovePair;
        typedef std::pair<MouseUpCb, HandlerBase*>    MouseUpPair;
        typedef std::pair<TimerCb, HandlerBase*>      TimerPair;
        typedef std::pair<QuitCb, HandlerBase*>       QuitPair;

        std::map<int, MouseDownPair>      _mouseDownCbMap;
        std::map<int, MouseMovePair>      _mouseMoveCbMap;
        std::map<int, MouseUpPair>        _mouseUpCbMap;
        std::map<int, QuitPair>           _quitCbMap;
        std::map<int, TimerPair>          _timerCbMap;

        static int                  mapVal;
        static Engine*                    instance;

        
        /**
        * @brief Empty constructor.
        *
        * No specific use. Yet mandated by Shedskin. Sets state as
        * uninitialized.
        */
        Engine();

        /**
        * @brief Used by Shedskin generated code to initialize this class.
        *
        * States that this class corresponds to a python class of same name.
        *
        * @param __ss_init Used by shedskin generated code. Not for users.
        */
        Engine(int __ss_init);
        
        /**
        * @brief Corresponding to Python's __init__. 
        *
        * Creates Engine class with state as unintialized.
        *
        * @return Always returns NULL. Can be ignored.
        */
        void *__init__();

        /**
        * @brief Initializes the HTML canvas/engine. 
        *
        * If canvas/engine is already initialized this call does nothing. Else 
        * creates the canvas.
        *
        * @return Always returns NULL. Can be ignored.
        */
        void *init();

        /**
        * @brief Cleans up the canvas/engine.
        *
        * After this call the canvas element is removed from the document. If
        * the engine/canvas was not initialized this call is ignored.
        *
        * @return Always returns NULL. Can be ignored.
        */
        void *cleanup();

        void *setTimerDelay(__ss_int delay);

        template <class T>
        void *connectMouseButtonDownCallback(T cb, HandlerBase* handler);        

        template <class T>
        void* connectMouseMoveCallback(T cb, HandlerBase* handler);

        template <class T>
        void* connectMouseButtonUpCallback(T cb, HandlerBase* handler);

        template <class T>
        void* connectQuitCallback(T cb, HandlerBase* handler);

        template <class T>
        void* connectTimerCallback(T cb, HandlerBase* handler);

        /**
        * @brief Begins a path in the HTML canvas.
        *
        * Begins a path in the HTML canvas. If canvas/engine is uninitialized,
        * this call is ignored.
        *
        * @return Always returns NULL. Can be ignored.
        */
        void *beginPath();

        /**
        * @brief Currently Unimplemented. TBD
        *
        * @param r
        * @param g
        * @param b
        * @param a
        *
        * @return 
        */
        void *strokeStyle(__ss_int r, __ss_int g, __ss_int b, __ss_int a = 255);
        
        /**
        * @brief Sets the width of the subsequent drawings.
        *
        * Sets the width of the subsequent drawing commands as w pixels. If
        * canvas/engine is uninitialized this call is ignored.
        *
        * @param w Width in pixels.
        *
        * @return Always returns NULL. Can be ignored.
        */
        void *lineWidth(__ss_int w);

        /**
        * @brief Moves to the specified point in the canvas
        *
        * Moves the begin point of the next drawing to a specific point in the
        * canvas. If canvas/engine is uninitialized this call is ignored.
        * 
        * @param x x-cordinate of the point moved to.
        * @param y y-cordinate of the point moved to.
        *
        * @return Always returns NULL. Can be ignored
        */
        void *moveTo(__ss_int x, __ss_int y);

        /**
        * @brief Draws a line to the specified point.
        *
        * Draws a line from the previously moved point to the specified point.
        * If canvas/engine is uninitialized this call is ignored. stroke() must
        * be called after this call to actually flush the drawing to the canvas
        *
        * @param x  x-cordinate of the point to which line is drawn
        * @param y  y-cordinate of the point to which line is drawn 
        *
        * @return Always returns NULL. Can be ignored
        */
        void *lineTo(__ss_int x, __ss_int y);

        void *arc(__ss_int x, __ss_int y, __ss_int r, double sAngle,
                                                      double eAngle);
        
        /**
        * @brief Flushes out the drawsing to the canvas
        *
        * @return Always returns NULL. Can be ignored
        */
        void *stroke();

        void *stop();

        void *loop();

        void *paint();

        void *clearRect();
        
    };

    /**
    * @brief Used by shedskin generated code to register a class
    *
    * This function provides the values to the above variables __name__ and 
    * cl_Engine. This function along with class's constructor actually
    * completes registration procedure
    */
    void __init();


    void mouseDownCbAdaptor(int mapVal, int x, int y, int button);


    void mouseMoveCbAdaptor(int mapVal, int x, int y);


    void mouseUpCbAdaptor(int mapVal, int x, int y, int button);


    void quitCbAdaptor(int mapVal);


    void timerCbAdaptor(int mapVal);
    

    template <class T>
    void* Engine::connectMouseButtonDownCallback(T cb, HandlerBase* handler)
    {
        _mouseDownCbMap.insert(std::pair<int, MouseDownPair> 
                             (mapVal, MouseDownPair((MouseDownCb)cb,handler)));
        PYJS_Draw_MouseDownCb adaptCb = mouseDownCbAdaptor;    
        PYJS_Draw_connectMouseButtonDownCallback(Engine::mapVal, adaptCb);
        ++Engine::mapVal;
        return NULL;
    }


    template <class T>
    void* Engine::connectMouseMoveCallback(T cb, HandlerBase* handler)
    {
        
        _mouseMoveCbMap.insert(std::pair<int, MouseMovePair>
                            (mapVal, MouseMovePair((MouseMoveCb)cb,handler)));
        PYJS_Draw_MouseMoveCb adaptCb = mouseMoveCbAdaptor; 
        PYJS_Draw_connectMouseMoveCallback(Engine::mapVal, adaptCb);
        ++Engine::mapVal;
        return NULL;
    }

    
    template <class T>
    void* Engine::connectMouseButtonUpCallback(T cb, HandlerBase* handler)
    {
        
        _mouseUpCbMap.insert(std::pair<int, MouseUpPair> 
                                (mapVal, MouseUpPair((MouseUpCb)cb,handler)));
        PYJS_Draw_MouseUpCb adaptCb = mouseUpCbAdaptor;    
        PYJS_Draw_connectMouseButtonUpCallback(Engine::mapVal, adaptCb);
        ++Engine::mapVal;
        return NULL;
    }

    
    template <class T>
    void* Engine::connectQuitCallback(T cb, HandlerBase* handler)
    {
       
        _quitCbMap.insert(std::pair<int, QuitPair> 
                                        (mapVal, QuitPair((QuitCb)cb,handler)));
        PYJS_Draw_QuitCb adaptCb = quitCbAdaptor;    
        PYJS_Draw_connectQuitCallback(Engine::mapVal, adaptCb);
        ++Engine::mapVal;
        return NULL;
    }


    template <class T>
    void* Engine::connectTimerCallback(T cb, HandlerBase* handler)
    {
        _timerCbMap.insert(std::pair<int, TimerPair> 
                                      (mapVal, TimerPair((TimerCb)cb,handler)));
        PYJS_Draw_TimerCb adaptCb = timerCbAdaptor;   
        PYJS_Draw_connectTimerCallback(Engine::mapVal, adaptCb);
        ++Engine::mapVal;
        return NULL;
    }

} // close module namespace

#endif

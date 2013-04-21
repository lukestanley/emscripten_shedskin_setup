#include "builtin.hpp"
#include "enginePyGame.hpp"
#include <iostream>
#include <queue>
#include <assert.h>
#include <algorithm>
#include "SDL_gfxPrimitives.h"
#include "SDL_rotozoom.h"

#define __USE_MATH_DEFINES
#include <math.h>

namespace __enginePyGame__ {

str *__name__;

const int SCALE = 4;
const int WIDTH = 640;
const int HEIGHT = 480;

Uint32 internal_timer_callback(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return (interval);
}

Engine::SdlLibrary* Engine::__sdlLibrary = 0;

Engine::SdlLibrary::SdlLibrary()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_WM_SetCaption("SDL Test", "SDL Test");

    __screen = SDL_SetVideoMode(640, 480, 0, 0);
    SDL_FillRect(__screen, NULL, SDL_MapRGB(__screen->format, 0, 0, 0));
}

Engine::SdlLibrary::~SdlLibrary()
{
    SDL_Quit();
}

/**
 * class Canvas
 */
class Canvas
{
    struct Cursor
    {
	int x;
	int y;
	Cursor() : x(0), y(0) {}
	Cursor(int x, int y): x(x), y(y) {}
	Cursor(const Cursor& c): x(c.x), y(c.y) {}
	Cursor& operator=(const Cursor& c) {
	    x = c.x;
	    y = c.y;
	    return *this;
	}
    };

    struct Color
    {
	int r;
	int g;
	int b;
	int a;
	Color(): r(0), g(0), b(0), a(255) {}
	Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a) {}
	Color(const Color& c): r(c.r), g(c.g), b(c.b), a(c.a) {}
	Color& operator=(const Color& c) {
	    r = c.r;
	    g = c.g;
	    b = c.b;
	    a = c.a;
	    return *this;
	}
    };

    struct Environment
    {
	int width;
	Color color;
	Cursor cursor;
	Environment(): width(1) {}
    };

    class Action
    {
    public:
	Action() {}
	virtual ~Action() {}
	virtual void execute(Environment &env) = 0;
    };

    class ArcAction : public Action
    {
	int __x;
	int __y;
	int __r;
	double __startAngle;
	double __endAngle;
	Canvas* __canvas;
    public:
	ArcAction(Canvas* canvas, int x, int y, int r, double startAngle, double endAngle) :
	    __canvas(canvas), __x(x), __y(y), __r(r), __startAngle(startAngle), __endAngle(endAngle) {}
	void execute(Environment &env) {
	    __canvas->drawArc(
		__x, __y,
		__r,
		env.width,
		__startAngle, __endAngle,
		env.color.r, env.color.g, env.color.b, env.color.a
		);
	}
    };

    class MoveToAction : public Action
    {
	int __x;
	int __y;
    public:
	MoveToAction(int x, int y): __x(x), __y(y) {}
	void execute(Environment &env) {
	    env.cursor.x = __x;
	    env.cursor.y = __y;
	}
    };

    class LineToAction : public Action
    {
	int __x;
	int __y;
	Canvas* __canvas;
    public:
	LineToAction(Canvas* canvas, int x, int y): __canvas(canvas), __x(x), __y(y) {}
	void execute(Environment &env) {
	    int x1 = env.cursor.x;
	    int y1 = env.cursor.y;
	    int x2 = __x;
	    int y2 = __y;
	    if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	    }

	    __canvas->drawLine(
		x1, y1, x2, y2,
		env.width,
		env.color.r, env.color.g, env.color.b, env.color.a
		);
	}
    };

    void flipScreen();

    Environment __environment;
    std::queue<Action*> __actions;

    void clearActions();

    SDL_Surface* const __screen; // provided by engine
    SDL_Surface* __buffer;

public:
    Canvas(SDL_Surface* screen);
    ~Canvas();

    void drawLine(int x1, int y1, int x2, int y2, int w, int r, int g, int b, int a);
    void drawArc(int x, int y, int radius, int w, double startAngle, double endAngle, int r, int g, int b, int a);

    void arc(__ss_int x, __ss_int y, __ss_int r, double sAngle, double eAngle);
    void lineTo(__ss_int x, __ss_int y);
    void moveTo(__ss_int x, __ss_int y);
    void beginPath();
    void stroke();
    void paint();
    void clearRect();
    void setLineWidth(int w);
    void setStrokeStyle(int r, int g, int b, int a = 255);
};

Canvas::Canvas(SDL_Surface* screen): __screen(screen)
{
    std::cout << "Canvas" << std::endl;

    __buffer = SDL_CreateRGBSurface(SDL_SWSURFACE,
	__screen->w * SCALE, __screen->h * SCALE,
	32,
	__screen->format->Rmask,
	__screen->format->Bmask,
	__screen->format->Gmask,
	__screen->format->Amask
	);
    SDL_FillRect(__buffer, NULL, SDL_MapRGB(__buffer->format, 0, 0, 0));
}

Canvas::~Canvas()
{
    std::cout << "~Canvas" << std::endl;
    SDL_FreeSurface(__buffer);
    clearActions();
}

void Canvas::flipScreen()
{
    SDL_Surface* shrinked = shrinkSurface(__buffer, SCALE, SCALE);
    SDL_BlitSurface(shrinked, NULL, __screen, NULL);
    SDL_Flip(__screen);
    SDL_FreeSurface(shrinked);

}

void Canvas::drawLine(int x1, int y1, int x2, int y2, int w, int r, int g, int b, int a)
{
    x1 *= SCALE;
    x2 *= SCALE;
    y1 *= SCALE;
    y2 *= SCALE;
    w *= SCALE;

    // NOTE: apparently the arcRGBA and circleRGBA swaps green and blue, so we have to compensate somehow
    //       if this bug is fixed, just comment the next line
    std::swap(g, b);

    thickLineRGBA(__buffer, x1, y1, x2, y2, w, r, g, b, a);
}

void Canvas::drawArc(int x, int y, int radius, int w,
    double startAngle, double endAngle,
    int r, int g, int b, int a)
{
    x *= SCALE;
    y *= SCALE;
    radius *= SCALE;
    w *= SCALE;
    radius -= w/2;
    startAngle *= 180. / M_PIl;
    endAngle *= 180. / M_PIl;

    // NOTE: apparently the arcRGBA and circleRGBA swaps green and blue, so we have to compensate somehow
    //       if this bug is fixed, just comment the next line
    std::swap(g, b);

    bool drawCircle = (abs(endAngle - startAngle) >= 360);

    if (drawCircle) {
	for (int dr=0; dr < w; dr++) {
	    circleRGBA(__buffer, x, y, radius + dr, r, g, b, a);
	}
    } else {
	for (int dr=0; dr < w; dr++) {
	    arcRGBA(__buffer, x, y, radius + dr, startAngle, endAngle, r, g, b, a);
	}
    }
}

void Canvas::clearActions()
{
    while(!__actions.empty()) {
	Action* action = __actions.front();
	__actions.pop();
	delete action;
    }
}

void Canvas::setLineWidth(int w)
{
    __environment.width = w;
}

void Canvas::setStrokeStyle(int r, int g, int b, int a)
{
    __environment.color = Color(r, g, b, a);
}

void Canvas::beginPath()
{
    clearActions();
}

void Canvas::arc(int x, int y, int r, double startAngle, double endAngle)
{
    __actions.push(new ArcAction(this, x, y, r, startAngle, endAngle));
}

void Canvas::lineTo(int x, int y)
{
    __actions.push(new LineToAction(this, x, y));
}

void Canvas::moveTo(int x, int y)
{
    __actions.push(new MoveToAction(x, y));
}

void Canvas::stroke()
{
    while(!__actions.empty()) {
	Action* action = __actions.front();
	__actions.pop();
	action->execute(__environment);
	delete action;
    }
}

void Canvas::paint()
{
    flipScreen();
}

void Canvas::clearRect()
{
    // clear the __buffer surface; comment if you want only to continue drawing
    SDL_FillRect(__buffer, NULL, SDL_MapRGB(__buffer->format, 0, 0, 0));
}

/**
class HandlerBase
*/

class_ *cl_HandlerBase;

void HandlerBase::__static__() {
}

/**
 * class Engine
 */

class_ *cl_Engine;

void Engine::handleEvent(CallbackHandlerEngineList& callbackList)
{
    for(CallbackHandlerEngineList::iterator it = callbackList.begin(); it != callbackList.end(); ++it) {
        CallbackHandlerEngine callback = it->first;
	HandlerBase* handler = it->second;
        if (!callback(handler, this)) break;
    }
}

void Engine::handleEvent(CallbackHandlerEngine2xIntList& callbackList, int x1, int x2)
{
    for(CallbackHandlerEngine2xIntList::iterator it = callbackList.begin();
	    it != callbackList.end(); ++it) {
        CallbackHandlerEngine2xInt callback = it->first;
	HandlerBase* handler = it->second;
        if (!callback(handler, this, x1, x2)) break;
    }
}

void Engine::handleEvent(CallbackHandlerEngine3xIntList& callbackList, int x1, int x2, int x3)
{
    for(CallbackHandlerEngine3xIntList::iterator it = callbackList.begin();
	    it != callbackList.end(); ++it) {
        CallbackHandlerEngine3xInt callback = it->first;
	HandlerBase* handler = it->second;
        if (!callback(handler, this, x1, x2, x3)) break;
    }
}

void *Engine::__init__()
{
    __running = false;
    return NULL;
}

void *Engine::init()
{
    if (!__sdlLibrary) {
        __sdlLibrary = new SdlLibrary();
    }
    if (!__canvas) {
        __canvas = new Canvas(__sdlLibrary->screen());
    }
    __running = false;
    __timerDelay = 0;
    return NULL;
}

void *Engine::cleanup() {
    if (__canvas)
        delete __canvas;
    if (__sdlLibrary) {
        delete __sdlLibrary;
        __sdlLibrary = 0;
    }
    return NULL;
}

void *Engine::setTimerDelay(__ss_int delay) {
    __timerDelay = delay;
    return NULL;
}

void *Engine::loop() {
    __running = true;
    SDL_AddTimer(__timerDelay, internal_timer_callback, 0);

    SDL_Event event;

    while (__running) {
        if (!SDL_WaitEvent(&event)) {
            break;
        }
        switch (event.type) {
            case SDL_QUIT:
                handleEvent(__quitCallbacks);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleEvent(__mouseButtonDownCallbacks, event.button.x, event.button.y, event.button.button);
                break;
            case SDL_MOUSEMOTION:
                handleEvent(__mouseMoveCallbacks, event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                handleEvent(__mouseButtonUpCallbacks, event.button.x, event.button.y, event.button.button);
                break;
            case SDL_USEREVENT:
                handleEvent(__timerCallbacks);
                break;
            default:
                break;
        }
    }
    return NULL;
}

void *Engine::stop() {
    __running = false;
    return NULL;
}

void *Engine::beginPath()
{
    assert(__canvas);
    __canvas->beginPath();
    return NULL;
}

void *Engine::strokeStyle(__ss_int r, __ss_int g, __ss_int b, __ss_int a)
{
    assert(__canvas);
    __canvas->setStrokeStyle(r, g, b, a);
    return NULL;
}

void *Engine::lineWidth(__ss_int w)
{
    assert(__canvas);
    __canvas->setLineWidth(w);
    return NULL;
}

void *Engine::moveTo(__ss_int x, __ss_int y)
{
    assert(__canvas);
    __canvas->moveTo(x, y);
    return NULL;
}

void *Engine::lineTo(__ss_int x, __ss_int y)
{
    assert(__canvas);
    __canvas->lineTo(x, y);
    return NULL;
}

void *Engine::arc(__ss_int x, __ss_int y, __ss_int r, double sAngle, double eAngle)
{
    assert(__canvas);
    __canvas->arc(x, y, r, sAngle, eAngle);
    return NULL;
}

void *Engine::stroke()
{
    assert(__canvas);
    __canvas->stroke();
    return NULL;
}

void *Engine::paint()
{
    assert(__canvas);
    __canvas->paint();
    return NULL;
}

void *Engine::clearRect()
{
    assert(__canvas);
    __canvas->clearRect();
}

void __init() {
    __name__ = new str("enginePyGame");

    cl_HandlerBase = new class_("HandlerBase");
    cl_Engine = new class_("Engine");
}

} // module namespace

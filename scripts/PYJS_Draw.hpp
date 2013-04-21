#ifndef PY_TO_JS_DRAW_HPP
#define PY_TO_JS_DRAW_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define PYJS_SCOPE extern

typedef void (*Int3Callback)(int, int, int, int);
typedef void (*Int2Callback)(int, int, int);
typedef void (*EmptyCallback)(int);

typedef Int3Callback PYJS_Draw_MouseDownCb;
typedef Int3Callback PYJS_Draw_MouseUpCb;
typedef Int2Callback PYJS_Draw_MouseMoveCb;
typedef EmptyCallback PYJS_Draw_QuitCb;
typedef EmptyCallback PYJS_Draw_TimerCb;

PYJS_SCOPE void PYJS_Draw_init();
PYJS_SCOPE void PYJS_Draw_cleanup();
PYJS_SCOPE void PYJS_Draw_connectMouseButtonDownCallback(int id, 
                                                    PYJS_Draw_MouseDownCb cb);
PYJS_SCOPE void PYJS_Draw_connectMouseMoveCallback(int id, 
                                                    PYJS_Draw_MouseMoveCb cb);
PYJS_SCOPE void PYJS_Draw_connectMouseButtonUpCallback(int id, 
                                                      PYJS_Draw_MouseUpCb cb);
PYJS_SCOPE void PYJS_Draw_connectQuitCallback(int id,
                                                     PYJS_Draw_QuitCb method);

PYJS_SCOPE void PYJS_Draw_setTimerDelay(int delay);
PYJS_SCOPE void PYJS_Draw_connectTimerCallback(int id, PYJS_Draw_TimerCb cb);

PYJS_SCOPE void PYJS_Draw_loop();
PYJS_SCOPE void PYJS_Draw_stop();

PYJS_SCOPE void PYJS_Draw_beginPath();
PYJS_SCOPE void PYJS_Draw_strokeStyle(int r, int g, int b, int a = 255);
PYJS_SCOPE void PYJS_Draw_lineWidth(int w);
PYJS_SCOPE void PYJS_Draw_moveTo(int x, int y);
PYJS_SCOPE void PYJS_Draw_lineTo(int x, int y);
PYJS_SCOPE void PYJS_Draw_arc(int x, int y, int r, double sAngle, 
                                                   double eAngle);
PYJS_SCOPE void PYJS_Draw_stroke();

PYJS_SCOPE void PYJS_Draw_paint();

PYJS_SCOPE void PYJS_Draw_clearRect();

#ifdef __cplusplus
}
#endif

#endif

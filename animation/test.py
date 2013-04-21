import math
#from engine import Engine, HandlerBase
from enginePyGame import Engine, HandlerBase

class Point:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

class DrawingHandler(HandlerBase):
    def __init__(self, val = 10):
        self.val = val
        self.__mouse_down = Point(0, 0)
        self.__mouse_curr = Point(-1, -1)
        self.__mouse_curr_old = Point(-1, -1)

    def on_mouse_button_down(self, engine = Engine(), x = 1, y = 1, button = 1):
        if engine != None:
            print "DrawingHandler::on_mouse_button_down: val:", self.val, x, y, button
            self.__mouse_down.x = x
            self.__mouse_down.y = y
        return True

    def on_mouse_button_up(self, engine = Engine(), x = 1, y = 1, button = 1):
        if engine != None:
            print "DrawingHelper::on_mouse_button_up: val:", self.val, x, y, button
        return True

    def on_mouse_move(self, engine = Engine(), x = 1, y = 1):
        if engine != None:
            #~ print "DrawingHelper::on_mouse_move: val:", self.val, x, y
            self.__mouse_curr.x = x
            self.__mouse_curr.y = y
        return True

    def on_quit(self, engine = Engine()):
        if engine != None:
            print "DrawingHandler::on_quit"
            engine.stop()
        return True

    def on_timer(self, engine = Engine()):
        if engine != None:
            if self.__mouse_curr_old.x != self.__mouse_curr.x or self.__mouse_curr_old.y != self.__mouse_curr.y:
                engine.clearRect()
                engine.beginPath()
                engine.lineWidth(2)
                engine.strokeStyle(255, 0, 0, 255)
                engine.moveTo(self.__mouse_down.x, self.__mouse_down.y)
                engine.lineTo(self.__mouse_curr.x, self.__mouse_curr.y)
                engine.stroke()

                engine.beginPath()
                engine.lineWidth(4)
                engine.strokeStyle(0, 255, 0, 255)
                engine.moveTo(self.__mouse_down.x, self.__mouse_down.y + 50)
                engine.lineTo(self.__mouse_curr.x, self.__mouse_curr.y + 50)
                engine.stroke()

                engine.beginPath()
                engine.strokeStyle(0, 255, 0, 126)
                engine.lineWidth(4)
                engine.arc(self.__mouse_curr.x, self.__mouse_curr.y, 50, 0, 2 * math.pi)
                engine.stroke()

                engine.beginPath()
                engine.strokeStyle(0, 0, 255, 255)
                engine.lineWidth(2)
                engine.arc(self.__mouse_curr.x, self.__mouse_curr.y, 70, 0, math.pi / 2)
                engine.stroke()

                engine.paint()
                self.__mouse_curr_old.x = self.__mouse_curr.x
                self.__mouse_curr_old.y = self.__mouse_curr.y
		return True

class TestHandler(HandlerBase):
    def __init__(self, val = 10):
        self.val = val

    def on_timer(self, engine = Engine()):
        if engine != None:
            #~ print "TestHandler::on timer: val:", self.val
            pass
        return True

    def on_mouse_button_down(self, engine = Engine(), x = 1, y = 1, button = 1):
        if engine != None:
            print "TestHandler::on mouse_button_down: val:", self.val, x, y, button
        return True

    def on_quit(self, engine = Engine()):
        if engine != None:
            print "TestHandler::on_quit"
        return True

# wrappers
def drawing_handler_on_mouse_button_down(handler = DrawingHandler(), engine = Engine(), x = 1, y = 1, button = 1):
    return handler.on_mouse_button_down(engine, x, y, button)

def drawing_handler_on_mouse_button_up(handler = DrawingHandler(), engine = Engine(), x = 1, y = 1, button = 1):
    return handler.on_mouse_button_up(engine, x, y, button)

def drawing_handler_on_mouse_move(handler = DrawingHandler(), engine = Engine(), x = 1, y = 1):
    return handler.on_mouse_move(engine, x, y)

def drawing_handler_on_quit(handler = TestHandler(), engine = Engine()):
    return handler.on_quit(engine)

def drawing_handler_on_timer(handler = TestHandler(), engine = Engine()):
    return handler.on_timer(engine)

def test_handler_on_timer(handler = TestHandler(), engine = Engine()):
    return handler.on_timer(engine)

def test_handler_on_mouse_button_down(handler = TestHandler(), engine = Engine(), x = -1, y = -1, button = -1):
    return handler.on_mouse_button_down(engine, x, y, button)

def test_handler_on_quit(handler = TestHandler(), engine = Engine()):
    return handler.on_quit(engine)

test_handler1 = TestHandler(100)
test_handler2 = TestHandler(-5)

drawing_handler = DrawingHandler(200)

egx = Engine()
egx.init()
egx.connectMouseButtonDownCallback(test_handler_on_mouse_button_down, test_handler2)
egx.connectMouseButtonDownCallback(drawing_handler_on_mouse_button_down, drawing_handler)
egx.connectMouseButtonDownCallback(test_handler_on_mouse_button_down, test_handler1)
egx.connectMouseMoveCallback(drawing_handler_on_mouse_move, drawing_handler)
egx.connectMouseButtonUpCallback(drawing_handler_on_mouse_button_up, drawing_handler)
egx.connectQuitCallback(test_handler_on_quit, test_handler2)
egx.connectQuitCallback(drawing_handler_on_quit, drawing_handler)
egx.setTimerDelay(5)
egx.connectTimerCallback(drawing_handler_on_timer, drawing_handler)
egx.connectTimerCallback(test_handler_on_timer, test_handler1)
egx.connectTimerCallback(test_handler_on_timer, test_handler2)
egx.loop()
egx.cleanup()

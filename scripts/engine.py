class HandlerBase:
    pass

class Engine:
    def __init__(self):
        print "Engine::__init__"

    def init(self):
        print "Engine::init"

    def cleanup(self):
        print "Engine::cleanup"

    def connectMouseButtonDownCallback(self, some_method_wrapper, some_class):
        print "Engine::connectMouseButtonDownCallback"
        some_method_wrapper(some_class, self)

    def connectMouseMoveCallback(self, some_method_wrapper, some_class):
        print "Engine::connectMouseMoveCallback"
        some_method_wrapper(some_class, self)

    def connectMouseButtonUpCallback(self, some_method_wrapper, some_class):
        print "Engine::connectMouseButtonUpCallback"
        some_method_wrapper(some_class, self)

    def connectQuitCallback(self, some_method_wrapper, some_class):
        print "Engine::connectQuitCallback"
        some_method_wrapper(some_class, self)

    def connectTimerCallback(self, some_method_wrapper, some_class):
        print "Engine::connectTimerCallback"
        some_method_wrapper(some_class, self)

    def setTimerDelay(self, delay = 1000):
        print "Engine::setTimer"

    def loop(self):
        print "Engine::loop"

    def stop(self):
        print "Engine::stop"

    def strokeStyle(self, r, g, b, a=1):
        print "Engine::strokeStyle", r, g, b, a

    def lineWidth(self, w):
        print "Engine::lineWidth", w

    def beginPath(self):
        print "Engine::beginPath"

    def moveTo(self, x, y):
        print "Engine::moveTo", x, y

    def lineTo(self, x, y):
        print "Engine::lineTo", x, y

    def arc(self, x, y, r, sAngle, eAngle):
        print "Engine::arc", x, y, r, sAngle, eAngle

    def paint(self):
        print "Engine::paint"

    def stroke(self):
        print "Engine::stroke"

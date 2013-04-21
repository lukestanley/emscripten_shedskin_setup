import pygame
import pygame.gfxdraw
import math

SCALE = 4

class HandlerBase:
    pass

class Canvas:
    class Cursor:
        def __init__(self, x = 0, y = 0):
            self.x = x
            self.y = y

    class Environment:
        def __init__(self, width = 1):
            self.cursor = Canvas.Cursor()
            self.color = pygame.Color(255, 255, 255, 255)
            self.width = width

    class Action:
        def execute(self, env):
            raise Exception("not implemented")

    class ArcAction(Action):
        def __init__(self, canvas, x, y, r, startAngle, endAngle):
            self.__canvas = canvas
            self.__x = x
            self.__y = y
            self.__r = r
            self.__startAngle = startAngle
            self.__endAngle = endAngle
        def execute(self, env):
            self.__canvas._Canvas__drawArc(self.__x, self.__y, self.__r,
                env.width,
                self.__startAngle, self.__endAngle,
                env.color
                )

    class MoveToAction(Action):
        def __init__(self, x, y):
            self.__x = x
            self.__y = y
        def execute(self, env):
            env.cursor.x = self.__x
            env.cursor.y = self.__y

    class LineToAction(Action):
        def __init__(self, canvas, x, y):
            self.__canvas = canvas
            self.__x = x
            self.__y = y
        def execute(self, env):
            x1 = self.__x
            y1 = self.__y
            x2 = env.cursor.x
            y2 = env.cursor.y
            if x1 > x2:
                x1, x2 = [x2, x1]
                y1, y2 = [y2, y1]
            self.__canvas._Canvas__drawLine(x1, y1, x2, y2,
                env.width, env.color)

    def __init__(self, screen):
        self.__environment = Canvas.Environment()
        self.__actions = []
        self.__screen = screen
        self.__buffer = pygame.Surface([x * SCALE for x in self.__screen.get_size()])

    def __drawArc(self, x, y, r, w, startAngle, endAngle, color):
        startAngle *= 180. / math.pi;
        endAngle *= 180. / math.pi;
        x *= SCALE
        y *= SCALE
        r *= SCALE
        w *= SCALE
        r -= w/2

        # NOTE: the arc looks better with gfxdraw
        #~ pygame.draw.arc(self.__buffer,
            #~ (color.r, color.g, color.b),
            #~ pygame.Rect(x - r, y - r, 2*r, 2*r),
            #~ startAngle, endAngle, w)

        if abs(endAngle - startAngle) >= 360:
            for dr in range(w):
                pygame.gfxdraw.circle(self.__buffer,
                    x, y, r + dr,
                    color)
        else:
            for dr in range(w):
                pygame.gfxdraw.arc(self.__buffer,
                    x, y, r + dr,
                    int(startAngle), int(endAngle),
                    color)

    def __drawLine(self, x1, y1, x2, y2, w, color):
        x1 *= SCALE
        y1 *= SCALE
        x2 *= SCALE
        y2 *= SCALE
        w *= SCALE

        pygame.draw.line(self.__buffer,
            color,
            (x1, y1), (x2, y2), w)

    def __flipScreen(self):
        surf = pygame.transform.smoothscale(self.__buffer, self.__screen.get_size())
        self.__screen.blit(surf, (0, 0))
        pygame.display.flip()

    def __clearActions(self):
        self.__actions = []

    def cleanup(self):
        self.__clearActions()

    def strokeStyle(self, r, g, b, a=255):
        self.__environment.color = pygame.Color(r, g, b, a)

    def lineWidth(self, w):
        self.__environment.width = w

    def beginPath(self):
        self.__clearActions()

    def moveTo(self, x, y):
        self.__actions.append(Canvas.MoveToAction(x, y))

    def lineTo(self, x, y):
        self.__actions.append(Canvas.LineToAction(self, x, y))

    def arc(self, x, y, r, sAngle, eAngle):
        self.__actions.append(Canvas.ArcAction(self, x, y, r, sAngle, eAngle))

    def stroke(self):
        for action in self.__actions:
            action.execute(self.__environment)
        self.__actions = []

    def paint(self):
        self.__flipScreen()

    def clearRect(self):
        self.__buffer.fill((0, 0, 0))

class Engine:
    def __init__(self):
        self.__canvas = None

    def init(self):
        pygame.init()
        self.__size = 640, 480
        self.__timerDelay = 0
        self.__timerCallbacks = []
        self.__quitCallbacks = []
        self.__mouseButtonDownCallbacks = []
        self.__mouseMoveCallbacks = []
        self.__mouseButtonUpCallbacks = []
        self.__running = False
        self.__screen = pygame.display.set_mode(self.__size, 0, 32)
        self.__canvas = Canvas(self.__screen)

    def cleanup(self):
        self.__canvas.cleanup()
        pygame.quit()

    def connectMouseButtonDownCallback(self, some_method_wrapper, some_class):
        self.__mouseButtonDownCallbacks.append([some_method_wrapper, some_class])

    def connectMouseMoveCallback(self, some_method_wrapper, some_class):
        self.__mouseMoveCallbacks.append([some_method_wrapper, some_class])

    def connectMouseButtonUpCallback(self, some_method_wrapper, some_class):
        self.__mouseButtonUpCallbacks.append([some_method_wrapper, some_class])

    def connectQuitCallback(self, some_method_wrapper, some_class):
        self.__quitCallbacks.append([some_method_wrapper, some_class])

    def connectTimerCallback(self, some_method_wrapper, some_class):
        self.__timerCallbacks.append([some_method_wrapper, some_class])

    def setTimerDelay(self, delay = 1000):
        self.__timerDelay = delay

    def __handleEventEngine(self, callbacks):
        for [wrapper, handler] in callbacks:
            if wrapper(handler, self) == False:
                break

    def __handleEventEngine2xInt(self, callbacks, x1, x2):
        for [wrapper, handler] in callbacks:
            if wrapper(handler, self, x1, x2) == False:
                break

    def __handleEventEngine3xInt(self, callbacks, x1, x2, x3):
        for [wrapper, handler] in callbacks:
            if wrapper(handler, self, x1, x2, x3) == False:
                break

    def loop(self):
        self.__running = True

        pygame.time.set_timer(pygame.USEREVENT, self.__timerDelay)

        while (self.__running):
            for e in pygame.event.get():
                if e.type == pygame.QUIT:
                    self.__handleEventEngine(self.__quitCallbacks)
                elif e.type == pygame.MOUSEBUTTONDOWN:
                    self.__handleEventEngine3xInt(self.__mouseButtonDownCallbacks, e.pos[0], e.pos[1], e.button)
                elif e.type == pygame.MOUSEMOTION:
                    self.__handleEventEngine2xInt(self.__mouseMoveCallbacks, e.pos[0], e.pos[1])
                elif e.type == pygame.MOUSEBUTTONUP:
                    self.__handleEventEngine3xInt(self.__mouseButtonUpCallbacks, e.pos[0], e.pos[1], e.button)
                elif e.type == pygame.USEREVENT:
                    self.__handleEventEngine(self.__timerCallbacks)

    def stop(self):
        self.__running = False

    def strokeStyle(self, r, g, b, a=1):
        self.__canvas.strokeStyle(r, g, b, a)

    def lineWidth(self, w):
        self.__canvas.lineWidth(w)

    def beginPath(self):
        self.__canvas.beginPath()

    def moveTo(self, x, y):
        self.__canvas.moveTo(x, y)

    def lineTo(self, x, y):
        self.__canvas.lineTo(x, y)

    def arc(self, x, y, r, sAngle, eAngle):
        self.__canvas.arc(x, y, r, sAngle, eAngle)

    def paint(self):
        self.__canvas.paint()

    def clearRect(self):
        self.__canvas.clearRect();

    def stroke(self):
        self.__canvas.stroke()

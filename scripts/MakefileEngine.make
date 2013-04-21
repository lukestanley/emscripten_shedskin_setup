all: replace_engine
	make CPPFLAGS="-g3 -fno-inline -O0 `sdl-config --cflags` `pkg-config SDL_gfx --cflags`" \
		LDFLAGS="`sdl-config --libs` `pkg-config SDL_gfx --libs`" -f Makefile

replace_engine: engineSDL.cpp engineSDL.hpp
	cp engineSDL.cpp enginePyGame.cpp
	cp engineSDL.hpp enginePyGame.hpp

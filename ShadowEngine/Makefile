CFLAGS = -std=c++20 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

ShadowEngine: main.cpp
	g++ $(CFLAGS) -o ShadowEngine main.cpp $(LDFLAGS)

.PHONY: test clean

test: ShadowEngine
	./ShadowEngine

clean:
	rm -f ShadowEngine

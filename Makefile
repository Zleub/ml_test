NAME = ml
INCLUDES = inc
FILES = src/lib.cpp \
				main.cpp
OBJECTS = $(FILES:.cpp=.o)

CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -I $(INCLUDES) \
	-I "/c/ProgramData/chocolatey/include"

LDFLAGS = \
	-L "/c/ProgramData/chocolatey/msvc110-64/lib" \
	-l glfw3 \
	# -l gdi32

all: $(OBJECTS)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(NAME)

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(OBJECTS)
	make clean

re:
	make fclean
	make all

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

NAME = ser2mqtt
CXXFLAGS = -Wall -Wextra -std=c++14
LDFLAGS = -lmosquittopp -lpthread
PREFIX = /usr/local

$(NAME): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(NAME)

.PHONY: install
install: $(NAME)
	install -m 0755 $< $(PREFIX)/bin

.PHONY: uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(NAME)

SRC = $(wildcard *.cpp)
DOCS = $(wildcard *.h *.hh *.hpp *.cpp *.cc *.c )

A2PS = a2ps
PS2PDF = ps2pdf

all:
	g++ $(SRC) -o thermometer -g


%.ps : %.cpp %.c %.cc %.h %.hh %.hpp
    $(A2PS $(input) -o $(output) )

%.pdf : %.ps
    $(PS2PDF $(input) -o $(output) )

doc: i2cclient.cpp.pdf
#$(addsuffix .pdf, $(basename $(SRC)) )

SRC = $(wildcard *.cpp Thermometer/*.cpp I2C/*.cpp SPI/*.cpp )
DOCS = $(wildcard *.h *.hh *.hpp *.cpp *.cc *.c )

A2PS = a2ps
PS2PDF = ps2pdf

all:
	g++ $(SRC) -o thermometer -g -IThermometer -I. -II2C -ISPI -IInterfaces


%.ps : %.cpp %.c %.cc %.h %.hh %.hpp
    $(A2PS $(input) -o $(output) )

%.pdf : %.ps
    $(PS2PDF $(input) -o $(output) )

doc: i2cclient.cpp.pdf
#$(addsuffix .pdf, $(basename $(SRC)) )

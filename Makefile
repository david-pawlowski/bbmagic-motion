PRG		=bbmagic_motion_sketch
BBM_LIB		=bbmagic_lib_1.2

all: clean
	gcc -o $(PRG) $(PRG).c $(BBM_LIB).a libbluetooth.a

clean:
	rm -f $(PRG)



all:
	(cd cmd && make)
	(cd nikhil-hw01 && make)
	(cd plugins/car_control && make)

clean:
	(cd cmd && make clean)
	(cd nikhil-hw01 && make clean)
	(cd plugins/car_control && make clean)

.PHONY: all clean

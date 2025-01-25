soTARGET = libcore.so
soFLAGS = -fPIC -shared -std=c++20
soSOURCE = core/src/*.cpp
soINCLUDES = core/includes

uSOURCE = user/src/*.cpp
uINCLUDES = user/includes

core: $(soSOURCE) $(soINCLUDES)/*.hpp
	g++ $(soFLAGS) -o $(soTARGET) $(soSOURCE) -I$(soINCLUDES)

migrate: $(uSOURCE) $(uINCLUDES)/*.hpp
	rm -f migrate
	g++ -I$(uINCLUDES) -o migrate $(uSOURCE) -L. -lcore
	LD_LIBRARY_PATH=$(shell pwd):$(LD_LIBRARY_PATH) ./migrate

clean:
	rm -f libcore.so

clean_all:
	rm -f libcore.so migrate schema.json migrations.sql

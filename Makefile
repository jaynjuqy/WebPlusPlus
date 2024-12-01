soTARGET = libcore.so
soFLAGS = -fPIC -shared -std=c++17
soSOURCE = core/src/*.cpp
soINCLUDES = core/includes

uSOURCE = user/src/*.cpp
uINCLUDES = user/includes

corelib: $(soSOURCE) $(soINCLUDES)/*.hpp
	g++ $(soFLAGS) -o $(soTARGET) $(soSOURCE) -I$(soINCLUDES)

migrate:
	g++ -I$(uINCLUDES) -o migrate $(uSOURCE) -L. -lcore
	LD_LIBRARY_PATH=$(shell pwd):$(LD_LIBRARY_PATH) ./migrate

clean_all:
	rm -f libcore.so migrate schema.json migrations.txt
	
clean:
	rm -f migrate
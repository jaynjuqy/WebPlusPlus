soTARGET = libcore.so
soFLAGS = -fPIC -shared -std=c++17
soSOURCE = core/src/*.cpp
soINCLUDES = core/includes

uSOURCE = user/src/*.cpp
uINCLUDES = user/includes

$(soTARGET): $(soSOURCE)
	g++ $(soFLAGS) -o $(soTARGET) $(soSOURCE) -I$(soINCLUDES)

migrate:
	g++ -I$(uINCLUDES) -o migrate $(uSOURCE) -L. -lcore
	
clean_all:
	rm -f libcore.so migrate
	echo "Cleaned!"
clean:
	rm -f migrate
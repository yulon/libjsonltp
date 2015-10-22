mkdir ./lib
g++ -O2 -shared -fPIC -o ./lib/liblowltp.so ./src/*.cpp -I../ltp/include/ -I../ltp/thirdparty/boost/include -L../ltp/lib/ -Wl,-Bstatic -lsegmentor -lboost_regex -lpostagger -Wl,-Bdynamic

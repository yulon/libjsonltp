if [ ! -d "`dirname $0`/lib" ]; then
	mkdir `dirname $0`/lib
fi
g++ -O2 -shared -fPIC -o `dirname $0`/lib/libjsonltp.so `dirname $0`/src/*.cpp `dirname $0`/src/*.c -I`dirname $0`/../ltp/include/ -I`dirname $0`/../ltp/thirdparty/boost/include -L`dirname $0`/../ltp/lib/ -Wl,-Bstatic -lsegmentor -lboost_regex -lpostagger -lner -lparser -lsrl -lmaxent -Wl,-Bdynamic

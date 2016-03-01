cp `dirname $0`/inc/*.h /usr/local/include/
cp `dirname $0`/lib/*.so /usr/local/lib/
ldconfig

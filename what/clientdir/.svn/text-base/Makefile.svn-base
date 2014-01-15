#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements. See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership. The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License. You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the
# specific language governing permissions and limitations
# under the License.
#

IN_BOOST_DIR = /usr/local/boost_1_48_0/
IN_THRIFT_DIR = /home/wangjianguo/Thrift_w/thrift_0.8.0/include/thrift/
CPP_FLAGS = -Wall -Wextra -g -O3 -DHAVE_NETINET_IN_H -fPIC

LIB_THRIFT_DIR = /home/wangjianguo/Thrift_w/thrift_0.8.0/lib
LIB_EVENT_DIR = /home/wangjianguo/Thrift_w/libevent/lib

GEN_SRC = ./gen-cpp/*.cpp
GEN_INC = ./gen-cpp

default: compile server client clientr clientw clientwt clientw_m clientr_m so

compile: Thread.cpp CacheTube.cpp CacheTubeService_server.cpp test.cpp testr.cpp testw.cpp testwt.cpp testw_m.cpp testr_m.cpp ./gen-cpp/*.cpp 
	g++ -c Thread.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o Thread.o
	g++ -c CacheTube.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o CacheTube.o
	g++ -c CacheTubeService_server.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o CacheTubeService_server.o
	g++ -c test.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o test.o
	g++ -c testr.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o testr.o
	g++ -c testw.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o testw.o
	g++ -c testwt.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o testwt.o
	g++ -c testw_m.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o testw_m.o
	g++ -c testr_m.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o testr_m.o
	g++ -c ./gen-cpp/CacheTubeService.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o ./gen-cpp/CacheTubeService.o
	g++ -c ./gen-cpp/CacheTubeService_types.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o ./gen-cpp/CacheTubeService_types.o
	g++ -c ./gen-cpp/CacheTubeService_constants.cpp -I${IN_THRIFT_DIR} -I${IN_BOOST_DIR} -I${GEN_INC} ${CPP_FLAGS} -o ./gen-cpp/CacheTubeService_constants.o

server:
	g++ -o server -L${LIB_THRIFT_DIR} -L${LIB_EVENT_DIR} -lthrift -lthriftnb -levent CacheTubeService_server.o CacheTube.o ./gen-cpp/*.o

client:
	g++ -o client -L${LIB_THRIFT_DIR} -lthrift test.o CacheTube.o ./gen-cpp/*.o

clientr:
	g++ -o clientr -L${LIB_THRIFT_DIR} -lthrift testr.o CacheTube.o ./gen-cpp/*.o

clientw:
	g++ -o clientw -L${LIB_THRIFT_DIR} -lthrift testw.o CacheTube.o ./gen-cpp/*.o

clientwt:
	g++ -o clientwt -L${LIB_THRIFT_DIR} -lthrift testwt.o CacheTube.o ./gen-cpp/*.o

clientw_m:
	g++ -o clientw_m -L${LIB_THRIFT_DIR} -lthrift testw_m.o Thread.o CacheTube.o ./gen-cpp/*.o
	
clientr_m:
	g++ -o clientr_m -L${LIB_THRIFT_DIR} -lthrift testr_m.o Thread.o CacheTube.o ./gen-cpp/*.o
	
so:
	g++ -shared -fPIC -o libcachetube.so -L${LIB_THRIFT_DIR} -lthrift CacheTube.o ./gen-cpp/*.o

clean:
	rm -f  server client clientr clientw clientwt clientw_m clientr_m so *.o ./gen-cpp/*.o


OS = linux
RM = /bin/rm -f
#编译.c文件的选项
CC = gcc 
CFLAGS =  -Wall -g -fPIC -D_GNU_SOURCE -DLINUX
#编译cpp文件的选项
CXX = g++
CXXFLAGS = -fPIC -Wall -D_GNU_SOURCE  -g -DLINUX  -Wno-deprecated
#编译so的选项
LD = g++
LDFLAGS = -shared

INCDIR=	  -I./ \
		  -I /usr/local/mysql/include \
		  -I../protocol/ \
		  -I../include/ \
		  -I../dep/curl/\
		  
CFLAGS += $(INCDIR)
          
SLIBS =	../dep/curl/libcurl.a ../dep/json/libjson.a 
DLIBS = -lcurl
#需要输出的文件名
TARGET = wslib

#取当前目录下的所有文件	      
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJS += $(patsubst %.c,%.o,$(wildcard *.c))

#依赖项
.SUFFIXES: .cpp .o .a

#用g++编译文件
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCDIR) $< -o $@	

LIBA= $(TARGET).a
LIBSO=$(TARGET).so
BIN=$(TARGET)

#需要输出的文件类型
TARGETS= $(BIN)

#三种文件的编码方式
CREATESO = $(LD)  $(LDFLAGS) -o $@ $^ $(SLIBS)
CREATEA = ar rc $(LIBA) $(OBJS) $(SLIBS) 
CREATEBIN=$(CXX) $^ -lpthread  $(SLIBS) $(DLIBS) -o $@  
	

all:$(TARGETS)

$(LIBSO):$(OBJS)  
	$(CREATESO) 
	@echo "----------so successed done!-----------------"
$(LIBA):$(OBJS) 
	$(CREATEA)
	@echo "----------.a successed done!-----------------"
$(BIN):$(OBJS)
	$(CREATEBIN)
	@echo "----------bin successed done!-----------------"

clean:
	$(RM) *.o core *.log* $(TARGETS)
depend:
	makedepend $(CFLAGS) $(SRCS)
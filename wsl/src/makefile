OS = linux
RM = /bin/rm -f
#����.c�ļ���ѡ��
CC = gcc 
CFLAGS =  -Wall -g -fPIC -D_GNU_SOURCE -DLINUX
#����cpp�ļ���ѡ��
CXX = g++
CXXFLAGS = -fPIC -Wall -D_GNU_SOURCE  -g -DLINUX 
#����so��ѡ��
LD = g++
LDFLAGS = -shared

INCDIR=	  -I./  -I ../include/

          
LIBS =	

#��Ҫ������ļ���
TARGET = wsl

#ȡ��ǰĿ¼�µ������ļ�	      
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJS += $(patsubst %.c,%.o,$(wildcard *.c))

#������
.SUFFIXES: .cpp .o .a

#��g++�����ļ�
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCDIR) $< -o $@	

LIBA= $(TARGET).a
LIBSO=$(TARGET).so
BIN=$(TARGET)

#��Ҫ������ļ�����
TARGETS= $(LIBA)

#�����ļ��ı��뷽ʽ
CREATESO = $(LD)  $(LDFLAGS) -o $@ $^ $(LIBS)
CREATEA = ar rc $(LIBA) $(OBJS) $(LIBS) 
CREATEBIN=$(CXX) $^ -lpthread  $(LIBS) -o $@  
	

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
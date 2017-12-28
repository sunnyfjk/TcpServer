TAG=main
SRC=$(shell find ./ -name "*.c")
INC=-I./include
LIBS= -levent
CONFIGS=-D__DEBUG__
CC=gcc
$(TAG):$(patsubst %.c,%.o,$(SRC))
	$(CC) -o $@ $^ $(LIBS)
.c.o:
	$(CC) -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" $(CONFIGS) $(LIBS) $(INC) -o "$@" "$<"
clean:
	rm -fr $(patsubst %.c,%.o,$(SRC)) $(patsubst %.c,%.d,$(SRC)) $(TAG)

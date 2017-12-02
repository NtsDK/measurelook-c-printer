HOST_OPTS=
OPTFLAGS= -DVEC_ENABLED=1
#OPTFLAGS= -no-vec -no-simd -DVEC_ENABLED=0
#CC=icc 
CC=gcc 
CFLAGS=-std=c99 -g -O3 -fPIC -Wall -Wextra -Isrc -rdynamic $(OPTFLAGS)
LDLIBS=
EXTRA_LIBS=-ldl -lm -liomp5 $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
#all: clean $(TARGET) tests
#all: clean $(TARGET) $(SO_TARGET) tests
all: host

make: clean $(TARGET) $(SO_TARGET) makeTests

.PHONY: host
host: CFLAGS += $(HOST_OPTS) 
host: clean $(TARGET) $(SO_TARGET) tests


#dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
#dev: CFLAGS=-g -Wall -Isrc -Wextra -DNDEBUG $(OPTFLAGS)
dev: CFLAGS=-g -Wall -Isrc -Wextra -DNDEBUG2 $(OPTFLAGS)
dev: all
# -openmp-stubs
$(TARGET): CFLAGS += -fPIC 
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

#original version
#tests: CFLAGS += $(TARGET)
#tests: LDLIBS += $(TARGET)
# The Unit Tests
.PHONY: tests
tests: LDLIBS = $(TARGET) $(EXTRA_LIBS)
tests: $(TESTS)
	sh ./tests/runtests.sh
	
.PHONY: micTests
micTests: LDLIBS = $(TARGET) $(EXTRA_LIBS)
micTests: $(TESTS)

.PHONY: makeTests
makeTests: LDLIBS = $(TARGET) $(EXTRA_LIBS)
makeTests: $(TESTS)


valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

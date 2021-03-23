# Makefile para los ficheros fuente del DSL para las comprobaciones
# estáticas de código fuente de las prácticas de POO
# Solamente se construyen aquí los módulos objeto comunes a todas las prácticas.
# ©2021 Gerardo - La Gran Unificación

# Makefile para los ficheros fuente del DSL para las comprobaciones
# estáticas de código fuente de las prácticas de POO
# Solamente se construyen aquí los módulos objeto comunes a todas las prácticas.
# ©2021 Gerardo - La Gran Unificación

CXX         := clang++
RTTIFLAG    := -fno-rtti
LLVMCXXFLAGS :=	\
	-I/usr/lib/llvm-10/include 
CXXFLAGS	:= $(LLVMCXXFLAGS) $(RTTIFLAG) -fexceptions
LLVMLDFLAGS	:= $(shell llvm-config --ldflags --system-libs --libs) $(LDFLAGS)

SRCS = caclibrary.cpp execute.cpp matchers.cpp
HDRS = $(SRCS:.cpp=.h) info.h
OBJS = $(SRCS:.cpp=.o)

CLANGLIBS = \
	-lclangFrontend \
	-lclangSerialization \
	-lclangDriver \
	-lclangTooling \
	-lclangParse \
	-lclangSema \
	-lclangAnalysis \
	-lclangEdit \
	-lclangAST \
	-lclangASTMatchers \
	-lclangLex \
	-lclangBasic \
	-lclangRewrite\
	-lclangRewriteFrontend \
	-luv

all: ${OBJS}

${OBJS}: ${HDRS}

clean:
	${RM} ${RMFLAGS} ${OBJS} *~ \#* core

.PHONY: all clean

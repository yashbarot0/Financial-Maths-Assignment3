# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -O3

# GSL flags (adjust based on your GSL installation)
GSL_CFLAGS = $(shell gsl-config --cflags)
GSL_LIBS = $(shell gsl-config --libs)

# OpenMP flag
OPENMP_FLAG = -fopenmp

# Targets
TARGETS = monte_carlo_pricer monte_carlo_pricer_omp

# Source files
SOURCES = monte_carlo_pricer.cpp monte_carlo_pricer_omp.cpp

# Default target
all: $(TARGETS)

# Serial version
monte_carlo_pricer: monte_carlo_pricer.cpp
	$(CXX) $(CXXFLAGS) $(GSL_CFLAGS) -o $@ $^ $(GSL_LIBS)

# OpenMP version
monte_carlo_pricer_omp: monte_carlo_pricer_omp.cpp
	/opt/homebrew/opt/llvm/bin/clang++ $(CXXFLAGS) $(OPENMP_FLAG) $(GSL_CFLAGS) -o $@ $^ $(GSL_LIBS)

# Clean
clean:
	rm -f $(TARGETS)
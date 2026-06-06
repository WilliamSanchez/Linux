CUDA_HOME ?= /usr

NVCC = $(CUDA_HOME)/bin/nvcc

TARGET = hello_gpu
SRC = hello_gpu.cu

all:
	$(NVCC) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

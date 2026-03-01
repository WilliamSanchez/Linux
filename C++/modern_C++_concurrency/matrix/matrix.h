#pragma once

#include <vector>
#include <thread>
#include <iostream>
#include "utils.h"
#include "common_objs.h"

class Matrix
{   
        int *data;
        int rows;
        int columns;
    
    public:

        Matrix(int _n, int _m): rows(_n), columns(_m)
        {
            data = new int[rows*columns];
            std::fill(data,data+rows*columns, 0);
        }

        void set_value(int i, int j, int value)
        {
            data[i*columns+j] = value;
        }

        void set_all(int value)
        {
            std::fill(data, data+rows*columns,value);
        }

        static void multiplicy(Matrix *x, Matrix *y, Matrix *result)
        {
            if(!(x->columns == y->columns) || !(x->rows == y->rows) && (y->columns == result->columns))
            {
                std::cout << "ERROR: Invalid matrix sizes for multilication\n";
                return;
            }

            int r = result->rows * result->columns;

            for(size_t i = 0; i<r; i++)
            {
                for(size_t j = 0; j< x->columns; j++)
                {
                    result->data[i] += x->data[(i/result->columns)*x->columns+j]*y->data[i%result->rows+j*y->columns];
                }
            }
        };

        static void parallel_multiplicy(Matrix *x, Matrix *y, Matrix *result)
        {
            struct process_data_chunk
            {
                void operator()(Matrix *result, Matrix *x, Matrix *y, int start_index, int end_index)
                {
                    for (size_t i = start_index; i < end_index; i++)
                    {
                        for (size_t j=0; j<x->columns; j++)
                        {
                            result->data[i] += x->data[(i/result->columns)*x->columns+j]*y->data[i%result->rows+j*y->columns];
                        }
                    }
                }
            };

            if(!(x->columns == y->columns) || !(x->rows == y->rows) && (y->columns == result->columns))
            {
                std::cout << "ERROR: Invalid matrix sizes for multilication\n";
                return;
            }

            int length = result->columns*result->rows;
            if(!length)
                return;
            
            int min_per_thread = 10000;
            int max_thread = (length + min_per_thread-1)/min_per_thread;
            int hardware_threads = std::thread::hardware_concurrency();
            int num_thread = std::min(hardware_threads != 0 ? : 2,max_thread);
            int block_size = length/num_thread;

            std::vector<std::thread> threads(num_thread -1);
            int block_start = 0;
            int block_end = 0;
            {
                join_threads joiner(threads);
                for(unsigned i=0; i<(num_thread-1); i++)
                {
                    block_start = i*block_size;
                    block_end = block_start+block_size;
                    threads[i] = std::thread(process_data_chunk(), result, x ,y, block_start, block_end);
                }

                process_data_chunk()(result,x,y,block_end,length);
            }
        }

        static void transpose(Matrix *x, Matrix *result)
        {
            if(!(x->columns == result->rows) || !(x->rows == result->columns))
            {
                std::cout << "ERROR: Invalid matrix sizes for multilication\n";
                return;
            }

            int r = result->rows*result->columns;
            int result_column = 0;
            int result_row = 0;

            int input_column = 0;
            int input_row = 0;

            for(ssize_t i=0; i<r; i++)
            {
                result_row = i/result->columns;
                result_column = i%result->columns;

                input_row = result_column;
                input_column = result_row;
                result->data[i] = x->data[input_row*x->columns+input_column];
            }
        }

        static void parallel_traspose(Matrix *x, Matrix *result)
        {
            struct  process_data_chunk
            {
                void operator()(Matrix *x, Matrix *result, int start_index, int end_inidex)
                {

                    int r = result->rows*result->columns;
                    int result_column = 0;
                    int result_row = 0;

                    int input_column = 0;
                    int input_row = 0;

                    for(ssize_t i=0; i<r; i++)
                    {
                        result_row = i/result->columns;
                        result_column = i%result->columns;

                        input_row = result_column;
                        input_column = result_row;
                        result->data[i] = x->data[input_row*x->columns+input_column];
                    }
                }            
            };

            if(!(x->columns == result->rows) || !(x->rows == result->columns))
            {
                std::cout << "ERROR: Invalid matrix sizes for multilication\n";
                return;
            }

            int length = result->columns*result->rows;
            if(!length)
                return;
            
            int min_per_thread = 10000;
            int max_thread = (length + min_per_thread-1)/min_per_thread;
            int hardware_threads = std::thread::hardware_concurrency();
            int num_thread = std::min(hardware_threads != 0 ? : 2,max_thread);
            int block_size = length/num_thread;

            std::vector<std::thread> threads(num_thread -1);
            int block_start = 0;
            int block_end = 0;
            {
                join_threads joiner(threads);
                for(unsigned i=0; i<(num_thread-1); i++)
                {
                    block_start = i*block_size;
                    block_end = block_start+block_size;
                    threads[i] = std::thread(process_data_chunk(), result, x , block_start, block_end);
                }

                process_data_chunk()(result,x,block_end,length);
            }
            
        }


        void print()
        {
            if(rows<50 && columns < 50)
            {
                for(size_t i = 0; i<rows; i++)
                {
                    for(size_t j = 0; j<columns; j++)
                    {
                        std::cout<<data[j+i*columns]<<"";
                    }
                    std::cout<<"\n";
                }
            }
        }

    ~Matrix()
    {
        delete data;
    }

};
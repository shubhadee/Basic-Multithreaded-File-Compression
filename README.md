# Basic-Multithreaded-File-Compression

**Name**: Shubhadeep Subal Devnath  
**Company**: CODTECH IT SOLUTIONS  
**Employee ID**: CT08EVR  
**Domain**: C++ Programming  
**Project Duration**: December 20th, 2024 - January 20th, 2025 
---

## Objective

The objective of this project is to provide a basic file compression and decompression utility written in C++, leveraging multithreading to efficiently handle large files. The program reads an input file, divides it into smaller chunks, compresses or decompresses each chunk in parallel, and writes the result to an output file. This project aims to demonstrate how multithreading can be utilized to speed up file processing tasks, particularly for large files, without implementing a complex compression algorithm.

## Functions

### **compressFile**
- This function reads an input file (`input.txt`), splits it into smaller chunks, compresses each chunk using multiple threads, and writes the compressed data to the output file (`compressed.bin`).
- **Steps**:
  - Opens the input file in binary mode.
  - Reads the entire file into memory as a string.
  - Divides the string into chunks of a specified size (`chunkSize`).
  - Creates a separate thread for each chunk to perform the compression.
  - Once all chunks are compressed, the threads are joined and the compressed chunks are written to the output file.

### **decompressFile**
- This function reads the compressed file (`compressed.bin`), decompresses each chunk in parallel, and writes the decompressed data to an output file (`decompressed.txt`).
- **Steps**:
  - Opens the compressed file in binary mode.
  - Reads the entire compressed file into memory.
  - Splits the compressed file into chunks based on the previously stored chunk sizes.
  - Creates a separate thread for each chunk to perform the decompression.
  - Once all chunks are decompressed, the threads are joined and the decompressed data is written to the output file.

### **compressChunk**
- This is a helper function that is responsible for processing a single chunk of data and performing the compression.
- **Details**:
  - It simply stores the chunk as it is in the `compressedData` vector, simulating a compression process.
  - In a real-world scenario, a compression algorithm (e.g., Huffman coding or LZ77) would be applied here.
  
### **decompressChunk**
- This is a helper function that decompresses a single chunk of compressed data.
- **Details**:
  - It currently just copies the chunk as it is into the decompressed output vector, simulating the decompression process.
  - In a real-world scenario, this function would apply a decompression algorithm to restore the original data.

## Working Process

### **Compression Process**

1. **File Reading**: The `compressFile` method reads the input file (`input.txt`) in binary mode to preserve all byte data, even for non-text files like images or audio.
   
2. **Chunking**: The content of the input file is divided into smaller chunks based on a specified size (`chunkSize`, typically 1024 bytes). This allows the file to be processed in manageable parts, improving parallelism.

3. **Multithreading**: Each chunk is processed by a separate thread, which performs compression. The use of multithreading ensures that multiple chunks can be compressed concurrently, significantly improving the speed of the operation, especially for large files.

4. **Compression**: In this simplified version, compression is simulated by simply storing each chunk of data in the `compressedData` vector. Typically, this would involve applying a data compression algorithm to reduce the size of the chunks.

5. **Writing Output**: After all chunks are processed and stored, the compressed chunks are written back to the output file (`compressed.bin`).

### **Decompression Process**

1. **File Reading**: The `decompressFile` method opens the compressed file (`compressed.bin`) and reads it into memory.

2. **Chunking**: The compressed data is split into individual chunks, based on the previous chunking method used during compression.

3. **Multithreading**: Each chunk is passed to a separate thread for decompression, allowing for parallel processing of the data. This speeds up the overall decompression process.

4. **Decompression**: In the current version, decompression simply copies the chunk as it is. In a real implementation, this would involve reversing the compression algorithm to restore the original data.

5. **Writing Output**: The decompressed data is written to the output file (`decompressed.txt`), completing the decompression process.

## How to Use

### **Step 1: Build the Program**
To compile the program, you can use a C++ compiler like `g++`. Ensure that the `-pthread` flag is used to enable multithreading support:
---
## Output
![image](https://github.com/user-attachments/assets/9c53cfb0-0840-4a19-9d05-2fb0d077fd1c)
---
```bash
g++ -o file_compressor file_compressor.cpp -std=c++11 -pthread



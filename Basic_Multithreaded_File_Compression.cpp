#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class FileCompressor {
private:
    mutex mtx;
    condition_variable cv;
    vector<thread> threads;
    vector<string> compressedData;
    string inputFile;
    string outputFile;
    size_t chunkSize;

    void compressChunk(const string& data, int index) {
        string compressedChunk = data;
        lock_guard<mutex> lock(mtx);
        compressedData[index] = compressedChunk;
    }

    void decompressChunk(const string& data, string& output) {
        output = data;
    }

public:
    FileCompressor(const string& input, const string& output, size_t chunk = 1024) : inputFile(input), outputFile(output), chunkSize(chunk) {}

    void compressFile() {
        ifstream input(inputFile, ios::binary);
        if (!input.is_open()) {
            throw runtime_error("Failed to open input file");
        }

        vector<string> chunks;
        stringstream buffer;
        buffer << input.rdbuf();
        string fileData = buffer.str();
        input.close();

        size_t fileSize = fileData.size();
        size_t totalChunks = (fileSize + chunkSize - 1) / chunkSize;
        compressedData.resize(totalChunks);

        for (size_t i = 0; i < fileSize; i += chunkSize) {
            chunks.emplace_back(fileData.substr(i, min(chunkSize, fileSize - i)));
        }

        for (size_t i = 0; i < totalChunks; ++i) {
            threads.emplace_back(&FileCompressor::compressChunk, this, chunks[i], i);
        }

        for (auto& t : threads) {
            t.join();
        }

        ofstream output(outputFile, ios::binary);
        if (!output.is_open()) {
            throw runtime_error("Failed to open output file");
        }

        for (const auto& chunk : compressedData) {
            output.write(chunk.data(), chunk.size());
        }

        output.close();
    }

    void decompressFile() {
        ifstream input(inputFile, ios::binary);
        if (!input.is_open()) {
            throw runtime_error("Failed to open input file");
        }

        stringstream buffer;
        buffer << input.rdbuf();
        string fileData = buffer.str();
        input.close();

        vector<string> decompressedChunks;
        vector<string> compressedChunks;
        size_t pos = 0;

        while (pos < fileData.size()) {
            size_t chunkSize;
            memcpy(&chunkSize, fileData.data() + pos, sizeof(size_t));
            pos += sizeof(size_t);

            compressedChunks.emplace_back(fileData.substr(pos, chunkSize));
            pos += chunkSize;
        }

        decompressedChunks.resize(compressedChunks.size());

        for (size_t i = 0; i < compressedChunks.size(); ++i) {
            threads.emplace_back(&FileCompressor::decompressChunk, this, compressedChunks[i], ref(decompressedChunks[i]));
        }

        for (auto& t : threads) {
            t.join();
        }

        ofstream output(outputFile, ios::binary);
        if (!output.is_open()) {
            throw runtime_error("Failed to open output file");
        }

        for (const auto& chunk : decompressedChunks) {
            output.write(chunk.data(), chunk.size());
        }

        output.close();
    }
};

int main() {
    try {
        FileCompressor compressor("input.txt", "compressed.bin");
        compressor.compressFile();

        FileCompressor decompressor("compressed.bin", "decompressed.txt");
        decompressor.decompressFile();

        cout << "Compression and decompression completed successfully." << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

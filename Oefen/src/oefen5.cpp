#include <iostream>
#include <vector>

std::vector<std::vector<int>> splitIntoChunks(const std::vector<int>& input) {
    int numLists = 8;
    std::vector<std::vector<int>> result(numLists);
    
    size_t chunkSize = (input.size() + numLists - 1) / numLists;  // Compute size per chunk
    for (int i = 0; i < numLists; ++i) {
        size_t start = i * chunkSize;
        size_t end = std::min(start + chunkSize, input.size());
        if (start < input.size()) {
            result[i] = std::vector<int>(input.begin() + start, input.begin() + end);
        }
    }

    return result;
}

int main() {
    std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    std::vector<std::vector<int>> splitData = splitIntoChunks(input);

    for (int i = 0; i < splitData.size(); ++i) {
        std::cout << "List " << i << ": ";
        for (int num : splitData[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}


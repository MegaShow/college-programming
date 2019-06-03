int buildHeap(std::vector<int>& data) {
    int size = data.size() / 2 - 1;
    for (int i = size; i >= 0; i--) {
        heapify(data, i);
    }
}

void heapify(std::vector<int>& data, int root) {
    int left = root * 2 + 1, right = root * 2 + 2;
    int large = root;
    if (data[large] < data[left]) large = left;
    if (data[large] < data[right]) large = right;
    if (large != root) {
        std::swap(data[large], data[root]);
        heapify(data, large);
    }
}

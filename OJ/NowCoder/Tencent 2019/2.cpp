#include <memory>
#include <vector>
#include <queue>

using namespace std;

class Allocator {
public:
    Allocator(int _size, int _eachSize): use(_size / _eachSize, 0) {
        size = _size;
        eachSize = _eachSize;
        malloc(data, 0, size);
    }

    ~Allocator() {
        free(data);
    }

    void* malloc() {
        for (int i = 0; i < use.size(); i++) {
            if (!use[i]) {
                use[i] = true;
                return data + i * eachSize;
            }
        }
        return nullptr;
    }

    void free(void* pointer) {
        use[(pointer - data) / eachSize] = false;
    }

private:
    void* data;
    vector<bool> use;
    int size;
    int eachSize;
};



class Allocator {
public:
    Allocator(int _size, int _eachSize) {
        size = _size;
        eachSize = _eachSize;
        malloc(data, 0, size);
        for (int i = 0; i < size / eachSize; i++) {
            notUse.push(i);
        }
    }

    ~Allocator() {
        free(data);
    }

    void* malloc() {
        if (notUse.empty()) return nullptr;
        int top = notUse.front();
        return data + top * eachSize;
    }

    void free(void* pointer) {
        int top = (pointer - data) / eachSize;
        notUse.push(top);
    }

private:
    void* data;
    queue<int> notUse;
    int size;
    int eachSize;
};



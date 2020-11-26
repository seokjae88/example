
#include "test_lrucache.hpp"

void setCacheData(std::string &key, int nowTime, TestDataClass* data) {
    if (data == nullptr) {
        return;
    }
    //std::lock_guard<std::mutex> lock(this->cacheSetLock_);
    lruCacheMap->put(key, nowTime, data);
}
TestDataClass* getCacheData(std::string &key, int nowTime) {
    //std::lock_guard<std::mutex> lock(this->cacheSetLock_);
    return lruCacheMap->get(key, nowTime);
}

std::map<std::string, int> keyListA = {
        { "a_959c930aae6f49dfab52005595bb8cb6", 1 },
        { "a_ac82ee19549f4379a8ddfa886bb73aa5", 2 },
        { "a_12e547931a224ab09b14acfd0deb51d4", 3 },
        { "9cfcc81be181f23e48fab1bf124fbbda", 4 },
        { "ebac1eb0558eb2d62c27979c4d1c9ab5", 5 },
        { "a_86633b65efa748ebbd1d6b62fbe75804", 6 }
};

LRUCache* lruCacheMap = nullptr;

int main() {
    lruCacheMap = new CTLRUCache(6);

    int nowTime = 193650940;
    for (auto &data : keyListA) {
        TestDataClass* temp = new TestDataClass(data.second);
        setCacheData(data.first, nowTime, temp);
    }

    // 밀어내기
    TestDataClass* temp = new TestDataClass(99);
    setCacheData("new_key", nowTime, temp);

    lruCacheMap->print();

    nowTime += cacheTTL;
    int count = 10;

    for (auto &data : keyListA) {
        TestDataClass* tdc = getCacheData(data.first, nowTime);
        if (tdc == nullptr) {
            // expired and update
            TestDataClass* temp = new TestDataClass(count);
            setCacheData(data.first, nowTime, temp);
        } else {
            std::cout << "get data ttl : " << data.first << "\n";
        }
        count++;
    }

    lruCacheMap->print();
    return;
}
#ifndef ASE_V3_TEST_LRUCACHE_HPP
#define ASE_V3_TEST_LRUCACHE_HPP

#include <iostream>
#include <map>
#include "hopscotch_map.h"

#define ONEHOUR_SECOND 3600
const int cacheTTL = ONEHOUR_SECOND;

class TestDataClass {
public:
    int dataNum;
    TestDataClass(int num) {
        this->dataNum = num;
    };
    ~TestDataClass();

};

struct LRUNode {
    std::string key;
    int expiredTime;
    TestDataClass* data;
    LRUNode* next;
    LRUNode* perv;
    LRUNode(std::string k, TestDataClass* d) : key(k), data(d), next(nullptr), perv(nullptr), expiredTime(0) {}
};

class LRUCache {
private:
    tsl::hopscotch_map<std::string, LRUNode*> lruMap;
    LRUNode* head;
    LRUNode* tail;
    int entriesNum;
    int maxEntries;

    void detach(LRUNode* node) {
        if (node == this->head && node->next) {
            this->head = node->next;
        }
        if (node == tail && node->perv) {
            this->tail = node->perv;
        }
        if (node->perv) {
            node->perv->next = node->next;
        }
        if (node->next) {
            node->next->perv = node->perv;
        }
    }

    void attach(LRUNode* node) {
        std::cout << "attach\n";
        if (this->head && this->head != node) {
            this->head->perv = node;
            node->next = head;
            node->perv = nullptr;
            this->head = node;
        } else if (!this->head) {
            this->head = node;
            this->tail = node;
        }
    }

public:
    LRUCache((int max) : maxEntries_(max), entriesNum_(0), head_(nullptr), tail_(nullptr) {}
    ~LRUCache() {
        LRUNode* cur = head;
        LRUNode* tmp;

        while (cur) {
            tmp = cur->next;
            delete cur;
            cur = tmp;
        }
    }

    void put(std::string key, int nowTime, TestDataClass* data) {
        if (this->lruMap.count(key)) {
            // update
            LRUNode* node = this->lruMap[key];
            node->expiredTime = nowTime + cacheTTL;
            node->data = data;
            this->detach(node);
            this->attach(node);
        } else {
            if (this->entriesNum >= this->maxEntries) {
                LRUNode* tmp = this->tail;
                this->detach(this->tail);
                this->lruMap.erase(tmp->key);
                delete tmp;
                this->entriesNum--;
            }
            LRUNode* node = new LRUNode(key, data);
            node->expiredTime = nowTime + ctCacheTTL;
            this->lruMap_[key] = node;
            this->attach(node);
            this->entriesNum_++;
        }
    }

    TestDataClass* get(std::string key, int nowTime) {
        if (this->lruMap_.count(key)) {
            LRUNode* node = this->lruMap_[key];
            if (nowTime > node->expiredTime) {
                return nullptr;
            }
            this->detach(node);
            this->attach(node);

            return node->data;
        }
        return nullptr;
    }

    void print() {
        LRUNode* cur = this->head;

        while (cur) {
            std::cout << cur->key << " / " << cur->data->dataNum << ". ";
            cur = cur->next;
        }

        std::cout << std::endl;
    }
};

#endif //ASE_V3_TEST_LRUCACHE_HPP

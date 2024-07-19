#ifndef __ALIST_H
#define __ALIST_H

#include <iostream>
#include <cstdlib>
#include "utils.h"

template<typename T>
class AdjList;

template<typename T>
class adjListNode {
    friend class AdjList<T>;
    public:
        adjListNode(int v, double w): vertex(v), weight(w){}
        int getVertex() const{
            return this->vertex;
        }
        double getWeight() const{
            return this->weight;
        }
    private:
        int vertex{};
        double weight{};
        adjListNode* next{};
};

template<typename T>
class AdjList {
    public:
    typedef adjListNode<T> listNode;
    class iterator{
        public:
            iterator(listNode* node): cur(node){}
            iterator& operator++(){
                cur = cur->next;
                return *this;
            }
            bool operator==(const iterator& rhs){
                return (this->cur == rhs.cur);
            }
            bool operator!=(const iterator& rhs){
                return (this->cur != rhs.cur);
            }
            listNode& operator*(){
                return *this->cur;
            }
        private:
            listNode* cur{};
    };
    public:
        AdjList(){
            this->tail = new listNode(INT_MIN, 0);
            this->tail->next = this->tail;
        }
        bool empty() const{
            return (this->tail->next == this->tail);
        }
        AdjList& append(int vertex, double weight){
            listNode* newNode = new listNode(vertex, weight);
            newNode->next = this->tail->next;
            this->tail->next = newNode;
            this->tail = newNode;
            return *this;
        }
        iterator begin(){
            return {this->tail->next->next};
        }
        iterator end(){
            return {this->tail->next};
        }
        ~AdjList(){
            if (this->tail){
                listNode* head = this->tail->next, *tmp;
                while (head != this->tail){
                    tmp = head->next;
                    free(head);
                    head = tmp;
                }
                free(head);
                this->tail = {};
            }
        }
        friend std::ostream& operator<<(std::ostream& output, const AdjList& A){
            output.put('[');
            if (!A.empty()){
                AdjList::listNode* tail = A.tail;
                AdjList::listNode* head = tail->next->next;
                for (; head != tail; head = head->next)
                    output << head->vertex << ", ";
                output << head->vertex;
            }
            output.put(']');
            return output;
        }
    private:
        listNode* tail{};
};

#endif  // __LIST_H

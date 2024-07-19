#ifndef __GPRIORITY_QUEUE
#define __GPRIORITY_QUEUE

template<typename T, typename P = int>
class PriorityQueue;

template<typename T, typename P = int>
class heapNode{
    friend class PriorityQueue<T, P>;
    public:
        template<typename... Args>
        heapNode(P priority, const Args&... args){
            this->__item = new T{args...};
            this->__priority = priority;
        }
        ~heapNode(){
            delete this->__item;
            this->__item = {};
        }
    private:
        T* __item{};
        P __priority{};
};

template<typename T, typename P>
class PriorityQueue{
    public:
        PriorityQueue(int size){
            if (size < 0)
                throw "Size Error";
            this->size = size;
            this->A = new heapNode<T, P>*[size];
            repeat(size)
                this->A[i] = {};
        }
        bool empty() const{
            return (!this->n);
        }
        template<typename... Args>
        PriorityQueue& insert(P priority, const Args&... args){
            int par = this->parent(this->n), cur = this->n;
            this->A[this->n] = new heapNode<T, P>(priority, args...);
            while ((par >= 0) && (A[cur]->__priority < A[par]->__priority)){
                this->swap(par, cur);
                cur = par;
                par = this->parent(cur);
            }
            ++(this->n);
            return *this;
        }
        T& extractMin(){
            T* a = this->A[0]->__item;
            --(this->n);
            this->swap(0, this->n);
            this->heapify(0);
            return *a;
        }
        ~PriorityQueue(){
            if (this->A){
                repeat(this->n)
                    delete this->A[i];
                delete this->A;
                this->A = {};
            }
        }
    private:
        heapNode<T, P>** A;
        int n{};
        int size{};

        static int parent(int n){
            return (n & 1) ? (n/2) : (n/2 - 1);
        }
        void swap(int i, int j){
            auto tmp = this->A[i];
            this->A[i] = this->A[j];
            this->A[j] = tmp;
        }
        void heapify(int root){
            int l = root * 2 + 1, r = l + 1, smallest = root;
            if ((l < n) && (A[l]->__priority < A[smallest]->__priority))
                smallest = l;
            if ((r < n) && (A[r]->__priority < A[smallest]->__priority))
                smallest = r;
            if (smallest != root){
                swap(root, smallest);
                heapify(smallest);
            }
        }
};

#endif  // __GPRIORITY_QUEUE

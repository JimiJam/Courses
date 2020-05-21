#include <iostream>
#include <vector>
#include <algorithm>

// custom heap
class MaxHeap {
  public:
    std::vector<long> heap;

    void InsertElement(long number) {
        heap.push_back(number);
        SiftUp(heap.size());
    }

    long ExtractMax() {
        long max = -1;
        if (heap.size() > 0) {
            max = heap[0];
            std::swap(heap[0], heap[heap.size() - 1]);
            heap.pop_back();
            SiftDown(1);    
        }
        
        return max;
    }

  private:
    int GetMaxChild(int index){
        long left_child = -1;
        long right_child = -1;
        
        if ((index * 2) <= heap.size()) {
            left_child = heap[index * 2 - 1];
        }

        if ((index * 2 + 1) <= heap.size()) {
            right_child = heap[index * 2];
        }

        if (left_child >= right_child) {
            return index * 2;
        }
        else {
            return (index * 2 + 1);
        }
    }

    void SiftUp(int index) {
        if (heap[index - 1] > heap[index / 2 -1] && index != 1){
            std::swap(heap[index - 1], heap[index / 2 - 1]);
            SiftUp(index / 2);         
        }
    }

    void SiftDown(int index) {
        int max_child = GetMaxChild(index);

        if (max_child <= heap.size() && heap[max_child - 1] > heap[index - 1]) {
            std::swap(heap[max_child - 1], heap[index - 1]);
            SiftDown(max_child);
        }
    }
};


// main func
void QueueWithPriority(){
    MaxHeap heap;
    int num;
    std::cin >> num;
    std::vector<long> result;

    for(int i = 0; i < num; i++){
	std::string command;
        std::cin >> command;
	if (command.find("Insert") != std::string::npos){
	    long number;
	    std::cin >> number;
	    heap.InsertElement(number);
	}
	else if (command.find("ExtractMax") != std::string::npos){
            int max = heap.ExtractMax();
            if (max != -1) {
                result.push_back(max);
            }
	    }
    }

    // print result
    for (auto &r : result){
        std::cout << r << std::endl;
    }
}
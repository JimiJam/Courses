#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

void DecodeHaffman(){
    // get data
    int n, str_len;
    std::cin >> n >> str_len;
    std::map<std::string, std::string> haff_dict;;
    
    // create haffman dict
    for(int i = 0; i < n; i++){
        std::string value, key;
        std::cin >> value >> key;
        value = value[0];
        haff_dict.insert(std::pair<std::string, std::string>(key, value));
    }
    
    std::string encoded_string;
    std::cin>>encoded_string;
    
    // decode string
    std::string res_string = "";
    std::string cur_code = "";
    
    for(auto& c : encoded_string){
        cur_code += c;
        if(haff_dict.count(cur_code) != 0){
            res_string += haff_dict[cur_code];
            cur_code = "";
        }
    }
    
    std::cout << res_string << std::endl;
}

struct Node{
    std::string key;
    int priority;
    Node *left;
    Node *right;
};

// Traverse tree and fill haffman dict
void TraverseTree(Node* leaf, std::string cur_code, std::map<std::string, std::string> *haffman_dict){
    if(leaf == NULL) return;
    // cargo check
    if(leaf->key.find("cargo_") == std::string::npos){
        // null pointer check
        if(haffman_dict){
		haffman_dict->insert(std::pair<std::string, std::string>(leaf->key, cur_code));
	}
    }

    TraverseTree(leaf->left, cur_code + "0", haffman_dict);
    TraverseTree(leaf->right, cur_code + "1", haffman_dict);
}

// lambda func for sorting
bool SortDescSecond(const Node* a, const Node* b) { 
    return (a->priority > b->priority); 
} 

// create new Node
Node* CreateNode(std::string key, int priority, Node* left_leaf, Node* right_leaf){
    Node* new_node = new Node;
    new_node->key = key;
    new_node->priority = priority;
    new_node->left = left_leaf;
    new_node->right = right_leaf;

    return new_node;
}

std::string EncodeHaffman(std::string input_str) {
    std::string encoded_str = "";
    
    // get priority
    std::vector<Node*> queue_with_priority;
    
    for(auto& c : input_str){
        bool not_find = true;
        std::string s;
        s.push_back(c);
        
        for(auto& q : queue_with_priority){
            if(q->key == s){
                q->priority += 1;
                not_find = false;
                break;
            }
        }
        
        if(not_find){
            queue_with_priority.push_back(CreateNode(s, 1, NULL, NULL));
        }
    }
    
    // sort queue
    sort(queue_with_priority.begin(), queue_with_priority.end(), SortDescSecond);
    
    // build binary tree
    int cargo_count = 1;
    while(queue_with_priority.size() != 1){
	Node* left_leaf = queue_with_priority.back();
        queue_with_priority.pop_back();
   	Node* right_leaf = queue_with_priority.back();
        queue_with_priority.pop_back();

        std::string cargo_key = "cargo_" + std::to_string(cargo_count);
        int cargo_priority = left_leaf->priority + right_leaf->priority;

	queue_with_priority.push_back(CreateNode(cargo_key, cargo_priority, left_leaf, right_leaf));
	sort(queue_with_priority.begin(), queue_with_priority.end(), SortDescSecond);

        cargo_count++;
    }
    
    // generate haffman dict
    std::map<std::string, std::string> haffman_dict;
    TraverseTree(queue_with_priority.back(), "", &haffman_dict);
    
    // for one element
    if(queue_with_priority.size() == 1 && haffman_dict.size() == 1){
        haffman_dict[queue_with_priority.back()->key] = "0";
    }
    
    // encoding input string
    for(auto& c : input_str){
        std::string s;
        s.push_back(c);
	if(haffman_dict.count(s) != 0){
            encoded_str += haffman_dict[s];
        }
    }
    
    return encoded_str;
}

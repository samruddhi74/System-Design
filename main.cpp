#include <iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<queue>
#include<numeric>
#include<set>
using namespace std;

typedef long long ll;

class ConsistentHasRing{
    private:
    map<int,string> ring;
    int replicas;
    int get_hash(const string& s){
        hash<string> hash_function;
        return hash_function(s);
    }
    public:
    ConsistentHasRing(int replicas): replicas(replicas){}
    void add_node(const string& node){
        for(int i=0;i<replicas;i++){
            int replica_key = get_hash(node + "_" + to_string(i));
            ring[replica_key] = node;
        }
    }

    void delete_node(const string& node){
        for(int i=0;i<replicas;i++){
            int replica_key = get_hash(node + "_" + to_string(i));
            ring.erase(replica_key);
        }
    }

    string get_node(const string& key){
        if(ring.empty()) return "";
        int hash_value = get_hash(key);
        auto nearest_node = ring.lower_bound(hash_value);
        
        if(nearest_node == ring.end()) nearest_node = ring.begin();
        return nearest_node->second;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ConsistentHasRing hash_ring(3);
    hash_ring.add_node("Node_A");
    hash_ring.add_node("Node_B");
    hash_ring.add_node("Node_C");
    string key = "first_key";
    string node = hash_ring.get_node("first_key");
    cout<<"The key "<< key << " is mapped to node " << node ;
    return 0;
}


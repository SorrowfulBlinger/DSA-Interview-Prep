/* Weighted Quick Union with Path Compression */

#ifndef WeightedQUPC_hpp
#define WeightedQUPC_hpp

#include <iostream>
#include <vector>

namespace DynamicConnectivity {
    
    class WeightedQUPC final {
        
    private:
        /* Number of connected components */
        int mCountCC;
        
        /* Vector storing parent pointers for all nodes*/
        std::vector<int> mParent;
        
        /* vector storing max depth for all nodes */
        std::vector<int> mMaxDepth;
        
        /* Total nodes in the system */
        int mCount;
        
        WeightedQUPC();
        
    public:
        
        /* Merges the 2 nodes */
        int DoUnion(int node1, int node2);
        
        /* Gets the root of node */
        int GetRoot(int node);
        
        /* Returns true if 2 nodes are connected */
        bool AreTheyConnected(int node1 , int node2);
        
        /* Get total nnumber of connected components*/
        int GetTotalCC();
        
        /* Builds the DS by reading from file */
        static void Build(const std::string pDataFile, bool pVerboseOn);
        
        /* Print Parent vector */
        void PrintParentVec();
        
        /* Print maxdepth vector */
        void PrintMaxDepthVec();
        
        explicit WeightedQUPC(int pCount);
    };
}
#endif /* WeightedQUPC_hpp */

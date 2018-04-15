/* Weighted Quick Union with Path Compression */

#include "WeightedQUPC.hpp"
#include <fstream>

namespace DynamicConnectivity {
    
    WeightedQUPC::WeightedQUPC(int pCount) :
    mCount(pCount),
    mCountCC(pCount){
        for(auto i=0; i< pCount; i++) {
            mParent.push_back(i);
            mMaxDepth.push_back(1);
        }
    };
    
    bool WeightedQUPC::AreTheyConnected(int node1, int node2) {
        if(GetRoot(node1) == GetRoot(node2)) {
            return true;
        }
        return false;
    }
    
    int WeightedQUPC::DoUnion(int node1, int node2) {
        if(AreTheyConnected(node1, node2)) {
            return GetRoot(node1);
        } else {
            auto node2Root = GetRoot(node2);
            auto node1Root =  GetRoot(node1);
            if(mMaxDepth.at(node1Root) > mMaxDepth.at(node2Root)) {
                mParent.at(node2Root) = node1Root;
                /* Weighted logic */
                if(mMaxDepth.at(node2Root) + 1 > mMaxDepth.at(node1Root)) {
                    mMaxDepth.at(node1Root) = mMaxDepth.at(node2Root) + 1;
                }
            } else {
                mParent.at(node1Root) = node2Root;
                /* Weighted logic */
                if(mMaxDepth.at(node1Root) + 1 > mMaxDepth.at(node2Root)) {
                    mMaxDepth.at(node2Root) = mMaxDepth.at(node1Root) + 1;
                }
            }
            mCountCC--;
            return node2Root;
        }
    }
    
    int WeightedQUPC::GetRoot(int node) {
        auto lRoot = node;
        while(lRoot != mParent.at(lRoot) ) {
            lRoot = mParent.at(lRoot);
        }
        /* Path Compression */
        auto lAnotherNode = node;
        while(lAnotherNode != mParent.at(lAnotherNode)) {
            auto lParent = mParent.at(lAnotherNode);
            auto lGParent = mParent.at(lParent);
            if(lGParent != lParent && lGParent!= lRoot) {
                mParent.at(lParent) = lRoot;
                lAnotherNode = lGParent;
            } else {
                lAnotherNode = lParent;
            }
        }
        return lRoot;
    }
    
    int WeightedQUPC::GetTotalCC() {
        return mCountCC;
    }
    
    /* Print Parent vector */
    void WeightedQUPC::PrintParentVec() {
        std::cout << "Parent Vector" << std::endl;
        std::for_each(mParent.cbegin(), mParent.cend(), [](const int& lElement) {
            std::cout << lElement << ":";
        });
        std::cout << std::endl;
    }
    
    /* Print maxdepth vector */
    void WeightedQUPC::PrintMaxDepthVec() {
        std::cout << "Max Depth Vector" << std::endl;
        std::for_each(mMaxDepth.cbegin(), mMaxDepth.cend(), [](const int& lElement) {
            std::cout << lElement << ":";
        });
        std::cout << std::endl;
    }
    
    void WeightedQUPC::Build(const std::string pDataFile, bool pVerboseOn) {
        std::cout << std::endl << "Reading " << pDataFile << std::endl;
        std::ifstream lInFile(pDataFile);
        int node1, node2, lCount;
        lInFile >> lCount;
        WeightedQUPC lQU(lCount);
        while(lInFile >> node1 >> node2) {
            lQU.DoUnion(node1, node2);
        }
        std::cout << "Total Connected Components - " << lQU.GetTotalCC() << std::endl;
        if(pVerboseOn) {
            lQU.PrintParentVec();
            lQU.PrintMaxDepthVec();
        }
    }
}

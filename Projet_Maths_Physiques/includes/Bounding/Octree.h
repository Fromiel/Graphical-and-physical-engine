#ifndef OCTREE_H
#define OCTREE_H

#include <algorithm>
#include <iostream>
#include <vector>

template<typename T>
class OctreeNode {
    private:
        float x, y, z, width;
        int depth;
        OctreeNode<T>* parent;
        std::vector<OctreeNode<T>*> children;
        std::vector<T> nodeContent;

        bool checkIfIn(const T &item) {
            if (x <= item.x && item.x + item.maxWidth <= x + width &&
                y <= item.y && item.y + item.maxWidth <= y + width &&
                z <= item.z && item.z + item.maxWidth <= z + width
            ) return true;
            else return false;
        }

        void createEightChildren() {
            children.emplace_back(new OctreeNode<T>(x, y, z, width, depth-1, this));
            children.emplace_back(new OctreeNode<T>(x + width, y, z, width, depth-1, this));
            children.emplace_back(new OctreeNode<T>(x, y + width, z, width, depth-1, this));
            children.emplace_back(new OctreeNode<T>(x, y, z + width, width, depth-1, this));
            children.emplace_back(new OctreeNode<T>(x + width, y + width, z, width, depth-1, this));
            children.emplace_back(new OctreeNode<T>(x, y + width, z + width, width, depth-1, this));
            children.emplace_back(new OctreeNode<T>(x + width, y, z + width, width, depth-1, this));
            children.emplace_back(new OctreeNode<T>(x + width, y + width, z + width, width, depth-1, this));
            return;
        }

        std::vector<std::pair<T, T>> collideWithEveryoneLower(const T &item) const {
            std::vector<std::pair<T, T>> collisions;
            std::vector<std::pair<T, T>> childCollisions;

            for (const OctreeNode<T>* child : children) {
                for (const T &childItem : child->nodeContent) {
                    collisions.emplace_back(std::pair<T, T>(item, childItem));
                }

                childCollisions = child->collideWithEveryoneLower(item);
                for (auto collision : childCollisions) collisions.push_back(collision);
            }

            return collisions;
        }
    
    public:
        OctreeNode(const float &x, const float &y, const float &z, const float &width, const int &depth, OctreeNode<T> *parent=nullptr) : x(x), y(y), z(z), width(width), depth(depth), parent(parent) {
            if (depth != 0) createEightChildren();
            return;
        }

        ~OctreeNode() {
            for (OctreeNode<T>* child : children) delete child;
            return;
        }

        void insertItem(const T &item) {
            int inCount = 0;
            for (OctreeNode<T>* childNode : children) if (childNode->checkIfIn(item)) inCount++;

            if (inCount != 1) {
                nodeContent.push_back(item);
                return;
            }

            for (OctreeNode<T>* childNode : children) {
                if (childNode->checkIfIn(item)) {
                    childNode->insertItem(item);
                    break;
                }
            }
            return;
        }

        std::vector<std::pair<T, T>> gatherCollisions() const {
            std::vector<std::pair<T, T>> collisions;
            std::vector<std::pair<T, T>> childCollisions;
            std::vector<std::pair<T, T>> intersectCollisions;

            for (long long unsigned int i=0; i<nodeContent.size(); ++i) {
                // Gather on same level
                for (long long unsigned int j=i+1; j<nodeContent.size(); ++j) {
                    collisions.emplace_back(std::pair<T, T>(nodeContent[i], nodeContent[j]));
                }

                // Gather on intersections
                intersectCollisions = collideWithEveryoneLower(nodeContent[i]);
                for (auto collision : intersectCollisions) collisions.push_back(collision);
            }


            // Gather on lower levels
            for (const OctreeNode<T>* child : children) {
                childCollisions = child->gatherCollisions();
                for (auto collision : childCollisions) collisions.push_back(collision);
            }

            return collisions;
        }

    friend std::ostream &operator<<(std::ostream &out, const OctreeNode<T> &node) {
        out << "(";
        for (const T &element : node.nodeContent) out << element << ";";
        out << ")\n";
        return out;
    }
};

template<typename T>
class Octree {
    private:
        OctreeNode<T>* rootNode;

    public:
        float x, y, z, width;
        int depth;

        Octree(const float &x, const float &y, const float &z, const float &width, const int depth=3) : x(x), y(y), z(z), width(width) {
            this->rootNode = new OctreeNode<T>(x, y, z, width, depth);
            return;
        }

        ~Octree() {
            delete rootNode;
            return;
        }

        void insertItem(const T &item) {
            rootNode->insertItem(item);
            return;
        }

        std::vector<std::pair<T, T>> gatherCollisions() const {
            return rootNode->gatherCollisions();
        }

    friend std::ostream &operator<<(std::ostream &out, const Octree &tree) {
        out << "(" << tree.x << ";" << tree.y << ";" << tree.z << ")";
        return out;
    }
};

#endif

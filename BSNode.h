#ifndef BSNode_H
#define BSNode_H

#include <ostream>

template <typename T>
class BSNode {
	public:
		//attributos
		T elem;
		BSNode<T>* left;
		BSNode<T>* right;

		//metodos
		BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr){
			this->elem = elem;
			this->left = left;
			this->right = right;
		}
		friend std::ostream& operator<<(std::ostream& os, const BSNode<T>& node) {
			os << node.elem;
			return os;
		}
};

#endif

#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
	private:
		//atributos privados
		int nelem;
		BSNode<T>* root;
		
		//metodos privados
		BSNode<T>* search(BSNode<T>* n, T e) const{
			if(n == nullptr){
				return nullptr;
			}
			if(e == n->elem){
				return n;
			}
			if(e < n->elem){
				return search(n->left, e);
			}
			return search(n->right, e);
		}
		BSNode<T>* insert(BSNode<T>* n, T e){
			if(n == nullptr){
				return new BSNode<T>(e);
			}
			if(e == n->elem){
				throw std::runtime_error("Elemento duplicado");
			}
			if(e < n->elem){
				n->left = insert(n->left, e);
			}else{
				n->right = insert(n->right, e);
			}
			return n;
		}
		void print_inorder(std::ostream &out, BSNode<T>* n) const{
			if(n == nullptr){
				return;
			}
			print_inorder(out, n->left);
			out << n->elem << " ";
			print_inorder(out, n->right);
		}
		BSNode<T>* remove(BSNode<T>* n, T e){
			if(n == nullptr){
				throw std::runtime_error("Elemento no encontrado");
			}
			if(e < n->elem){
				n->left = remove(n->left, e);
			}else if(e > n->elem){
				n->right = remove(n->right, e);
			}else{
				if(n->left == nullptr){
					BSNode<T>* aux = n->right;
					delete n;
					return aux;
				}
				if(n->right == nullptr){
					BSNode<T>* aux = n->left;
					delete n;
					return aux;
				}
				n->elem = max(n->left);
				n->left = remove_max(n->left);
			}
			return n;
		}
		T max(BSNode<T>* n) const{
			if(n == nullptr){
				throw std::runtime_error("Arbol vacio");
			}
			if(n->right != nullptr){
				return max(n->right);
			}
			return n->elem;
		}
		BSNode<T>* remove_max(BSNode<T>* n){
			if(n->right == nullptr){
				BSNode<T>* aux = n->left;
				delete n;
				return aux;
			}
			n->right = remove_max(n->right);
			return n;
		}
		void delete_cascade(BSNode<T>* n){
			if(n == nullptr){
				return;
			}
			delete_cascade(n->left);
			delete_cascade(n->right);
			delete n;
		}

	public:
		//metodos publicos
		BSTree(){
			nelem = 0;
			root = nullptr;
		}
		int size() const{
			return nelem;
		}
		T search(T e) const{
			BSNode<T>* n = search(root, e);
			if(n == nullptr){
				throw std::runtime_error("Elemento no encontrado");
			}
			return n->elem;
		}
		T operator[](T e) const{
			return search(e);
		}
		void insert(T e){
			root = insert(root, e);
			nelem++;
		}
		friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
			bst.print_inorder(out, bst.root);
			return out;
		}
		void remove(T e){
			nelem--;
			remove(root, e);
		}
		~BSTree(){
			delete_cascade(root);
		}
};

#endif

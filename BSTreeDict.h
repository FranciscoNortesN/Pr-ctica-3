#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
	private:
		//atributos
		BSTree<TableEntry<V>>* tree;
	public:
		//metodos
		BSTreeDict(){
			tree = new BSTree<TableEntry<V>>();
		}
		~BSTreeDict(){
			delete tree;
		}
		friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
			out << *bs.tree;
			return out;
		}
		V operator[](std::string key) const {
			return search(key);
		}
		int entries() override{
			return tree->size();
		}
		void insert(std::string key, V value) override{
			TableEntry<V> entry(key, value);
			tree->insert(entry);
		}
		V search(std::string key) override{
			TableEntry<V> entry(key, V());
			TableEntry<V> *result = tree->search(entry);
			if(result == nullptr){
				throw std::invalid_argument("Key not found");
			}
			return result->getValue();
		}
		void remove(std::string key) override{
			TableEntry<V> entry(key, V());
			tree->remove(entry);
		}
};

#endif

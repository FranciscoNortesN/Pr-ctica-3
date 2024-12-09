#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <string>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../Pr-ctica-1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
	private:
		//atributos privados
		int n;
		int max;
		ListLinked<TableEntry<V> > *table;

		//metodos privados
		int h(std::string key){
			int sum = 0;
			for (int i = 0; i<key.length(); i++){
				sum+=int(key.at(i));
			}
			return sum % max;
		}

	public:
		//metodos publicos
		HashTable(int size){
			n = 0;
			max = size;
			table = new ListLinked<TableEntry<V>> [max];
		}
		~HashTable(){
			delete [] table;
		}
		int capacity(){
			return max;
		}
		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			for (int i = 0; i<th.max; i++){
				if (th.table[i].empty()){
					out << i << ": " << "empty" << std::endl;
					continue;
				}
				out << i << ": " << th.table[i] << std::endl;
			}
			return out;
		}
		V operator[](std::string key){
			return search(key);
		}
		void insert(std::string key, V value) override{
			int pos = h(key);
			TableEntry<V> entry(key, value);
			if (table[pos].search(entry) == -1) table[pos].append(entry);
			else throw std::runtime_error("Key already exists");
			n++;
		}
		V search(std::string key) override{
			int pos = h(key);
			TableEntry<V> entry(key, V());
			int i = table[pos].search(entry);
			if (i == -1){
				throw std::runtime_error("Key not found");
			}
			return table[pos].get(i).value;
		}
		V remove(std::string key) override{
			int pos = h(key);
			TableEntry<V> entry(key, V());
			int i = table[pos].search(entry);
			if (i == -1){
				throw std::runtime_error("Key not found");
			}
			V value = table[pos].get(i).value;
			table[pos].remove(i);
			n--;
			return value;
		}
		int entries() override{
			return n;
		}

};

#endif

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../Pr-ctica-1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        //atributos privados
	int n;
	int max;
	ListLinked<TableEntry<V>> *table;
	//métodos privados
	int h(std::string key){
		int sum = 0;
		for (int i = 0; i < key.length(); i++) {
			sum += int(key.at(i));
		}
		return sum % max;
	}

    public:
        // métodos públicos
	HashTable(int size){
		max = size;
		table = new ListLinked<TableEntry<V>>[max];
		n = 0;
	}
	~HashTable(){
		delete[] table;
	}
	int capacity(){
		return max;
	}
	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
		for (int i = 0; i < th.max; i++) {
			out << i << ": ";
            ListLinked<TableEntry<V>>& bucket = th.table[i];
            if (bucket.size() == 0) {
                out << "(vacía)";
            } else {
                for (int j = 0; j < bucket.size(); j++) {
                    out << bucket.get(j).key << " " << bucket[j].value;
                }
            }
            out << endl;
		}
		return out;
	}
	V operator[](std::string key){
		int pos = h(key);
		ListLinked<TableEntry<V>> aux = table[pos];
		for(int i=0; i < table[pos].size(); i++){
			if (aux[i].key == key) {
				return aux[i].value;
			}
		}
		throw std::runtime_error("Key not found");
	}
	void insert(std::string key, V value) override {
		int pos = h(key);
		TableEntry<V> entry(key, value);
		if (table[pos].search(entry) == -1) {
			table[pos].append(entry);
			n++;
		}
	}
	V search(std::string key) override {
		int pos = h(key);
		V value;
		ListLinked<TableEntry<V>> aux = table[pos];
		for(int i=0; i < table[pos].size(); i++){
			if (aux[i].key == key) {
				value = aux[i].value;
				return value;
			}
		}
		throw std::runtime_error("Key not found");
	}
	V remove(std::string key) override {
		int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).key == key) {
                V value = bucket.get(i).value;
                bucket.remove(i);
                n--;
                return value;
            }
        }
        throw runtime_error("Key not found");
	}
	int entries() override {
		return n;
	}
};

#endif

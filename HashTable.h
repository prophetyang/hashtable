#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <map>
#include <list>
#include <iostream>
#include <stdlib.h>

using std::map;
using std::list;
using std::pair;
using std::cout;
using std::endl;

const int DefaultHashBuckets = 128;

template<typename T>
class HashTable {
public:
	HashTable() {}

	bool AddElement(T &element) {
		int hashKey = GenHashKey(element);

		if (m_hashTable.find(hashKey) == m_hashTable.end()) {
			list<T> *pList = new list<T>;
			if (! pList) {
				return false;
			}

			m_hashTable.insert(pair<int, list<T>*>(hashKey, pList));
		}

		(m_hashTable[hashKey])->push_back(element);

		return true;	
	}

	bool IsElementInHashTable(T &element) {
		int hashKey = GenHashKey(element);

		if (m_hashTable.find(hashKey) != m_hashTable.end()) {
			return IsElementInHashEntry(m_hashTable[hashKey], element);
		}

		return false;
	}

	void DumpHashTable() const {
		typename map<int, list<T>*>::const_iterator mapIter;

		for (mapIter=m_hashTable.begin(); mapIter!=m_hashTable.end(); mapIter++) {
			DumpHashEntry(mapIter->first, mapIter->second);
		}
	}

	void FreeHashTable() {
		typename map<int, list<T>*>::iterator mapIter;

		//cout << __func__ << "() before m_hashTable.size()=" << m_hashTable.size() << endl;
		for (mapIter=m_hashTable.begin(); mapIter!=m_hashTable.end(); mapIter++) {
			m_hashTable.erase(mapIter);
			FreeHashEntry(mapIter->first, mapIter->second);
			delete mapIter->second;
		}
		//cout << __func__ << "() after m_hashTable.size()=" << m_hashTable.size() << endl;
	}

	virtual void PrintElement(int hashKey, T element) const {
		cout << "HashKey=" << hashKey << ", value=" << element << endl;
	}

	virtual ~HashTable() { FreeHashTable(); }

protected:
	virtual int GenHashKey(T &element) {
		int hashKey = 0;
		int size = sizeof(T);
		char *content = reinterpret_cast<char *>(&element);

		for (int i=0; i<size; i++) {
			hashKey += content[i];
		}

		return abs(hashKey % DefaultHashBuckets);
	}

	bool IsElementInHashEntry(list<T> *pList, T &element) {
		typename list<T>::const_iterator listIter;

		for (listIter=pList->begin(); listIter!=pList->end(); listIter++) {
			if ((*listIter) ==  element) {
				return true;
			}
		}

		return false;
	}

	void DumpHashEntry(int hashKey, list<T> *pList) const {
		typename list<T>::const_iterator listIter;

		for (listIter=pList->begin(); listIter!=pList->end(); listIter++) {
			PrintElement(hashKey, (*listIter));
		}
	}

	void FreeHashEntry(int hashKey, list<T> *pList) {
		typename list<T>::iterator listIter;

		//cout << __func__ << "() before pList->size()=" << pList->size() << endl;
		for (listIter=pList->begin(); listIter!=pList->end(); listIter++) {
			pList->erase(listIter);
			--listIter;
		}
		//cout << __func__ << "() after pList->size()=" << pList->size() << endl;
	}

protected:
	map<int, list<T>*> m_hashTable;
};

#endif


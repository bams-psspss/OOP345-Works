#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include "Book.h"

namespace seneca
{
	template <typename T, unsigned C>
	class Collection
	{
		//T = array
		//C = capacity of the item
		T m_items[C]{};
		unsigned m_size{};

		static T m_smallestItem;
		static T m_largestItem;

	protected:
		void setSmallestItem(const T& items);
		void setLargestItem(const T& items);

		T& operator[](unsigned index);
		void incrSize();


	public:
		Collection();

		//return m_snallestItem
		static T getSmallestItem();
		//return m_largestItem
		static T getLargestItem();

		//return current number of items
		unsigned size() const;
		//return capacity of collection
		unsigned capacity() const;
		//If size same as capacity return false
		//Otherwise update the and return true
		bool operator+=(const T& items);

		std::ostream& print(std::ostream& os) const;
	};

	template <typename T, unsigned C>
	Collection<T, C>::Collection() : m_size{ 0 } {}


	template <typename T, unsigned C>
	T Collection<T, C>::m_smallestItem = T(9999);

	template <typename T, unsigned C>
	T Collection<T, C>::m_largestItem = T(-9999);

	//Template Specialize
	template <>
	Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

	template <>
	Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

	template <>
	Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);

	template <>
	Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);


	template <typename T, unsigned C>
	void Collection<T, C>::setSmallestItem(const T& items) {
		if (items < m_smallestItem) {
			m_smallestItem = items;
		}
	}

	template <typename T, unsigned C>
	void Collection<T, C>::setLargestItem(const T& items) {
		if (items > m_largestItem) {
			m_largestItem = items;
		}
	}

	template<typename T, unsigned C>
	T& Collection<T, C>::operator[](unsigned index) {
		return m_items[index];
	}

	template<typename T, unsigned C>
	void Collection<T, C>::incrSize() {
		m_size++;
	}

	template <typename T, unsigned C>
	T Collection<T, C>::getSmallestItem() {
		return m_smallestItem;
	}

	template <typename T, unsigned C>
	T Collection<T, C>::getLargestItem() {
		return m_largestItem;
	}


	template <typename T, unsigned C>
	unsigned Collection<T, C>::size() const {
		return m_size;
	}

	template <typename T, unsigned C>
	unsigned Collection<T, C>::capacity() const {
		return C;
	}

	template <typename T, unsigned C>
	bool Collection<T, C>::operator+=(const T& items) {
		bool answer = true;
		if (m_size >= C) {
			answer = false;
		}
		setSmallestItem(items);
		setLargestItem(items);
		m_items[m_size++] = items;

		return answer;
	}

	template <typename T, unsigned C>
	std::ostream& Collection<T, C>::print(std::ostream& os) const {
		os << "[";
		for (unsigned i = 0; i < m_size; ++i) {
			os << m_items[i];
			i != m_size - 1 ? os << "," : os << "";
		}
		os << "]" << std::endl;

		return os;
	}

//Don't know how to do the specialize in the prin() or book and capacity 72??
	template <>
	std::ostream& Collection<Book, 10>::print(std::ostream& os) const {
		os << "| ---------------------------------------------------------------------------|\n";

		for (unsigned i = 0; i < m_size; ++i) {
			os << "|";
			os << std::setw(57) << std::right << m_items[i].getTitle() + ","
				+ std::to_string(m_items[i].getNumChapters()) + ","
				+ std::to_string(m_items[i].getNumPages()) << " | ";

			os << std::setw(15) << std::left << "(" + std::to_string(m_items[i].avgPage()) + ")";
			os << std::setw(2) << std::right << "|";

			if (i <= m_size - 1) {
				os << "\n";
			}
		}
		os << "| ---------------------------------------------------------------------------|\n";

		return os;
	}

	template <>
	std::ostream& Collection<Book, 72>::print(std::ostream& os) const {
		os << "| ---------------------------------------------------------------------------|\n";

		for (unsigned i = 0; i < m_size; ++i) {
			os << "|";
			os << std::setw(57) << std::right << m_items[i].getTitle() + ","
				+ std::to_string(m_items[i].getNumChapters()) + ","
				+ std::to_string(m_items[i].getNumPages()) << " | ";

			os << std::setw(15) << std::left << "(" + std::to_string(m_items[i].avgPage()) + ")";
			os << std::setw(2) << std::right << "|";

			if (i <= m_size - 1) {
				os << "\n";
			}
		}
		os << "| ---------------------------------------------------------------------------|\n";

		return os;
	}
}




#endif // !SENECA_COLLECTION_H

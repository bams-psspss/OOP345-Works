#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H
#include "Collection.h"

namespace seneca
{
	template <typename T>
	class OrderedCollection : public Collection<T, 72> {
	public:
		bool operator+=(const T& item);
	};

    template<typename T>
    bool OrderedCollection<T>::operator+=(const T& item) {
        bool answer = true;
        unsigned index = 0;

        if (this->size() >= 72) {
            answer = false; // Collection is full, insertion failed
        }
        else {
            // Find the appropriate index to insert the new item
            while (index < this->size() && this->operator[](index) < item) {
                ++index;
            }

            // Make space for the new item by shifting elements to the right
            for (unsigned i = this->size(); i > index; --i) {
                this->operator[](i) = this->operator[](i - 1);
            }

            // Insert the new item at the appropriate index
            this->operator[](index) = item;

            // Increment the size of the collection
            this->incrSize();
        }

        return answer; // Return true if insertion is successful, false otherwise
    }

}


#endif // !SENECA_ORDEREDCOLLECTION_H
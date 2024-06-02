/***********************************************************************
Name:		Pattarawan Saravaneeyawong
Date:		02 June 2024
StudentID:	130618234
Email:		psaravaneeyawong@myseneca.ca

I declar that this submission is the result of my own work and I only copied the code 
that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.
***********************************************************************/
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
            answer = false; 
        }
        else {
            while (index < this->size() && this->operator[](index) < item) {
                ++index;
            }

            for (unsigned i = this->size(); i > index; --i) {
                this->operator[](i) = this->operator[](i - 1);
            }

            this->operator[](index) = item;

            this->incrSize();
            this->setSmallestItem(item);
            this->setLargestItem(item);
        }

        return answer;
    }

}


#endif // !SENECA_ORDEREDCOLLECTION_H

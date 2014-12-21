//#include "Deck.h"
//
//
//template<typename T>
//Deck<T>::Deck()
//{
//}
//
//template<typename T>
//Deck<T>::~Deck()
//{
//}
//
//template<typename T>
//Deck<T>& Deck<T>::operator=(const Deck& other)
//{
//	this->list = other->list;
//}
//
//template<typename T>
//int Deck<T>::Size() const
//{
//	return list.size();
//}
//
//template<typename T>
//T Deck<T>::Get(int index) const
//{
//	if (index < list.size())
//		return list.at(index);
//	else
//		return;
//}
//
//template<typename T>
//void Deck<T>::Add(const T& elem)
//{
//	list.push_back(elem);
//}
//
//template<typename T>
//void Deck<T>::Shuffle()
//{
//	std::shuffle(list.begin(), list.end(), Utils::RandomNumber(list.size() - 1))
//}
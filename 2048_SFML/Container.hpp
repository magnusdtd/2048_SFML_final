#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "utils.hpp"

/**
 * @class Container
 * @brief A class that represents a container for storing data.
 *
 * This class provides a way to store and manage a collection of data.
 */
class Container {
public:
	u64 size; ///< The size of the container.
	u64* data; //< The pointer to the data stored in the container.

	/**
	 * @brief Default constructor.
	 *
	 * Initializes the container with a size of 0 and a null data pointer.
	 */
	Container() : data(nullptr), size(0) {}

	/**
	 * @brief Constructor that initializes the container with a given size.
	 *
	 * @param size The size of the container.
	 */
	Container(u64 size) {
		this->size = size;
		data = new u64[size];
	}

	/**
	 * @brief Destructor.
	 *
	 * Cleans up the data stored in the container.
	 */
	~Container() {
		delete[] data;
		data = nullptr;
		size = 0;
	}
};


#endif

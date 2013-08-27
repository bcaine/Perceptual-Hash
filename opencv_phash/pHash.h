#include <opencv2/imgproc/imgproc.hpp>
#include <map>
/*	Author: Ben Caine
	Date: 8/22/2013

	An educational and experimental Perceptual Hash Library for use with 
	OpenCV Mat objects.

	If you have comments or suggestions on ways to improve this code, notice
	errors or have questions, feel free to contact me. This is for education
	only, so feedback is greatly appreciated.
	
	Current Todo's:
	- Handle Collisions
	- Implement a hash[image_object] = DataType style syntax for assignments of
	  new hashes
	- Auto-resizing?
	- Possibly move getHash function into its own source file
	- Possibly create a new getHash function using Discrete Cosine
	  Transformations for more flexibility
	- Pay attention to coding standards, spend time working on efficiency.
*/
template <typename T>

class pHash {
private:
	//Our generic data
	T* my_data;

	// A storage of our Key vals and Images
	std::map<unsigned int, cv::Mat> keys;

	//Hash Table Size
	unsigned int table_size;
	
	//Number of elements in our table
	unsigned int num_elements;

	unsigned int getHash(const cv::Mat& image) {
		//Create a 8x8 version of our image.
		//Don't worry about it scaling correctly.
		cv::Mat smaller, gray;
		cv::resize(image, smaller, Size(8, 8));
		cv::cvtColor(smaller, gray, CV_BGR2GRAY);
		// Calculate the scalar average of the pixels;
		double avg = mean(gray)[0];
		unsigned long long hash_val = 0;
		for(int x=0; x<8; x++) {
			for(int y=0; y<8; y++) {
				hash_val <<= 1;
				hash_val |= 1*(static_cast<double>(gray.at<uchar>(x,y))>=avg );
			}
		}
		return hash_val % table_size;
	}
	
public:
	pHash(unsigned int size) {
		table_size = size;
		num_elements = 0;
		// Initialize our Hash Table data for our given table size
		my_data = new T[table_size];
	}

	~pHash() {
		delete[] my_data;
	}

	pHash operator= (pHash<T> second) {
		// Use iterators to copy seconds data into first.
		// This should take care of changing the number of
		// elements we say is in the hash
		this.table_size = second.max_size();
	}

	/**************************************************************************
	Iterators:
		- begin      Return iterator to beginning
		- end        Return iterator to end
		- rbegin     Return revsere iterator to reverse beginning
		- rend       Return reverse iterator to reverse end
		- cbegin     Return Const iterator to beginning
		- cend       Return Const iterator to end
		- crbegin    Return Const reverse iterator to reverse beginning
		- crend      Return Const reverse iterator to reverse end
	**************************************************************************/

	/**************************************************************************
	Capacity:
		- empty      Returns True if hash is empty
		- size		 Returns number of elements in hash
		- max_size   Returns size of the hash table
	**************************************************************************/
	// Returns whether the hash is empty or not
	bool empty() {
		if (num_elements == 0)
			return true;
		else
			return false;
	}

	// How many elements we have in our hash
	unsigned int size() {
		return num_elements;
	}

	// Total size of the table
	unsigned int max_size() {
		return table_size;
	}

	/**************************************************************************
	Element access:
		- operator[] Access Element (const or not, depending 
					 on pHash declaration
		- at         Access Element
	**************************************************************************/

	T& at(const cv::Mat& im) {
		T data = my_data[getHash(im)];
		// Doesn't work currently. How do I check if an index of an array
		// of a templated type was never set...
		if (data == NULL)
			num_elements++;
		return my_data[getHash(im)];
	}

	// Non-const version of subscript operator
	T& operator[] (const cv::Mat& im) {
		return at(im); 
	}

	// Const version of subscript operator
	const T& operator[] (const cv::Mat& im) const {
		return at(im); 
	}

	/**************************************************************************
	Modifiers:
		- Insert
		- Erase
		- Swap
		- Clear
		- Emplace
		- Emplace_hint
	**************************************************************************/
	
	// Insert 

	void erase(const cv::Mat& im) {
		my_data[getHash(im)] = NULL;
		keys.erase(im);	
	}

	/*************************************************************************
	RANDOM
	**************************************************************************/
	
	// Returns a map with the keys and images that we are using.
	std::map<unsigned int, cv::Mat> getKeys() {
		return keys;
	}
};
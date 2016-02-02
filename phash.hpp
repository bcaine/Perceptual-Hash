#ifndef PHASH_HPP
#define PHASH_HPP

#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <set>

/*	Author: Ben Caine
	Date: 8/22/2013

	An educational and experimental Perceptual Hash Library for use with
	OpenCV Mat objects. Many of its capabilities are based off the STL
	unordered_map library.

	If you have comments or suggestions on ways to improve this code,
	notice errors or have questions, feel free to contact me.
	This is for education only, so feedback is greatly appreciated.

	Current Todo's:
	- Handle Collisions
	- Iterators!
	- Possibly create a new getHash function using Discrete Cosine
	  Transformations for more flexibility between image variations
*/
template <typename T>

class phash {
  private:
    std::vector<T> data;
    std::set<unsigned int> used_indices;

    // A reverse of our data array (image is stored at hash value)
    std::vector<cv::Mat> keys;

    unsigned int table_size;
    unsigned int num_elements;

    unsigned int getHash(const cv::Mat& image);
  public:
    phash(unsigned int size);

    /**************************************************************************
    Capacity:
    	- empty      Returns True if hash is empty
    	- size		 Returns number of elements in hash
    	- max_size   Returns size of the hash table
    **************************************************************************/

    bool empty() {
        return (num_elements == 0);
    }
    unsigned int size() {
        return num_elements;
    }
    unsigned int max_size() {
        return table_size;
    }

    /**************************************************************************
    Element access:
    	- operator[] Access Element (const or not, depending
    	             on phash declaration
    	- at         Access Element
    **************************************************************************/

    T& at(const cv::Mat& im);

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
    	- Erase
    	- Clear
    **************************************************************************/

    void erase(const cv::Mat& im);
    void clear();
};

/******************************************************************************
These implementations are inside our header file for simplicity. If this
gets extra bloaty, splitting out would be smart.
*****************************************************************************/

template <typename T>
phash<T>::phash(unsigned int size) {
    table_size = size;
    num_elements = 0;
    // Initialize our Hash Table data for our given table size
    data = std::vector<T*>(table_size);
    // Our Images that we are using for keys
    keys = std::vector<cv::Mat*>(table_size);
}

template <typename T>
unsigned int phash<T>::getHash(const cv::Mat& image) {
    //Create a 8x8 version of our image.
    //Don't worry about it scaling correctly.
    cv::Mat smaller, gray;
    cv::resize(image, smaller, cv::Size(8, 8));
    cv::cvtColor(smaller, gray, CV_BGR2GRAY);
    // Calculate the scalar average of the pixels;
    double avg = mean(gray)[0];
    // The largest possible size is somewhere bigger than 32 bits
    // and smaller than 64 bits.
    unsigned long long hash_val = 0;
    // If the
    for(int x=0; x<8; x++) {
        for(int y=0; y<8; y++) {
            hash_val <<= 1;
            // If the greyscale value of a pixel is greater than the average
            // Put a 1 in that bit. Otherwise have it be a 0
            hash_val |= 1*(static_cast<double>(gray.at<uchar>(x,y))>=avg );
        }
    }
    return hash_val % table_size;
}

template <typename T>
void phash<T>::erase(const cv::Mat& im) {
    unsigned int location = getHash(im);
    data[location] = NULL;
    keys[location] = NULL;
    num_elements--;
}

template <typename T>
void phash<T>::clear() {
    for(int i=0; i < table_size; i++) {
        data[i] = NULL;
        keys[i] = NULL;
    }
    num_elements = 0;
}

template <typename T>
T& phash<T>::at(const cv::Mat& im) {
    unsigned int location = getHash(im);
    if (used_indices.count(location) == 0) {
        cv::Mat copy(im);
        keys[location] = &copy;
        num_elements++;
    }
    return data[location];
}

#endif // PHASH_HPP

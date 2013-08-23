#include <opencv2/imgproc/imgproc.hpp>
#include <map>
/*	Author: Ben Caine
	Date: 8/22/2013

	An educational and experimental Perceptual Hash Library for use with OpenCV Mat objects.

	If you have comments or suggestions on ways to improve this code, notice errors or have questions,
	feel free to contact me. This is for education only, so feedback is greatly appreciated.
	
	Current Todo's:
	- Handle Collisions
	- Implement a hash[image_object] = DataType style syntax for assignments of new hashes
	- Auto-resizing?
	- Possibly move getHash function into its own source file
	- Possibly create a new getHash function using Discrete Cosine Transformations for more flexibility
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
				hash_val |= 1*( static_cast<double>(gray.at<uchar>(x,y)) >= avg );
			}
		}
		return hash_val % table_size;
	}
	
public:
	pHash(unsigned int size) {
		table_size = size;
		// Initialize our Hash Table data for our given table size
		my_data = new T[table_size];
	}
	~pHash() {
		delete[] my_data;
	}

	void set(const cv::Mat& im, const T& val) {
		//Calculate our index with our hashing function
		unsigned int index = getHash(im);
		keys[index] = im;
		std::cout << "Set: " << index << " to: " << val << std::endl;
		my_data[index] = val;
	}

	T get(const cv::Mat& im) {
		return my_data[getHash(im)];
	}

	void remove(const cv::Mat& im) {
		my_data[getHash(im)] = NULL;
		keys.erase(im);	
	}
	
	// Currently appears broken. Either that or I don't know how to properly iterate through Maps
	 std::map<unsigned int, cv::Mat> getKeys() {
		return keys;
	}

	// Syntactic sugar for get
	T operator[] (const cv::Mat& im) {
		return get(im);
	}

};
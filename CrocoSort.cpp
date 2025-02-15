#include <iostream>

#define and &&
#define or ||
#define not !

typedef unsigned long long ull;

template<class T>
auto inline __Fusion3SortedList(T* buffer, int* data1, ull len1, T* data2, ull len2, T* data3, ull len3) -> void {

	while (len1 > 0 and len2 > 0 and len3 > 0) {
		if (*data1 <= *data3) {
			if (*data1 <= *data2) {
				*buffer = *data1;
				data1++;
				len1--;
			}
			else {
				*buffer = *data2;
				data2++;
				len2--;
			}
		}
		else if (*data2 <= *data3) {
			*buffer = *data2;
			data2++;
			len2--;
		}
		else {
			*buffer = *data3;
			data3++;
			len3--;
		}

		buffer++;
	}
	while (len1 > 0 and len2 > 0) {
		if (*data1 <= *data2) {
			*buffer = *data1;
			data1++;
			len1--;
		}
		else {
			*buffer = *data2;
			data2++;
			len2--;
		}
		buffer++;
	}

	while (len2 > 0 and len3 > 0) {
		if (*data1 <= *data3) {
			*buffer = *data1;
			data1++;
			len1--;
		}
		else {
			*buffer = *data3;
			data3++;
			len3--;
		}
		buffer++;
	}

	while (len2 > 0 and len3 > 0) {
		if (*data2 <= *data3) {
			*buffer = *data2;
			data2++;
			len2--;
		}
		else {
			*buffer = *data3;
			data3++;
			len3--;
		}
		buffer++;
	}

	while (len1 > 0) {
		*buffer = *data1;
		buffer++;

		data1++;
		len1--;
	}
	
	while (len2 > 0) {
		*buffer = *data2;
		buffer++;

		data2++;
		len2--;
	}

	while (len3 > 0) {
		*buffer = *data3;
		buffer++;

		data3++;
		len3--;
	}
}

template<class T>
auto __DoubleCrocoSort(T* data, unsigned long long length, T* buffer) -> void {
	switch (length) {
	case(0):
		break;
	case (1):
		break;
	case (2):
		if (data[1] < data[0]) {
			T temp = data[0];
			data[0] = data[1];
			data[1] = temp;
		}
		break;
	default:
		T& chain1_last_element = data[0];
		T& chain2_last_element;

		ull chain1_length = 1;
		unsigned long long chain2_length = 0;

		T& chain2_first_element;

		ull i = 1;
		while (i < length and data[i] >= chain1_last_element) {
			chain1_last_element = data[i];
			i++;
		}

		if (i == length) {
			//bingo the data was already sorted
			return;
		}

		chain1_length = i;

		//std::cout << "i: " << i << ", chain1_length: " << chain1_length << ", chain1_last_element: " << chain1_last_element << ", chain2_last_element: " << data[i]  << "\n";

		chain2_last_element = data[i];
		chain2_length = 1;
		chain2_first_element = chain2_last_element;

		i++;

		while (i < length) {
			T value = data[i];
			if (value >= chain1_last_element) {
				chain1_last_element = value;
				chain1_length++;
			}
			else if (value >= chain2_last_element) {
				chain2_last_element = value;
				chain2_length++;
			}
			i++;
		}

		T* buffer = new int[length];
		buffer[0] = data[0];

		T* chain1_begin_ptr = buffer + 1;
		T* chain2_begin_ptr = buffer + chain1_length;
		T* remainder_chain_begin_ptr = chain2_begin_ptr + chain2_length;

		chain1_last_element = data[0];

		chain2_last_element = chain2_first_element;

		for (i = 1; i < length; i++) {
			T& value = data[i];

			if (value >= chain1_last_element) {
				*chain1_begin_ptr = value;
				chain1_last_element = value;
				chain1_begin_ptr++;
			}
			else if (value >= chain2_last_element) {
				*chain2_begin_ptr = value;
				chain2_last_element = value;
				chain2_begin_ptr++;
			}
			else {
				*remainder_chain_begin_ptr = value;
				remainder_chain_begin_ptr++;
			}
		}

		ull remaining_length = length - chain1_length - chain2_length;
		chain2_begin_ptr = buffer + chain1_length;
		remainder_chain_begin_ptr = chain2_begin_ptr + chain2_length;
		__DoubleCrocoSort(remainder_chain_begin_ptr, remaining_length, data);

		__Fusion3SortedList(data, buffer, chain1_length, chain2_begin_ptr, chain2_length, remainder_chain_begin_ptr, remaining_length);
	}
}

// Stable
// Average time complexity : O((n^2)/log(n))
// Space complexity : O(n)
// Best case : sorted list (O(n))
// Worst case : Reversed sorted list (O(n^2))
template<class T>
auto inline DoubleCrocoSort(T* data, unsigned long long length) {
	int* buffer = new int[length];
	__DoubleCrocoSort(data, length, buffer);
	delete[] buffer;
}

template<class T>
void __Fusion2SortedList(T* buffer, T* data1, ull len1, T* data2, ull len2) {
	while (len1 > 0 and len2 > 0) {
		if (*data1 <= *data2) {
			*buffer = *data1;
			data1++;
			len1--;
		}
		else {
			*buffer = *data2;
			data2++;
			len2--;
		}
		buffer++;
	}

	while (len1 > 0) {
		*buffer = *data1;
		buffer++;
		data1++;
		len1--;
	}

	while (len2 > 0) {
		*buffer = *data2;
		buffer++;
		data2++;
		len2--;
	}
}

template<class T>
inline void swap(T* ptr1, T* ptr2) {
	T temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

template<class T>
void __CrocoSort(T* data, ull length, T* buffer) {
	switch (length) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		if (data[0] > data[1]) {
			swap(data, data + 1);
		}
		break;
	default:
		T maxi = buffer[0] = data[0];

		T* const end = data + length;

		T* current = data + 1;

		T* dest = buffer;
		T* last = buffer + length;

		ull sorted_len = 1;

		while (current != end) {
			if (current[0] >= maxi) {
				dest++;
				*dest = (maxi = current[0]);
				sorted_len++;
			}
			else {
				last--;
				*last = current[0];
			}

			current++;
		}
		__CrocoSort(buffer + sorted_len, length - sorted_len, data);

		__Fusion2SortedList(data, buffer, sorted_len, last, length - sorted_len);
	}

}

// non stable
// Average time complexity : O((n^2)/log(n))
// Space complexity : O(n)
// Best case : sorted list (O(n))
// Worst case : max -> min -> max -> min -> ... (O(n^2))
template<class T>
void CrocoSort(T* data, ull length) {
	T* buffer = new T[length];

	__CrocoSort(data, length, buffer);

	delete[] buffer;
}


auto main() -> int {
	
	const auto length = 100;
	int values[length] = { 1, 16, 19, 11, 97, 52, 81, 92, 75, 12, 15, 84, 60, 65, 72, 7, 10, 22, 57, 63, 99, 90, 79, 59, 67, 76, 91, 38, 66, 13, 56, 37, 29, 48, 47, 14, 80, 27, 73, 68, 70, 25, 64, 61, 49, 69, 34, 32, 55, 21, 86, 51, 23, 26, 18, 33, 31, 53, 44, 98, 17, 89, 41, 39, 93, 40, 88, 54, 28, 20, 62, 6, 43, 83, 87, 24, 9, 36, 50, 46, 78, 5, 82, 95, 3, 30, 71, 74, 58, 8, 96, 77, 35, 4, 0, 94, 45, 85, 42, 2 };

	CrocoSort(values, length);

	for (int i = 0; i < length; i++) {
		std::cout << values[i] << ", " << std::flush;
	}

	return 0;
}
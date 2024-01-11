#include <iostream>
using namespace std;

int count = 0;

int interpolationSearch(int arr[], int n, int x)
{
	// Find indexes of two corners
	int low = 0, high = (n - 1);
	// Since array is sorted, an element present
	// in array must be in range defined by corner
	while (low <= high && x >= arr[low] && x <= arr[high]) {
		count++;

		if (low == high) {
			if (arr[low] == x) return low;
			return -1;
		}
		// Probing the position with keeping
		// uniform distribution in mind.
		int pos = low + (((double)(high - low) /
			(arr[high] - arr[low])) * (x - arr[low]));

		// Condition of target found
		if (arr[pos] == x)
			return pos + 1;
		// If x is larger, x is in upper part
		if (arr[pos] < x)
			low = pos + 1;
		// If x is smaller, x is in the lower part
		else
			high = pos - 1;
	}

	return -1;
}

// Main function
int main(int argc, char** argv) {
    int x = atoi(argv[1]);

    int a[100], idx = 0;
    for (int i = 2; i < argc; i++) {
        a[idx++] = atoi(argv[i]);
    }

    cout << interpolationSearch(a, idx, x) << " - " << count << "\n";

    return 0;
}

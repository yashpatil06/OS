#include <iostream>
using namespace std;

void Bankers(int need[][10], int available[], int allocated[][10], int p, int n) {
	int n_available[n];
	bool finish[p] = { false };
	int safeSeq[p];
	int count = 0;

	for (int i = 0; i < n; i++) {
		n_available[i] = available[i];
	}

	while (count < p) {
		bool found = false;
		for (int i = 0; i < p; i++) {
			if (!finish[i]) {
				bool canAllocate = true;
				for (int j = 0; j < n; j++) {
					if (need[i][j] > n_available[j]) {
						canAllocate = false;
						break;
					}
				}
				if (canAllocate) {
					for (int j = 0; j < n; j++) {
						n_available[j] += allocated[i][j];
					}
					safeSeq[count++] = i;
					finish[i] = true;
					found = true;
				}
			}
		}
		if (!found) {
			cout << "\nSystem is not in a safe state." << endl;
			return;
		}
	}

	cout << "System is in a safe state.\nSafe Sequence is: ";
	for (int i = 0; i < p; i++) {
		cout << safeSeq[i] << " ";
	}
	cout << endl;
}

int main() {
	int i, j, n;
	
		cout << "\nEnter the number of Resources: ";
		cin >> n;

	int t_resource[n];
		cout << "\nEnter the instances of Resources:" << endl;
		for (i = 0; i < n; i++) {
			cout << "R" << i + 1 << ": ";
				cin >> t_resource[i];
		}

	int p;
		cout << "\nEnter the Number of Processes: ";
		cin >> p;

	int allocated[p][10], max[p][10], need[p][10];
	int t_allocated[10] = {0}, available[10];

		cout << "\nEnter the values of Allocated matrix: " << endl;
		for (i = 0; i < p; i++) {
			for (j = 0; j < n; j++) {
				cin >> allocated[i][j];
			}
		}

	cout << "\nAllocated Matrix" << endl;
	for (i = 0; i < p; i++) {
		for (j = 0; j < n; j++) {
		cout << allocated[i][j] << " ";
		}
	cout << endl;
	}

	cout << "\nEnter the values of Max matrix: " << endl;
	for (i = 0; i < p; i++) {
		for (j = 0; j < n; j++) {
		cin >> max[i][j];
		}
	}

	for (i = 0; i < p; i++) {
		for (j = 0; j < n; j++) {
		need[i][j] = max[i][j] - allocated[i][j];
		}
	}

	cout << "\nNeed Matrix" << endl;
	for (i = 0; i < p; i++) {
		for (j = 0; j < n; j++) {
			cout << need[i][j] << " ";
		}
	cout << endl;
	}

	for (j = 0; j < n; j++) {
		for (i = 0; i < p; i++) {
			t_allocated[j] += allocated[i][j];
		}
	}	

	cout << "\nTotal Allocated" << endl;
	for (i = 0; i < n; i++) {
		cout << t_allocated[i] << " ";
	}

	for (i = 0; i < n; i++) {
		available[i] = t_resource[i] - t_allocated[i];
	}

	cout << "\nAvailable: " << endl;
	for (i = 0; i < n; i++) {
		cout << available[i] << " ";
	}

	Bankers(need, available, allocated, p, n);
return 0;
}

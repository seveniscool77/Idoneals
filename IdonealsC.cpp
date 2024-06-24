#include <iostream>
#include <vector>
#include <numeric> // Include numeric header for iota
#include <fstream> // Include fstream for file operations

using namespace std;

// Function to generate combinations similar to Python's combinations function
template<typename T>
class Combinations {
private:
    vector<T> pool;
    vector<int> indices;
    bool done;

public:
    Combinations(const vector<T>& iterable, int r)
        : pool(iterable), indices(r), done(false)
    {
        iota(indices.begin(), indices.end(), 0); // Initialize indices as 0, 1, 2, ..., r-1
    }

    vector<T> next_combination() {
        if (done) return {}; // No more combinations

        vector<T> combination;
        for (int i : indices) {
            combination.push_back(pool[i]);
        }

        // Update indices to the next combination
        done = !next_permutation(indices.begin(), indices.end());

        return combination;
    }
};

int main() {
    int l, u, r;

    // Input for l and u
    cout << "Enter the lower bound (l): ";
    cin >> l;
    cout << "Enter the upper bound (u): ";
    cin >> u;

    r = 3; // Size of combinations

    vector<int> iterable(u);
    iota(iterable.begin(), iterable.end(), 1); // Fill iterable with 1, 2, ..., u

    Combinations<int> comb(iterable, r);
    set<int> comb_values;

    // Generate all combinations and compute a*b + a*c + b*c
    vector<int> combination;
    while (!(combination = comb.next_combination()).empty()) {
        int a = combination[0];
        int b = combination[1];
        int c = combination[2];
        comb_values.insert(a * b + a * c + b * c);
    }

    set<int> idoneal;

    // Find idoneal values in the range [l, u]
    for (int num = l; num <= u; ++num) {
        if (comb_values.find(num) == comb_values.end()) {
            idoneal.insert(num);
        }
    }

    // Print and save idoneal values
    ofstream outfile("idoneal_numbers.txt");
    if (outfile.is_open()) {
        cout << "Idoneal values in the range [" << l << ", " << u << "]:" << endl;
        outfile << "Idoneal values in the range [" << l << ", " << u << "]:" << endl;
        for (int num : idoneal) {
            cout << num << " ";
            outfile << num << " ";
        }
        cout << endl;
        outfile << endl;
        outfile.close();
    } else {
        cerr << "Error opening file for writing." << endl;
    }

    return 0;
}

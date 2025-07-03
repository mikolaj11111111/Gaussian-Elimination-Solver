#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<cctype>
#include <tuple> 
#include <iomanip> 
using namespace std;

void printMatrix(const vector<vector<float>>& A, int N) {
    cout << fixed << setprecision(2);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
}

void saveMatrixToFile(const vector<vector<float>>& A, int N, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << fixed << setprecision(2);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N + 1; j++) {
                outFile << A[i][j] << " ";
            }
            outFile << endl;
        }
        outFile << "----------------------" << endl;
        outFile.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku!" << endl;
    }
}

tuple<vector<vector<float>>, vector<float>, int> read_file(string file) {
    ifstream myfile(file);
    if (!myfile.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return { {},{}, 0 };
    }

    vector<vector<float>> A;
    vector<float> b;
    int N;
    string line;
    string tmp;
    float value;

    cout << "Plik otwarty, wczytywanie danych..." << endl;

    // Read matrix size N
    while (getline(myfile, line)) {
        stringstream ss(line);
        ss >> tmp;

        if (tmp == "N") {
            ss >> tmp;  // Skip '='
            ss >> N;
            cout << "Wczytano N = " << N << endl;
            break;
        }
    }

    // Read vector b
    bool reading_b = false;
    while (getline(myfile, line)) {
        stringstream ss(line);
        ss >> tmp;

        if (tmp == "b:") {
            reading_b = true;
            continue;
        }

        if (reading_b) {
            stringstream line_stream(line);
            while (line_stream >> value) {
                b.push_back(value);
            }

            cout << "Wczytano b: ";
            for (int i = 0; i < b.size(); i++) {
                cout << b[i] << " ";
            }
            cout << endl;
            break;
        }
    }

    // Read matrix A
    bool found_A = false;
    while (getline(myfile, line)) {
        stringstream ss(line);
        ss >> tmp;

        if (tmp == "A:") {
            found_A = true;
            continue;
        }

        if (found_A) {
            vector<float> row;
            stringstream line_stream(line);
            while (line_stream >> value) {
                row.push_back(value);
            }
            if (!row.empty()) {
                A.push_back(row);
            }
        }
    }

    cout << "N = " << N << endl;
    cout << "b: ";
    for (int i = 0; i < b.size(); i++) {
        cout << b[i] << " ";
    }
    cout << endl;

    cout << "A:" << endl;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    return make_tuple(A, b, N);
}

void GaussMethod(vector<vector<float>>& A, vector<float>& b, int N, const string& fileName) {
    // Create augmented matrix
    for (int i = 0; i < N; i++) {
        A[i].push_back(b[i]);
    }

    // Forward elimination with partial pivoting
    for (int i = 0; i < N; i++) {
        int maxRow = i;

        // Find pivot element (largest in current column)
        for (int k = i + 1; k < N; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        // Swap rows if needed
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
        }

        // Check for singular matrix
        if (abs(A[i][i]) < 1e-12) {
            cout << "Macierz jest osobliwa, rozwiazanie nie istnieje." << endl;
            return;
        }

        // Eliminate column entries below pivot
        for (int j = i + 1; j < N; j++) {
            float factor = A[j][i] / A[i][i];
            for (int k = i; k < N + 1; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
        cout << "Po redukcji wierszy dla zmiennej x" << i + 1 << ":" << endl;
        printMatrix(A, N);
    }

    // Back substitution
    vector<float> x(N, 0);
    for (int i = N - 1; i >= 0; i--) {
        x[i] = A[i][N] / A[i][i];
        for (int j = i - 1; j >= 0; j--) {
            A[j][N] -= A[j][i] * x[i];
        }
    }

    cout << "Rozwiazanie: \n";
    for (int i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }

    saveMatrixToFile(A, N, fileName);
}

int main() {
    vector<string> files{ "gauss_elimination_gr1IO_A.txt", "gauss_elimination_gr1IO_B.txt", "gauss_elimination_gr1IO_C.txt" };

    for (const string& file : files) {
        tuple<vector<vector<float>>, vector<float>, int> result = read_file(file);
        vector<vector<float>> A = get<0>(result);
        vector<float> b = get<1>(result);
        int N = get<2>(result);
        cout << "\n";

        string outputFileName = file.substr(0, file.find_last_of(".")) + "_reduced.txt";
        GaussMethod(A, b, N, outputFileName);
    }

    return 0;
}
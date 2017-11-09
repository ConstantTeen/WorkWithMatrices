#include <iostream>
#include <vector>

using namespace std;

void create(vector< vector<double> > &matrix, int n){
    vector<double> mediator;
    double m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> m;
            mediator.push_back(m);
        }
        matrix.push_back(mediator);
        mediator.clear();
    }
}

void output(vector< vector<double> > &matrix){
    int n = matrix.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
           cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

main(){
vector< vector<double> > matrix;
int n;
int m = -1;

while(m){
    cout << "1 - Create new matrix\n2 - Show actual matrix\n0 - Exit\n";
    cin >> m;
    switch(m){
        case 1:
            cout << "Type the size of matrix: ";
            cin >> n;
            create(matrix, n);
        break;
        case 2:
            output(matrix);
        break;
    }
}
return 0;
}

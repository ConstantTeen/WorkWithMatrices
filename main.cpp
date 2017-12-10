
#include <iostream>
#include <vector>

using namespace std;

void create(vector< vector<double> > &matrix, int n){
    vector<double> mediator;
    double m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n+1; j++){
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
        for(int j = 0; j < n+1; j++){
           cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

double determinant(vector< vector<double> > matrix){
    if(matrix.size() == 2){
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    else{
        double m,det;
        vector< vector<double> > mediator;

        for(int i = 0; i < matrix.size(); i++){
            // Здесь должно быть создание медиатора
            det = determinant(mediator);
            if(i % 2 == 0) m-= matrix[i][0] * det;
            else m+= matrix[i][0] * det;
        }
        return m;
    }
}

void mulRowNum(vector<double> &row,double num){
    for(int i = 0; i < row.size(); i++)
        row[i] = row[i]*num;
}

void addRowRow(vector<double> &row1,vector<double> row2){
for(int i = 0; i < row1.size();i++){
    row1[i] = row1[i] + row2[i];
}
}

int isRowEmpty(vector<double> row){
if(row[row.size()-1] != 0 && row[row.size()-2] == 0) return -1;
int i;
for(i = 0; i < row.size() && row[i] == 0; i++);
if(i == row.size())return 0;
else return 1;
}

void gauss(vector< vector<double> > matrix){
int sizeOfMtrx = matrix.size(), k, index, numOfIndSolutions = 0;
bool indSolutions[sizeOfMtrx+1] = {false};

for(index = 0; index < sizeOfMtrx && isRowEmpty(matrix[index]) == 0; index++);
if(index == sizeOfMtrx){
    cout << "The solution of this system is the set of real numbers.";
    return;
}
for(int i = 1,l = 1; i < sizeOfMtrx && l <= sizeOfMtrx;l++,i++){
        if(matrix[i-1][l-1] == 0){
            for(k = i + 1; k <= sizeOfMtrx && matrix[k-1][l-1] == 0; k++);
            if(k == sizeOfMtrx+1) {
                numOfIndSolutions++;
                indSolutions[l] = true;
                i--;
            }
            else {
                addRowRow(matrix[i-1],matrix[k-1]);
                i--;
                l--;
            }
        }
        else{
            for(int j = i; j < sizeOfMtrx;j++){
                if(matrix[j][l-1] != 0){
                    mulRowNum(matrix[j],-matrix[i-1][l-1]/matrix[j][l-1]);
                    addRowRow(matrix[j],matrix[i-1]);
                }
            }
        }
        output(matrix);
        cout << "\n";
}

int rang = sizeOfMtrx, i;
for(i = sizeOfMtrx; i > 0; i--){
    if(isRowEmpty(matrix[i-1]) == 0)rang--;
    else if(isRowEmpty(matrix[i-1]) == 1) break;
    else{
        cout << "The system doesn't have the solution.";
        return;
    }
}

if(matrix[rang-1][sizeOfMtrx-2] != 0)
    for(int i = rang+1; i <= sizeOfMtrx; i++) {
        numOfIndSolutions++;
        indSolutions[i] = true;
    }
else indSolutions[sizeOfMtrx] = false;

vector< vector<double> > solution(sizeOfMtrx + 1);

for(int j = 1; j <= rang; j++){
        for(index = 1; matrix[j-1][index-1] == 0;index++);
        for(int i = 1; i < sizeOfMtrx + 1; i++){
            if(indSolutions[i]) solution[index].push_back(-matrix[j-1][i-1]/matrix[j-1][index-1]);
        }
        solution[index].push_back(matrix[j-1][sizeOfMtrx]/matrix[j-1][index-1]);
}
int sizeOfSolution = solution[index].size();
vector<double> mediator(sizeOfSolution);

for(int i = rang-1; i > 0; i--){
    for(index = 1; matrix[i-1][index-1] == 0;index++);
    for(int j = index+1; j <= sizeOfMtrx; j++)
        if(!indSolutions[j]){
            mediator = solution[j];
            mulRowNum(mediator,-matrix[i-1][j-1]/matrix[i-1][i-1]);
            addRowRow(solution[i],mediator);
        }
}

for(int i = 1; i <= sizeOfMtrx; i++)
    if(!indSolutions[i]){
        cout << "\nx" << i << " = ";
        for(int k = i + 1, j = 0; k <= sizeOfMtrx; k++){
            if(indSolutions[k]){
                cout << solution[i][j] << "*" << "x" << k << " ";
                j++;
            }
        }
        cout << solution[i][sizeOfSolution - 1];
    }
}

main(){
vector< vector<double> > matrix;
int n;
int m = -1;

while(m){
    cout << "\n\n1 - Create new matrix\n2 - Show actual matrix\n3 - Get determinant\n4 - Find the solution by Gauss\n0 - Exit\n";
    cin >> m;
    switch(m){
        case 1:
            cout << "Type the size of matrix: ";
            cin >> n;
            matrix.clear();
            create(matrix, n);
        break;
        case 2:
            output(matrix);
        break;
        case 3:
            cout << "Determinant: " << determinant(matrix) << "\n";
        break;
        case 4:
            gauss(matrix);
        break;
    }
}
return 0;
}

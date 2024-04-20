#include "kNN.hpp"

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc1155()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract();
dataset_extract.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1156()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract(0, -1, 0, -1);
dataset_extract.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1157()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract(0, 0, 0, -1);
dataset_extract.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc1158()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract(0, -2, 0, -1);
Dataset dataset_extract2 = Dataset(dataset_extract);
dataset_extract2.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}


// TesCase 1205

void tc_knn_score(int k, int size_X){
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");

kNN knn = kNN(k);
Dataset X_train, X_test, y_train, y_test;
Dataset feature = dataset.extract(0, size_X, 1, -1);
Dataset label = dataset.extract(0, size_X, 0, 0);

train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
knn.fit(X_train, y_train);
Dataset y_pred = knn.predict(X_test);
double accuracy = knn.score(y_test, y_pred);
cout << "Accuracy: " << accuracy << endl;
// cout << ""
}

void tc1205()
{
tc_knn_score(10, 10);
}

int main() {
    tc1155();
    tc1156();
    tc1157();
    // tc1205();
    return 0;
}
#include "main.hpp"

template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual void getArray(T* Array) const = 0;

    virtual List<T> *subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
};

template <typename T>
class Image : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node *next;

    public:
        Node(T pointer, Node *next = nullptr) : pointer(pointer), next(next) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    Image()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~Image()
    {
        this->clear();
    }
    void push_back(T value)
    {
        Node *newNode = new Node(value);
        if(this->size == 0) {
            this->head = newNode;
            this->tail = newNode;
        }
        else {
            this->tail->next = newNode;
            this->tail = newNode;
        }
        delete newNode;
        this->size++;
    }
    void push_front(T value)
    {
        Node *newNode = new Node(value);
        if(this->size == 0) {
            this->head = newNode;
            this->tail = newNode;
        }
        else {
            newNode->next = this->head;
            this->head = newNode;
        }
        delete newNode;
        this->size++;
    }
    void insert(int index, T value)
    {
        if(index < 0 || index > this->size) return;

        if(index == this->size) return push_back(value);
        else if(index == 0) return push_front(value);
        else {
            Node *newNode = new Node(value);
            Node *temp = this->head;
            for(int i = 0; i < index - 1; i++) temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        this->size++;
    }

    void getArray(T* Array) const
    {
        Node* current = head;
        int index = 0;
        while (current != nullptr && index < size) {
            Array[index] = current->pointer;
            current = current->next;
            index++;
        }
    }

    void remove(int index)
    {
        if(index < 0 || index >= size) return;

        if(index == (this->size - 1)) {
            Node *temp = this->head;
            for(int i = 0; i < index - 1; i++) temp = temp->next;
            Node *delNode = this->tail;
            this->tail = temp;
            delete delNode;
        }
        else if(index == 0) {
            Node *delNode = this->head;
            this->head = this->head->next;
            delete delNode;
        }
        else {
            Node *temp = this->head;
            for(int i = 0; i < index - 1; i++) temp = temp->next;
            Node *delNode = temp->next;
            temp->next = temp->next->next;
            delete delNode;
        }
        this->size--;
    }
    T &get(int index) const
    {
        if(index < 0 || index >= this->size)  throw out_of_range("get(): Out of range");
        Node *temp = this->head;
        for(int i = 0; i < index; i++) temp = temp->next;
        return temp->pointer;
    }
    int length() const
    {
        return size;
    }
    void clear()
    {
        while(this->size != 0) {
            Node *temp = this->head;
            this->head= this->head->next;
            delete temp;
            this->size--;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
    void print() const
    {
        if (size == 0)
            return;
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (i == this->size - 1)
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }
    void reverse()
    {
        if(this->size <= 1) return;
        Node *pre = this->head->next;
        Node *curr = this->head;

        for(int i = 0; i < this->size - 1; i++) {
            Node* temp = pre->next;
            pre->next = curr;
            curr = pre;
            pre = temp;
        }

        this->head->next = nullptr;
        this->tail = this->head;
        this->head = curr;
    }
    void printStartToEnd(int start, int end) const
    {
        Node *temp = head;
        if(start == end && end == 0) cout << endl;
        for (int i = 0; i < start; i++)
            temp = temp->next;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }
    List<T> *subList(int start, int end)
    {
        List<T>* result = new Image<T>();
        if(this->size <= start || start < 0 || end <= 0 || start >= end) return result;
        else if(end > this->size) end = size;

        Node *temp = this->head;
        for(int i = 0; i < start; i++) temp = temp->next; 
        for(int i = start; i < end && temp != nullptr; i++) {
            result->push_back(temp->pointer);
            temp = temp->next;
        }
        delete result;
        return result;
    }
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *nameCol;
    // You may need to define more
public:
    Dataset()
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int> *>();
    }

    ~Dataset()
    {
        delete data;
        delete nameCol;
    }

    Dataset(const Dataset &other)
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int> *>();
        // TODO: implement Task 2
        if(other.nameCol->length() != 0)
        for (int i = 0; i < other.nameCol->length(); ++i) {
            this->nameCol->push_back(other.nameCol->get(i));
        }

        if(other.data->length() != 0) {
            for (int i = 0; i < other.data->length(); ++i) {
                List<int>* newRow = new Image<int>();
                for (int j = 0; j < other.data->get(i)->length(); ++j) {
                    newRow->push_back(other.data->get(i)->get(j));
                }
                this->data->push_back(newRow);
            }
        }
    }

    Dataset &operator=(const Dataset &other)
    {
        if(this == &other) return *this;   
        this->nameCol = new Image<string>();
        this->data = new Image<List<int>*>();
        // cout << "(---<>---)";
        if(other.nameCol->length() != 0)
        for (int i = 0; i < other.nameCol->length(); ++i) {
            this->nameCol->push_back(other.nameCol->get(i));
        }
 
        if(other.data->length() != 0) {
            for (int i = 0; i < other.data->length(); ++i) {
                List<int>* newRow = new Image<int>();
                for (int j = 0; j < other.data->get(i)->length(); ++j) {
                    newRow->push_back(other.data->get(i)->get(j));
                }
                this->data->push_back(newRow);
            }
        }

        return *this;
    }

    List<List<int> *> *getData() const
    {
        return data;
    }

    bool loadFromCSV(const char *fileName)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string str;
            int n;
            file >> str;

            for (int i = 0; i < str.length(); i++) {
                if (str[i] == ',') str[i] = ' ';
            }

            stringstream ss(str);

            while (ss >> str) {
                nameCol->push_back(str);
            }

            while (file >> str)
            {
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') str[i] = ' ';
                }

                stringstream ss(str);
                List<int> *tempList = new Image<int>();

                while (ss >> n) {
                    tempList->push_back(n);
                }
                data->push_back(tempList);
            }
            return true;
        }
        return false;
    }

    void getShape(int &nRows, int &nCols) const
    {
        nRows = data->length();
        nCols = data->get(0)->length(); 
        if(nRows <= 0 || nCols <= 0) throw std::out_of_range("get(): Out of range");
    }

    void columns() const
    {
        nameCol->print();
    }

    int rowLength() const {
        return data->length();
    }

    void printHead(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0) return;

        if(this->data->length() != 0) {     
            if(nameCol->length() != 0) {
                nameCol->printStartToEnd(0, nCols);
                cout << endl;
            }
        }
        else {
            if(nameCol->length() != 0) {
                nameCol->printStartToEnd(0, nCols);
                cout << endl;
            }
        }

        if(this->data->length() != 0)         
        for (int i = 0; i < min(nRows, data->length()); ++i) {
            data->get(i)->printStartToEnd(0, min(nCols, data->get(i)->length()));
            if(i != min(nRows, data->length()) - 1) cout << endl;
        }
    }

    void printTail(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0) return;
        if(this->data->length() != 0)  {
            int len1 = max(nCols, data->get(0)->length());
            nameCol->printStartToEnd(len1 - nCols, len1);
            cout << endl;
        }
        else {
            int len1 = max(nCols, data->get(0)->length());
            nameCol->printStartToEnd(len1 - nCols, len1);
            cout << endl;
        }

        int start = max(0, data->length() - nRows);
        int end = data->length();
        if(this->data->length() != 0)  
        for (int i = start; i < end; ++i) {
            data->get(i)->printStartToEnd(max(0, data->get(i)->length() - nCols), data->get(i)->length());
            if(i != end - 1) cout << endl;
        }
    }

    bool drop(int axis = 0, int index = 0, string columns = "")
    {
        if(this->data->length() == 0 && this->nameCol->length() == 0) return false;
        if (axis != 0 && axis != 1) {
            return false;
        }

        if (axis == 0) {
            if (index < 0 || index >= data->length()) {
                return false;
            }
            if(data->length() == 1)
            data->clear();
            else if(data->length() > 1)
            data->remove(index);
            return true;
        } else {
            int columnIndex = -1;
            for (int i = 0; i < nameCol->length(); ++i) {
                if (nameCol->get(i) == columns) {
                    columnIndex = i;
                    break;
                }
            }

            if (columnIndex == -1) {
                return false;
            }

            
            if (data->get(0)->length() == 1){
                for(int i = 0; i < data->length(); i++){
                    data->get(i)->clear();
                    delete data->get(i);
                }
                data->clear();
            }
            else if(data->get(0)->length() > 1)
            for (int i = 0; i < data->length(); ++i) {
                if(data->get(i)->length() != 0)
                data->get(i)->remove(columnIndex);
            }

            if(nameCol->length() != 0)
            nameCol->remove(columnIndex);
            return true;
        }
    }

    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        Dataset extractedData;
        if(data->length() == 0) return extractedData;
        int numCol = data->get(0)->length();

        if (endRow == -1) {
            endRow = data->length() - 1;
        }
        if (endCol == -1) {
            endCol = numCol - 1;
        }
        if(startRow >= data->length() || startCol >= numCol) return extractedData;

        if(startRow > endRow || startCol > endCol) return extractedData;

        if(endRow >= data->length()) endRow = data->length() - 1;
        if(endCol >= numCol) endCol = numCol - 1;

        // cout << "{" << startCol << "}";

        delete extractedData.nameCol;
        extractedData.nameCol = nameCol->subList(startCol, min(endCol + 1, nameCol->length()));
        if(this->data->length() != 0) {
            for (int i = startRow; i <= endRow; ++i) {
                List<int>* rowData = data->get(i)->subList(startCol, endCol + 1);
                extractedData.data->push_back(rowData);
            }
        }

        return extractedData;
    }

    double distanceEuclidean(const List<int> *a, const List<int> *b) const
    {
        int xSize = a->length();
        int ySize = b->length();
        int maxSize = max(xSize, ySize);
        double distance = 0.0;

        int *arrayX = new int[maxSize];
        a->getArray(arrayX);

        int *arrayY = new int[maxSize];
        b->getArray(arrayY);

        for (int i = 0; i < maxSize; i++) {
            double xValue = (i < xSize) ? arrayX[i] : 0;
            double yValue = (i < ySize) ? arrayY[i] : 0;
            distance += (xValue - yValue) * (xValue - yValue);
        }

        delete[] arrayX;
        delete[] arrayY;

        return sqrt(distance);
    }


    Dataset predict(const Dataset &X_train, const Dataset &Y_train, const int k) const
    {
        Dataset predictions;    

        int temp_k = k;

        if(k <= 0) return predictions;

        if(X_train.getData()->length() == 0 || this->getData()->length() == 0)  return predictions;

        // if(k > X_train.getData()->length()) temp_k = X_train.getData()->length();

        int sort_len = min(X_train.getData()->length(), Y_train.getData()->length());

        // if(k > sort_len) temp_k = sort_len;
        if(k >= sort_len) throw std::out_of_range("get(): Out of range");

        predictions.nameCol->push_back(Y_train.nameCol->get(0));

        for (int i = 0; i < this->getData()->length(); ++i) {
            List<int>* current_instance = this->getData()->get(i);
            pair<double, int> distances[X_train.getData()->length()];

            for (int j = 0; j < sort_len; ++j) {
                List<int>* train_instance = X_train.getData()->get(j);
                double distance = distanceEuclidean(current_instance, train_instance);
                distances[j] = make_pair(distance, j); 
            }

            for (int i = 0; i < sort_len - 1; ++i) {
                for (int j = 0; j < sort_len - i - 1; ++j) {
                    if (distances[j].first > distances[j + 1].first) {
                        swap(distances[j], distances[j + 1]);
                    }
                }
            }

            int label_count[10] = {0};
            for (int n = 0; n < temp_k; ++n) {
                int index = distances[n].second;
                // List<int>* neighbor_label = Y_train.getData()->get(index);
                // int label = neighbor_label->get(0);
                int label = Y_train.getData()->get(index)->get(0);
                label_count[label]++;
            }

            int max_count = 0;
            int predicted_label = -1;
            for (int l = 0; l < 10; ++l) { 
                if (label_count[l] > max_count) {
                    max_count = label_count[l];
                    predicted_label = l;
                }
            }

            List<int>* predicted_label_row = new Image<int>();
            predicted_label_row->push_back(predicted_label);
            predictions.getData()->push_back(predicted_label_row);
        }

        return predictions;
        // return Dataset();
    }
    double score(const Dataset &y_predict) const
    {
        List<List<int> *> *y_test_data = this->getData();
        List<List<int> *> *y_pred_data = y_predict.getData();

        if(y_predict.data->length() == 0) return -1;

        if (y_test_data->length() != y_pred_data->length() || y_test_data->length() == 0 || y_pred_data->length() == 0)
        {
            return -1; 
        }

        int correct_predictions = 0;

        for (int i = 0; i < y_test_data->length(); ++i)
        {
            List<int> *test_sample = y_test_data->get(i);
            List<int> *pred_sample = y_pred_data->get(i);

            if (test_sample->get(0) == pred_sample->get(0))
            {
                correct_predictions++;
            }
        }

        double accuracy = static_cast<double>(correct_predictions) / y_test_data->length();
        return accuracy;
        // return -1;
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
        if(k > X_train.rowLength() || k > Y_train.rowLength()) k = min(X_train.rowLength(), Y_train.rowLength());
    }
    Dataset predict(const Dataset &X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset &X, Dataset &Y, double test_size, Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test) {
    if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0) return;

    // double n = 1.0e-15;
    int nRow = X.getData()->length();
    double rowSplit = nRow * (1 - test_size);

    // if(abs(round(rowSplit) - rowSplit) < n * nRow) rowSplit = round(rowSplit);

    X_train = X.extract(0, rowSplit - 1, 0, -1);
    Y_train = Y.extract(0, rowSplit - 1, 0, -1);

    X_test = X.extract(rowSplit, -1, 0, -1);
    Y_test = Y.extract(rowSplit, -1, 0, -1);
}

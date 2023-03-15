#include <iostream>
#include <string>
#include <istream>

#define MAX_SIZE 31
using namespace std;





class element{
    
public:
    string name;//이름
    int id;//아이디
    string school;//학교
    element();
    element(string new_name, int new_id, string new_school);
};
element::element(){

}

element::element(string new_name, int new_id, string new_school){
    name = new_name;
    id = new_id;
    school = new_school;
}





class min_heap{
private:
       
    int size;

public:
    min_heap();


    int INSERT(element arr[], element new_element);
    element MINIMUM(element arr[]);
    element EXTRACT_MIN(element arr[]);
    void DECREASE_KEY(element arr[], int x, int k);


    bool fullcheck();
    bool emptycheck();
    int getSize();
    element getElement(element arr[], int i);
    void adjust(element arr[], int root);

};

min_heap::min_heap(){
    size = 0;
}

int min_heap::INSERT(element arr[], element new_element){
    if(!fullcheck()){
        size ++;
        int k = size;

        while((k != 1) && (new_element.id < arr[k/2].id)){//추가한 원소가 parents 보다 key 값이 작으면 parents의 값을 child에 대입 
            arr[k] = arr[k/2];
            k /=2;
        }

        //연산이 끝나고나면 k의 값이 새로운 element를 넣어야 할 위치
        arr[k] = new_element;
        
        return 1;
    }
    else{
        return 0;
    }
}

element min_heap::MINIMUM(element arr[]){
    return arr[1];
}// index는 1부터 시작하고 heap이기 때문에 index가 1인 값 return

element min_heap::EXTRACT_MIN(element arr[]){
    element t;//끝 원소
    element last;
    int parent, child;

    if(!emptycheck()){
                
        parent = 1;
        child =2;
        t = MINIMUM(arr);
        last = arr[size];
        size --;

        while (child <= size){
            if((child <size) && arr[child].id > arr[child+1].id){//child 중 오른쪽 child가 값이 더 작을 경우 
                child++;//오른쪽 child 선택
            }
            if(last.id <= arr[child].id)
                break;//끝원소의 값과 비교했을 때 작으면 break
                
            arr[parent] = arr[child];
            parent = child;
            child *=2;
            }
            //parent에 끝 원소닶 넣어주기
            arr[parent] = last;
        
    }   
    return t;
}

void min_heap::DECREASE_KEY(element arr[], int x, int k){
  
    arr[x].id = k;

    for(int i=size/2; i>=1; i--){//heapify
        adjust(arr, i);
    }
   
}

bool min_heap::fullcheck(){
    if(size>30){
        return true;
    }
    return false;
}
bool min_heap::emptycheck(){
    if(size<1){
        return true;
    }
    return false;
}
int min_heap::getSize(){
    return size;
}

element min_heap::getElement(element arr[], int i){
    return arr[i];
}



void min_heap::adjust(element arr[], int root){

    int key = arr[root].id;//root의 ID
    int child = 2*root;
    element tmp = arr[root];

    while(child <= size){
        if((child<size) && (arr[child].id>arr[child+1].id)){//child가 size보다 작고 && child의 왼쪽 오른쪽 비교
            child++;
        }
        if(key<arr[child].id) break;
        else{
            arr[child/2] = arr[child];
            child *=2;
        }
    }
    arr[child/2] = tmp;
}

string countNum(string input){
    //문자열 중에서 숫자의 개수를 알려주는 함수
    //숫자의 갯수가 4개이면 문자열 ret
    int count=0;
    string tmp="";


    for(int i=0; i<input.size(); i++){
        if(input.at(i)>=48 && input.at(i)<=57){//숫자일 경우 
            count++;
            tmp +=input.at(i);
        } 
    }

    if(count==4) return tmp;
    return "false";
}


bool checkAllNum(string input){
//input이 모두 숫자인지 판별하는 함수
//첫번째 원소가 0일 경우, 숫자 사이에 문자가 존재할 경우 false return

    if(input.at(0)==48) return false;

    for(int i=1; i<4; i++){
            if(input.at(i)<48 || input.at(i)>57) return false;
    }

    return true;
}

string checkId(string input){
//id의 형식이 올바른지 확인하고 문자열 return

    int size = input.size();

    if(size<4){

        cout<< "Type ID Properly!!!"<<endl<<endl;
        return "false";//길이가 4보다 작을 경우 false
    } 
    else if(size == 4){
        
        if(checkAllNum(input)){
            
            return input;//모두 숫자일 경우 true
            
        }
        else{
            cout<< "Type ID Properly!!!"<<endl<<endl;
            return "false";//첫번째 숫자가 0이 아니거나 숫자 사이에 문자가 존재 false
        }
    }
    else{
        //전체 문자열 중 숫자가 4개일 경우 그 숫자로 input을 넣어줌
        //숫자가 4개보다 적거나 많을 경우 false

        if(checkAllNum(countNum(input))){
            
            if(countNum(input)== "false"){
                cout<< "Type ID Properly!!!"<<endl<<endl;
                return "false";
            } 
            else return countNum(input);
            
        }
        else{
            cout<< "Type ID Properly!!!"<<endl<<endl;
            return "false";//첫번째 숫자가 0이 아니거나 숫자 사이에 문자가 존재 false
        }

    }
}


int main(){
    char input;//입력메뉴
    string name_tmp;//임시 이름
    
    int id_tmp;//임시 ID
    string school_tmp;//임시 학교
    min_heap students;
    
    element min_queue[MAX_SIZE];

    do{
    cout << "*********** MENU ****************"<<endl;
    cout << "I : Insert new element into queue."<<endl; 
    cout << "D : Delete element with smallest key from queue" << endl;
    cout << "C : Decrease key of element in queue."<<endl;
    cout << "P : Print out all elements in queue. "<<endl;
    cout << "Q : Quit"<<endl<<endl;
    cout<< "Choose menu: ";
    cin >> input;
    cin.ignore();

    if(input == 'I'){
        string id_first;

        cout << "Enter name of element: ";
        cin >> name_tmp;
        cin.ignore();

        do{
            cout << "Enter id of element: ";
            getline(cin,id_first);//id를 string으로 먼저 받기
        }while(checkId(id_first)=="false");

        id_tmp = stoi(checkId(id_first));
        

        cout<< "Enter school of element: ";
        cin>> school_tmp;
        cin.ignore();

        if(students.INSERT(min_queue, element(name_tmp, id_tmp, school_tmp))){
            cout << "New element [" << name_tmp << ", "<< id_tmp << ", " << school_tmp << "] is inserted."<<endl<<endl;
        }
        else{
            cout << "It is full"<<endl<<endl;
        }
    }

    else if(input == 'D'){
        if(!students.emptycheck()){
            element tmp = students.EXTRACT_MIN(min_queue);
            cout << "[" << tmp.name << ", " << tmp.id  << ", " << tmp.school  << "]" << " is deleted."<<endl<<endl;
        }
        else{
            cout << "Heap is Empty"<<endl<<endl;
        }
        
        
    }

    else if(input == 'C'){
        int size = students.getSize();
        int index_element, change_value;
        string input_id;

        if(size >=1){
            do{
                cout<< "Enter index of element: ";
                cin >> index_element;
                cin.ignore();

            }while(index_element>size);

            do{

            cout << "Enter id of element: ";
            getline(cin,input_id);//id를 string으로 먼저 받기

            }while(checkId(input_id)=="false");

            change_value = stoi(checkId(input_id));
            cout << endl <<endl;
            students.DECREASE_KEY(min_queue, index_element, change_value);
        }
        else{
            cout<<"Heap is Empty!!"<<endl<<endl;
        }
                
    }

    
    else if(input == 'P'){
        if(students.getSize() >=1){
            for(int i=1; i<=students.getSize(); i++){
                element tmp = students.getElement(min_queue, i);
            cout << i << " = [" << tmp.name << ", "<< tmp.id << ", " << tmp.school << "]  "<<endl <<endl;
        }
        }
        else{
            cout<<"Heap is Empty!!"<<endl<<endl;
        }
        
    }
    else if(input=='Q'){
        cout<< "Thank you, Bye!";
    }

    else{
        cout<<"Choose Menu Again!!"<<endl<<endl;
    }


    }while(input != 'Q');
    
    

    return 0;
}
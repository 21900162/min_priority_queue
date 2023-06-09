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
    element input[MAX_SIZE];   
    int size;

public:
    min_heap();
    int insert(element new_element);
    int minimum();
    element extract_min();
    void decrease();
    bool fullcheck();
    bool emptycheck();
    int getSize();
    element getElement(int i);
    void adjust(int root);

};

min_heap::min_heap(){
    size = 0;
}

int min_heap::insert(element new_element){
    if(!fullcheck()){
        size ++;
        int k = size;

        while((k != 1) && (new_element.id < input[k/2].id)){//추가한 원소가 parents 보다 key 값이 작으면 parents의 값을 child에 대입 
            input[k] = input[k/2];
            k /=2;
        }

        //연산이 끝나고나면 k의 값이 새로운 element를 넣어야 할 위치
        input[k] = new_element;
        
        return 1;
    }
    else{
        return 0;
    }
}

int min_heap::minimum(){
    return 1;
}// index는 1부터 시작하고 heap이기 때문에 index가 1인 값 return

element min_heap::extract_min(){
    element t;//끝 원소
    element last;
    int parent, child;

    if(!emptycheck()){
                
        parent = 1;
        child =2;
        t = input[1];
        last = input[size];
        size --;

        while (child <= size){
            if((child <size) && input[child].id > input[child+1].id){//child 중 오른쪽 child가 값이 더 작을 경우 
                child++;//오른쪽 child 선택
            }
            if(last.id <= input[child].id)
                break;//끝원소의 값과 비교했을 때 작으면 break
                
            input[parent] = input[child];
            parent = child;
            child *=2;
            }
            //parent에 끝 원소닶 넣어주기
            input[parent] = last;
        
    }   
    return t;
}

void min_heap::decrease(){
    int index;
    int change_value;

    do{
        cout<< "Enter index of element: ";
        cin >> index;
        cin.ignore();

    }while(index>size);
    
    cout<< "Enter id value: ";
    cin >> change_value;
    cin.ignore();
    cout << endl <<endl;
    input[index].id = change_value;

    for(int i=size/2; i>=1; i--){//heapify
        adjust(i);
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

element min_heap::getElement(int i){
    return input[i];
}



void min_heap::adjust(int root){

    int key = input[root].id;//root의 ID
    int child = 2*root;
    element tmp = input[root];

    while(child <= size){
        if((child<size) && (input[child].id>input[child+1].id)){//child가 size보다 작고 && child의 왼쪽 오른쪽 비교
            child++;
        }
        if(key<input[child].id) break;
        else{
            input[child/2] = input[child];
            child *=2;
        }
    }
    input[child/2] = tmp;
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

    if(size<4) return "false";//길이가 4보다 작을 경우 false
    else if(size == 4){
        
        if(checkAllNum(input)){
            
            return input;//모두 숫자일 경우 true
            
        }
        else{
            return "false";//첫번째 숫자가 0이 아니거나 숫자 사이에 문자가 존재 false
        }
    }
    else{
        //전체 문자열 중 숫자가 4개일 경우 그 숫자로 input을 넣어줌
        //숫자가 4개보다 적거나 많을 경우 false

        if(checkAllNum(countNum(input))){
            
            if(countNum(input)== "false") return "false";
            else return countNum(input);
            
        }
        else{
            return "false";//첫번째 숫자가 0이 아니거나 숫자 사이에 문자가 존재 false
        }

    }
}


int main(){
    char input;//입력메뉴
    string name_tmp;//임시 이름
    string id_first;//string으로 받을 ID
    int id_tmp;//임시 ID
    string school_tmp;//임시 학교
    min_heap students;
    
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

        if(students.insert(element(name_tmp, id_tmp, school_tmp))){
            cout << "New element [" << name_tmp << ", "<< id_tmp << ", " << school_tmp << "] is inserted."<<endl<<endl;
        }
        else{
            cout << "It is full"<<endl<<endl;
        }
    }

    else if(input == 'D'){
        if(!students.emptycheck()){
            element tmp = students.extract_min();
            cout << "[" << tmp.name << ", " << tmp.id  << ", " << tmp.school  << "]" << " is deleted."<<endl<<endl;
        }
        else{
            cout << "Heap is Empty"<<endl<<endl;
        }
        
        
    }

    else if(input == 'C'){
        if(students.getSize() >=1){
            students.decrease();
        }
        else{
            cout<<"Heap is Empty!!"<<endl<<endl;
        }
                
    }

    
    else if(input == 'P'){
        if(students.getSize() >=1){
            for(int i=1; i<=students.getSize(); i++){
                element tmp = students.getElement(i);
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
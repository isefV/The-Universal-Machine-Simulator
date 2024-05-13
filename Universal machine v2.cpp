#include <iostream>
#include <sstream> 
#include <string>
#include <vector>

#include <conio.h>
#include <set>
#include <map>
#include <cmath>

std::string prime_factor_list;
int size_command_list;

//Portotype
bool isPrime(int);
bool print(std::string, bool = false);
int get_Index(std::vector<int>&, int&);
int universal_machin(int* arrXn, int y, int sizeArr);
int* set_Xn(int* arr, int sizeArr);
int* prime_Factor(int);
int* find_pair(int, bool = false);
std::vector<int>* list_Prime(int);
std::string create_arr_Print(int*, int);
std::string find_command(int, int, int);
std::string find_labl_or_var(int, bool = true);
void getout();


int main() {
    int flag = -1;
    int number = 0;

    while (flag) {
        system("CLS");
        print("1-Number Godel to code\n2-Pair number to command\n3-Find Godel list\n4-Pair to command\n5-Universal Machin Y value\n\n0-Exit\nPlease Enter Your Option :");
        std::cin >> flag;

        switch (flag)
        {
        case 0:
            flag = 0;
            break;

        case 1:
            print("Enter the Godel number :");
            try
            {
                std::cin >> number;
                int* command_list = prime_Factor(number + 1);
                //----------------------------

                int n = sizeof(command_list) / sizeof(command_list[0]);

                std::set<int> uniq_command_code;
                std::map<int, std::string> commands_code;
                int* temp = new int[3]{};

                // filling the array values in the set
                for (int i = 0; i < size_command_list; i++)
                {
                    uniq_command_code.insert(command_list[i]);
                }

                for (auto i : uniq_command_code) {
                    temp = find_pair(i, true);
                    commands_code.insert(std::pair<int, std::string>(i, find_command(temp[0], temp[1], temp[2])));
                }
                std::cout <<number<<"="<< prime_factor_list << "-1" << " \n";
                for (int i = 0;i < size_command_list;i++) {
                    //std::cout<<command_list[i]<<" - ";

                    std::cout << i + 1 << "\t" << commands_code[command_list[i]];
                }
                //----------------------------
                getout();
            }
            catch (const std::exception& e)
            {
                number = 0;
                flag = 0;
            }
            break;

        case 2:
            print("Enter the pair number :");
            try
            {
                std::cin >> number;

                int* temp = new int[3]{};
                temp = find_pair(number, true);

                std::cout << find_command(temp[0], temp[1], temp[2]) << "\n";

                getout();
            }
            catch (const std::exception& e)
            {
                number = 0;
                flag = 0;
            }
            break;

        case 3:
            print("Enter the number wants to Godel list :");
            try
            {
                std::cin >> number;
                prime_Factor(number);
                print(prime_factor_list);

                getout();
            }
            catch (const std::exception& e)
            {
                number = 0;
                flag = 0;
            }
            break;
        case 4:
            print("Enter the pair <a,<b,c>> = a b c :");
            try
            {
                int* numbers = new int[3]{};
                std::cin >> numbers[0] >> numbers[1] >> numbers[2];

                std::cout << find_command(numbers[0], numbers[1], numbers[2]) << "\n";

                getout();
            }
            catch (const std::exception& e)
            {
                number = 0;
                flag = 0;
            }
            break;

        case 5:
            try {
                int cntXn =3;
                /*
                print("Enter the count of Xn:");
                std::cin >> cntXn;
                int* arrXn= new int[cntXn];
                print("\nEnter the (X1,X2,...,Xn) => X1 X2 ... Xn:");
                for (int i = 0;i < cntXn;i++) {
                    std::cin >> arrXn[i];
                }
                */
                print("\nEnter the y:");
                std::cin >> number;
                int arrXn[3] = { 1,3,2 };
                //number = 5;
                std::cout<<"\nY in Universal machin is :"<< universal_machin(arrXn,number,cntXn)<<"\n";
                getout();
            }catch(const std::exception& e){
                number = 0;
                flag = 0;
            }
            break;

        default:
            flag = -1;
            break;
        }
    }
    return 0;
}


//----------------------------------- prime factor list section -------------------------------------

//check the number is prime or not
bool is_Prime(int num) {
    bool is_prime = true;
    int numhalf = num / 2;

    if (num == 0 || num == 1) {
        is_prime = false;
    }
    // loop to check if n is prime
    for (int i = 2; i <= numhalf; ++i) {
        if (num % i == 0) {
            is_prime = false;
            break;
        }
    }
    return is_prime;
}

// return a list of prime of 2 to that number we want
std::vector<int>* list_Prime(int num) {
    std::vector<int>* list_p = new std::vector<int>;
    for (int i = 2;i <= num;i++) {
        if (is_Prime(i))
        {
            (*list_p).push_back(i);
        }
    }
    return list_p;
}

//return array of Godel number(Prime factor of that number)
int* prime_Factor(int num) {
    std::vector<int>* list = list_Prime(num);
    int count = (*list).size();
    int* arr = new int[count] {};
    int div, last;
    while (num > 1) {
        for (std::vector<int>::iterator itr = (*list).end() - 1; itr != (*list).begin()-1; itr--) {
            div = (*itr);
            if (num % div == 0)
            {
                int indx = get_Index((*list), div);
                if (indx != -1)
                {
                    arr[indx]++;
                    num /= div;
                }
                break;
            }
        }
    }

    for (int i = 0; i < count;i++) {
        if (arr[i] != 0)
            last = i;
    }
    size_command_list = last + 1;
    int* pfl = new int[size_command_list];

    for (int i = 0; i <= last;i++) {
        pfl[i] = arr[i];
    }

    prime_factor_list = create_arr_Print(pfl, size_command_list);
    delete arr;
    return pfl;
}

//calculate the index of number in vector for array index
int get_Index(std::vector<int>& list, int& num) {
    auto it = find(list.begin(), list.end(), num);
    if (list.end() != it) {
        return (it - list.begin());
    }
    return -1;
}


//----------------------------------- command decode section ----------------------------------------

//convert number Z to pair number <x,y>
int* find_pair(int num, bool part) {
    num++;
    //std::cout<<num<<"\n";
    int x = 0, y = 0, ts;
    double n, t;
    while (num > 1)
    {
        n = num;
        if (num % 2 == 0) {
            ts = log2(n);
            if (pow(2, ts) == n) {
                x = ts;
                break;
            }
            else {
                num /= 2;
                x++;
            }
        }
        else {
            num--;
            num /= 2;
            y = num;
            break;
        }
    }



    if (part) {
        //std::cout<<x<<"-"<<y<<"\n";
        int* retArr = new int[3]{};
        int* testArr = new int[2]{};
        testArr = find_pair(y);
        retArr[0] = x;
        retArr[1] = testArr[0];
        retArr[2] = testArr[1];
        delete testArr;
        return retArr;
    }
    //std::cout<<num<<" - "<<x<<" "<<y<<"\n";
    int* retArr = new int[2]{ x,y };
    return retArr;
}

//decode pair <labl<cmd,var>> to command
std::string find_command(int labl, int cmd, int vari) {
    std::string str = "[ " + std::to_string(labl) + " , " + std::to_string(cmd) + " , " + std::to_string(vari) + " ] |\t", vr = find_labl_or_var(vari, false);
    if (labl != 0) {
        str += "[" + find_labl_or_var(labl, true) + "]:\t";
    }
    else {
        str += "\t";
    }
    switch (cmd)
    {
    case 0:
        str += vr + " <-- " + vr;
        break;
    case 1:
        str += vr + " <-- " + vr + " + 1";
        break;
    case 2:
        str += vr + " <-- " + vr + " - 1";
        break;

    default:
        str += "IF " + vr + "!=0 Goto " + find_labl_or_var(cmd - 2, true);
        break;
    }
    return str + "\n";
}

//calculate index of label or variable
std::string find_labl_or_var(int num, bool flag) {
    if (flag) {
        int test = num % 5;
        switch (test)
        {
        case 0:
            test = num / 5;
            return "E" + std::to_string(test);
        case 1:
            test = ((num - 1) / 5) + 1;
            return "A" + std::to_string(test);
        case 2:
            test = ((num - 2) / 5) + 1;
            return "B" + std::to_string(test);
        case 3:
            test = ((num - 3) / 5) + 1;
            return "C" + std::to_string(test);
        case 4:
            test = ((num - 4) / 5) + 1;
            return "D" + std::to_string(test);
        }
    }
    else {
        num++;
        if (num == 1 || num == 0)
            return "Y";
        int test = num % 2;
        switch (test)
        {
        case 0:
            test = num / 2;
            return "X" + std::to_string(test);
        case 1:
            test = ((num - 1) / 2);
            return "Z" + std::to_string(test);
        }
    }
    return "";
}

//----------------------------------- other section -------------------------------------------------

//print text with new line or not
bool print(std::string text, bool endln) {

    endln ? std::cout << text << std::endl : std::cout << text;
    return true;
}

//string of Godel list
std::string create_arr_Print(int* arr, int indx) {
    std::string str = "[";
    for (int i = 0; i < indx; i++) {
        std::ostringstream s;
        s << (arr[i]);
        str += s.str();
        str += " - ";
    }
    str.append("\b\b]");
    return str;
}

//get stop for each section
void getout() {

    std::cout << "\nPress key to continue ...";
    _getch();
    
    /* timer 
    std::cout << "Second left :  ";
    int x = 0;
    for (int i = 700000;i > 0;i--) {
        
        if (i % 10000)
            x = (i / 10000)-10;
            if (x > 9)
                std::cout << "\b\b" << x;
            
        
        //std::cout << "\33[2K\r" << (i / 10000) << "second left :";
    }
    */
}

int* set_Xn(int* arr,int sizeArr) {
    sizeArr = sizeArr * 2;
    int* newArr = new int[sizeArr];
    for (int i = 0; i < sizeArr;i++) {
        if (i % 2 != 0) {
            // arr[X1,X2,X3] index<0 1 2> ---> newArr [Y,X1,Z1,X2,Z2,X3,Z3] index<0 1 2 3 4 5 6>
            newArr[i] = arr[(i-1)/2];
            continue;
        }
        newArr[i] = 0;
    }
    return  newArr;
}

//----------------------------------- Universal Machin ----------------------------------------------

int universal_machin(int* arrXn ,int y ,int sizeArr)  {

    //Godel list (Length of program)
    int* Z = prime_Factor(y + 1);                           // Z <- y+1
    int Lt_Z = size_command_list;                           // Lt(Z)

    //Variable list
    int* S = set_Xn(arrXn,sizeArr);                         // S <- multy i=1 to n :(p_2i)^Xi;
    int S_size = sizeArr * 2;

    int K = 1;                                              // K <- 1

    while ( K != 0 || K < Lt_Z ) {                         // [C] IF K=Lt((Z)_K) V K=0 Goto F
        
        int* ZK = find_pair(Z[K-1]);                        // <a,U>
        int* U = find_pair(ZK[1]);                          // U=<b,c>

        int P = U[1];                                       // P <- P_ci+1     P=ci
        
        if (U[0] == 0) {                                    // IF l(U)=0 Goto N 
            K++;                                            // [N] K <- K+1
            continue;                                       // Goto C
        }
        if (U[0] == 1) {                                    // IF l(U)=1 Goto A 
            S[P]++;                                         // [A] S <- S.P
            K++;                                            // [N] K <- K+1
            continue;                                       // Goto C
        }
        if (U[0] == 2) {                                    // IF l(U)=2 Goto M
            if (P + 1 > S_size && S[P] != 0)                // IF ~(P|S) Goto N
            {
                K++;                                        // [N] K <- K+1
                continue;                                   // Goto C     
            }
            S[P]--;                                         // [M] S <- S/P
            K++;                                            // [N] K <- K+1
            continue;                                       // Goto C 
        }

        for (int i = 0; i < Lt_Z;i++) {                     // min i<=Lt_Z [
            int* ZI = find_pair(Z[i]);                      //                          --ZI = <ai , Ui> , 
            if (ZI[0] + 2 == U[0])                          // l((Z)_i) + 2 = l(U)]     -- l((Z)_i) = ZI[0]= ai
            {
                K = U[0];                                   // K <- l(U)
                continue;                                   // Goto C
            }
        }
    }
    
     return S[0];                                           //[F] Y <- (S)1
}
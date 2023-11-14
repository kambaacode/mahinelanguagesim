#include <bits/stdc++.h>

using namespace std;


string to_hexa(vector <string> Regi , int x1 , int x2)
{
    stringstream ss;
     int decimalNumber = stoi(Regi[x1], nullptr, 16);
     int decimalNumber2 = stoi(Regi[x2], nullptr, 16);
     int answer =  decimalNumber + decimalNumber2;
     ss << hex << uppercase << answer;
     return ss.str();
}
class Machine
{
protected:
    vector <string> lines;
public:
    Machine(vector <string> code)
    {
        lines.resize(256 , "0");
        this -> lines = code;
    }
    virtual void setMemory()
    {}
    virtual void showMemory()
    {}
    virtual void setIR()
    {}
    virtual void setinstructions()
    {}
    virtual void setRegisters()
    {}
    virtual void ShowRegister()
    {}
};

class Memory : public Machine
{
    vector <string> memory;
public:
    Memory(vector <string> code) : Machine(code)
    {
        memory.resize(256 , "0");
    }
    void setMemory()
    {
        int n = 0;
        for(int i = 0 ; i < lines.size() ; i++)
        {
            if(lines.at(i)[0] == 'C')
            {
                memory[n] = lines.at(i).substr(0,2);
                memory[n+1] = lines.at(i).substr(2);
                n+=2;
                break;
            }
            memory[n] = lines.at(i).substr(0,2);
            memory[n+1] = lines.at(i).substr(2);
            n+=2;
        }
    }
    void showMemory()
    {
        for (auto i : memory)
        {
            cout << i << endl;
        }
    }
};

class CPU : public Machine
{
public:
    string IR;
    int counter = 0;
public:
    CPU(vector <string> codes) : Machine(codes){}
    void setIR()
    {
        IR = lines[counter];
        counter++;
    }
};

//5 2 3 4
//

class Registers: public CPU
{
protected:
    vector <string> Reg;
public:
    
    Registers(vector <string> codes) : CPU(codes){
         Reg.resize(16, "0");
    }
    // virtual void sum(){}
    void ShowRegister()
    {
        for(auto i : Reg)
        {
            cout << i << endl;
        }
    }
};

class instructions : public Registers 
{
protected:
    string regist;
    int Register_number;
    int Register_number1;
    int Register_number2;
public:

instructions(vector <string> codes) : Registers(codes){}

    void setinstructions()
    {
        switch (IR[0])
        {
        case '1':
            
            break;
        case '2':
            Reg[IR[1] - '0'] = IR.substr(2);
            break;
        case '3':
            break;
        case '4':
            Register_number1 = IR[2] - '0';
            Register_number2 = IR[3] - '0'; 
            if(Reg[Register_number1] != "0")
            {
                Reg[Register_number2] = Reg[Register_number1];
            }
            break;
        case '5':
            Register_number = IR[1] - '0';
            Register_number1 = IR[2] - '0';
            Register_number2 = IR[3] - '0';
            Reg[Register_number] = to_hexa(Reg , Register_number1 , Register_number2) ;
            break;
        case 'B':
            break;
        case 'C':
            break;
        default:
            cout << "Enter valid operation";
            break;
        }
    }
    char getIR()
    {
        return IR[0];
    }
}; 


int main()
{
    fstream myFile;
    myFile.open("memory.txt",ios_base :: out);
    if(myFile.is_open())
    {
        string line;
        while (getline(cin , line) && !line.empty())
        {
            myFile << line << endl;
        }
        myFile.close();
    }
    string str1 = "";
    vector <string> operations;
    
    myFile.open("memory.txt" , ios_base::in);

    if(myFile.is_open())
    {
        string line;
        while (getline(myFile , line))
        {
            str1 = "";
            for(int i = 0 ; i < line.length() ; i++)
            {
                if((line[i] == '0' && line[i+1] == 'x') || (line[i] == 'x') || (line[i] == ' '))
                {
                    continue; 
                }
                str1 += line[i];
                if(i == line.length() - 1) operations.push_back(str1);
            }
        }
        myFile.close();
    }

    Machine *ptr = new Memory(operations);
    cout << "MEMORY: "<< endl;
    ptr -> setMemory();
    ptr -> showMemory();
    cout << endl << "REGISTERS: " << endl;
    instructions R(operations);
   
    for(int i = 0;i < operations.size();i++){
        if(R.getIR() == 'C')
        {
            break;
        }
        R.setIR();
        R.setinstructions();
        R.setRegisters();
    }
    R.ShowRegister();
}
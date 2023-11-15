#include <bits/stdc++.h>

using namespace std;

int fun(char IR)
{
    int Register_number;
     if(IR >= 'A' && IR <= 'F')
        {
            Register_number = IR - '7';
        }
        else
     {   
            Register_number = IR - '0';
        }
    return Register_number;
}


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
        cout << counter << " ";
    }
};

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
    string str;
    map <string , string> mem;
public:

instructions(vector <string> codes) : Registers(codes){}

    void setinstructions()
    {
        switch (IR[0])
        {
        case '1':
                Register_number = fun(IR[1]);
                Reg[Register_number] = mem[IR.substr(2)];
            break;
        case '2':
         if(IR[1] >= 'A' && IR[1] <= 'F')
            {
                Register_number = IR[1] - '7';
                Reg[Register_number] = IR.substr(2);
            }
            else
            {    
                Register_number = IR[1] - '0';
            }
            Reg[Register_number] = IR.substr(2);
            break;
        case '3':
            Register_number = fun(IR[1]);
            str = IR.substr(2);
            mem.insert({str , Reg[Register_number]});
            break;
        case '4':
            Register_number1 = fun(IR[2]);
            Register_number2 = fun(IR[3]); 
            Reg[Register_number2] = Reg[Register_number1];
            break;
        case '5':
           Register_number = fun(IR[1]);
           Register_number1 = fun(IR[2]);
           Register_number2 = fun(IR[3]);
           Reg[Register_number] = to_hexa(Reg,Register_number1,Register_number2);
            break;
        case 'B':
            Register_number = IR[1] - '0';
            if(Reg[Register_number] == Reg[0])
            {
                counter ++;    
            }
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
    string str1,filename;
    vector <string> operations;
    int choice;
    cout << "Enter the name of the file: ";
    cin >> filename;

    filename += ".txt"; 
    fstream File;
    File.open(filename , ios_base::in);
    
    if(File.is_open())
    {
        string line;
        while (getline(File , line))
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
        File.close();
    }

    cout << "What do you want to display?\n"
             << "1 - Memory\n"
             << "2 - Registers\n"
             << "3 - All: ";
    cin >> choice;
    
    Machine *ptr = new Memory(operations);
    instructions R(operations);

    if(choice == 1)
    {
        ptr -> setMemory();
        ptr -> showMemory();
    }

    if(choice == 2)
    {
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
    if(choice == 3)
        {    
        cout << "MEMORY: " << endl;
        ptr -> setMemory();
        ptr -> showMemory();
            
        cout << "Registers: " << endl;
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
     {
    }
}
}

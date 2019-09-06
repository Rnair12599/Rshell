#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;


class Base {
    public:
        Base() {};
        
        virtual void parse(){};
        virtual bool execute(){};
        virtual string getOp(){};
        virtual string getARGS(){};
        virtual string getEXEC(){};
        string print() {
            string DollarSign;
            return DollarSign;
        }
};





class Command : public Base {
    public: 
        string command;
        string exec;
        vector <string> argList;
        string op;
        void print();
    
    Command(string command):Base(){
        this -> command = command;
        this -> parse();
    }
    
    string getOp(){
        string OP = this ->op;
        return OP;
    }
    
    string getARGS(){
        string ARGS;
    
        if (argList.size() > 1){
           for (int i = 0; i < argList.size() - 1; ++i ){
               ARGS += argList.at(i) + " ";
           }
        }
        
        ARGS += argList.at(argList.size() - 1);
        
        return ARGS;
    }
    
    string getEXEC(){
        string EXEC = this -> exec;
        return EXEC;
    }
    
    void parse(){
        int k = 0;
        string arg; 
        for(int  i = 0; (command[i] != ' '); ++i){
            this -> exec += command[i];
            k = i;
        }
        
   for(int i = k + 2; i < command.size(); ++i){
            
            if(command[i] == ' '){
                argList.push_back(arg);
                arg = "";
            }else if((command[i] == '&') && (command[i+1] == '&')){
                this -> op = "&&";
                ++i;
            }else if((command[i] == '|') && (command[i+1] == '|')){
                this -> op = "||";
                ++i;
            }else if(command[i] == ';'){
                this -> op = ";";
                argList.push_back(arg);
            }else if(i == command.size() - 1){
                arg += command[i];
                argList.push_back(arg);
                this -> op = "";
            }else {
                arg += command[i];
            }
        }     
    }
  bool execute(){
        char* args[argList.size()];
        for(int i=0; i < argList.size()+2; ++i){
            if(i == 0){
                char* execChar = new char[exec.length()+1];
                strcpy(execChar, exec.c_str());
                args[i] = execChar;
            }else if(i == (argList.size()+1)){
                args[i-1] = NULL;
            }else{
                char* argChar = new char[argList.at(i-1).length()+1];
                strcpy(argChar, argList.at(i-1).c_str());
                args[i] = argChar;
            }
        }
        int childStatus;
        pid_t child_pid = fork();
        pid_t r_pid;
        if(child_pid == 0){
            execvp(args[0], args);
            perror("execvp");
            return false;
        }else if(child_pid > 0){
            if( (r_pid = wait(&childStatus)) < 0){
                perror("wait");
                exit(1);
            }
            cout << "evaluated" << endl;
            return true;
            
        }else{
            perror("fork failed");
            exit(1);
        }
    }
    
};

class Exit : public Base{
    public:
        string op;
        
    Exit(string op):Base(){
        this -> op = op;
    }
    
    string getOp(){
        string OP = this ->op;
        return OP;
    }
    
    bool execute(){
        exit(1);
        return true;
    }
};


class CommandLine : public Base{
    public:
        string commandLine;
        vector <Base*> commands;
    CommandLine(string commandLine):Base(){
        this -> commandLine = commandLine;
        this ->parse();
    }
    
    void parse(){
        for(int i = 0; i < commandLine.size(); ++i){
            string exec = "";
	    string comment = "";
            while((commandLine[i] != '&') && (commandLine[i] != '|') && (commandLine[i] != ';')){
                if ((commandLine[i] != commandLine.size() - 1) && (commandLine[i + 1] == '#')){
                    Command* command = new Command(exec);
                    commands.push_back(command);
                    i = commandLine.size() - 1;
                    break;
                }
                else {
                    exec += commandLine.at(i);
                    int size = commandLine.size();
                    if(i == commandLine.size() - 1){
                        if(exec == "exit"){
                            Exit* command = new Exit(" ");
                            commands.push_back(command);
                            break;
                        }else{
                            Command* command = new Command(exec);
                            commands.push_back(command);
                            break;
                        }
                    }
                    ++i;
                }
            }

	    if (commandLine.at(i) == '&' && (commandLine.at(i+1) == '&')){
                exec +=  "&&";
                if(exec == "exit"){
                    Exit* command = new Exit("&&");
                    commands.push_back(command);
                }else{
                    Command* command = new Command(exec);
                    commands.push_back(command);
                }
                i = i + 2;
            }
            if (commandLine.at(i) == '|'){
                 exec +=  "||";
                if(exec == "exit"){
                    Exit* command = new Exit("||");
                    commands.push_back(command);
                }else{
                    Command* command = new Command(exec);
                    commands.push_back(command);
                }
                 i = i + 2;
            }
            if (commandLine.at(i) == ';'){
                exec +=  ';';
                if(exec == "exit"){
                    Exit* command = new Exit(";");
                    commands.push_back(command);
                }else{
                    Command* command = new Command(exec);
                    commands.push_back(command);
                }
                 ++i;
            }
        }
    }
    
    bool execute(){
        
        if (commands.size() == 1){
            commands.at(0)->execute();
            return true;
        }else if (commands.size() > 1) {
            bool RunPrev = commands.at(0)->execute();
            string prevOp = commands.at(0)->getOp();
            
          for(int i = 1; i < commands.size(); ++i){
                if(prevOp == "&&"){
                    if(RunPrev){
                      RunPrev = commands.at(i)->execute();
                      prevOp = commands.at(i)->getOp();
                    }
                }
                else if (prevOp == "||"){
                    if(!RunPrev){
                      RunPrev = commands.at(i)->execute();
                      prevOp = commands.at(i)->getOp();
                    }
                }
                else if (prevOp == ";"){
                    RunPrev = commands.at(i)->execute();
                    prevOp = commands.at(i)->getOp();
                    
                }
                
            }
            return true;
            
        }
    }
};



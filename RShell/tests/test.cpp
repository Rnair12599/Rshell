#include <iostream>
#include <string>
#include <vector>
#include "Classes.h" 
//#include "rshell.cpp"
#include "gtest/gtest.h"

using namespace std;


 TEST(ParsingtSet, ParseTestOne){
      CommandLine cmdlist("cd desktop; cd CS100; echo hello and yes && echo is this right; g++ cs100");
      EXPECT_EQ("cd", cmdlist.commands.at(0) -> getEXEC());
      EXPECT_EQ("desktop", cmdlist.commands.at(0) -> getARGS());
      EXPECT_EQ(";", cmdlist.commands.at(0) -> getOp());
      EXPECT_EQ("echo",cmdlist.commands.at(2) -> getEXEC());
      EXPECT_EQ("hello and yes", cmdlist.commands.at(2) -> getARGS() );
      EXPECT_EQ("&&", cmdlist.commands.at(2) -> getOp());
      EXPECT_EQ("g++", cmdlist.commands.at(cmdlist.commands.size() - 1) -> getEXEC());
      EXPECT_EQ("", cmdlist.commands.at(cmdlist.commands.size() - 1) -> getOp());
      
 }

TEST(ParsingtSet, ParseTestTwo){
      CommandLine cmdlist("ls -a; echo hello && mkdir test || echo world; git status");
      EXPECT_EQ("ls", cmdlist.commands.at(0) -> getEXEC());
      EXPECT_EQ("-a", cmdlist.commands.at(0) -> getARGS());
      EXPECT_EQ(";", cmdlist.commands.at(0) -> getOp());
      EXPECT_EQ("echo",cmdlist.commands.at(1) -> getEXEC());
      EXPECT_EQ("hello", cmdlist.commands.at(1) -> getARGS() );
      EXPECT_EQ("&&", cmdlist.commands.at(1) -> getOp());
      EXPECT_EQ("mkdir",cmdlist.commands.at(2) -> getEXEC());
      EXPECT_EQ("test", cmdlist.commands.at(2) -> getARGS() );
      EXPECT_EQ("||", cmdlist.commands.at(2) -> getOp());
      EXPECT_EQ("git", cmdlist.commands.at(cmdlist.commands.size() - 1) -> getEXEC());
      EXPECT_EQ("status", cmdlist.commands.at(cmdlist.commands.size() - 1) -> getARGS());
      EXPECT_EQ("", cmdlist.commands.at(cmdlist.commands.size() - 1) -> getOp());
      
 }

TEST(ExecSet, ExecTestOne) {
  CommandLine cmdlist("ls -a; echo hello && mkdir yes || echo world; git status");
  
  EXPECT_EQ(true, cmdlist.commands.at(0) -> execute());
  EXPECT_EQ(true, cmdlist.commands.at(1) -> execute());
  EXPECT_EQ(true, cmdlist.commands.at(2) -> execute());
  EXPECT_EQ(true, cmdlist.commands.at(3) -> execute());
  EXPECT_EQ(true, cmdlist.commands.at(4) -> execute());
  EXPECT_EQ(true, cmdlist.execute());

 }



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


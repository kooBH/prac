#CMAKE version of Ubuntu 16.04 is 3.5.
cmake_minimum_required(VERSION 3.5)
project(iip_demo)

set(vars)

list(APPEND vars "vars ")

function(func1 o1)
  # Not working 
  # list(APPEND o1 "func1 " ) 

  # need to add a space.
  set(${o1} "${o1} " "func1 " PARENT_SCOPE)
endfunction(func1)


func1(vars)

list(APPEND vars "var2 ")

message(STATUS ${vars})


#!/usr/bin/env zsh

#rebuild our workflow
clear;
cd ~/Desktop/unilang_workflow/project/src;
update;
make;

#perform the transfers
unilang_workflow

#sync our tests
#needs replaced with a c++ program
cd ~/Desktop/work-related/fresh/SimHost/Tests;
./unit-tests --sync;

#return back to desktop
cd ~/Desktop;



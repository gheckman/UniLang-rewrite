#!/usr/bin/env bash

#transfer and sync
#clear;cd UniLang-rewrite/code; ./sync; cd ../../;cd work-related/fresh/SimHost/Tests; ./unit-tests --sync; cd ../../../../;

#rebuild our workflow
clear;
cd ~/Desktop/unilang_workflow/project/src;
make;

#perform the transfers
unilang_workflow

#sync our tests
cd ~/Desktop/work-related/fresh/SimHost/Tests;
./unit-tests --sync;

#return back to desktop
cd ~/Desktop;



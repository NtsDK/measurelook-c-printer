# About project ([README Rus](https://github.com/NtsDK/measurelook-c-printer/wiki/README-RUS))

This repo contains printer of Measurelook format for C language. Printer is based on bstring lib. In this repo you will find the full example of computational experiment which prints data in Measurelook.

Project is based on Zed Shaw C project template from book Learn C The Hard Way.

# Installation and run

0. Download repo
1. make

Checked with gcc 4.4.6.

# Project structure

- src
  - lcthw
    - mlBuilder - (measurelook builder) - Measurelook file builder
    - bstrlib - [string library for C](http://bstring.sourceforge.net/)
  - distances - distance functions
  - distancesPerformanceTest - distance functions performance test
  - env - extra functions to get environment information in runtime
  - mlExtras - reusable printing on environement information in experiment metainformation
  - dbg.h - Zed Shaw's debug macros
- testRes/distances - results of test run
- tests
  - env_tests - testing of environment information getters in runtime
  - distances_performance_tests - performance test starter
  - minunit.h - test autostarter 
  - runtests.sh - test autostarter

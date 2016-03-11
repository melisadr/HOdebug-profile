 
```
 gcc -O0 -c profile_me_1.c -o profile_me_1.o
 gcc profile_me_1.o -o test_profile_me1_O0.e
 gcc -O1 -c profile_me_1.c -o profile_me_2.o
 gcc profile_me_2.o -o test_profile_me1_O1.e
 gcc -O3 -c profile_me_1.c -o profile_me_3.o
 gcc profile_me_3.o -o test_profile_me1_O3.e

``` 

Primero:

``` 
time ./test_profile_me1_O0.e
Violación de segmento (`core' generado)

real	0m0.097s
user	0m0.000s
sys	0m0.001s
  

time ./test_profile_me1_O1.e 
Violación de segmento (`core' generado)

real	0m0.114s
user	0m0.002s
sys	0m0.000s

time ./test_profile_me1_O3.e 

real	0m0.003s
user	0m0.000s
sys	0m0.001s

```
El size es mas grande que el tamaño del stack, hay que resolver ese bug alocando los vectores a, b y c.

Generé el archivo _malloc para resolver este problema.

``` 
  time ./test_profile_me1_mallocO0.e 
real	0m0.637s
user	0m0.594s
sys	0m0.040s
  time ./test_profile_me1_mallocO1.e 

real	0m0.373s
user	0m0.310s
sys	0m0.060s
  time ./test_profile_me1_mallocO3.e 

real	0m0.004s
user	0m0.000s
sys	0m0.001s
``` 

Con perf los resultados fueron

``` 
  perf stat ./test_profile_me1_mallocO0.e 

 Performance counter stats for './test_profile_me1_mallocO0.e':

        628,596289 task-clock (msec)         #    0,995 CPUs utilized          
                56 context-switches          #    0,089 K/sec                  
                 3 cpu-migrations            #    0,005 K/sec                  
             2.002 page-faults               #    0,003 M/sec                  
     2.291.910.658 cycles                    #    3,646 GHz                    
     1.085.245.522 stalled-cycles-frontend   #   47,35% frontend cycles idle   
       543.811.797 stalled-cycles-backend    #   23,73% backend  cycles idle   
     3.894.058.308 instructions              #    1,70  insns per cycle        
                                             #    0,28  stalled cycles per insn
       178.196.157 branches                  #  283,483 M/sec                  
            30.294 branch-misses             #    0,02% of all branches        

       0,631720131 seconds time elapsed

  perf stat ./test_profile_me1_mallocO1.e 

 Performance counter stats for './test_profile_me1_mallocO1.e':

        368,986438 task-clock (msec)         #    0,992 CPUs utilized          
                37 context-switches          #    0,100 K/sec                  
                 2 cpu-migrations            #    0,005 K/sec                  
             2.002 page-faults               #    0,005 M/sec                  
     1.335.634.454 cycles                    #    3,620 GHz                    
       920.387.451 stalled-cycles-frontend   #   68,91% frontend cycles idle   
       669.583.786 stalled-cycles-backend    #   50,13% backend  cycles idle   
     1.118.666.549 instructions              #    0,84  insns per cycle        
                                             #    0,82  stalled cycles per insn
       178.127.130 branches                  #  482,747 M/sec                  
            29.380 branch-misses             #    0,02% of all branches        

       0,372024345 seconds time elapsed

  perf stat ./test_profile_me1_mallocO3.e 

 Performance counter stats for './test_profile_me1_mallocO3.e':

          0,486474 task-clock (msec)         #    0,156 CPUs utilized          
                 1 context-switches          #    0,002 M/sec                  
                 0 cpu-migrations            #    0,000 K/sec                  
               119 page-faults               #    0,245 M/sec                  
           765.201 cycles                    #    1,573 GHz                    
           445.036 stalled-cycles-frontend   #   58,16% frontend cycles idle   
           335.359 stalled-cycles-backend    #   43,83% backend  cycles idle   
           683.004 instructions              #    0,89  insns per cycle        
                                             #    0,65  stalled cycles per insn
           130.181 branches                  #  267,601 M/sec                  
             5.021 branch-misses             #    3,86% of all branches        

       0,003120004 seconds time elapsed

``` 
-O1
Samples: 2K of event 'cycles', Event count (approx.): 2315616186                                                                                                                                             
 41,72%  test_profile_me  test_profile_me1_mallocO0.e  [.] first_assign
 25,75%  test_profile_me  test_profile_me1_mallocO0.e  [.] main
 24,24%  test_profile_me  test_profile_me1_mallocO0.e  [.] second_assign
  8,29%  test_profile_me  [kernel.kallsyms]            [k] 0xffffffff8104f45a

Samples: 1K of event 'cycles', Event count (approx.): 1337008754                                                                                                                                             
 47,67%  test_profile_me  test_profile_me1_mallocO1.e  [.] first_assign
 26,40%  test_profile_me  test_profile_me1_mallocO1.e  [.] main
 13,57%  test_profile_me  test_profile_me1_mallocO1.e  [.] second_assign
 12,36%  test_profile_me  [kernel.kallsyms]            [k] 0xffffffff8104f45a

Samples: 8  of event 'cycles', Event count (approx.): 1247645                                                                                                                                                
100,00%  test_profile_me  [kernel.kallsyms]  [k] 0xffffffff8104f45a

# profile 2

los tiempos disminuyen a medida que aumento la optimización, como era de esperarse.
perf stat ./profile_me_2_0.e 1000000
-nan
 Performance counter stats for './profile_me_2_0.e 1000000':

         45,890334 task-clock (msec)         #    0,942 CPUs utilized          
                 6 context-switches          #    0,131 K/sec                  
                 1 cpu-migrations            #    0,022 K/sec                  
             1.458 page-faults               #    0,032 M/sec                  
       140.109.476 cycles                    #    3,053 GHz                    
        46.165.453 stalled-cycles-frontend   #   32,95% frontend cycles idle   
        15.089.820 stalled-cycles-backend    #   10,77% backend  cycles idle   
       283.221.090 instructions              #    2,02  insns per cycle        
                                             #    0,16  stalled cycles per insn
        50.855.354 branches                  # 1108,193 M/sec                  
            14.056 branch-misses             #    0,03% of all branches        

       0,048737768 seconds time elapsed

  perf stat ./profile_me_2_1.e 1000000
-nan
 Performance counter stats for './profile_me_2_1.e 1000000':

         41,765772 task-clock (msec)         #    0,938 CPUs utilized          
                 6 context-switches          #    0,144 K/sec                  
                 1 cpu-migrations            #    0,024 K/sec                  
             1.457 page-faults               #    0,035 M/sec                  
       126.757.161 cycles                    #    3,035 GHz                    
        48.835.228 stalled-cycles-frontend   #   38,53% frontend cycles idle   
        30.473.799 stalled-cycles-backend    #   24,04% backend  cycles idle   
       201.227.442 instructions              #    1,59  insns per cycle        
                                             #    0,24  stalled cycles per insn
        47.858.701 branches                  # 1145,883 M/sec                  
            13.919 branch-misses             #    0,03% of all branches        

       0,044511186 seconds time elapsed

  perf stat ./profile_me_2_3.e 1000000
-nan
 Performance counter stats for './profile_me_2_3.e 1000000':

         40,078740 task-clock (msec)         #    0,971 CPUs utilized          
                 5 context-switches          #    0,125 K/sec                  
                 2 cpu-migrations            #    0,050 K/sec                  
             1.457 page-faults               #    0,036 M/sec                  
       119.729.990 cycles                    #    2,987 GHz                    
        37.833.026 stalled-cycles-frontend   #   31,60% frontend cycles idle   
        21.710.609 stalled-cycles-backend    #   18,13% backend  cycles idle   
       212.230.993 instructions              #    1,77  insns per cycle        
                                             #    0,18  stalled cycles per insn
        47.848.477 branches                  # 1193,862 M/sec                  
            13.546 branch-misses             #    0,03% of all branches        

       0,041281945 seconds time elapsed




# OS LAB2

## BUILDING
---
```
cd  build
cmake .. \    
    -DCMAKE_SYSTEM_NAME=Windows \
    -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
    -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++
make
```

## RUNNING
---
```
wine build/Main.exe    
wine build/Tests.exe 
```

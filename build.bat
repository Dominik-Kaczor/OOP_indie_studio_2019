mkdir .\Build
cd .\Build
cmake . ..
cmake --build .
copy Debug\bomberman.exe .
.\bomberman.exe
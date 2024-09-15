./build.sh

if [ $? -eq 0 ]; then
    ./.build/choren ~/02-areas/Sheets/test-Eb.txt -t7
fi

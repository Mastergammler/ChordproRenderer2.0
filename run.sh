./build.sh

if [ $? -eq 0 ]; then
    ./.build/choren ~/02-areas/Sheets/test-Eb.txt -t-5
fi

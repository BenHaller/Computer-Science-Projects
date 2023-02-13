#!/bin/bash
echo "Welcome to $0!";
echo "The arguments are: $@";

if [[ $# != 4 ]]; then
        echo "Proper usage is $0 -i inputfile -o outputfile";
        exit 1;
fi;

input=""; # This will be out inputfile
output=""; # This will be our outputfile

# (Allow either order)
if [[ $1 == "-i" && $3 == "-o" ]]; then
        input=$2;
        output=$4;
elif [[ $1 == "-o" && $3 == "-i" ]]; then
        input=$4;
        output=$2;
else
        echo "Proper usage is $0 -i inputfile -o outputfile";
        exit 1;
fi;
echo "Ready to decrypt ${input} to ${output}";
read -p "Press y to continue: " usercommand;
if [[ ${usercommand} != "y" && ${usercommand} != "Y" ]]; then
        echo "Cancelling because you said ${usercommand}";
        exit 1;
fi;

echo -n "Encrypting in "
for i in 3 2 1; do
        echo -n "$i ";
        sleep 1;        #Pause for 1 second
done;
echo

#Split this long command over multiple lines with a backslash
tr NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm \
   ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz \
   < $input \
   > $output

if [[ $? == 0 ]]; then
        echo "Decryption done!";
else
        echo "Decryption failed!";
        exit 1;
fi;
exit 0;

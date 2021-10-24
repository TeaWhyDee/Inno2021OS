mkdir -p week01
echo TeaWide > week01/file.txt
link week01/file.txt _ex2.txt
echo "i-node is: $(ls week01/file.txt -i | awk '{print $1}')" 1>&2
find ./ -inum $(ls week01/file.txt -i | awk '{print $1}') > ex2.txt
find ./ -inum $(ls week01/file.txt -i | awk '{print $1}') -exec rm {} \;
